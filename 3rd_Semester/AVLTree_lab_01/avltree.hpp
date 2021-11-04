#include <iostream>
#include <cstring>
#include <ctime>

struct avl {
    int key;
    char *value;

    int height;
    avl *left;
    avl *right;
};

void free_avl_tree(avl *tree);

avl *lookup(avl *tree, int key);

avl *create_tree(int key, char *value);

int height(avl *tree);

int bfactor(avl *tree);

avl *avltree_rl_rotate(avl *P);

avl *avltree_lr_rotate(avl *P);

int maxheight(int h1, int h2);

avl *avltree_left_rotate(avl *tree);

avl *avltree_right_rotate(avl *tree);

avl *avltree_add(avl *tree, int key, char *value);

avl *node_deletion(avl *tree, int key);

void tree_out(avl* tree,int level);


//Дополнительные функции
avl *fixbalance(avl *tree);
//Поиск минимального элемента
avl *min(avl *tree);
//Поиск максимального элемента
avl* max(avl* tree);
//Удаление узла из дерева
avl *delnode(avl *tree, int key);
//Возвращает минимальный узел для правого поддерева, для последующего удаления
avl *mindel(avl *tree, avl *parent);
