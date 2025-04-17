#pragma once

#include <cmath>

// Linear interpolation (no easing)
inline float ease_linear(float t) {
    return t;
}

// Quadratic easing in (starts slow)
inline float ease_in_quad(float t) {
    return t * t;
}

// Quadratic easing out (ends slow)
inline float ease_out_quad(float t) {
    return t * (2 - t);
}

// Quadratic easing in-out (starts and ends slow)
inline float ease_in_out_quad(float t) {
    return t < 0.5f ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

// Cubic easing in
inline float ease_in_cubic(float t) {
    return t * t * t;
}

// Cubic easing out
inline float ease_out_cubic(float t) {
    t -= 1;
    return t * t * t + 1;
}

// Exponential easing in
inline float ease_in_expo(float t) {
    return t == 0 ? 0 : powf(2, 10 * (t - 1));
}

// Exponential easing out
inline float ease_out_expo(float t) {
    return t == 1 ? 1 : 1 - powf(2, -10 * t);
}

// Elastic easing in
inline float ease_in_elastic(float t) {
    if (t == 0) return 0;
    if (t == 1) return 1;
    return -powf(2, 10 * (t - 1)) * sinf((t - 1.1f) * 5 * M_PI);
}

// Bounce easing out
inline float ease_out_bounce(float t) {
    if (t < (1 / 2.75f)) {
        return 7.5625f * t * t;
    } else if (t < (2 / 2.75f)) {
        t -= 1.5f / 2.75f;
        return 7.5625f * t * t + 0.75f;
    } else if (t < (2.5f / 2.75f)) {
        t -= 2.25f / 2.75f;
        return 7.5625f * t * t + 0.9375f;
    } else {
        t -= 2.625f / 2.75f;
        return 7.5625f * t * t + 0.984375f;
    }
}

// Clamp a value between min and max
inline float clamp(float value, float min, float max) {
    return (value < min) ? min : ((value > max) ? max : value);
}

inline float ease_apply(float start, float end, float* current_time, float duration, float delta_time, float (*ease)(float))
{
    *current_time += delta_time;
    float t = clamp(*current_time / duration, 0.0f, 1.0f);
    t = ease(t);
    return start + (end - start) * t;
}