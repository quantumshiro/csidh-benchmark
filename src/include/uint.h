#ifndef UINT_H
#define UINT_H

#include <stdbool.h>
#include <stdint.h>

#include "params.h"

extern const unit uint_1;

void uint_set(unit *x, uint64_t y);

bool uint_bit(unit const *x, uint64_t k);

bool uint_add3(unit *x, unit const *y, unit const *z); /* returns carry */
bool uint_sub3(unit *x, unit const *y, unit const *z); /* returns borrow */

void uint_mul3_64(unit *x, unit const *y, uint64_t z);

#endif
