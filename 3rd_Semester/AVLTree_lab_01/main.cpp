#include "avltree.hpp"
#include <ctime>
#include <iomanip>

const unsigned int count = 12;
const unsigned int delay = 5000;

int main()
{
    srand(time(NULL));

    char *str = (char *)"string";
    avl_node *root = create_tree(rand() % 100, str);

    for (int i = 1; i < int(count); i++)
    {
        root = avltree_add(root, i, str);

        if (i % delay == 0)
        {
            clock_t start = clock();
            lookup(root, rand() % i - 1);
            clock_t end = clock();
            std::cout << std::fixed << std::setprecision(8); 
            double t = double((double)(end - start) / CLOCKS_PER_SEC);
            std::cout << "Time (i = " << i << ") : " << t << std::endl;
        }
    }   

    delnode(root, 3);

    tree_out(root, 0);

    return 0;
}