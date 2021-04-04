#pragma once

typedef struct bstree{

    int value;

    bstree *left;
    bstree *right;

    char *key; // Пятизначный ключ
};

bstree *bstree_create(char *key, int value);
void bstree_add(bstree *tree, char *key, int value);
bstree *bstree_lookup(bstree *tree, char *key);
bstree *bstree_delete(bstree *tree, char *key);
bstree *bstree_min(bstree *tree);
bstree *bstree_max(bstree *tree);