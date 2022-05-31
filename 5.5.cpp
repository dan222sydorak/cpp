#include <stdio.h>
#include <stdlib.h>

size_t min_rec() {
	size_t n = 3;
	int x, x1, x2, x3;

	x1 = x2 = x3 = -99;
	while (x3 < 0) {
		x = x1 + x3 + 100;
		printf("%d=%d+%d+100\n", x, x1, x3);
		x1 = x2;
		x2 = x3;
		x3 = x;
		n++;
	}
	return n;
}

int main() {
	printf("%zu", min_rec());
}