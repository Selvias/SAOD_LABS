#include "avltree.hpp"

  ////////////////////////////////////////////////
 ///////////ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ//////////////
////////////////////////////////////////////////
int height(avl *tree) {
    return tree ? tree->height : -1;
}

void fixheight(avl *tree) {
    int h1 = height(tree->left);
    int h2 = height(tree->right);
    tree->height = (h1 > h2 ? h1 : h2) + 1;
}

int bfactor(avl *tree) {
    return height(tree->left) - height(tree->right);
}

avl *fixbalance(avl *tree) {
    fixheight(tree);
    //Перекос влево
    if (bfactor(tree) == 2)
    {
        if (bfactor(tree->left) == -1)
            return avltree_lr_rotate(tree);
        return avltree_right_rotate(tree);
    }
    //Перекос вправо
    if (bfactor(tree) == -2)
    {
        if (bfactor(tree->right) == 1)
            return avltree_rl_rotate(tree);
        return avltree_left_rotate(tree);
    }
    return tree;
}
  ///////////////////////////////////////////////
 //////////////////ПОВОРОТЫ/////////////////////
///////////////////////////////////////////////
avl *avltree_rl_rotate(avl *P) {
    P->right = avltree_right_rotate(P->right);
    return avltree_left_rotate(P);
}

avl *avltree_lr_rotate(avl *P) {
    P->left = avltree_left_rotate(P->left);
    return avltree_right_rotate(P);
}

avl *avltree_left_rotate(avl *tree) {
    avl *right = tree->right;
    tree->right = right->left;
    right->left = tree;
    fixheight(tree);
    fixheight(right);
    return right;
}

avl *avltree_right_rotate(avl *tree) {
    avl *left = tree->left;
    tree->left = left->right;
    left->right = tree;
    fixheight(tree);
    fixheight(left);
    return left;
}

/////////////////////////////////////////////////
/////СОЗДАНИЕ И ДОБАВЛЕНИЕ УЗЛА AVL ДЕРЕВА///////
/////////////////////////////////////////////////
avl *create_tree(int key, char *value) {
    avl *node = new avl;
    if (node != NULL)
    {
        node->key = key;
        node->value = new char [10];
        strcpy(node->value, value);
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }
    return node;
}

avl *avltree_add(avl *tree, int key, char *value) {
    if (tree == NULL)
        return create_tree(key, value);

    if (key < tree->key)
    {
        tree->left = avltree_add(tree->left, key, value);
        if (bfactor(tree) == 2)
        {
            if (key < tree->left->key)
                tree = avltree_right_rotate(tree);
            else
                tree = avltree_lr_rotate(tree);
        }
    }
    else if (key > tree->key)
    {
        tree->right = avltree_add(tree->right, key, value);
        if (bfactor(tree) == -2)
        {
            if (key > tree->right->key)
                tree = avltree_left_rotate(tree);
            else
                tree = avltree_rl_rotate(tree);
        }
    }
    fixheight(tree);
    return tree;
}

 /////////////////////////////////////////////////
 ///////////////ПОИСК В AVL ДЕРЕВЕ///////////////
////////////////////////////////////////////////
avl *lookup(avl *tree, int key) {
    while (tree != NULL)
    {
        if (key == tree->key)
            return tree;
        else if (key < tree->key)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

avl* min(avl* tree) {
	return tree->left ? min(tree->left) : tree;
}

avl* max(avl* tree) {
	return tree->right ? max(tree->right) : tree;
}

  /////////////////////////////////////////////////
 //////////////////Удаление узла//////////////////
/////////////////////////////////////////////////

//Возвращает минимальный узел для правого поддерева, для последующего удаления
avl *mindel(avl *tree, avl *parent = NULL) {
    //Если справа от мина есть элемент (1 элемент)
    if (tree->left == NULL)
        return tree->right;
    tree->left = mindel(tree->left);
    return fixbalance(tree);
}

avl *delnode(avl *tree, int key) {
    if (tree != NULL)
    {
        if (key > tree->key)
            tree->right = delnode(tree->right, key);
        else if (key < tree->key)
            tree->left = delnode(tree->left, key);
        else if (key == tree->key)
        {
                avl * left = tree->left;
                avl *right = tree->right;
                delete tree;
                
                //Если правого поддерева нет
                if (right == NULL)
                    return left;
                //Если есть правое поддерево (необходимо найти в нём минимальный элемент)
                avl *rightmin = min(right);
                rightmin->right = mindel(right);
                rightmin->left = left;
                return fixbalance(rightmin);
        }
        return fixbalance(tree);
    }
    return tree;
}

//Полное удаление АВЛ дерева
void free_avl_tree(avl *tree) {
    if (tree == NULL)
        return;
    
    free_avl_tree(tree->left);
    free_avl_tree(tree->right);
    delete [] tree->value;
    delete tree;
}

  ////////////////////////////////////////////////
 ////////////////ВЫВОД AVL ДЕРЕВА////////////////
////////////////////////////////////////////////

void tree_out(avl* tree,int level)
{
    int i{0};
    if(tree != NULL)
    {
        tree_out(tree->right,level+3);
        for(;i < level;i++)
        {
            std::cout << "  ";

        }
        // printf("%3d\n", tree->key);
        std::cout << tree->key << "(" << level << ")\n";
        tree_out(tree->left, level+3);
    }
}
