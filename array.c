#include <stdlib.h>

long sum_array(long *array, size_t size)
{
    long sum = 0;
    for (size_t i = 0; i < size; ++i)
    {
        sum += array[i];
    }
    return sum;
}

void print_array(size_t row, size_t col, long array[][col])
{
    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0; j < col; ++j)
            printf("%ld", array[i][j]);
        printf("\n");
    }
}