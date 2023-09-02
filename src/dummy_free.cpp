#include <cstring>

extern "C" {
    #include "include/mont.h"
    #include "include/fp.h"
    #include "include/dummy_free.h"
    #include "include/rng.h"
    #include "include/params.h"
    #include "include/addchain.h"
}

void random_key(uint8_t key[]) {
    uint8_t tmp, r;
    int8_t exp, sgn;

    for (uint8_t i = 0; i < N; i++) {
        r = B[i] & 0x1;
        
        randombytes(&tmp, 1);
        while (isSmaller((int32_t)B[i], (int32_t)tmp) == -1) {
            randombytes(&tmp, 1);
        }
        exp = (int8_t)tmp;

        exp = ((exp & 0x1) - (B[i] + r)) >> 1;

        exp = (exp << 0x1) + r;
        sgn = exp >> 0x7;
        
        cmov(&exp, -exp, sgn == -1);
        key[i] = (exp << 1) ^ (1 & (1 + sgn));
    }
}

void action_eval(proj C, const uint8_t key[], const proj A) {
    uint8_t batches[BATCHES][SIZE_EACH_BATCH[0]];
    uint8_t size_each_batch[BATCHES];

    for (uint8_t i = 0; i < BATCHES; i++) {
        std::memcpy(batches[i], BATCH[i], sizeof(uint8_t) + SIZE_EACH_BATCH[i]);
    }

    std::memcpy(size_each_batch, SIZE_EACH_BATCH, sizeof(uint8_t) * BATCHES);

    uint8_t complement_each_batch[BATCHES][N];
    uint8_t size_complement_each_batch[BATCHES];

    std::memcpy(complement_each_batch, COMPLEMENT_EACH_BATCH, sizeof(uint8_t) * BATCHES * N);
    std::memcpy(size_complement_each_batch, SIZE_EACH_COMPLEMENT_BATCH, sizeof(uint8_t) * BATCHES);

    // public key and private data
    uint8_t tmp_e[N];
    std::memcpy(tmp_e, key, sizeof(uint8_t) * N);

    proj current_A, current_T[2];
    point_copy(current_A, A);

    int8_t ec = 0;
    uint16_t cnt = 0;
    proj G[2], K[(LARGE_L >> 1) + 1];
    uint8_t finish[N];
    std::memset(finish, 0, sizeof(uint8_t) * N);

    int8_t cnter[N];
    std::memset(cnter, 0, sizeof(int8_t) * N);
    std::memcpy(cnter, B, sizeof(int8_t) * N);
    uint64_t isogeny_cnter = 0;


    uint8_t last_issogeny[BATCHES];
    std::memcpy(last_issogeny, LAST_ISOGENY, sizeof(uint8_t) * BATCHES);
    uint32_t bc;

    uint8_t m = 0;
    uint64_t number_batches = BATCHES;
    uint32_t si;

    while (isogeny_cnter < ISOGENIES) {
        m = (m + 1) % number_batches;

        if (cnt == MY*number_batches) {
            m = 0;
            size_complement_each_batch[m] = 0;
            size_each_batch[m] = 0;
            number_batches = 1;

            for (uint8_t i = 0; i < N; i++) {
                if (cnter[i] == 0) {
                    complement_each_batch[m][size_complement_each_batch[m]] = i;
                    size_complement_each_batch[m]++;
                } else {
                    last_issogeny[0] = i;
                    batches[m][size_each_batch[m]] = i;
                    size_each_batch[m]++;
                }
            }
        }
        
    }
    
}