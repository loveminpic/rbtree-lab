#include "rbtree.h"
#include "rbtree.c"
#include <stdio.h>

int main(int argc, char *argv[]) {

    // rbtree *p = new_rbtree();

    // rbtree_insert(p, 3);
    // rbtree_insert(p, 2);
    // node_t *temp6 = rbtree_insert(p, 5);
    // rbtree_insert(p, 1);

    // node_t *temp = rbtree_max(p);
    // node_t *temp2 = rbtree_min(p);
    // node_t *temp3 = rbtree_find(p,5);
    // printf("%d\n", temp->key);
    // printf("%d\n", temp2->key);

    // if (temp3 == temp6){
    //     printf("YES");
    // }
    // printf("%d\n",p->root->key);
    // printf("%d\n",p->root->left->key);
    // printf("%d\n",p->root->right->key);
    // printf("%d\n",p->root->left->left->key);

    // printf("%d\n",p->root->color);
    // printf("%d\n",p->root->left->color);
    // printf("%d\n",p->root->right->color);
    // printf("%d\n",p->root->left->left->color);

    rbtree *t = new_rbtree();
    rbtree_insert(t, 8);
    rbtree_insert(t, 7);
    rbtree_insert(t, 9);
    rbtree_insert(t, 3);
    rbtree_insert(t, 6);
    rbtree_insert(t, 4);
    rbtree_insert(t, 5);
    rbtree_insert(t, 12);
    if(t->root != t->nil){
    printf("%d\n", t->root->key); // 8
    printf("%d\n", t->root->left->key); // 6
    printf("%d\n", t->root->right->key); // 9
    printf("%d\n", t->root->right->left->key); // 0
    printf("%d\n", t->root->right->right->key); //12
    }
    else{
        printf("확인");
    }
}