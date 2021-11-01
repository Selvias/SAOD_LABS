#include <iostream>
#include <cstring>
#include <ctime>

struct avl {
    char *key;
    int value;

    int height;
    avl *left;
    avl *right;
};

void free_avl_tree(avl *tree);

avl *lookup(avl *tree, char *key);

avl *create_tree(char *key, int value);

int avltree_height(avl *tree);

int avltree_balance(avl *tree);

avl *avltree_rl_rotate(avl *P);

avl *avltree_lr_rotate(avl *P);

int maxheight(int h1, int h2);

avl *avltree_left_rotate(avl *tree);

avl *avltree_right_rotate(avl *tree);

avl *avltree_add(avl *tree, char *key, int value);

avl *node_deletion(avl *tree, char *key);

void tree_out(avl* tree,int level);


//Дополнительные функции
avl *fixbalance(avl *tree);
//Поиск минимального элемента
avl *min(avl *tree);
avl *delnode(avl *tree, int key);
//Возвращает минимальный узел для правого поддерева, для последующего удаления
avl *mindel(avl *tree);