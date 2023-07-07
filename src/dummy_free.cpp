extern "C" {
    #include "include/mont.h"
    #include "include/fp.h"
    #include "include/dummy_free.h"
    #include "include/rng.h"
    #include "include/params.h"
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
}