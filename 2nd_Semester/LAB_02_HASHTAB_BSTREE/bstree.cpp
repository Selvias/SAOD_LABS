#include <iostream>
#include <cstdlib>
#include <cstring>
#include "bstree.hpp"

using namespace std;

bstree *bstree_create(char *key, int value) {

    bstree *node;

    node = (bstree*)malloc(sizeof(*node));

    node->key  = (char*)malloc(21*sizeof(char));

    if (node != NULL)
    {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void bstree_add(bstree *tree, char *key, int value) {
    if (tree == NULL)
        return;

    bstree *parent, *new_node;

    while (tree != NULL)
    {
        parent = tree;

        if (strcmp(key, tree->key)< 0){
            tree = tree->left;
        } else if(strcmp(key, tree->key)> 0) {
            tree = tree->right;
        } else 
            return;
    }

    new_node = bstree_create(key, value);

    if (strcmp(key, parent->key)< 0)
        parent->left = new_node;
    else
        parent->right = new_node;
}

bstree *bstree_lookup(bstree *tree, char *key) {
    while (tree != NULL)
    {
        if(strcmp(key, tree->key) == 0)
        {
            return tree;
        } else if (strcmp(key, tree->key) < 0) {
            tree = tree->left;
        } else  
            tree = tree->right;
    }
    if (tree->key != key) 
    {
        return NULL;
    } else 
        return tree;
}

bstree *bstree_min(bstree *tree) {

    if (tree == NULL)
        return NULL;

    while (tree->left != NULL)
        tree = tree->left;
    
    return tree;
    
}

bstree *bstree_max(bstree *tree) {

    if (tree == NULL)
        return NULL;

    while (tree->right != NULL)
        tree = tree->right;

    return tree;
}

bstree *bstree_delete(bstree *tree, char *key) {
    
    bstree *node = bstree_lookup(tree, key);
    cout << "To del " << node->value << "\n";
    static bstree *parent = tree;

    while ((parent->left != node) && (parent->right != node))    //Поиск родительского элемента
    {
        if (parent->left == node || parent->right == node)
        if (strcmp(node->key, parent->key) > 0)
        {
            parent = parent->right;
        } else {
            parent = parent->left;
        } else
            break;
    }

    if (node->left == NULL && node->right == NULL)        // Нет потомков
    {
        if (strcmp(node->key, parent->key) > 0)
        {
            parent->right = NULL;
        } else 
            parent->left = NULL;

        free(node);

    } else if (node->left != NULL && node->right == NULL) { // 1 потомок
        if (strcmp(node->key, parent->key) > 0) {
            parent->right = node->left;
            free(node);
        } else if (strcmp(node->key, parent->key) < 0) {
            parent->left = node->left;
            free(node);
        }
    } else if(node->right != NULL && node->left == NULL) {
        if (strcmp(node->key, parent->key) > 0) {
            parent->right = node->right;
            free(node);
        } else if (strcmp(node->key, parent->key) < 0) {
           parent->left = node->right; 
           free(node);
        }
    } else if (node->left != NULL && node->right != NULL) { // 2 потомка
            static bstree *min_right = bstree_min(node->right);
            static bstree *temp = node;
            node = min_right;
            min_right = temp;
            bstree_delete(tree, key);
    }
    return tree;
}