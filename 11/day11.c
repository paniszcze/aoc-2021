#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "../file.c"

#define ENERGY_LEVELS 10
#define SIZE 10
#define STEPS 100

#define DIRECTIONS 8

#define FLASHES 1
#define SYNCHRO 0

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

static void forward()
{
    printf("\x1b[%dB", SIZE);
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

long count_flashes(char *buffer, int mode)
{
    long energy[SIZE][SIZE] = {0};
    size_t step_count = 0, flash_count = 0, flashes_per_step = 0;
    bool flashing = false;

    for (size_t i = 0; i < SIZE; ++i)
    {
        for (size_t j = 0; j < SIZE; ++j)
            energy[i][j] = *buffer++ - '0';
        ++buffer;
    }

    while (mode ? step_count < STEPS : flashes_per_step < SIZE * SIZE)
    {
        bool flashed[SIZE][SIZE] = {0};
        flashes_per_step = 0;

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
                        ++flashes_per_step;
                        increase_neighbours(energy, flashed, i, j);
                        flashing = true;
                    }
        }

        ++step_count;
        print_levels(energy);
        back();
        usleep(120000);
    }
    forward();

    return mode ? flash_count : step_count;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 11!\n");
    printf("* pt. 1: %ld\n", count_flashes(buffer, FLASHES));
    printf("* pt. 2: %ld\n", count_flashes(buffer, SYNCHRO));

    free(buffer);

    return 0;
}