#ifndef PS2_VU_MAC_STATE_V1
#define PS2_VU_MAC_STATE_V1
#include <stdint.h>
#include <string.h>
/* Finalize supplied FMAC result bits. This does not execute VADD/VSUB/VMUL. */
typedef struct { uint32_t destination[4], mac, current_status; } ps2_mac_result;
static inline ps2_mac_result ps2_mac_finalize(const uint32_t raw[4], const uint32_t previous[4], unsigned mask, int clamp) {
    ps2_mac_result result = {{0},0,0};
    memcpy(result.destination, previous, 16);
    for (unsigned lane=0; lane<4; lane++) {
        unsigned bit=1u<<(3-lane);
        if (!(mask&bit)) continue;
        uint32_t value=raw[lane], magnitude=value&0x7fffffffu, exponent=(value>>23)&255u;
        if (value>>31) result.mac|=bit<<4;
        if (!magnitude) result.mac|=bit;
        else if (!exponent) {result.mac|=bit|(bit<<8);value&=0x80000000u;}
        else if (exponent==255) {result.mac|=bit<<12;if(clamp)value=(value&0x80000000u)|0x7f7fffffu;}
        result.destination[lane]=value;
    }
    for (unsigned group=0;group<4;group++)
        if(result.mac&(15u<<(group*4)))result.current_status|=1u<<group;
    return result;
}
static inline uint32_t ps2_mac_commit_status(uint32_t previous, uint32_t current) {
    return (previous&0xff0u)|(current&15u)|((current&15u)<<6);
}
typedef struct {
    uint32_t mac,status,macs[4],currents[4];
    uint64_t cycle,last_issue,ready[4];
    unsigned head,count,issued;
} ps2_mac_state;
static inline void ps2_mac_init(ps2_mac_state*s,uint32_t mac,uint32_t status) {
    memset(s,0,sizeof(*s));s->mac=mac&0xffffu;s->status=status&0xfffu;
}
static inline int ps2_mac_advance(ps2_mac_state*s,uint64_t cycle) {
    if(cycle<s->cycle)return 0;
    s->cycle=cycle;
    while(s->count&&s->ready[s->head]<=cycle) {
        s->mac=s->macs[s->head];s->status=ps2_mac_commit_status(s->status,s->currents[s->head]);
        s->head=(s->head+1u)&3u;s->count--;
    }
    return 1;
}
static inline int ps2_mac_issue(ps2_mac_state*s,uint64_t cycle,ps2_mac_result result) {
    if(cycle<s->cycle||(s->issued&&cycle==s->last_issue)||cycle>UINT64_MAX-4u)return 0;
    if(!ps2_mac_advance(s,cycle)||s->count>=4)return 0;
    unsigned tail=(s->head+s->count)&3u;
    s->macs[tail]=result.mac;s->currents[tail]=result.current_status;s->ready[tail]=cycle+4u;
    s->last_issue=cycle;s->issued=1;s->count++;return 1;
}
#endif
