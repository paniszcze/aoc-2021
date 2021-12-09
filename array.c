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