#include <stdlib.h>
#include <assert.h>
#include "dictionary.h"
#include <string.h>


struct bstnode {
  void *item;                // key
  void *value;               // additional value (augmentation)
  struct bstnode *left;
  struct bstnode *right;
  int size;                  // *** new augmentation (see notes)
};

struct dictionary {
  struct bstnode *root;
  // function pointers
  DictKeyCompare key_compare;
  FreeFunction free_key;
  FreeFunction free_val;
  PrintKeyVal print_keyval;  
};

const int PREORDER = -1;
const int INORDER = 0;
const int POSTORDER = 1;

/////////////////////////////

//  see dictionary.h for details
Dictionary dict_create(DictKeyCompare cmp_function,
                       FreeFunction free_key_function,
                       FreeFunction free_val_function,
                       PrintKeyVal print_function) {
  Dictionary dict = malloc(sizeof(struct dictionary));
  dict->root = NULL;
  dict->key_compare = cmp_function;
  dict->free_key = free_key_function;
  dict->free_val = free_val_function;
  dict->print_keyval = print_function;
  return dict;
}


//  calc_size(node) recalculate the size of 'node'
//  requires: node is a valid pointer
//  effects: moifies node
//  time:   O(1)
static void calc_size(struct bstnode *node) {
  assert(node);
  int left_size = 0;
  int right_size = 0;
  if (node->left) left_size = node->left->size;
  if (node->right) right_size = node->right->size;
  node->size = left_size + right_size + 1;
}


//  insert_bstnode(key, val, node, d) inserts key/val pair in d and
//    retain bst properties if key already exists then it replaces 
//    the old value
// effects: modifies node 
// time:    O(h)
static struct bstnode *insert_bstnode(void *key, void *val, struct bstnode *node, Dictionary d) {
  DictKeyCompare cmp = d->key_compare;
  FreeFunction free_val_function = d->free_val;
  FreeFunction free_key_function = d->free_key;
  if (node == NULL) {
    node = malloc(sizeof(struct bstnode));
    node->item = key;
    node->value = val;
    node->left = NULL;
    node->right = NULL;  
  } else if (cmp(key, node->item) == -1) {
    node->left = insert_bstnode(key, val, node->left, d);
  } else if (cmp(key, node->item) == 1) {
    node->right = insert_bstnode(key, val, node->right, d);
  } else { 
    free_key_function(node->item);
    free_val_function(node->value);
    node->item = key;
    node->value = val;
  }
  calc_size(node);
  return node;
}


//  see dictionary.h for details
void dict_insert(void *key, void *val, Dictionary d) {
  d->root = insert_bstnode(key, val, d->root, d);
}


//  see dictionary.h for details
void *dict_lookup(void *key, Dictionary d) {
  struct bstnode *curnode = d->root;
  DictKeyCompare cmp = d->key_compare;
  while (curnode) {
    if (cmp(key, curnode->item) == 0) {
      return curnode->value;
    } else if (cmp(key, curnode->item) == -1) {
      curnode = curnode->left;
    } else {
      curnode = curnode->right;
    }
  }
  return NULL;
}


//  remove_bstnode(key, node, d) removes the node that has the 
//    corresponding 'key' from d
// effects: modifies node, frees key/value
// time:    O(h)
static struct bstnode *remove_bstnode(void *key, struct bstnode *node, Dictionary d) {
  if (node == NULL) return NULL;
  DictKeyCompare cmp = d->key_compare;
  FreeFunction free_val_function = d->free_val;
  FreeFunction free_key_function = d->free_key;
  if (cmp(key, node->item) == -1) {
    node->left = remove_bstnode(key, node->left, d);
  } else if (cmp(key, node->item) == 1) {
    node->right = remove_bstnode(key, node->right, d);
  } else if (node->left == NULL) {
    struct bstnode *new_node = node->right;
    free_val_function(node->value);
    free_key_function(node->item);
    free(node);
    return new_node;
  } else if (node->right == NULL) {
    struct bstnode *new_node = node->left;
    free_val_function(node->value);
    free_key_function(node->item);
    free(node);
    return new_node;
  } else {
    struct bstnode *next = node->right;
    struct bstnode *parent_of_next = NULL;
    while (next->left) {
      parent_of_next = next;
      next = next->left;
    }
    free_key_function(node->item);
    free_val_function(node->value);

    node->item = next->item;
    node->value = next->value;

    if (parent_of_next) {
      parent_of_next->left = next->right;
    } else {
      node->right = next->right;
    }
    free(next);
  }
  calc_size(node);
  return node;
}


//  see dictionary.h for details
void dict_remove(void *key, Dictionary d) {
  d->root = remove_bstnode(key, d->root, d);
}


//  node_print(order, node, d) prints the node in the given order
//  requires: order is one of (PREORDER, INORDER, POSTORDER)
//  effects:  displays output
//  time:     O(n)
static void node_print(int order, const struct bstnode *node, Dictionary d) {
  assert(order == PREORDER || order == INORDER || order == POSTORDER);
  if (node == NULL) return;
  PrintKeyVal print_function = d->print_keyval;

  if (order == PREORDER) 
    print_function(node->item, node->value);

  node_print(order, node->left, d);

  if (order == INORDER)
    print_function(node->item, node->value);

  node_print(order, node->right, d);

  if (order == POSTORDER)
    print_function(node->item, node->value);
}


//  see dictionary.h for details
void dict_print(int order, Dictionary d) {
  node_print(order, d->root, d);
}


//  see dictionary.h for details
int dict_size(Dictionary d) {
  return d->root->size;
}


//  bstnode_select(k, node) finds the k-th key in node
// requires: 0 <= k < node->size
//           node is a valid pointer
// time:     O(h)
static void *bstnode_select(int k, const struct bstnode *node) {
  assert(node);
  assert(k >= 0);
  assert(k < node->size);
  int left_size = 0;
  if (node->left) left_size = node->left->size;
  if (k < left_size) return bstnode_select(k, node->left);
  if (k == left_size) return node->item;
  return bstnode_select(k - left_size - 1, node->right);
}


//  see dictionary.h for details
void *dict_select(int k, Dictionary d) {
  assert(d);
  assert(k >= 0);
  assert(k < dict_size(d));
  return bstnode_select(k, d->root);
}


//  free_bstnode(node, d) free all memmory associated with node
//  effects: node and its associated objects are no longer valid
//  times:    O(n)
static void free_bstnode(struct bstnode *node, Dictionary d) {
  assert(d);
  FreeFunction free_key_function = d->free_key;
  FreeFunction free_val_function = d->free_val;
  if (node) {
    free_bstnode(node->left, d);
    free_bstnode(node->right, d);
    free_val_function(node->value);
    free_key_function(node->item);
    free(node);
  }
}

//  see dictionary.h for details
void dict_destroy(Dictionary d) {
  assert(d);
  free_bstnode(d->root, d);
  free(d);
}
