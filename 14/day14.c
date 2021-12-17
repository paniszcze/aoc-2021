#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "../file.c"
#include "../strings.c"

#define LETTERS ('Z' - 'A' + 1)

void polymerize(size_t pairs[][LETTERS], char rules[][LETTERS])
{
    size_t tmp_pairs[LETTERS][LETTERS] = {0};

    for (size_t row = 0; row < LETTERS; ++row)
    {
        for (size_t col = 0; col < LETTERS; ++col)
            if (pairs[row][col] > 0)
            {
                size_t indx = rules[row][col] - 'A';
                tmp_pairs[indx][col] += pairs[row][col];
                tmp_pairs[row][indx] += pairs[row][col];
            }
    }

    // copy tmp to pairs
    for (size_t row = 0; row < LETTERS; ++row)
        for (size_t col = 0; col < LETTERS; ++col)
            pairs[row][col] = tmp_pairs[row][col];
}

size_t count_elements(char *buffer, size_t steps)
{
    // read the polymer template and store the initial count of specific pairs in the array
    size_t pairs[LETTERS][LETTERS] = {0};
    char first_element = *buffer, last_element;

    while (isalpha(*buffer) && isalpha(*(buffer + 1)))
    {
        size_t indx_a = *buffer++ - 'A';
        size_t indx_b = *buffer - 'A';

        ++(pairs[indx_b][indx_a]);
        last_element = *buffer;
    }

    // read and store the insertion rules
    char rules[LETTERS][LETTERS] = {0};

    while (*buffer)
    {
        buffer = find_letter(++buffer);
        size_t indx_a = *buffer++ - 'A';
        size_t indx_b = *buffer++ - 'A';

        buffer = find_letter(buffer);
        rules[indx_b][indx_a] = *buffer;
    }

    // preform insertions
    for (size_t i = 0; i < steps; ++i)
        polymerize(pairs, rules);

    // count the elements
    size_t elements[LETTERS] = {0};
    size_t biggest = 0, lowest = ULONG_MAX;

    for (size_t i = 0; i < LETTERS; ++i)
        for (size_t j = 0; j < LETTERS; ++j)
            if (pairs[i][j] != 0)
            {
                elements[i] += pairs[i][j];
                elements[j] += pairs[i][j];
            }
    ++(elements[first_element - 'A']);
    ++(elements[last_element - 'A']);
    for (size_t i = 0; i < LETTERS; ++i)
        elements[i] >>= 1;

    for (size_t i = 0; i < LETTERS; ++i)
        if (elements[i] > 0)
        {
            biggest = biggest > elements[i] ? biggest : elements[i];
            lowest = lowest < elements[i] ? lowest : elements[i];
        }

    return biggest - lowest;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 14!\n");
    printf("* pt. 1: %lu\n", count_elements(buffer, 10));
    printf("* pt. 2: %lu\n", count_elements(buffer, 40));

    free(buffer);

    return 0;
}