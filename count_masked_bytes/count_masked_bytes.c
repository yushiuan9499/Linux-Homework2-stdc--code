#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef LINUX
/* Carl Chatfield / Jan Achrenius G+ version for 32-bit */
static inline long count_masked_bytes(long mask)
{
	/* (000000 0000ff 00ffff ffffff) -> ( 1 1 2 3 ) */
	long a = (0x0ff0001 + mask) >> 23;
	/* Fix the 1 for 00 case */
	return a & mask;
}
#else
#ifdef MY
static inline long count_masked_bytes(long mask)
{
	if ((mask & 0xff) == 0x00)
		return 0;
	mask >>= 8;
	if ((mask & 0xff) == 0x00)
		return 1;
	mask >>= 8;
	if ((mask & 0xff) == 0x00)
		return 2;
	mask >>= 8;
	if ((mask & 0xff) == 0x00)
		return 3;
	return -1; // shouldn't happen
}
#endif
#endif

long for_test[4] = { 0x00000000, 0x000000ff, 0x0000ffff, 0x00ffffff };

int main()
{
	srand(time(NULL));
	unsigned long tot = 0;
	for (int i = 0; i < 1000000000; i++) {
		int idx = rand() % 4;
		long mask = for_test[idx];
		tot += count_masked_bytes(mask);
	}
	printf("Total: %lu\n", tot);
	return 0;
}
