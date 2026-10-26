#pragma once
#include <cstdint>
extern "C" {
std::uint64_t hm_00112420(std::uint64_t magnitude, std::uint64_t sign);
std::uint64_t hm_00112468(std::uint64_t value);
std::uint32_t hm_001124a0(std::uint64_t value);
}
// Verified positive-dimension NTSC/PAL subset; false leaves output unchanged.
extern "C" bool hm_00100310(std::uint64_t* output, std::int16_t framebuffer,
    std::int16_t width, std::int16_t height, std::int16_t x, std::int16_t y,
    std::int16_t interlaced, std::int16_t mode, std::int16_t frame);
using HmGsWrite = void (*)(void*, std::uint32_t, std::uint64_t);
extern "C" bool hm_00100580(const std::uint64_t* environment, std::uint16_t revision,
    HmGsWrite write, void* context);
extern "C" std::int32_t hm_00100640(std::uint64_t format, std::int16_t width,
    std::int16_t height, std::uint64_t gs_state);
