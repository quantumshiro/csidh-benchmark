#ifndef __DUMMY_FREE_H__
#define __DUMMY_FREE_H__

#define BATCHES 5
#define MY 11

#include <stdint.h>

static int8_t B[] {
    7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7,
    8, 8, 8, 8, 8, 8, 8, 11,
    11, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 11,
    11, 13, 13, 13, 13, 13, 13, 13, 
    13, 13, 13, 13, 13, 13, 13, 13, 
    13, 13, 13, 13, 13, 13, 13, 13, 
    13, 13, 13, 13, 13,  5,  7,  7, 
    7,  7 
};

// (NUMBER_OF_BATCHES) different subsets (i.e., batches)
static uint8_t BATCH_0[] = { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70 };
static uint8_t BATCH_1[] = { 1, 6, 11, 16, 21, 26, 31, 36, 41, 46, 51, 56, 61, 66, 71 };
static uint8_t BATCH_2[] = { 2, 7, 12, 17, 22, 27, 32, 37, 42, 47, 52, 57, 62, 67, 72 };
static uint8_t BATCH_3[] = { 3, 8, 13, 18, 23, 28, 33, 38, 43, 48, 53, 58, 63, 68, 73 };
static uint8_t BATCH_4[] = { 4, 9, 14, 19, 24, 29, 34, 39, 44, 49, 54, 59, 64, 69 };

static uint8_t SIZE_EACH_BATCH[BATCHES] = { 15, 15, 15, 15, 14 };
static uint8_t *BATCH[BATCHES] = { BATCH_0, BATCH_1, BATCH_2, BATCH_3, BATCH_4 };



#endif // __DUMMY_FREE_H__