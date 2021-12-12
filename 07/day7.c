#include <stdio.h>
#include <stdlib.h>
#include "../file.c"
#include "../strings.c"

#define ABS(x) (((x) < 0) ? -(x) : (x))

#define MAX_POSITION 2000

#define LINNEAR 1
#define ACCUMULATIVE 0

long find_lowest_fuel_consumption(char *buffer, int mode)
{
    long position_count[MAX_POSITION] = {0};
    long biggest_value = 0, lowest_fuel_cost = INT64_MAX;

    while (*buffer != 0)
    {
        buffer = find_digit(buffer);
        long position = strtol(buffer, &buffer, 10);
        ++position_count[position];
        if (position > biggest_value)
            biggest_value = position;
    }

    for (long i = 0; i <= biggest_value; ++i)
    {
        long sum = 0;
        for (long j = 0; j <= biggest_value; ++j)
        {
            long offset = ABS(j - i);
            if (mode)
                sum += offset * position_count[j];
            else
                sum += ((offset * (offset + 1)) / 2) * position_count[j];
        }
        if (sum < lowest_fuel_cost)
            lowest_fuel_cost = sum;
    }

    return lowest_fuel_cost;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 7!\n");
    printf("* pt. 1: %ld\n", find_lowest_fuel_consumption(buffer, LINNEAR));
    printf("* pt. 2: %ld\n", find_lowest_fuel_consumption(buffer, ACCUMULATIVE));

    free(buffer);

    return 0;
}