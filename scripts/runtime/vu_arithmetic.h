#ifndef PS2_VU_ARITHMETIC_V1
#define PS2_VU_ARITHMETIC_V1
#include <stdint.h>
#include "vu_mac_state.h"
/* PCSX2 interpreter clamp/RNE reference profile, not hardware-verified PS2 math. */
typedef struct {uint32_t limb[9];} ps2_big288;
static inline uint32_t ps2_arith_normalize(uint32_t v) {
    unsigned e=(v>>23)&255u;
    return !e?v&0x80000000u:e==255?(v&0x80000000u)|0x7f7fffffu:v;
}
static inline unsigned ps2_big_bit(ps2_big288 v,int bit) {
    return bit<0||bit>=288?0u:(v.limb[(unsigned)bit/32]>>((unsigned)bit%32))&1u;
}
static inline uint32_t ps2_big_round(ps2_big288 v,int shift) {
    uint32_t q=0;
    for(int bit=0;bit<32;bit++)q|=ps2_big_bit(v,bit+shift)<<(unsigned)bit;
    if(shift>0&&ps2_big_bit(v,shift-1)) {
        unsigned sticky=0;
        for(int bit=0;bit<shift-1&&bit<288;bit++)sticky|=ps2_big_bit(v,bit);
        if(sticky||(q&1u))q++;
    }
    return q;
}
static inline uint32_t ps2_big_pack(unsigned sign,ps2_big288 v,int scale) {
    int length=288;while(length&&!ps2_big_bit(v,length-1))length--;
    uint32_t s=sign<<31;
    if(!length)return s;
    int e=scale+length-1;
    if(e < -126)return s|ps2_big_round(v,-149-scale);
    uint32_t m=ps2_big_round(v,length-24);
    if(m==0x1000000u){m>>=1;e++;}
    if(e>127)return s|0x7f800000u;
    return s|((uint32_t)(e+127)<<23)|(m&0x7fffffu);
}
static inline ps2_big288 ps2_big_shift(uint32_t m,unsigned shift) {
    ps2_big288 v={{0}};
    if(m){uint64_t wide=(uint64_t)m<<(shift%32);v.limb[shift/32]=(uint32_t)wide;
        if(shift/32+1<9)v.limb[shift/32+1]=(uint32_t)(wide>>32);}
    return v;
}
/* op: 0=add, 1=sub, 2=mul. Callers validate the opcode. */
static inline uint32_t ps2_arithmetic_bits(unsigned op,uint32_t a,uint32_t b) {
    a=ps2_arith_normalize(a);b=ps2_arith_normalize(b);
    if(op==1)b^=0x80000000u;
    unsigned sa=a>>31,sb=b>>31,ea=(a>>23)&255u,eb=(b>>23)&255u;
    uint32_t ma=ea?(a&0x7fffffu)|0x800000u:0,mb=eb?(b&0x7fffffu)|0x800000u:0;
    if(op==2){uint64_t product=(uint64_t)ma*mb;ps2_big288 v={{0}};
        v.limb[0]=(uint32_t)product;v.limb[1]=(uint32_t)(product>>32);
        return ps2_big_pack(sa^sb,v,(int)ea+(int)eb-300);}
    ps2_big288 x=ps2_big_shift(ma,ea?ea-1:0),y=ps2_big_shift(mb,eb?eb-1:0),v={{0}};
    unsigned sign=sa;
    if(sa==sb){uint64_t carry=0;for(unsigned i=0;i<9;i++){
        uint64_t sum=(uint64_t)x.limb[i]+y.limb[i]+carry;v.limb[i]=(uint32_t)sum;carry=sum>>32;}}
    else {int comparison=0;for(int i=8;i>=0;i--)if(x.limb[i]!=y.limb[i]){comparison=x.limb[i]>y.limb[i]?1:-1;break;}
        if(!comparison)return 0;
        if(comparison<0){ps2_big288 temp=x;x=y;y=temp;sign=sb;}
        uint64_t borrow=0;for(unsigned i=0;i<9;i++){uint64_t sub=(uint64_t)y.limb[i]+borrow;
            v.limb[i]=(uint32_t)((uint64_t)x.limb[i]-sub);borrow=(uint64_t)x.limb[i]<sub;}}
    return ps2_big_pack(sign,v,-149);
}
static inline ps2_mac_result ps2_arithmetic_result(unsigned op,const uint32_t fs[4],const uint32_t ft[4],const uint32_t previous[4],unsigned mask) {
    uint32_t raw[4];for(unsigned i=0;i<4;i++)raw[i]=ps2_arithmetic_bits(op,fs[i],ft[i]);
    return ps2_mac_finalize(raw,previous,mask,1);
}
#endif
