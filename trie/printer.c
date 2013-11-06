
void print_word(const char *prefix, int count,  void *uesr) {
	printf("%s: %d\n", prefix, count);
}

void print() {
	trie_each(root, &print_word, NULL);
}


