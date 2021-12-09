#include <stdio.h>
#include <stdlib.h>
#include "../file.c"

long count_increments(char *buffer)
{
    char *end = buffer;

    long prev, next, cnt = 0;
    next = prev = strtol(buffer, &end, 10);

    while (*end != 0 && next != 0)
    {
        next = strtol(buffer, &end, 10);
        if (next > prev) ++cnt;
        prev = next;
        buffer = end;
    }

    return cnt;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 1!\n");
    printf("* pt. 1: %ld\n", count_increments(buffer));
    // printf("* pt. 2: %ld\n", count_increments(fp));

    free(buffer);

    return 0;
}