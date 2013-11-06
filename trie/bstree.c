#include <string.h>
#include <stdlib.h>

typedef struct tree tree;
struct tree {
	int count;
	char *word;
	tree *left;
	tree *right;
};

tree *tree_new(const char *word, int count) {
	tree *node = (tree*)malloc(sizeof(tree));
	node->word = strdup(word);
	node->count = count;
	node->left = node->right = NULL;
	return node;
}

tree *insert(tree *root, const char *word) {
	if (root == NULL) {
		return tree_new(word, 1);
	}
	int cmp = strcmp(word, root->word);
	if (cmp == 0) {
		root->count++;
	  return root;
	} else if (cmp < 0) {
		root->left = insert(root->left, word);
	} else {
		root->right = insert(root->right, word);
	}
	return root;
}

tree * root;
void add(const char *word) {
  root = insert(root, word);
}

