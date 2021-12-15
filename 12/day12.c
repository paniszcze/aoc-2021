#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../file.c"

long find_passage(char *buffer)
{
    return 0;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 12!\n");
    printf("* pt. 1: %ld\n", find_passage(buffer));
    // printf("* pt. 2: %ld\n", find_passage(buffer));

    free(buffer);

    return 0;
}