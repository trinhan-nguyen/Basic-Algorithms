#include <stdlib.h>
#include "trie.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

static const int NUM_ALPHABET = 26;

//	see trie.h for details
struct trie *trie_create(void) {
	struct trie *t = malloc(sizeof(struct trie));
	t->root = NULL;
  	return t;
}


// 	node_add(s, node, cur, len) adds the word s to trienode node
// 	effects: modifies node
// 	time:    O(n), n is the length of s
static void node_add(const char *s, struct trienode *node, int cur, int len) {
	if (cur == len) {
		node->word_end = true;
		return;
	}
	
	int cur_char = s[cur] - 97;
	node->children[cur_char] = malloc(sizeof(struct trienode));
	node->children[cur_char]->word_end = false;
	for (int i = 0; i < NUM_ALPHABET; ++i) 
		node->children[cur_char]->children[i] = NULL;	
	node_add(s, node->children[cur_char], cur + 1, len);
}


//	see trie.h for details
void trie_add(const char *s, struct trie *t) {
	assert(s);
	int len = strlen(s);
	if (t->root == NULL) {
		t->root = malloc(sizeof(struct trienode));			
		for (int i = 0; i < NUM_ALPHABET; ++i) 
			t->root->children[i] = NULL;
	}
	if (len == 0) {
		t->root->word_end = true;
		return;
	}
	node_add(s, t->root, 0, len);
}


// 	there_are_others(node) determines if this node has at least
//		a child
//	requires: node is a valid pointer
//	time:	O(1)
static bool there_are_others(const struct trienode *node) {
	bool others = false;
	for (int i = 0; i < NUM_ALPHABET; ++i) {
		if (node->children[i]) others = true;
	}
	return others;
}

// 	node_remove(s, node, cur, len, removed, found) removes the word  
//		s from trienode 'node' (if it exists) and any trienodes 
//		that are no longer needed
// 	effects: may modify node
// 	time:    O(n), n is the length of s
static void node_remove(const char *s, struct trienode *node, int cur, int len, bool *removed, bool *found) {
	if (node == NULL) return;
	if (cur == len) {
		*found = true;
		if (!there_are_others(node)) free(node);
		return;
	}
	int cur_char = s[cur] - 97;
	node_remove(s, node->children[cur_char], cur + 1, len, removed, found);
	if (cur < len && node->word_end) {
		*removed = true;
	}
	node->children[cur_char] = NULL;
	if (*removed || !(*found) || there_are_others(node)) return;	
	free(node);
}


//	see trie.h for details
void trie_remove(const char *s, struct trie *t) {
	assert(s);
	int len = strlen(s);
	if (len == 0 && t->root) {
		t->root->word_end = false;
		for (int i = 0; i < NUM_ALPHABET; ++i) {
			if (t->root->children[i]) return;
		}	
		free(t->root);
	}
	bool found = false;
	bool removed = false;
	node_remove(s, t->root, 0, strlen(s), &found, &removed);
}


// 	node_lookup(s, node, cur, len) determines if node contains the word s
// 	time: O(n), n is the length of s
static bool node_lookup(const char *s, struct trienode *node, int cur, int len) {
	if (node == NULL) return false;
	if (cur == len && node->word_end) return true;
	else if (cur == len) return false;
	int cur_char = s[cur] - 97;
	return node_lookup(s, node->children[cur_char], cur + 1, len);
}


//	see trie.h for details
bool trie_lookup(const char *s, const struct trie *t) {
  	return node_lookup(s, t->root, 0, strlen(s));
}


// node_destroy(node) frees all memory associated with node
// effects: node is no longer valid
// time:    O(n), n is the number of characters in node and its children
static void node_destroy(struct trienode *node) {
	if (node == NULL) return;	
	for (int i = 0; i < NUM_ALPHABET; ++i) {
		node_destroy(node->children[i]);
		node->children[i] = NULL;
	}	
	free(node);
}


//	see trie.h for details
void trie_destroy(struct trie *t) {
	node_destroy(t->root);
	free(t);
}


// node_count(node) determines how many words are in node
// time: O(n), n is the number of trienode in node
static int node_count(const struct trienode *node) {
	if (node == NULL) return 0;
	int count = 0;
	if (node->word_end) ++count;
	for (int i = 0; i < NUM_ALPHABET; ++i) {		
		count += node_count(node->children[i]);
	}
	return count;
}


//	see trie.h for details
int trie_count(const struct trie *t) {
	assert(t);
  	return node_count(t->root);
}


// 	node_to_aos(aos, node, aos, len, maxlen, cur, maxcur) generates 
//		a new array containing all of the words in node in alphabetical 
//		order, each word is a new string
//	effects: allocates memory 
// 	time:	O(n), n is the number of characters in all of the words in t
static char **node_to_aos(char **s, const struct trienode *node, char **aos, int len, int maxlen, int cur, int maxcur) {
	if (node == NULL) return aos;
	if (node->word_end) {		
		aos[cur] = malloc((len + 1) * sizeof(char));
		for (int i = 0; i < len; ++i) 
			aos[cur][i]	= (*s)[i];
		aos[cur][len] = 0;	
		++cur;	
		if (cur == maxcur) {
			maxcur *= 2;
			aos = realloc(aos, maxcur * sizeof(char*));
		}
	}

	for (int i = 0; i < NUM_ALPHABET; ++i) {
		if (node->children[i] == NULL) continue;

		if (len == maxlen - 1) {
			maxlen *= 2;
			*s = realloc(*s, maxlen * sizeof(char));
		}

		char cur_char = i + 97;
		(*s)[len] = cur_char;
		return node_to_aos(s, node->children[i], aos, len + 1, maxlen, cur, maxcur);
	}
	return aos;
}


//	see trie.h for details
char **trie_to_aos(const struct trie *t) {
  	assert(t);
  	int size = trie_count(t);
  	if (size == 0) return NULL;
  	char **tmp = malloc(sizeof(char*));
  	char *s = malloc(sizeof(char));
  	s[0] = 0;
  	char **ans = node_to_aos(&s, t->root, tmp, 0, 1, 0, 1);
  	free(s);
  	return ans;
}



//	see trie.h for details
void trie_print(const struct trie *t) {
	char **aos = trie_to_aos(t);
	int size = trie_count(t);
	for (int i = 0; i < size; ++i) {
		printf("%s\n", aos[i]);
		free(aos[i]);
	}
	free(aos);
}