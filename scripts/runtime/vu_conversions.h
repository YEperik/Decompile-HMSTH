#ifndef PS2_VU_CONVERSIONS_V1
#define PS2_VU_CONVERSIONS_V1
#include "vector_storage.h"

/* Value conversion only; scheduling and VU register state belong to the caller. */
static inline uint32_t ps2_vftoi_lane(uint32_t bits, unsigned fraction) {
    unsigned encoded_exponent = (bits >> 23) & 255u;
    int exponent = (int)encoded_exponent - 127 + (int)fraction;
    uint32_t magnitude;
    if (encoded_exponent == 0 || exponent < 0) return 0;
    if (exponent >= 31)
        return (bits >> 31) ? UINT32_C(0x80000000) : UINT32_C(0x7fffffff);
    magnitude = (bits & UINT32_C(0x007fffff)) | UINT32_C(0x00800000);
    if (exponent >= 23) magnitude <<= (unsigned)(exponent - 23);
    else magnitude >>= (unsigned)(23 - exponent);
    return (bits >> 31) ? UINT32_C(0) - magnitude : magnitude;
}

static inline ps2_vec128 ps2_vftoi_apply(ps2_vec128 value, unsigned mask, unsigned fraction) {
    for (unsigned lane = 0; lane < 4; ++lane) {
        if (mask & (8u >> lane)) {
            unsigned offset = lane * 4;
            uint32_t bits = (uint32_t)value.bytes[offset]
                | ((uint32_t)value.bytes[offset + 1] << 8)
                | ((uint32_t)value.bytes[offset + 2] << 16)
                | ((uint32_t)value.bytes[offset + 3] << 24);
            bits = ps2_vftoi_lane(bits, fraction);
            for (unsigned byte = 0; byte < 4; ++byte)
                value.bytes[offset + byte] = (uint8_t)(bits >> (byte * 8));
        }
    }
    return value;
}

static inline ps2_vec128 ps2_vftoi0(ps2_vec128 value, unsigned mask) {
    return ps2_vftoi_apply(value, mask, 0);
}
static inline ps2_vec128 ps2_vftoi4(ps2_vec128 value, unsigned mask) {
    return ps2_vftoi_apply(value, mask, 4);
}
#endif
