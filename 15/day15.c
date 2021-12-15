#include <stdio.h>
#include <stdlib.h>
#include "../file.c"

long func(char *buffer)
{
    return 0;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 15!\n");
    printf("* pt. 1: %ld\n", func(buffer));
    // printf("* pt. 2: %ld\n", func(buffer));

    free(buffer);

    return 0;
}