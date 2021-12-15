#include <stdio.h>
#include <stdlib.h>
#include "../file.c"

void create_graph(char *buffer)
{

}

long count_possible_paths(char *buffer)
{
    create_graph(buffer);


    return 0;
}

int main()
{
    char *buffer = read_file("sample1.txt");

    printf("Day 12!\n");
    printf("* pt. 1: %ld\n", count_possible_paths(buffer));
    // printf("* pt. 2: %ld\n", find_passage(buffer));

    free(buffer);

    return 0;
}