#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define sign(n) (n < 0 ? -1 : 1)
#define abs(n) (n < 0 ? -n : n)

typedef uint8_t bool; // A smaller type to boolean.

void rotate(uint8_t *f, uint32_t l, int32_t key) {

	uint32_t i = 0, j;
	uint8_t c, fr, to;
	bool lower;

	for (; i < l; i++) {

		c = f[i];

		if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) {

			continue;

		}

		lower = c > 'Z';

		fr = lower ? 'a' : 'A';
		to = lower ? 'z' : 'Z';

		for (j = 0; j < abs(key); j++) {

			c = f[i] + sign(key);

			f[i] = c + (c > to ? -26 : c < fr ? 26 : 0);

		}

	}

}

int main(int argc, char **argv) {

	uint8_t *h[] = {"-h", "--help"};

	for (uint32_t i = 0, j; i < argc; i++) {

		for (j = 0; j < 2; j++) {

			if (!strcmp(argv[i], h[j])) {

				printf("CESAR Code decoder/encoder\n"
					 "Usage: %s <string> <key> [-d]\n"
					 "Where:\n string : The string to be processed\n"
					 "    key : The secret key\n"
					 "     -d : If used, decode content. Unless, encode content.\n", *argv);

				return 0;

			}

		}

	}

	if (argc < 3) {

		fprintf(stderr, "No enough arguments.\n");

		return 1;

	}

	uint8_t *w = argv[1];
	int32_t n = strtol(argv[2], NULL, 10);

	if (argc > 3 && !strcmp(argv[3], "-d"))
		n = -n;

	rotate(w, strlen(w), n);

	printf("%s\n", w);

	return 0;
}