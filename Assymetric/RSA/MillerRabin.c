#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <mpir.h>
#include "Crypto.h"


short MillerRabin(mpz_t X, mpz_t a) {
    mpz_t q, modX, Xphi;
    mpz_inits(q, modX, Xphi, (mpz_ptr)NULL);

    //If evenX is even
	if (mpz_even_p(X)) {
        mpz_clears(q, modX, Xphi, (mpz_ptr)NULL);
        printf("Even! \n");
		return 1;
	}

    mpz_t* gcd = cc_gcd(X, a);
    //If *gcd is larger than 1 and not equal to X, a.k.a a divides X
    if (mpz_cmp_ui(*gcd, 1) > 0 && mpz_cmp(*gcd, X) < 0) {
        mpz_clears(q, modX, Xphi, *gcd, (mpz_ptr)NULL);
        free(gcd);
        printf("GCD is non-trivial! \n");
        return 1;
    }
    mpz_clear(*gcd);
    free(gcd);

    mpz_sub_ui(q, X, 1);
    short k = 0;
    while (mpz_even_p(q) != 0) {
        mpz_div_ui(q, q, 2);
        k = k + 1;
    }

    mpz_powm(a, a, q, X);
    mpz_mod(modX, a, X);
    if (mpz_cmp_ui(modX, 1) == 0) {
        mpz_clears(q, modX, Xphi, (mpz_ptr)NULL);
        printf("a^q == 1 \n");
        return 0;
    }

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
    }
    mpz_clears(q, modX, Xphi, (mpz_ptr)NULL);
    printf("Last \n");
	return 1;
}
