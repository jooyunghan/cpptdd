#include <stdlib.h>
#include <memory.h>

typedef struct trie_node trie;
struct trie_node {
	int count;
	trie *children[26];
};

trie *trie_new() {
	trie *p = malloc(sizeof(trie));
	memset(p, 0, sizeof(trie));
	return p;
}

trie *trie_put(trie *root, const char *word) {
	if (root == NULL) {
		root = trie_new();
	}
	if (*word) {
		root->children[*word - 'a']  = trie_put(root->children[*word - 'a'], word+1);
	} else {
		root->count++;
	}
	return root;
}

trie *root;

void add(const char *word) {
	root = trie_put(root, word);
}

typedef void (*trie_f)(const char* word, int count, void *user);

void trie_each_(trie *root, int prefix_len, char * prefix, trie_f f, void *user) {
	int i;
	if (root == NULL) return;
	if (root->count > 0) {
		f(prefix, root->count, user);
	}
  for (i=0; i<26; i++) {
		prefix[prefix_len] = 'a' + i;
		trie_each_(root->children[i], prefix_len + 1, prefix, f, user);
	}	
	prefix[prefix_len] = 0;
}

void trie_each(trie *root, trie_f f, void *user) {
	char prefix[256] = {0, };
  trie_each_(root, 0, prefix, f, user);
}

