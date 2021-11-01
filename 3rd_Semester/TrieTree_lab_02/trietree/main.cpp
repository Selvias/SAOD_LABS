#include "trie.hpp"
#include <ctime>
#include <fstream>
#include <iomanip>

const int MAX{200000};
const int delay{20000};
//Множитель для увеличения времени поиска в n раз
const int mult{1000000};

// int main() {
//     // char *str = (char *)"stringtrtrtr";
//     trie *root = trieCreate();
//     // trieInsert(root, str, 300);

//     std::ifstream in("source.txt");

//     for (int i{1}; i < MAX; i++)
//     {
//         char *s = new char[50];
//         in.getline(s, 50);
//         trieInsert(root, s, i);

//         if (!(i%20000))
//         {
//             clock_t start = clock();
//             for (int j{0}; j < mult; j++)
//                 trieLookup(root, s);
//             clock_t end = clock();
//             std::cout << std::fixed << std::setprecision(8); 
//             double t = double((double)(end - start) / CLOCKS_PER_SEC);
//             std::cout << "Trie Time (i = " << i << "," << s << ") : " << t << std::endl;

//             // if (look)
//             //     std::cout << "Key : " << look->value << std::endl;
//         }
//     }

//     in.close();

//     return 0;
// }

int main()
{
    srand(time(NULL));

    trie *root = trieCreate();
    trieInsert(root, (char *)("cat"), 10);
    trieInsert(root, (char *)("code"), 21);
    trieInsert(root, (char *)("car"), 20);
    trieInsert(root, (char *)("card"), 25);
    trieInsert(root, (char *)("cet"), 29);
    trieInsert(root, (char *)("doooooc"), 31);
    trieInsert(root, (char *)("pisos"), 300);
    trieInsert(root, (char *)("plush"), 300300);
    trieInsert(root, (char *)("cort"), 3009);
    trieInsert(root, (char *)("pool"), 3010);

    trie *look = trieLookup(root, (char *)("cat"));
    if (look != NULL)
        std::cout << "KEY IS " << look->value << std::endl;

    // look = trieLookup(root, (char *)("car"));
    // if (look != NULL)
    //     std::cout << "KEY2 IS " << look->value << std::endl;

    // trieDeletion(root, (char *)("car"));

    // look = trieLookup(root, (char *)("car"));
    // if (look != NULL)
    //     std::cout << "KEY2 IS " << look->value << std::endl;

    triePrint(root);
    std::cout << std::endl;

    // look = trieLookup(root, (char *)("cat"));
    // if (look != NULL)
    //     std::cout << "KEY IS " << look->value << std::endl;

    return 0;
}