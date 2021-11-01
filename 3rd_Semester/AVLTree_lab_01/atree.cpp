#include "avltree.hpp"

void free_avl_tree(avl_node *tree) {
    if (tree == NULL)
        return;
    
    free_avl_tree(tree->left);
    free_avl_tree(tree->right);
    delete tree;
}

avl_node *lookup(avl_node *tree, int key) {
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

avl_node *create_tree(int key, char *value) {
    avl_node *node = new avl_node;
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


int avltree_height(avl_node *tree) {
    return (tree != NULL) ? tree->height : -1;
}

int avltree_balance(avl_node *tree) {
    return (avltree_height(tree->left) - avltree_height(tree->right));
}

int maxheight(int a, int b) {
    return (a >= b) ? a : b;
}

avl_node *avltree_rl_rotate(avl_node *P) {
    P->right = avltree_right_rotate(P->right);
    return avltree_left_rotate(P);
}

avl_node *avltree_lr_rotate(avl_node *P) {
    P->left = avltree_left_rotate(P->left);
    return avltree_right_rotate(P);
}

avl_node *avltree_left_rotate(avl_node *tree) {
    avl_node *right;

    right = tree->right;
    tree->right = right->left;
    right->left = tree;

    tree->height = maxheight(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    right->height = maxheight(avltree_height(right->right), tree->height) + 1;
    return right;
}

avl_node *avltree_right_rotate(avl_node *tree) {
    avl_node *left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;

    tree->height = maxheight(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    left->height = maxheight(avltree_height(left->left), tree->height) + 1;
    return left;
}

avl_node *fixbalance(avl_node *tree) {
    tree->height = 1 + maxheight(avltree_height(tree->left), avltree_height(tree->right));
    if (avltree_balance(tree) == 2)
    {
        if (avltree_balance(tree->right) < 0 )
			tree->right = avltree_right_rotate(tree->right);
		return avltree_left_rotate(tree);
    }
    if (avltree_balance(tree) == -2)
    {
        if(avltree_balance(tree->left) > 0 )
			tree->left = avltree_left_rotate(tree->left);
		return avltree_right_rotate(tree);
    }
    return tree;
}

avl_node* min(avl_node* tree) {
	return tree->left ? min(tree->left) : tree;
}
//Возвращает минимальный узел для правого поддерева, для последующего удаления
avl_node *mindel(avl_node *tree) {
    if (tree->left == NULL)
        return tree->right;
    tree->left = mindel(tree->left);
    return fixbalance(tree);
}

avl_node *delnode(avl_node *tree, int key) {
    //Обработка случая, когда элемента нет в дереве
    if (!tree)
        return nullptr;
    if (key < tree->key)
        tree->left = delnode(tree->left, key);
    else if (key > tree->key)
        tree->right = delnode(tree->right, key);
    else
    {
        //Нет потомков
        avl_node *left = tree->left;
        avl_node *right = tree->right;
        delete tree;
        
        //Если правого поддерева нет
        if (!right)
            return left;
        //Если есть правое поддерево (необходимо найти в нём минимальный элемент)
        avl_node *rightmin = min(right);
        rightmin->right = mindel(right);
        rightmin->left = left;
        return fixbalance(rightmin);
    }
    return fixbalance(tree);
}

avl_node *avltree_add(avl_node *tree, int key, char *value) {
    if (tree == NULL)
        return create_tree(key, value);

    if (key < tree->key)
    {
        tree->left = avltree_add(tree->left, key, value);
        if (avltree_height(tree->left) - avltree_height(tree->right) == 2)
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
        if (avltree_height(tree->right) - avltree_height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = avltree_left_rotate(tree);
            else
                tree = avltree_rl_rotate(tree);
        }
    }
    tree->height = maxheight(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    return tree;
}

void tree_out(avl_node* tree,int level)
{
    int i{0};
    if(tree != NULL)
    {
        tree_out(tree->right,level+3);
        for(;i < level;i++)
        {
            std::cout << "  ";

        }
        printf("%3d\n", tree->key);
        tree_out(tree->left, level+3);
    }
}