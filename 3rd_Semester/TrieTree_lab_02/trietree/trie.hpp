#pragma once
#include "avl/avltree.hpp"

struct trie {
    int value;
    //Если 1 - значит такой ключ существует (не является только частью какого-то ключа)
    //Если 0 - такого ключа нет, является подстрокой какого-то ключа
    bool isKey;
    //Множество символов алфавита для i-й ноды
    avl *tree;
};

trie *trieCreate() {
    trie *node = new trie;
    if (node == nullptr)
        return nullptr;
    node->isKey = false;
    node->value = 0;
    node->tree = nullptr;
    return node;
}

trie *trieInsert(trie *root, char *key, int value) {
    trie *node = root, *list;
    //Пока не достигнут конец ключа
    for (int i = 0; key[i] != '\0'; i++)
    {
        avl *anode = lookup(node->tree, key[i]);
        //Если i-й уровень trie tree не содержит i-го символа ключа
        if (anode == nullptr)
        {
            node->tree = avltree_add(node->tree, key[i], (list = trieCreate()));
            node = list;
        }
        else
            node = (trie*)anode->value;
    }
    node->value = value;
    node->isKey = true;
    return node;
}

trie *trieLookup(trie *root, char *key) {
    trie *node = root;
    for (; *key != '\0'; key++)
    {
        avl *anode = lookup(node->tree, *key);
        if (anode == nullptr)
            return nullptr;
        else
            node = (trie *)anode->value; 
    }
    if (node->isKey == true)
        return node;
    else
        return nullptr;
}

trie *trieLookup2(trie *root, char key) {
    trie *node = root;
    avl *anode = lookup(node->tree, key);
    if (anode == nullptr)
        return nullptr;
    else
        node = (trie *)anode->value; 
    return node;
}

trie *trieDeletion(trie *root, char *key, trie *prev = nullptr, int i = 0) {
    trie *current = root;
    //std::cout << i << std::endl;
    //Если прошли по дереву и нашли ключевой узел trie tree
    //Выход из рекурсивного алгоритма удаления
    if (key[i] == '\0')
    {
        std::cout << "ENDLINE\n";
        //Если узел листовой
        if (current->tree == nullptr)
        {
            delete current;
            delnode(prev->tree, key[i - 1]);
            return prev;
        }
        //Если узел не листовой или такого улюча нет
        else if (current->tree != nullptr || current->isKey == false)
        {
            current->isKey = false;
            //Возвращает узел, до которого дошёл алгоритм поиска
            return current;
        }
    }
    else if (key[i] != '\0')
    {
        if ((current = trieLookup2(current, key[i])))
        {
            i+=1;
            //return trieDeletion(current, key, root, i);
            trieDeletion(current, key, root, i);
        }
        else
            //Такого ключа нет
            return nullptr;
        //
    }
    //Удаление по ходу сворачивания дерева рекурсивных вызовов
    if (current->isKey == false && current->tree == nullptr)
        delete current;

    return prev;
}

void triePrint(trie *root, int level = 0);

int tree_out(avl* tree, int level = 0)
{
    if(tree != NULL)
    {
        int t = tree_out(tree->left,level);
        if (t == level)
        {
            std::cout << "\n";
            if (level != 0)
                for(int i = 0;i < level;i++)
                {
                    std::cout << "  ";
                }
        }
        int d = tree_out(tree->right,level);
        if (d == level)
        {
            
            std::cout << "\n";
            if (level != 0)
            {
                for(int i = 0 ;i < level;i++)
                    std::cout << "  ";
            }
        }
        // // std::cout << level;
        std::cout << (char)tree->key << " ";
        triePrint((trie *)(tree->value), level+1);
        return level;
    }
    return -1;
}

void triePrint(trie *root, int level) {
    trie *node = root;
    tree_out(node->tree, level);
}