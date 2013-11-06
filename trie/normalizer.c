#include <ctype.h>

char *normalize(char *buf) {
	char *src, *dest;
	for (src = dest = buf; *src; src++) {
		if (isalpha(*src)) {
			*dest++ = tolower(*src);
		}
	}
	*dest = '\0';
	return buf;
}

