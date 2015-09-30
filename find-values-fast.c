#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

unsigned hash(const char *s, size_t len)
{
	unsigned hash = 5381;
	for (size_t i = 0; i < len; i++)
		hash = ((hash << 5) + hash) + *s++;
	return hash;
}

unsigned partial_hash(const char *s, size_t len)
{
	unsigned hash = 5381;
	for (size_t i = 0; i < len; i++)
		hash = ((hash << 5) + hash) + *s++;
	hash = ((hash << 5) + hash);
	return hash;
}

int increment(char *s, int offset, size_t len)
{
	int next = 0;
	if (offset < 0)
		return 0;
	s[offset]++;
	while (!isalnum(s[offset])) {
		int val = ++s[offset];
		/* Optimize slightly. */
		if (val >= 'z')
			val = 0;
		if (!val) {
			s[offset] = '0';
			if (!increment(s, offset-1, len))
				return 0;
			next = 1;
		}
	}
	return next ? 2 : 1;
}

int print_values_matching(unsigned pow)
{
	char s[] = "00000000000";
	const size_t len = sizeof(s) - 1;
	unsigned mask = pow - 1;
	size_t total = 0;
	unsigned cache = partial_hash(s, len - 1);

	while (total < pow) {
		unsigned h = cache + s[len - 1];
#if 0
		if (h != hash(s, len)) {
			fprintf(stderr, "%08x %08x %s\n", h, hash(s, len), s);
			abort();
		}
#endif
		if (!(h & mask)) {
			printf("    \"%s\": null,\n", s);
			total++;
		}
		int ret = increment(s, len - 1, len);
		if (ret == 2)
			cache = partial_hash(s, len - 1);
		if (!ret)
			return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	int res;
	unsigned pow;
	if (argc < 2) {
		fprintf(stderr, "need a power of two");
		return 2;
	}

	pow = atoi(argv[1]);
	if (!pow || (pow & (pow -1))) {
		fprintf(stderr, "need a power of two");
		return 3;
	}

	printf("{\n");
	res = print_values_matching(pow);
	/* Trailing comma is not valid in JSON, so generate a dummy entry. */
	printf("    \"irrelevant\": null\n}\n");

	return res;
}
