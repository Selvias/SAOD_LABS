#include <iostream>
#include <cstring>
#include <ctime>

struct avl {
    char key;
    void *value;

    int height;
    avl *left;
    avl *right;
};

void free_avl_tree(avl *tree);

int avltree_height(avl *tree);

int avltree_balance(avl *tree);

avl *avltree_rl_rotate(avl *P);

avl *avltree_lr_rotate(avl *P);

int maxheight(int h1, int h2);

avl *avltree_left_rotate(avl *tree);

avl *avltree_right_rotate(avl *tree);

avl *node_deletion(avl *tree, char key);

int tree_out(avl* tree,int level);


//Дополнительные функции
avl *fixbalance(avl *tree);
//Поиск минимального элемента
avl *min(avl *tree);
//Поиск максимального элемента
avl* max(avl* tree);
//Удаление узла из дерева
avl *delnode(avl *tree, char key);
//Возвращает минимальный узел для правого поддерева, для последующего удаления
avl *mindel(avl *tree);


/////////////////////////////////////////////////
/////СОЗДАНИЕ И ДОБАВЛЕНИЕ УЗЛА AVL ДЕРЕВА///////
/////////////////////////////////////////////////

avl *avltree_add(avl *tree, char key, void *value);

avl *create_tree(char key, void *value);

/////////////////////////////////////////////////
//*************ПОИСК В AVL ДЕРЕВЕ**************//
/////////////////////////////////////////////////
avl *lookup(avl *tree, char key);