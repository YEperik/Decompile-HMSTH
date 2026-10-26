#include "math_bits.hpp"
// SLUS_202.51: bit-level reconstruction, preserving payloads without host FP arithmetic.
std::uint64_t hm_00112420(std::uint64_t magnitude, std::uint64_t sign) {
    constexpr std::uint64_t sign_mask = UINT64_C(0x8000000000000000);
    return (magnitude & ~sign_mask) | (sign & sign_mask);
}
std::uint64_t hm_00112468(std::uint64_t value) {
    return value & UINT64_C(0x7fffffffffffffff);
}
std::uint32_t hm_001124a0(std::uint64_t value) {
    const auto high = static_cast<std::uint32_t>(value >> 32) & UINT32_C(0x7fffffff);
    return static_cast<std::uint32_t>(high + UINT32_C(0x80100000)) >> 31;
}
bool hm_00100310(std::uint64_t* output, std::int16_t framebuffer,
    std::int16_t width, std::int16_t height, std::int16_t x, std::int16_t y,
    std::int16_t interlaced, std::int16_t mode, std::int16_t frame) {
    if (!output || width <= 0 || height <= 0 || (mode != 2 && mode != 3) ||
        (interlaced != 0 && interlaced != 1) || (frame != 0 && frame != 1)) return false;
    const std::int64_t scale = (static_cast<std::int64_t>(width) + 2559) / width;
    const std::int64_t dx = static_cast<std::int64_t>(x) * scale + (mode == 2 ? 636 : 656);
    const std::int64_t dy = y + (mode == 2 ? (interlaced ? 50 : 25) : (interlaced ? 72 : 36));
    const std::int64_t dh = static_cast<std::int64_t>(height) * (interlaced && frame ? 2 : 1) - 1;
    output[0] = 0x66;
    output[1] = !interlaced ? 2 : (frame ? 3 : 1);
    output[2] = ((static_cast<std::uint64_t>(framebuffer) & 15) << 15) |
        ((static_cast<std::uint64_t>((static_cast<std::int64_t>(width)+63)>>6) & 63) << 9);
    output[3] = (static_cast<std::uint64_t>(scale-1) << 23) |
        (static_cast<std::uint64_t>(scale*width-1) << 32) |
        (static_cast<std::uint64_t>(dx) & 4095) |
        (static_cast<std::uint64_t>(dh) << 44) |
        ((static_cast<std::uint64_t>(dy) & 4095) << 12);
    output[4] = 0;
    return true;
}
bool hm_00100580(const std::uint64_t* environment, std::uint16_t revision,
    HmGsWrite write, void* context) {
    if (!environment || !write) return false;
    write(context, 0x12000000, environment[0]);
    if (revision == 1) {
        write(context, 0x12000070, environment[2]);
        write(context, 0x12000080, environment[3]);
        write(context, 0x120000c0, environment[4]);
    } else {
        write(context, 0x12000020, environment[1]);
        write(context, 0x12000090, environment[2]);
        write(context, 0x120000a0, environment[3]);
        write(context, 0x120000e0, environment[4]);
    }
    return true;
}
std::int32_t hm_00100640(std::uint64_t format, std::int16_t width,
    std::int16_t height, std::uint64_t gs_state) {
    const std::int32_t columns = (static_cast<std::int32_t>(width) + 63) / 64;
    const std::int32_t rows = (static_cast<std::int32_t>(height) + ((format & 2) ? 63 : 31)) / ((format & 2) ? 64 : 32);
    const std::uint32_t multiplier = (gs_state & UINT64_C(0xffff0000ffff)) == 1 ? 65536u : 131072u;
    const std::uint32_t packed = static_cast<std::uint32_t>(columns * rows) * multiplier;
    const std::uint32_t high = packed >> 16;
    return high < 32768u ? static_cast<std::int32_t>(high) : static_cast<std::int32_t>(high) - 65536;
}
