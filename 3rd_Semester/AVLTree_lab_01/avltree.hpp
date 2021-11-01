#include <iostream>
#include <cstring>
#include <ctime>

struct avl_node {
    int key;
    char *value;

    int height;
    avl_node *left;
    avl_node *right;
};

void free_avl_tree(avl_node *tree);

avl_node *lookup(avl_node *tree, int key);

avl_node *create_tree(int key, char *value);

int avltree_height(avl_node *tree);

int avltree_balance(avl_node *tree);

avl_node *avltree_rl_rotate(avl_node *P);

avl_node *avltree_lr_rotate(avl_node *P);

int maxheight(int h1, int h2);

avl_node *avltree_left_rotate(avl_node *tree);

avl_node *avltree_right_rotate(avl_node *tree);

avl_node *avltree_add(avl_node *tree, int key, char *value);

avl_node *node_deletion(avl_node *tree, int key);

void tree_out(avl_node* tree,int level);


//Дополнительные функции
avl_node *fixbalance(avl_node *tree);
//Поиск минимального элемента
avl_node *min(avl_node *tree);
avl_node *delnode(avl_node *tree, int key);
//Возвращает минимальный узел для правого поддерева, для последующего удаления
avl_node *mindel(avl_node *tree);