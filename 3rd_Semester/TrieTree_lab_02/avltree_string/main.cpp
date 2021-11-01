#include "avltree.hpp"
#include <ctime>
#include <fstream>
#include <iomanip>

const unsigned int count = 200000;
const unsigned int delay = 20000;
const int loop{1000000};

int main()
{
    // srand(time(NULL));

    char *str = (char *)"stringtrtrtr";
    avl *root = create_tree(str, rand() % 100000);

    std::ifstream in("source.txt");

    for (int i = 1; i < int(count); i++)
    {
        char *s = new char [50];
        in.getline(s, 50);
        root = avltree_add(root,s, i);

        if (i % delay == 0)
        {
            clock_t start = clock();
            for (int j{0}; j < loop; j++)
                lookup(root, s);
            clock_t end = clock();
            std::cout << std::fixed << std::setprecision(8); 
            double t = double((double)(end - start) / CLOCKS_PER_SEC);
            std::cout << "Time (i = " << i << "," << s << ") : " << t << std::endl;
        }
    }   

    in.close();

    // tree_out(root, 0);

    return 0;
}
// #include "avltree.hpp"
// #include <ctime>
// #include <fstream>

// const int MAX{50000};

// int main()
// {
//     srand(time(NULL));
//     // clock_t start;
//     // double time;

//     char *str = (char *)"string";
//     avl *root = create_tree(str, rand() % 100);

//     std::ifstream in;
//     in.open("../source.txt");

//     for (int i{1}; i < MAX; i++)
//     {
//         std::cout << i << " ";
//         char *s = new char[70];
//         in.getline(s, 70);
//         std::cout << s << std::endl;

//         // if ((i % 20000 == 0))
//         // {
//         //     std::cout << "AVL TIME : ";
//         //     // start = clock();

//         //     root = avltree_add(root, s, i);

//         //     // start = clock() - start;

//         //     // time = (double)start / CLOCKS_PER_SEC;
//         //     // printf("%.5f\n", time);
//         //     std::cout << "\n";
//         // }
//         // else
            
//         root = avltree_add(root, s, i);
//         delete [] s;

//     }

//     // char *str = (char *)"string";
//     // avl_node *root = create_tree(rand() % 100, str);

//     // std::cout << root << std::endl;

//     // int t = 0;
//     // for (int i = 0; i < 10; i++)
//     // {
//     //     root = avltree_add(root, t = rand() % 100, str);
//     //     std::cout << "t : " << t << std::endl;
//     //     if (root->left != NULL && root->left->left != NULL)
//     //         std::cout << root->left->left->value << std::endl;
//     // }
//     in.close();

//     return 0;
// }