#include <iostream>
#include <vector>
#include <chrono>
#include <cassert>
#include <iomanip>
#include <cstring>
#include <string>

extern "C" {
    #include "include/fp.h"
    #include "include/csidh.h"
    #include "include/params.h"
}

void uint_print(const unit* x)
{
    for (size_t i = 8 * LIMBS; i != SIZE_MAX; --i)
        std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>((reinterpret_cast<const unsigned char*>(x->c))[i]);
}

void fp_print(const fp* x)
{
    unit y;
    fp_dec(&y, x);
    uint_print(&y);
}

int main() {
    private_key priv_alice, priv_bob;
    public_key pub_alice, pub_bob, shared_alice, shared_bob;

    csidh_private(&priv_alice);
    csidh_private(&priv_bob);

    csidh(&pub_alice, &base, &priv_alice);
    csidh(&pub_bob, &base, &priv_bob);

    csidh(&shared_alice, &pub_bob, &priv_alice);
    csidh(&shared_bob, &pub_alice, &priv_bob);

    std::cout << "Alice's private key: ";
    for (int i = 0; i < (NUM_PRIMES + 1) / 2; ++i)
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)priv_alice.e[i];
    std::cout << std::endl;

    std::cout << "Bob's private key: ";
    for (int i = 0; i < (NUM_PRIMES + 1) / 2; ++i)
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)priv_bob.e[i];
    std::cout << std::endl;

    std::cout << "Alice's public key: ";
    fp_print(&pub_alice.A);
    std::cout << std::endl;

    std::cout << "Bob's public key: ";
    fp_print(&pub_bob.A);
    std::cout << std::endl;

    std::cout << "Alice's shared secret: ";
    fp_print(&shared_alice.A);
    std::cout << std::endl;

    std::cout << "Bob's shared secret: ";
    fp_print(&shared_bob.A);
    std::cout << std::endl;

    return 0;
}
