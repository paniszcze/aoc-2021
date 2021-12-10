#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../file.c"

#define BIT_COUNT 5

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

typedef struct record
{
    long value;
    bool discarded_oxy;
    bool discarded_co2;
} record;

long read_life_support(long *numbers, size_t count)
{
    record records[count];
    for (size_t i = 0; i < count; ++i)
    {
        records[i].value = numbers[i];
        records[i].discarded_oxy = false;
        records[i].discarded_co2 = false;
    }

    long oxygen;
    size_t records_left_oxy = count;
    printf("\ncount %lu %lu\n", records_left_oxy, records_left_oxy >> 1);
    for (size_t i = 0; i < BIT_COUNT; ++i)
    {
        long bit_sum_oxy = 0;
        for (size_t j = 0; j < count; ++j)
        {
            if (!records[j].discarded_oxy)
            {
                bit_sum_oxy += records[j].value >> (BIT_COUNT - i - 1) & 1;
                printf("%lu, ", records[j].value);
            }
        }
        long bit_oxy = 0;
        if (bit_sum_oxy > (records_left_oxy >> 1)) bit_oxy = 1;
        else if (bit_sum_oxy = (records_left_oxy >> 1)) bit_oxy = 1;
        printf("\n%lu:%ld left %lu\n", bit_sum_oxy, bit_oxy, records_left_oxy);
        for (size_t j = 0; j < count; ++j)
        {
            if (!records[j].discarded_oxy &&
                ((records[j].value >> (BIT_COUNT - i - 1)) & 1 == bit_oxy))
            {
                oxygen = records[j].value;
                printf("oxy %lu, ", oxygen);
            }
            else if (!records[j].discarded_oxy)
            {
                records[j].discarded_oxy = true;
                --records_left_oxy;
                printf("ile %lu, ", records_left_oxy);
            }
        }
        printf("\n");
        if (records_left_oxy == 1) break;
    }

    long co2 = 1;

    printf("\n%lu %lu\n", oxygen, co2);
    return oxygen * co2;
}

int main()
{
    size_t count = 0;
    long *numbers = read_numbers_from_file("sample.txt", &count, 2);

    printf("Day 3!\n");
    printf("* pt. 1: %ld\n", read_power_consumption(numbers, count));
    printf("* pt. 2: %ld\n", read_life_support(numbers, count));

    free(numbers);

    return 0;
}