#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "crypto.h"

int primitive_roots(int p) {
	int count = 0;
	int* prim_roots = malloc(sizeof(int) * p);
	for (int i = 2; i < p; i++) {
		for (int j = 0; j < p - 1; j++) {
			prim_roots[j] = fastpoweralgo_lowmem(p, i, j);
			if (prim_roots[j] == i) {
				count = count + 1;
			}
			if (count > 1) {
				count = 0;
				goto skip;
			}
		}
		count = 0;
		printf("%d is a primitive root \n", i);
		skip:
			continue;
	}
	return 0;
}
