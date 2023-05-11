#include "rbtree.h"

#include <stdlib.h>
void left_rotate(rbtree *t, node_t *node);
void right_rotate(rbtree *t, node_t *node);
void insert_fixup(rbtree *t, node_t *node);
void rbtree_delete_fixup(rbtree *t, node_t *x);
void transplant(rbtree *t,node_t *u, node_t *v);
int inorder(const rbtree *t, node_t *node, key_t *arr, const size_t n, int idx);
void delete_node(rbtree *t, node_t *node);

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil_node = (node_t *)calloc(1,sizeof(node_t));
  nil_node->color = RBTREE_BLACK;
  p->root = nil_node;
  p->nil = nil_node;
  return p;
}

void delete_rbtree(rbtree *t) {
  delete_node(t, t->root);
  free(t->nil);
  free(t);
}
void delete_node(rbtree *t, node_t *node){
    if (node == t->nil) return;  
  
    delete_node(t, node->left);
    delete_node(t, node->right);

    free(node);
}
node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *parent_node = t->nil;
  node_t *current_node = t->root;

  while (current_node != t->nil) {
      parent_node = current_node;
      if (key < current_node->key) {
          current_node = current_node->left;
      } else {
          current_node = current_node->right;
      }
  }

  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->parent = parent_node;
  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->color = RBTREE_RED;

  if (parent_node == t->nil) {
      t->root = new_node;
  } else if (new_node->key < parent_node->key) {
      parent_node->left = new_node;
  } else {
      parent_node->right = new_node;
  }

  insert_fixup(t, new_node);

  return t->root;
}

void insert_fixup(rbtree *t, node_t *node){
   while (node != t->root && node->parent->color == RBTREE_RED) {
    if (node->parent == node->parent->parent->left) {
      node_t *s = node->parent->parent->right;
      if (s->color == RBTREE_RED) {
        node->parent->color = RBTREE_BLACK;
        s->color = RBTREE_BLACK;
        node->parent->parent->color = RBTREE_RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          left_rotate(t, node);
        }
        node->parent->color = RBTREE_BLACK;
        node->parent->parent->color = RBTREE_RED;
        right_rotate(t, node->parent->parent);
      }
    } else {
      node_t *s = node->parent->parent->left;
      if (s->color == RBTREE_RED) {
        node->parent->color = RBTREE_BLACK;
        s->color = RBTREE_BLACK;
        node->parent->parent->color = RBTREE_RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          right_rotate(t, node);
        }
        node->parent->color = RBTREE_BLACK;
        node->parent->parent->color = RBTREE_RED;
        left_rotate(t, node->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

void left_rotate(rbtree *t, node_t *node){
  node_t *y = node->right;
  node->right = y->left;
  if (y->left != t->nil) {
    y->left->parent = node;
  }
  y->parent = node->parent;

  if (node->parent == t->nil){
    t->root = y;
  }else if (node == node->parent->left){
    node->parent->left = y;
  }else {
    node->parent->right = y;
  }
  y->left = node;
  node->parent = y;
}

void right_rotate(rbtree *t, node_t *node){
  node_t *y = node->left;
  node->left = y->right;
  if (y->right != t->nil) {
    y->right->parent = node;
  }
  y->parent = node->parent;

  if (node->parent == t->nil){
    t->root = y;
  }else if (node == node->parent->right){
    node->parent->right = y;
  }else {
    node->parent->left = y;
  }
  y->right = node;
  node->parent = y;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *current = t->root;
  while (current->key != key){
    if(current == t->nil){
        return NULL;
    }
    if(current->key > key){
      current = current->left;
    } else if(current->key < key) {
      current = current->right;
    }
  }
  return current;
}
node_t *rbtree_min(const rbtree *t) {
  node_t *current = t->root;
  while (current != t->nil){
    if (current->left == t->nil){
      return current;
    }
    current = current->left;
  }
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *current = t->root;
  while (current != t->nil){
    if (current->right == t->nil){
      return current;
    }
    current = current->right;
  }
  return t->root;
}
 
int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  node_t *node = p;
  node_t *x = t->nil;
  color_t originalcolor = node->color;
  if (p->left == t->nil){
    x = p->right;
    transplant(t,p,p->right);
  }else if(p->right==t->nil){
    x = p->left;
    transplant(t,p,p->left);
  }else{
    node = node->right;
    while(node->left!=t->nil){node = node->left;}
    originalcolor = node->color;
    x = node->right;
    if (node->parent == p){
      x->parent = node;
    }else{
      transplant(t,node,node->right);
      node->right = p->right;
      node->right->parent = node;
    }
    transplant(t,p,node);
    node->left = p->left;
    node->left->parent = node;
    node->color = p->color;
  }
  if (originalcolor == RBTREE_BLACK){
   
     rbtree_delete_fixup(t,x);
    }
  x->color = RBTREE_BLACK;
  return 0;
}

void transplant(rbtree *t,node_t *u, node_t *v){
  if(u->parent == t->nil){
    t->root = v;
  }else if(u == u->parent->left){
    u->parent->left = v;
  }else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void rbtree_delete_fixup(rbtree *t, node_t *x){
  node_t *w = t->nil;
  while (x != t->root && x->color == RBTREE_BLACK){
    if(x == x->parent->left){
      w = x->parent->right;
      if(w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t,x->parent);
        w = x->parent->right;
      }
      if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      } else {
        if (w->right->color == RBTREE_BLACK){
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t,w);
          w = x->parent->right;
        }
        w->color= x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t,x->parent);
        x = t->root;
      }
    } else {
      w = x->parent->left;
      if(w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t,x->parent);
        w = x->parent->left;
      }
      if(w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      } else {
        if (w->left->color == RBTREE_BLACK){
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t,w);
          w = x->parent->left;
        }
        w->color= x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t,x->parent);
        x = t->root;
      }
    }
  }
}


int inorder(const rbtree *t, node_t *node, key_t *arr, const size_t n, int idx){
  if (idx < n){
    if (node->left != t->nil){
      idx = inorder(t,node->left,arr,n,idx);
    }
    arr[idx++] = node->key;
    if (node->right != t->nil){
      idx = inorder(t,node->right,arr,n,idx);
    }
  }
  return idx;
}


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  inorder(t,t->root,arr,n,0);
  return 0;
}

