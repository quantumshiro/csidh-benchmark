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


static inline int compare(fp *x, fp *y, int NUM) {
  for (int i = NUM - 1; i >= 0; i--)
    if (x[i] != y[i]) return x[i] > y[i] ? 1:-1;
  return 0;
}

static inline int iszero(fp *x, )
#endif
