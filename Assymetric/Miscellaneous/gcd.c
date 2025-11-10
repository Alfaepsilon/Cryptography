#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <crypto.h>

int gcd() {
	int a;
	int b;
	printf("Type a number: \n");
	scanf("%d", &a);
	printf("Type another number: \n");
	scanf("%d", &b);
	while (a != b) {
		if (a > b) {
			a = a - b;
		}
		else {
			b = b - a;
		}
	}
	printf("%d", a);
}
