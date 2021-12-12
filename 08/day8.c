#include <stdio.h>
#include <stdlib.h>
#include "../file.c"

long find_lowest_fuel_consumption(char *buffer)
{
    return 0;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 8!\n");
    printf("* pt. 1: %ld\n", count_unique(buffer));

    free(buffer);

    return 0;
}