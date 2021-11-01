#include "avltree.hpp"

void free_avl_tree(avl *tree) {
    if (tree == NULL)
        return;
    
    free_avl_tree(tree->left);
    free_avl_tree(tree->right);
    delete tree;
}

avl *lookup(avl *tree, char *key) {
    while (tree != NULL)
    {
        if (strcmp(key, tree->key) == 0)
            return tree;
        else if (strcmp(key, tree->key) > 0)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

avl *create_tree(char *key, int value) {
    avl *node = new avl;
    if (node != NULL)
    {
        // node->key = key;
        // node->value = new char [10];
        node->key = new char [70];
        strcpy(node->key, key);
        node->value = value;
        //strcpy(node->value, value);
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }
    return node;
}


int avltree_height(avl *tree) {
    return (tree != NULL) ? tree->height : -1;
}

int avltree_balance(avl *tree) {
    return avltree_height(tree->left) - avltree_height(tree->right);
}

int maxheight(int a, int b) {
    return (a >= b) ? a : b;
}

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
    right->left =tree;

    tree->height = 1 + maxheight(avltree_height(tree->left), avltree_height(tree->right));
    right->height = 1 + maxheight(avltree_height(right->right), tree->height);

    return right;
}

avl *avltree_right_rotate(avl *tree) {
    avl *left = tree->left;
    tree->left = left->right;
    left->right = tree;

    tree->height = 1 + maxheight(avltree_height(tree->left), avltree_height(tree->right));
    left->height = 1 + maxheight(avltree_height(left->left), tree->height);
    return left;
}

avl *fixbalance(avl *tree) {
    tree->height = 1 + maxheight(avltree_height(tree->left), avltree_height(tree->right));
    if (avltree_balance(tree) == 2)
    {
        if(avltree_balance(tree->right) < 0 )
			tree->right = avltree_right_rotate(tree->right);
		return avltree_left_rotate(tree);
    }
    if (avltree_balance(tree) == -2)
    {
        if(avltree_balance(tree->right) > 0 )
			tree->left = avltree_left_rotate(tree->left);
		return avltree_right_rotate(tree);
    }
    return tree;
}

avl* min(avl* tree) {
	return tree->left ? min(tree->left) : tree;
}
//Возвращает минимальный узел для правого поддерева, для последующего удаления
avl *mindel(avl *tree) {
    if (tree->left == NULL)
        return tree->right;
    tree->left = mindel(tree->left);
    return fixbalance(tree);
}

avl *delnode(avl *tree, char *key) {
    //Обработка случая, когда элемента нет в дереве
    if (tree != NULL)
    {
        if (strcmp(key, tree->key) < 0)
            tree->right = delnode(tree->right, key);
        else if (strcmp(key, tree->key) > 0)
            tree->left = delnode(tree->left, key);
        else if (strcmp(key, tree->key) == 0)
        {
            //Нет потомков
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

avl *avltree_add(avl *tree, char *key, int value) {
    if (tree == NULL)
        return create_tree(key, value);

    if (strcmp(key, tree->key) > 0)
    {
        tree->left = avltree_add(tree->left, key, value);
        if (avltree_height(tree->left) - avltree_height(tree->right) == 2)
        {
            if (strcmp(key, tree->left->key) > 0)
                tree = avltree_right_rotate(tree);
            else
                tree = avltree_lr_rotate(tree);
        }
    }
    else if (strcmp(key, tree->key) < 0)
    {
        tree->right = avltree_add(tree->right, key, value);
        if (avltree_height(tree->right) - avltree_height(tree->left) == 2)
        {
            if (strcmp(key, tree->right->key) < 0)
                tree = avltree_left_rotate(tree);
            else
                tree = avltree_rl_rotate(tree);
        }
    }
    tree->height = maxheight(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    return tree;
}

// avl_node *node_deletion(avl_node *tree, int key) {

// }

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
        printf("%3d\n", tree->value);
        tree_out(tree->left, level+3);
    }
}