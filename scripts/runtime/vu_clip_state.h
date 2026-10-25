#ifndef PS2_VU_CLIP_STATE_V1
#define PS2_VU_CLIP_STATE_V1
#include <stdint.h>
#include <string.h>

/* Explicit VU-cycle model. Does not schedule EE instructions or other VU units. */
typedef struct {
    uint32_t history, visible, values[4];
    uint64_t ready[4], cycle, last_issue;
    unsigned head, count, issued;
} ps2_clip_state;

static inline uint32_t ps2_clip_value(uint32_t previous, const uint32_t fs[4], const uint32_t ft[4]) {
    uint32_t limit = (ft[3] & 0x7f800000u) ? ft[3] & 0x7fffffffu : 0x007fffffu;
    uint32_t flags = 0;
    for (unsigned lane = 0; lane < 3; lane++) {
        if ((fs[lane] & 0x7fffffffu) > limit)
            flags |= 1u << (2u * lane + (fs[lane] >> 31));
    }
    return ((previous << 6) | flags) & 0xffffffu;
}

static inline void ps2_clip_init(ps2_clip_state *state, uint32_t initial) {
    memset(state, 0, sizeof(*state));
    state->history = state->visible = initial & 0xffffffu;
}

static inline int ps2_clip_advance(ps2_clip_state *state, uint64_t cycle) {
    if (cycle < state->cycle) return 0;
    state->cycle = cycle;
    while (state->count && state->ready[state->head] <= cycle) {
        state->visible = state->values[state->head];
        state->head = (state->head + 1u) & 3u;
        state->count--;
    }
    return 1;
}

static inline int ps2_clip_issue(ps2_clip_state *state, uint64_t cycle, const uint32_t fs[4], const uint32_t ft[4]) {
    if (cycle < state->cycle || (state->issued && cycle == state->last_issue) || cycle > UINT64_MAX - 4u) return 0;
    if (!ps2_clip_advance(state, cycle) || state->count >= 4) return 0;
    state->history = ps2_clip_value(state->history, fs, ft);
    unsigned tail = (state->head + state->count) & 3u;
    state->values[tail] = state->history;
    state->ready[tail] = cycle + 4u;
    state->count++;
    state->last_issue = cycle;
    state->issued = 1;
    return 1;
}
#endif
