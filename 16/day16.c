#include <stdio.h>
#include <stdlib.h>
#include "../file.c"

size_t func(char *buffer)
{
    return 0;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 16!\n");
    printf("* pt. 1: %lu\n", func(buffer));
    // printf("* pt. 2: %lu\n", func(buffer));

    free(buffer);

    return 0;
}