#include <stdio.h>

void add(const char *word);
void normalize(char *word);

int main() {
	char word[256];
	int count = 0;
	while (scanf("%s", word) > 0) {
		normalize(word);
		add(word);
		count++;
	}
//	print();
  printf("%d\n", count);
	return 0;
}
