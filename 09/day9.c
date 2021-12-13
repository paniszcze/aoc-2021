#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../file.c"

#define WIDTH 100
#define HEIGHT 100

bool is_lowpoint(long map[HEIGHT][WIDTH], size_t row, size_t col)
{
    if (row == 0)
    {
        if (col == 0)
        {
            return (map[row + 1][col] > map[row][col] && map[row][col + 1] > map[row][col]);
        }
        else if (col == WIDTH - 1)
        {
            return (map[row + 1][col] > map[row][col] && map[row][col - 1] > map[row][col]);
        }
        else
        {
            return (map[row + 1][col] > map[row][col] &&
                    map[row][col + 1] > map[row][col] &&
                    map[row][col - 1] > map[row][col]);
        }
    }
    else if (row == HEIGHT - 1)
    {
        if (col == 0)
        {
            return (map[row - 1][col] > map[row][col] && map[row][col + 1] > map[row][col]);
        }
        else if (col == WIDTH - 1)
        {
            return (map[row - 1][col] > map[row][col] && map[row][col - 1] > map[row][col]);
        }
        else
        {
            return (map[row - 1][col] > map[row][col] &&
                    map[row][col + 1] > map[row][col] &&
                    map[row][col - 1] > map[row][col]);
        }
    }
    else
    {
        if (col == 0)
        {
            return (map[row - 1][col] > map[row][col] &&
                    map[row + 1][col] > map[row][col] &&
                    map[row][col + 1] > map[row][col]);
        }
        else if (col == WIDTH - 1)
        {
            return (map[row - 1][col] > map[row][col] &&
                    map[row + 1][col] > map[row][col] &&
                    map[row][col - 1] > map[row][col]);
        }
        else
        {
            return (map[row - 1][col] > map[row][col] &&
                    map[row + 1][col] > map[row][col] &&
                    map[row][col - 1] > map[row][col] &&
                    map[row][col + 1] > map[row][col]);
        }
    }
}

long sum_risk_levels(char *buffer)
{
    long hightmap[HEIGHT][WIDTH] = {0};
    long sum = 0;

    for (size_t i = 0; i < HEIGHT; ++i)
    {
        for (size_t j = 0; j < WIDTH; ++j)
            hightmap[i][j] = *buffer++ - '0';
        ++buffer;
    }

    for (size_t i = 0; i < HEIGHT; ++i)
    {
        for (size_t j = 0; j < WIDTH; ++j)
        {
            if (is_lowpoint(hightmap, i, j))
            {
                sum += hightmap[i][j] + 1;
            }
        }
    }

    return sum;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 9!\n");
    printf("* pt. 1: %ld\n", sum_risk_levels(buffer));
    // printf("* pt. 2: %ld\n", lava(buffer));

    free(buffer);

    return 0;
}