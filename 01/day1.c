#include <stdio.h>
#include <stdlib.h>
#include "../file.c"
#include "../array.c"

long count_increments(char *buffer, size_t n)
{
    char *end = buffer;
    long frame[n];
    long prev_sum, next_sum = 0, cnt = 0;

    for (size_t i = 0; i < n; ++i)
    {
        frame[i] = strtol(buffer, &end, 10);
        buffer = end;
    }

    prev_sum = sum_array(frame, n);

    while (*end != 0 && frame[n - 1] != 0)
    {
        for (size_t i = 0; i < n - 1; ++i)
        {
            frame[i] = frame[i + 1];
        }
        frame[n - 1] = strtol(buffer, &end, 10);
        next_sum = sum_array(frame, n);
        if (next_sum > prev_sum) ++cnt;
        prev_sum = next_sum;
        buffer = end;
    }

    return cnt;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 1!\n");
    printf("* pt. 1: %ld\n", count_increments(buffer, 1));
    printf("* pt. 2: %ld\n", count_increments(buffer, 3));

    free(buffer);

    return 0;
}