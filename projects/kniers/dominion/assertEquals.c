#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int assertEquals(char *message, int actual, int expected) {
	printf("%s - expected: %d, actual: %d\n", message, expected, actual);
	if (actual == expected) return 0;
	else {
		printf("^TEST FAILURE^\n");
		return 1;
	}
}