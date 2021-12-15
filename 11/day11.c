#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "../file.c"

#define ENERGY_LEVELS 10
#define SIZE 10
#define STEPS 100

#define DIRECTIONS 8

void print_levels(long array[][SIZE])
{
    for (size_t i = 0; i < SIZE; ++i)
    {
        for (size_t j = 0; j < SIZE; ++j)
            if (array[i][j] < 3)
                printf("%ld", array[i][j]);
            else if (array[i][j] < 5)
                printf("\x1b[38;5;220m%ld\x1b[0m", array[i][j]);
            else if (array[i][j] < 7)
                printf("\x1b[38;5;214m%ld\x1b[0m", array[i][j]);
            else if (array[i][j] < 9)
                printf("\x1b[38;5;208m%ld\x1b[0m", array[i][j]);
            else
                printf("\x1b[38;5;202m%ld\x1b[0m", array[i][j]);

        printf("\n");
    }
}

static void back()
{
    printf("\x1b[%dD", SIZE);
    printf("\x1b[%dA", SIZE);
}

void increase_neighbours(long array[][SIZE], bool flashed[][SIZE], size_t row, size_t col)
{
    long directions[DIRECTIONS][2] =
    {
        {-1, -1},
        { 0, -1},
        { 1, -1},
        { 1,  0},
        { 1,  1},
        { 0,  1},
        {-1,  1},
        {-1,  0}
    };

    for (size_t i = 0; i < DIRECTIONS; ++i)
    {
        size_t n_row = row + directions[i][0];
        size_t n_col = col + directions[i][1];
        if (0 <= n_row && n_row < SIZE)
            if (0 <= n_col && n_col < SIZE)
                if (!flashed[n_row][n_col])
                    ++(array[n_row][n_col]);
    }
}

long count_flashes(char *buffer)
{
    long energy[SIZE][SIZE] = {0};
    size_t flash_count = 0;
    bool flashing = false;

    for (size_t i = 0; i < SIZE; ++i)
    {
        for (size_t j = 0; j < SIZE; ++j)
            energy[i][j] = *buffer++ - '0';
        ++buffer;
    }

    for (size_t steps = 0; steps < STEPS; ++steps)
    {
        bool flashed[SIZE][SIZE] = {0};

        for (size_t i = 0; i < SIZE; ++i)
            for (size_t j = 0; j < SIZE; ++j)
                if (++(energy[i][j]) > 9)
                    flashing = true;

        while (flashing)
        {
            flashing = false;
            for (size_t i = 0; i < SIZE; ++i)
                for (size_t j = 0; j < SIZE; ++j)
                    if (energy[i][j] > 9 && !flashed[i][j])
                    {
                        energy[i][j] = 0;
                        flashed[i][j] = true;
                        ++flash_count;
                        increase_neighbours(energy, flashed, i, j);
                        flashing = true;
                    }
        }

        print_levels(energy);
        if (steps != STEPS - 1)
            back();
        usleep(120000);
    }

    return flash_count;
}

int main()
{
    char *buffer = read_file("sample.txt");

    printf("Day 11!\n");
    printf("* pt. 1: %ld\n", count_flashes(buffer));
    // printf("* pt. 2: %ld\n", octo(buffer));

    free(buffer);

    return 0;
}