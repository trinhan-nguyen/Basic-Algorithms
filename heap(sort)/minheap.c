#include <stdlib.h>
#include "minheap.h"
#include <assert.h>


//	see minheap.h for details
struct minheap *minheap_create(void) {
	struct minheap *h = malloc(sizeof(struct minheap));
	h->len = 0;
	h->maxlen = 1;
	h->data = malloc(h->maxlen * sizeof(int));
  	return h;
}


//	see minheap.h for details
bool minheap_is_empty(const struct minheap *h) {
  	return h->len == 0;
}


//	swap_if_larger(a, b) swaps the value of a and b if a is larger 
//		than b and returns true; otherwise, returns false
//	effects: may modify a, b
//	time:	O(1)
static bool swap_if_larger(int *a, int *b) {
	if (*a <= *b) return false;
	int tmp = *a;
	*a = *b;
	*b = tmp;
	return true;
}


//	see minheap.h for details
void minheap_insert(int i, struct minheap *h) {
	if (h->len == h->maxlen) {
		h->maxlen = h->len * 2 + 1;
		h->data = realloc(h->data, h->maxlen * sizeof(int));
	}
	h->data[h->len] = i;
	//	move up
	int cur = h->len;
	while (cur > 0 && h->data[cur] < h->data[(cur - 1)/2]) {
		swap_if_larger(&h->data[(cur - 1)/2], &h->data[cur]);
		cur = (cur - 1)/2;
	}
	h->len += 1;
}


//	see minheap.h for details
int minheap_top(const struct minheap *h) {
	assert(h);
	assert(!minheap_is_empty(h));
  	return h->data[0];
}


//	see minheap.h for details
int minheap_remove(struct minheap *h) {
	assert(h);
	assert(!minheap_is_empty(h));
	int ans = h->data[0];
	h->len -= 1;
	h->data[0] = h->data[h->len];
	//	move down
	int cur = 0;
	while (true) {
		if (cur * 2 + 1 >= h->len) break;		
		if (cur * 2 + 2 >= h->len) {
			swap_if_larger(&h->data[cur], &h->data[cur * 2 + 1]);
			break;
		}
		int left = cur * 2 + 1;
		int right = left + 1;
		if (left < right) {
			if (!swap_if_larger(&h->data[cur], &h->data[left])) break;
			cur = left;
		} else {
			if (!swap_if_larger(&h->data[cur], &h->data[right])) break;
			cur = right;
		}
	}
	//	resize if redundant
	if (h->len * 5 < h->maxlen) {
		h->maxlen = h->len * 2 + 1;
		h->data = realloc(h->data, h->maxlen * sizeof(int));
	}
  	return ans;
}


//	see minheap.h for details
void minheap_destroy(struct minheap *h) {
	free(h->data);
	free(h);
}


//	see minheap.h for details
void heapsort(int a[], int len) {
	assert(a);
	struct minheap *h = minheap_create();
	for (int i = 0; i < len; ++i)
		minheap_insert(a[i], h);
	for (int i = 0; i < len; ++i) 
		a[i] = minheap_remove(h);
	minheap_destroy(h);
}
