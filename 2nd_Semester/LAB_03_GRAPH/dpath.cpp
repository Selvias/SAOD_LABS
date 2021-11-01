#include "queue.hpp"
#include "heap.hpp"

void spd (graph *g, heap *h, int src, int *prev) {

    //Количество элементов для графа-решётки
    // int els = (g->vertexes)*(g->vertexes);

    //Количество элементов для связного графа
    int elem = g->vertexes;

    //Массив посещённых вершин
    short int visited[elem + 1] = {0};

    int way[elem + 1];

    //Инициаализация бинарной кучи и массива путей prev для всех вершин, кроме исходной
    for (int i = 1; i <= elem; i++)
    {
        if (i != src)
        {
            way[i] = INF;
            prev[i] = -1;
            heap_insert(h, INF, i);
        }
    }

    way[src] = 0;
    prev[src] = -1;
    heap_insert(h, 0 , src);

    //Алгоритм Дейкстры
    for (int i = 1; i < elem; i++)
    {
        heapnode minnode = heap_ext_min(h);
        visited[minnode.value] = 1;
        printf("MINNODE : %d, KEY : %d\n", minnode.value, minnode.key);

        for (int j = 1; j <= elem; j++)
        {
                if (visited[h->nodes[j].value] != 1 && (minnode.key + g->m[minnode.value - 1][j - 1]) < way[j])
                {
                    way[j] = (minnode.key + g->m[minnode.value - 1][j - 1]);
                    heap_decrease_key(h, j, way[j]);
                    heap_heapify(h, 1);
                    prev[j] = minnode.value;
                }
        }
    }
    printf("WAY ARR : ");
    for(int a = 1; a <= elem; a++)
        printf("%d ", way[a]);

    printf("PISOS\n");
    int dest = 2;
    for (int y = 1; y <= elem; y++) {
        printf("%d ", (prev)[y]);
    }
    recovery(g, src, dest, prev);
}

void spd_sharp (graph *gt, heap *hg, int src, int *prev, int **sharp) {

    //Количество элементов для связного графа
    int elem = (gt->vertexes)*(gt->vertexes);

    //Массив посещённых вершин
    short int visited[elem + 1] = {0};

    unsigned int way[elem + 1];

    //Инициаализация бинарной кучи и массива путей prev для всех вершин, кроме исходной
    for (int i = 1; i <= elem; i++)
    {
        if (i != src)
        {
            // h->nodes[i].key = INF;
            way[i] = INF;
            prev[i] = -1;
            heap_insert(hg, INF, i);
        }
    }

    way[src] = 0;
    prev[src] = -1;
    heap_insert(hg, 0 , src);

    for (int i = 1; i < elem; i++)
    {
        heapnode minnode = heap_ext_min(hg);
        visited[minnode.value] = 1;
        //printf("MINNODE : %d, KEY : %d\n", minnode.value, minnode.key);

        for (int j = 1; j <= elem; j++)
        {
                if (sharp[minnode.value - 1][j - 1] != 0 && ((unsigned int)minnode.key + (unsigned int)sharp[minnode.value - 1][j - 1]) < way[j])
                {
                    way[j] = (minnode.key + sharp[minnode.value - 1][j - 1]);
                    heap_decrease_key(hg, j, way[j]);
                    //heap_heapify(hg, 1);
                    prev[j] = minnode.value;
                }
        }
    }
    printf("WAY ARR : ");
    for(int a = 1; a <= elem; a++)
    {
        if (way[a] != INF)
        {
            printf("%d ", way[a]);
        } else {
            way[a] = -1;
            printf("%d ", way[a]);
        }
    }

    printf("PISOS\n");
    int dest = 2;
    for (int y = 1; y <= elem; y++) {
        printf("%d ", (prev)[y]);
    }
    recovery(gt, src, dest, prev);
}

void recovery(graph *g, int src, int dst, int *prev) {
    int i = dst;
    int pl = 1;

    while (i != src && i <= g->vertexes)
    {
        pl = pl + 1;
        i = prev[i];
    }

    int j = 0;
    i = dst;
    int path[pl + 1] = {0};
    path[pl] = dst;

    while (i != src) {
        i = prev[i];
        path[pl - j - 1] = i;
        j++;
        // i = prev[i];
    }

    printf("PATH RECOVERY : ");
    for (int k = 1; k <= pl; k++) {
        printf("%d ", path[k]);
    }
    printf("\n");

    printf("PATHLEN : %d\n", pl);
}