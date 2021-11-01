#include <iostream>
#include <cstring>
#include <cstdlib>
#include "hashtab.hpp"

unsigned int hashtab_hash (char *key) {
    unsigned int h = 0, hash_mult = 31;

    while (*key)
        h = h*hash_mult + (unsigned int)*key++; //Фишки постфиксного инкремента (сначала берёт значение из ячейки массива (строки), затем "перемещает указатель на следующий элемент массива")
    
    return h % HASHTAB_SIZE; //Деление необходимо для того,чтобы значение было уместным в рамках массива

}

void hashtab_init (struct hashlist **hashtab) {
    for (int i = 0; i < HASHTAB_SIZE; i++)
        hashtab[i] = NULL;
}

void hashtab_add (struct hashlist **hashtab, char *key, int value) {
    struct hashlist *node;

    int index = hashtab_hash (key);
    node = (struct hashlist*)malloc(sizeof(*node));

    if (node != NULL)
    {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];

        hashtab[index] = node;
    }
}
struct hashlist *hashtab_lookup (struct hashlist **hashtab, char *key) {
    struct hashlist *node;

    int index = hashtab_hash(key);

    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (strcmp(node->key, key) == 0)
            return node;
    }
    return NULL;
}

void hashtab_delete (struct hashlist **hashtab, char *key) {
    struct hashlist *node, *prev = NULL;
    int index = hashtab_hash(key);

    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (strcmp(node->key, key) == 0)
        {
            if (prev == NULL)
                hashtab[index] = node->next;
            else
                prev->next = node->next;
            free(node);
            return;
        }
        prev = node;
    }
}