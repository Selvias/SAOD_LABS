#pragma once

#define HASHTAB_SIZE 200000

using namespace std;

struct hashlist {
    char *key;
    int value;
    struct hashlist *next;
};                  //В hash-массив можно записывать адрес на первую структуру связного списка (ключ-значение присвоить узлу связного списка,к которому можно также добавить указатель на следующий элемент с таким же хэшем)

static struct hashlist *hashtab[HASHTAB_SIZE];

unsigned int hashtab_hash (char *key);
void hashtab_init (struct hashlist **hashtab);
void hashtab_add (struct hashlist **hashtab, char *key, int value);
struct hashlist *hashtab_lookup (struct hashlist **hashtab, char *key);
void hashtab_delete (struct hashlist **hashtab, char *key);