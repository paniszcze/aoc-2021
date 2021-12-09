#include <stdio.h>
#include <stdlib.h>
#include "../file.c"

long follow_instructions(char *buffer)
{
    long position = 0, depth = 0;

    char *end = buffer;

    return position * depth;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 2!\n");
    printf("* pt. 1: %ld\n", follow_instructions(buffer));
    // printf("* pt. 2: %ld\n", follow_instructions(buffer));

    free(buffer);

    return 0;
}