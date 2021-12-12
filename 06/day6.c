#include <stdio.h>
#include <stdlib.h>
#include "../file.c"
#include "../strings.c"

#define DAYS_IN_CYCLE 9
#define RESTART_DAY 6

long count_fish(char *buffer, size_t days)
{
    size_t fish[DAYS_IN_CYCLE] = {0};

    while (*buffer != 0)
    {
        buffer = find_digit(buffer);
        size_t days_left = strtoul(buffer, &buffer, 10);
        ++fish[days_left];
    }

    for (size_t i = 0; i < days; ++i)
    {
        size_t tmp = fish[0];
        for (size_t j = 0; j < DAYS_IN_CYCLE - 1; ++j)
            fish[j] = fish[j + 1];
        fish[DAYS_IN_CYCLE - 1] = tmp;
        fish[RESTART_DAY] += tmp;
    }

    size_t sum = 0;
    for (size_t i = 0; i < DAYS_IN_CYCLE; ++i)
        sum += fish[i];

    return sum;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 6!\n");
    printf("* pt. 1: %ld\n", count_fish(buffer, 80UL));
    printf("* pt. 2: %ld\n", count_fish(buffer, 256UL));

    free(buffer);

    return 0;
}