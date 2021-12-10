#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
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

typedef struct Record
{
    long value;
    bool discarded_oxy;
    bool discarded_co2;
} Record;

long read_life_support(long *numbers, size_t count)
{
    Record records[count];
    for (size_t i = 0; i < count; ++i)
    {
        records[i].value = numbers[i];
        records[i].discarded_oxy = false;
        records[i].discarded_co2 = false;
    }

    long oxygen;
    size_t records_left_oxy = count;
    for (size_t i = 0; i < BIT_COUNT; ++i)
    {
        long bit_sum_oxy = 0;
        for (size_t j = 0; j < count; ++j)
        {
            if (!records[j].discarded_oxy)
                bit_sum_oxy += (records[j].value >> (BIT_COUNT - i - 1)) & 1;
        }
        long bit_oxy = 0;
        if (bit_sum_oxy > (records_left_oxy >> 1)) bit_oxy = 1;
        else if (!(records_left_oxy & 1) && (bit_sum_oxy == (records_left_oxy >> 1))) bit_oxy = 1;
        for (size_t j = 0; j < count; ++j)
        {
            if (!records[j].discarded_oxy &&
                (((records[j].value >> (BIT_COUNT - i - 1)) & 1) == bit_oxy))
            {
                oxygen = records[j].value;
            }
            else if (!records[j].discarded_oxy)
            {
                records[j].discarded_oxy = true;
                --records_left_oxy;
            }
        }
        if (records_left_oxy == 1) break;
    }

    long co2;
    size_t records_left_co2 = count;
    for (size_t i = 0; i < BIT_COUNT; ++i)
    {
        long bit_sum = 0;
        for (size_t j = 0; j < count; ++j)
        {
            if (!records[j].discarded_co2)
                bit_sum += (records[j].value >> (BIT_COUNT - i - 1)) & 1;
        }
        long bit = 1;
        if (bit_sum > (records_left_co2 >> 1)) bit = 0;
        else if (!(records_left_co2 & 1) && (bit_sum == (records_left_co2 >> 1))) bit = 0;
        for (size_t j = 0; j < count; ++j)
        {
            if (!records[j].discarded_co2 &&
                (((records[j].value >> (BIT_COUNT - i - 1)) & 1) == bit))
            {
                co2 = records[j].value;
            }
            else if (!records[j].discarded_co2)
            {
                records[j].discarded_co2 = true;
                --records_left_co2;
            }
        }
        if (records_left_co2 == 1) break;
    }

    return oxygen * co2;
}

int main()
{
    size_t count = 0;
    long *numbers = read_numbers_from_file("input.txt", &count, 2);

    printf("Day 3!\n");
    printf("* pt. 1: %ld\n", read_power_consumption(numbers, count));
    printf("* pt. 2: %ld\n", read_life_support(numbers, count));

    free(numbers);

    return 0;
}