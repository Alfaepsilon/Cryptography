#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "crypto.h"

unsigned long long shanks(unsigned long long val, unsigned long long p, unsigned long long g) {
	unsigned long long inverse = exeucalgo(g, p, 1);
	unsigned long long N = DLP(1, p, g);
	unsigned long long n = 1 + floor(sqrt(N));
	unsigned long long l1[n];
	for(unsigned long long i = 0; i < n; i++){
		l1[i] = fastpoweralgo_lowmem(p, g, i);
	}
	for(unsigned long long i = 0; i < n; i++){
		for(unsigned long long j = 0; j < n; j++){
			if((val * fastpoweralgo_lowmem(p, inverse, i * n) % p) == l1[j]){
				printf("%llu", j + i*n);
			}
		}
	}
	return 0;
}
