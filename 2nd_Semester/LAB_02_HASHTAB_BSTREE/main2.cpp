#include <iostream>
#include <fstream>
#include <time.h>
#include "bstree.hpp"
#include "hashtab.hpp"

int main() {

    unsigned int i, cntr = 0;

    clock_t start;
    double time;

    static char *words = NULL;
    words = (char*)malloc(800*sizeof(char*));

    // static struct hashlist *hashtab[HASHTAB_SIZE];

    ifstream read;
    read.open("source.txt");

    while(read) {
        read.getline(&words[cntr], 15); //Функция ломается, когда встречает дефис в строке...WHY?
        cout << cntr << "\n";
        cout << &words[cntr] << "\n";
        cntr++;
    }

    read.close();

    bstree *tree, *node;

    cout << "RESULT : " << &words[50] << "\n";
    // printf("%p\n", words[2]);

    // tree = bstree_create(&words[0], 0);

    // for (i = 2; i < 400; i++) {
    //     bstree_add(tree, &words[i - 1], i - 1);
    //     cout << words[i] << "\n";

    //     if (i % 10 == 0)
    //     {
    //         start = clock();
    //         node = bstree_lookup(tree, &words[rand() % i-1]);

    //     start = clock() - start;

    //     time = (double)start / CLOCKS_PER_SEC;

    //     // cout << &words[i - 1] << "\n";
    //     printf("TIME : %.6f, N = %d\n", time, i - 1);
    //     }
    // }

    free(words);

    return 0;
}