#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "crypto.h"

unsigned long long fastpoweralgo_lowmem(unsigned long long modulo, unsigned long long base, unsigned long long exponent) {
	unsigned long long a = base;
	unsigned long long b = 1;
	while (exponent > 0) {
		if (exponent % 2 == 1) {
			b = (b * a) % modulo;
		}
		a = (a * a) % modulo;
		exponent = exponent / 2;

	}
	return b;
}
