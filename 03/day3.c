#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../file.c"

#define BIT_COUNT 12

long read_power_consumption(long *numbers, size_t count)
{
    long gamma = 0, epsilon = 0;

    for (size_t i = 0; i < BIT_COUNT; ++i)
    {
        long bit_sum = 0;
        for (size_t j = 0; j < count; ++j)
        {
            bit_sum += numbers[j] >> (BIT_COUNT - i - 1) & 1;
        }
        if (bit_sum > count / 2) gamma |= 1 << (BIT_COUNT - i - 1);
        else epsilon |= 1 << (BIT_COUNT - i - 1);
    }

    return gamma * epsilon;
}

int main()
{
    size_t count = 0;
    long *numbers = read_numbers_from_file("input.txt", &count, 2);

    printf("Day 3!\n");
    printf("* pt. 1: %ld\n", read_power_consumption(numbers, count));

    free(numbers);

    return 0;
}