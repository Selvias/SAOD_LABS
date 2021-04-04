#include "queue.hpp"

graph *graph_create(int vertexes);
void graph_init(graph *g);

int main () {

    graph *g;
    g = graph_create(10);

    graph_set_edge_weight(g, 1, 2, 1);
    graph_set_edge_weight(g, 1, 4, 1);
    graph_set_edge_weight(g, 5, 4, 1);
    graph_set_edge_weight(g, 6, 4, 1);
    graph_set_edge_weight(g, 3, 4, 1);

    cout << "DFS : \n";
    graph_DFS(g, 2);
    graph_print(g);

    graph_free(g);

    return 0;
}

//Создание графа (выделение памяти под  поля графа и саму структуру)
graph *graph_create(int vertexes) {

    graph *g = NULL;
    g = (graph*)malloc(sizeof(g));

    g->vertexes = vertexes;
    
    g->m = (int**)malloc(vertexes*sizeof(int*));
    for (int i = 0; i < vertexes; i++) { g->m[i] = (int*)malloc(vertexes*sizeof(int)); }
    
    g->visited = (int*)malloc(vertexes*sizeof(int));

    graph_init(g);

    return g;
}


//Инициализация графа нулями
void graph_init(graph *g) {
    int i, j;

    for (i = 0; i < g->vertexes; i++) 
    {
        g->visited[i] = 0;
        for (j = 0; j < g->vertexes; j++)
        {
            g->m[i][j] = 0;
        }
    }
}

//Освобождение памяяти из под полей графа и самой структуры
void graph_free (graph *g) {
    free(g->m);
    free(g->visited);
    free(g);
}

//Установление веса ребра графа
void graph_set_edge_weight(graph *g, int i, int j, int w) {
    g->m[i][j] = w;
    g->m[j][i] = w;

}

int graph_get_edge_weight(graph *g, int i, int j) {
    return g->m[i][j];
}

//Обход графа в глубину Deep ... Search (рекурсивный алгоритм)
void graph_DFS(graph *g, int v) {
    int i;

    g->visited[v -1] = 1;
    cout << "Vertex : " << v << "\n";

    for (i = 0; i < g->vertexes; i++) 
    {
        if (g->m[v][i] > 0 && g->visited[i] == 0)
            graph_DFS(g, i + 1);
    }
}

void graph_print(graph *g) {
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << g->m[i][j] << " ";
            if (j == 9)
                cout << "\n";
        }
    }
}