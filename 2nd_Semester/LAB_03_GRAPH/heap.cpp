#include "heap.hpp"

heap *heap_create(int maxsize) {
    heap *h;
    h = (heap *)malloc(sizeof(*h));

    if (h != NULL) {
        h->maxsize = maxsize;
        h->nnodes = 0;
        h->nodes = (heapnode*)malloc(sizeof(*h->nodes)*(maxsize + 1));
        h->pos = (int *)calloc((maxsize + 1), sizeof(int));
    
        if (h->nodes == NULL) {
            free(h);
            return NULL;
        }
    }
    return h;
}

void heap_free(heap *h) {
    free(h->pos);
    free(h->nodes);
    free(h);
}

void heap_swap(heapnode *a, heapnode *b, heap *h) {
    int t = h->pos[a->value];
    h->pos[a->value] = h->pos[b->value];
    h->pos[b->value] = t;

    heapnode temp = *a;
    *a = *b;
    *b = temp;
    //cout << "A "<< a->value << " B " << b->value << "\n";
}

heapnode *heap_min(heap *h) {
    if (h->nnodes == 0)
        return NULL;
    return &h->nodes[1];
}

int heap_insert(heap *h, int key, int value) {
    if (h->nnodes >= h->maxsize)
        return -1;

    h->nnodes++;
    h->nodes[h->nnodes].key = key;
    h->nodes[h->nnodes].value = value;
    h->pos[value] = h->nnodes;

    for (int i = h->nnodes; i > 1 && h->nodes[i].key < h->nodes[i/2].key; i = i / 2) 
    {
        heap_swap(&h->nodes[i], &h->nodes[i / 2], h);
    }
    return 0;
}

heapnode heap_ext_min(heap *h) {
    if (h->nnodes == 0)
        return (heapnode){0, 0};

    heapnode minnode = h->nodes[1];
    h->nodes[1] = h->nodes[h->nnodes];
    h->pos[h->nodes[h->nnodes].value] = 1; //Т.к. происходит перестановка узлов, то соответ-но последний становится первым                       
    h->nnodes--;                           //В противном случае останутся 2 одинаковых элемента
    heap_heapify(h, 1);

    return minnode;
}

void heap_heapify(heap *h, int index) {
    while (1)
    {
        int left = 2 * index;
        int right = 2 * index + 1;
        int smallest = index;

        if (left < h->nnodes && h->nodes[left].key < h->nodes[smallest].key) {
            smallest = left;
        }
        if (right < h->nnodes && h->nodes[right].key < h->nodes[smallest].key) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }

        heap_swap(&h->nodes[index], &h->nodes[smallest], h);
        index = smallest;
    }
}

int heap_decrease_key(heap *h, int index, int newkey) {
    
    index = h->pos[index];                      //Определение "действительного индекса"

    if (h->nodes[index].key <= newkey)
        return -1;

    h->nodes[index].key = newkey;

    while (index > 1 && h->nodes[index].key < h->nodes[index / 2].key) 
    {
        heap_swap(&h->nodes[index], &h->nodes[index / 2], h);
        index = index / 2;
    }
    return index;
}