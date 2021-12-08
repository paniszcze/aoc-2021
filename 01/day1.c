#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int read_file_to_array(long *array)
{
    char *filename = "sample.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s\n", filename);
        return -1;
    }

    fclose(fp);

    return 0;
}

long count_increments(long *array)
{
    char input[] = "199 200 208 210 200 207 240 269 260 263";
    char *ptr_end = input, *ptr_start = input;

    long next, prev, cnt = 0;
    prev = strtol(ptr_start, &ptr_end, 10);

    while (*ptr_end != 0)
    {
        next = strtol(ptr_start, &ptr_end, 10);
        if (next > prev) ++cnt;
        prev = next;
        ptr_start = ptr_end;
    }

    return cnt;
}

int main()
{
    long input[BUFFER_SIZE] = {0};
    read_file_to_array(input);

    printf("Day 1!\n");
    printf("* pt. 1: %ld\n", count_increments(input));
    // printf("* pt. 2: %ld\n", count_increments(fp));

    return 0;
}