#ifndef FP_H
#define FP_H

#include <stdbool.h>

#include "params.h"

#define N 74
#define LOG2_n_PLUS_one 8
#define NUMBERWORDS 8

extern const fp fp_0;
extern const fp fp_1;

void fp_set(fp *x, uint64_t y);

void fp_enc(fp *x, unit const *y); /* encode to Montgomery representation */
void fp_dec(unit *x, fp const *y); /* decode from Montgomery representation */

void fp_add2(fp *x, fp const *y);
void fp_sub2(fp *x, fp const *y);
void fp_mul2(fp *x, fp const *y);

void fp_add3(fp *x, fp const *y, fp const *z);
void fp_sub3(fp *x, fp const *y, fp const *z);
void fp_mul3(fp *x, fp const *y, fp const *z);

void fp_sq1(fp *x);
void fp_sq2(fp *x, fp const *y);
void fp_inv(fp *x);
bool fp_issquare(fp *x); /* destroys input! */

void fp_random(fp *x);

#define set_zero(x, NUM) memset(x, 0, sizeof(uint64_t) * NUM);
#define set_one(x, NUM) x[0] = 1; for(int i = 1; i < NUM; i++) x[i] = 0;
#define copy(x, y, NUM) memcpy(x, y, sizeof(uint64_t)*NUM);


static inline int compare(uint64_t *x, unit y, int NUM) {
  for (int i = NUM - 1; i >= 0; i--) {
    if (x[i] != y.c[i]) return x[i] > y.c[i] ? 1:-1;
  }
  return 0;
}

static inline int iszero(uint64_t *x, int NUM) {
  uint64_t c = 0;
  for (int i = NUM - 1; i > 0; i--) {
    c |= x[i];
  }
  return c == 0;
}

static void cmov(int8_t *r, const int8_t a, uint32_t b) {
  uint32_t t;
  b = -b;
  t = (*r ^ a) & b;
  *r ^= t;
}

/* check if a and b are equal in constant time  */
static int is_equal(uint64_t *a, uint64_t *b, int NUM) {
  uint64_t r = 0;
  for (int i = 0; i < NUM; i++) {
    r |= a[i] ^ b[i];
  }
  r = -r;
  r = r >> 63;
  return (int)(1 - r);
}

// /* get priv[pos] in constant time  */
static void get_priv(uint64_t *r, uint64_t *priv, int pos, int NUM) {
  uint64_t mask = 0;
  for (int i = 0; i < NUM; i++) {
    mask |= (i == pos) ? 0 : priv[i];
  }
  for (int i = 0; i < NUM; i++) {
    r[i] = priv[i] & mask;
  }
}

// constant-time comparison: -1 if x < y, 0 otherwise.
static int32_t isSmaller(int32_t x, int32_t y)
{
  int32_t xy = x ^ y;
  int32_t c = x - y;
  c ^= xy & (c ^ x);
  return (c >> 31);
}
#endif
