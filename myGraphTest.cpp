#include <iostream>
#include "myGraph.h"
int main(int, char **)
{
    int row0[] = {0, 1, 1, 1};
    int row1[] = {0, 0, 1, 0};
    int row2[] = {0, 0, 0, 1};
    int row3[] = {0, 0, 0, 0};

    int *neighbour_matrix[] =
        {
            row0,
            row1,
            row2,
            row3,
        };

    /*
        以上测试例子描述了这样的一个图
        0------->1------->2------->3
         \---------------↗
    */

    Graph g1(Matrix(neighbour_matrix, 4, 4), true);

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            std::cout << "Node " << i << (g1.CanReach(i, j) ? " can" : " cannot") << " reach Node " << j << std::endl;
        }
    }
}
