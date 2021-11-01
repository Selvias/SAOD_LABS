#pragma once
#include <iostream>

using namespace std;

typedef struct heapnode {
    int key;
    int value;
} Heap_Alias;

typedef struct heap {
    int maxsize;
    int nnodes;
    heapnode *nodes;
    int *pos;
} HP_ALIAS;

heap *heap_create(int maxsize);
void heap_free(heap *h);
void heap_swap(heapnode *a, heapnode *b, heap *h);
heapnode *heap_min(heap *h);
int heap_insert(heap *h, int key, int value);
heapnode heap_ext_min(heap *h);
void heap_heapify(heap *h, int index);
int heap_decrease_key(heap *h, int index, int newkey);
void build_min_heap(int *arr, int n);