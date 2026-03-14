#include <stdio.h>

int main()
{
	union {
		float f;
		unsigned int i;
	} x;
	x.f = 0.1;

	union {
		double d;
		unsigned long l;
	} y;
	y.d = 0.1;

	printf("Binary form of 0.1 in float:\n");
	for (int offset = 31; offset >= 0; offset--) {
		printf("%u", (x.i >> offset) & 1);
	}

	printf("\n\n");
	printf("Binary form of 0.1 in double:\n");
	for (int offset = 63; offset >= 0; offset--) {
		printf("%lu", (y.l >> offset) & 1);
	}
	printf("\n");
	return 0;
}
