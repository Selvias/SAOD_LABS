#include "queue.hpp"

graph *graph_create(int vertexes);
void graph_init(graph *g);
int **matrix_create(graph *g);
void matrix_init(int **mx, int size);
void matrix_print(int **matrix, int size_m);
void matrix_filling(int **matrix_to_fill, graph *g);

int main () {

    graph *g;
    g = graph_create(3);

    int **matrix = (int**)malloc(g->vertexes*sizeof(int*));

    for (int t = 0; t < g->vertexes; t++) {
        for (int k = 0; k < g->vertexes; k++) {
            if (t != k)
                graph_set_edge_weight(g, t, k, rand() % 100 + 1);
        }
    }

    cout << "DFS : \n";
    graph_DFS(g, 2);
    graph_print(g);

    matrix = (matrix_create(g));
    matrix_filling(matrix, g);
    // matrix_print(matrix, g->vertexes); //ВЫВОД МАТРИЦЫ СМЕЖНОСТИ

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

//Обход графа в глубину Deep First Search (рекурсивный алгоритм)
void graph_DFS(graph *g, int v) {
    int i;

    g->visited[v - 1] = 1;
    cout << "Vertex : " << v << "\n";

    for (i = 0; i < g->vertexes; i++) 
    {
        if (g->m[v - 1][i] > 0 && g->visited[i] == 0)
            graph_DFS(g, i + 1);
    }
}

void graph_print(graph *g) {
    for (int i = 0; i < g->vertexes; i++)
    {
        for (int j = 0; j < g->vertexes; j++)
        {
            cout << g->m[i][j] << " ";
            if (j == g->vertexes - 1)
                cout << "\n";
        }
    }
}

int **matrix_create(graph *g) {

    int m_size = (g->vertexes)*(g->vertexes);
    int **mx;

    mx = (int**)malloc(m_size*sizeof(int*));

    for (int i = 0; i < m_size; i++) { 
        mx[i] = (int*)malloc(m_size*sizeof(int)); 
    }

    matrix_init(mx, m_size);

    return mx;
}

void matrix_init(int **mx, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mx[i][j] = 0;
        }
    }
}

void matrix_print(int **matrix, int size_m) {
    for (int i = 0; i < (size_m)*(size_m); i++) {
        for (int j = 0; j < (size_m)*(size_m); j++) {
            cout << matrix[i][j] << "  ";
            if (j == (size_m)*(size_m) - 1)
                cout << "\n";
        }
    }
}

void matrix_filling(int **matrix_to_fill, graph *g) {

    int size = (g->vertexes);

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            //Заполнение матрицы смежности для внутренних вершин графа-решётки
            if (i > 0 && i < size - 1 && j > 0 && j < size - 1)
            {
                matrix_to_fill[i*size + j][i*size + (j - 1)] = g->m[i][j - 1];
                matrix_to_fill[i*size + j][i*size + (j + 1)] = g->m[i][j + 1];
                matrix_to_fill[i*size + j][(i - 1)*size + j] = g->m[i - 1][j];
                matrix_to_fill[i*size + j][(i + 1)*size + j] = g->m[i + 1][j];
            } else if (i == 0 && j == 0) {
            //Заполнение матрицы смежности для верхнего левого угла
                matrix_to_fill[i*size + j][i*size + (j + 1)] = g->m[i][j + 1];
                matrix_to_fill[i*size + j][(i + 1)*size + j] = g->m[i + 1][j];
            } else if (i == size - 1 && j == size - 1) {
            //Заполнение матрицы смежности для правого нижнего угла
                matrix_to_fill[i*size + j][i*size + (j - 1)] = g->m[i][j - 1];
                matrix_to_fill[i*size + j][(i - 1)*size + j] = g->m[i - 1][j];
            }else if (i == 0 && j == size - 1) {
            //Заполнение матрицы смежности для правого верхнего угла
                matrix_to_fill[i*size + j][i*size + (j - 1)] = g->m[i][j - 1];
                matrix_to_fill[i*size + j][(i + 1)*size + j] = g->m[i + 1][j];
            } else if (i == size - 1 && j == 0) {
            //Заполнение матрицы смежности для левого нижнего угла
                matrix_to_fill[i*size + j][i*size + (j + 1)] = g->m[i][j + 1];
                matrix_to_fill[i*size + j][(i - 1)*size + j] = g->m[i - 1][j];
            } else if (i > 0 && i < size - 1 && j == 0) {
            //Заполнение матрицы смежности для левой грани
                matrix_to_fill[i*size + j][i*size + (j + 1)] = g->m[i][j + 1];
                matrix_to_fill[i*size + j][(i - 1)*size + j] = g->m[i - 1][j];
                matrix_to_fill[i*size + j][(i + 1)*size + j] = g->m[i + 1][j];
            } else if (i > 0 && i < size - 1 && j == size - 1) {
            //Заполнение матрицы смежности для правой грани
                matrix_to_fill[i*size + j][i*size + (j - 1)] = g->m[i][j - 1];
                matrix_to_fill[i*size + j][(i - 1)*size + j] = g->m[i - 1][j];
                matrix_to_fill[i*size + j][(i + 1)*size + j] = g->m[i + 1][j];
            } else if (i == 0 && j > 0 && j < size - 1) {
            //Заполнение матрицы смежности для верхней грани
                matrix_to_fill[i*size + j][i*size + (j - 1)] = g->m[i][j - 1];
                matrix_to_fill[i*size + j][i*size + (j + 1)] = g->m[i][j + 1];
                matrix_to_fill[i*size + j][(i + 1)*size + j] = g->m[i + 1][j];      
            } else if (i == size - 1 && j > 0 && j < size - 1) {
            //Заполнение матрицы смежности для нижней грани
                matrix_to_fill[i*size + j][i*size + (j - 1)] = g->m[i][j - 1];
                matrix_to_fill[i*size + j][i*size + (j + 1)] = g->m[i][j + 1];
                matrix_to_fill[i*size + j][(i - 1)*size + j] = g->m[i - 1][j];
            }
        }
    }
}