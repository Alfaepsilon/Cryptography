#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gmp.h>
#include "Miscellaneous.h"


short MillerRabin(mpz_t X, mpz_t a) {
    //If evenX is even
    if (mpz_even_p(X)) {
        printf("Even! \n");
        return 1;
    }
    mpz_t gcd;
    mpz_init(gcd);
    cc_gcd(gcd, X, a);
    //If *gcd is larger than 1 and not equal to X, a.k.a a divides X
    if (mpz_cmp_ui(gcd, 1) > 0 && mpz_cmp(gcd, X) < 0) {
        mpz_clear(gcd);
        printf("GCD is non-trivial! \n");
        return 1;
    }
    mpz_clear(gcd);
    mpz_t q;
    mpz_init(q);
    mpz_sub_ui(q, X, 1);
    short k = 0;
    while (mpz_even_p(q) != 0) {
        mpz_div_ui(q, q, 2);
        k = k + 1;
    }
    cc_powmod(a, X, a, q);
    mpz_t modX;
    mpz_mod(modX, a, X);
    if (mpz_cmp_ui(modX, 1) == 0) {
        mpz_clears(q, modX, (mpz_ptr)NULL);
        printf("a^q == 1 \n");
        return 0;
    }
    mpz_t Xphi;
    mpz_init(Xphi);
    mpz_sub_ui(Xphi, X, 1); //A.k.a -1 mod X
    for (short i = 0; i < k; i++) {
        mpz_mod(modX, a, X);
        if (mpz_cmp(modX, Xphi) == 0) {
            mpz_clears(q, modX, Xphi, (mpz_ptr)NULL);
            printf("a^q*k == -1 \n");
            return 0;
        }
        if (mpz_cmp_ui(modX, 1) == 0) {
            mpz_clears(q, modX, Xphi, (mpz_ptr)NULL);
            printf("a^q*k == 1 \n");
            return 1;
        }
        mpz_powm_ui(a, a, 2, X);
        //cc_powmod(pow, X, a, (mpz_ptr)2);
    }
    mpz_clears(q, modX, Xphi, (mpz_ptr)NULL);
    printf("Last \n");
    return 1;
}