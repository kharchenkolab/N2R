/*
 * The AArch64 compatibility shim is based off of sse2neon.
 *
 * sse2neon is freely redistributable under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if defined(__aarch64__)
#include <stdint.h>
#include <stdlib.h>
#include <arm_neon.h>
#include <math.h>
#else
#include <xmmintrin.h>
#endif

#pragma push_macro("FORCE_INLINE")
#pragma push_macro("ALIGN_STRUCT")
#define FORCE_INLINE static inline __attribute__((always_inline))
#define ALIGN_STRUCT(x) __attribute__((aligned(x)))

// Warning: This shim only supports Aarch64. 32-bit ARM will not work.

#if defined(__aarch64__)
#define _MM_HINT_T0 0
#define _MM_HINT_T1 1

typedef int64x1_t __m64;
typedef float32x4_t __m128; /* 128-bit vector containing 4 floats */
typedef float64x2_t __m128d; /* 128-bit vector containing 2 doubles */
typedef int64x2_t __m128i; /* 128-bit vector containing integers */

FORCE_INLINE void _mm_prefetch(const void *p, int i) {
    (void) i;
    __builtin_prefetch(p);
}

FORCE_INLINE __m128 _mm_loadu_ps(const float *p) {
    return vld1q_f32(p);
}

FORCE_INLINE void _mm_store_ps(float *p, __m128 a) {
    vst1q_f32(p, a);
}

FORCE_INLINE __m128 _mm_set1_ps(float _w) {
    return vdupq_n_f32(_w);
}

FORCE_INLINE __m128 _mm_add_ps(__m128 a, __m128 b) {
    return vaddq_f32(a, b);
}

FORCE_INLINE __m128 _mm_sub_ps(__m128 a, __m128 b) {
    return vsubq_f32(a, b);
}

FORCE_INLINE __m128 _mm_mul_ps(__m128 a, __m128 b) {
    return vmulq_f32(a, b);
}
#endif