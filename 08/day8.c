#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file.c"
#include "../strings.c"

// Segments pattern: 0b0absdefg
// Digits with unique segments count:
#define ONE     0b00010010  // 2
#define FOUR    0b00111010  // 4
#define SEVEN   0b01010010  // 3
#define EIGHT   0b01111111  // 7

// Five-segment digits:
#define TWO     0b01011101
#define THREE   0b01011011
#define FIVE    0b01101011

// Six-segment digits:
#define ZERO    0b01110111
#define SIX     0b01101111
#define NINE    0b01111011

size_t count_unique(char *buffer)
{
    size_t len, count = 0;
    char *begin = buffer, *end = buffer;

    while (*begin != 0)
    {
        begin = strchr(begin, '|');
        while (*begin != '\n' && *begin != 0)
        {
            begin = find_letter(begin);
            end = find_space(begin);
            len = end - begin;
            if (len == 2 || len == 3 || len == 4 || len == 7)
                ++count;
            begin = end;
        }
    }

    return count;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 8!\n");
    printf("* pt. 1: %lu\n", count_unique(buffer));

    free(buffer);

    return 0;
}