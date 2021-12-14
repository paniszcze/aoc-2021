#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../file.c"

#define WIDTH 100
#define HEIGHT 100
#define DIRECTIONS 4

#define BASINS_BUFFER 550

bool is_lowpoint(long map[HEIGHT][WIDTH], size_t row, size_t col)
{
    long directions[DIRECTIONS][2] =
    {
        {-1,  0},
        { 0, -1},
        { 1,  0},
        { 0,  1}
    };

    for (size_t i = 0; i < DIRECTIONS; ++i)
    {
        size_t n_row = row + directions[i][0];
        size_t n_col = col + directions[i][1];
        if (0 <= n_row && n_row < HEIGHT)
            if (0 <= n_col && n_col < WIDTH)
                if (map[n_row][n_col] <= map[row][col])
                    return false;
    }

    return true;
}

void explore_basin(long map[HEIGHT][WIDTH],
                   bool visited[HEIGHT][WIDTH],
                   size_t row, size_t col, size_t *size)
{
    if (visited[row][col] == true)
        return;
    visited[row][col] = true;
    ++(*size);

    long directions[DIRECTIONS][2] =
    {
        {-1,  0},
        { 0, -1},
        { 1,  0},
        { 0,  1}
    };

    for (size_t i = 0; i < DIRECTIONS; ++i)
    {
        size_t n_row = row + directions[i][0];
        size_t n_col = col + directions[i][1];
        if (0 <= n_row && n_row < HEIGHT)
            if (0 <= n_col && n_col < WIDTH)
                if (map[n_row][n_col] >= map[row][col] && map[n_row][n_col] < 9)
                    explore_basin(map, visited, n_row, n_col, size);
    }
}

int compare(const void *a, const void *b)
{
    return *(long *)b - *(long *)a;
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
        for (size_t j = 0; j < WIDTH; ++j)
            if (is_lowpoint(hightmap, i, j))
                sum += hightmap[i][j] + 1;

    return sum;
}

long find_basins(char *buffer)
{
    long hightmap[HEIGHT][WIDTH] = {0};

    for (size_t i = 0; i < HEIGHT; ++i)
    {
        for (size_t j = 0; j < WIDTH; ++j)
            hightmap[i][j] = *buffer++ - '0';
        ++buffer;
    }

    bool visited[HEIGHT][WIDTH] = {0};
    long basins[BASINS_BUFFER] = {0};
    size_t count = 0;

    for (size_t i = 0; i < HEIGHT; ++i)
        for (size_t j = 0; j < WIDTH; ++j)
            if (is_lowpoint(hightmap, i, j))
            {
                size_t size = 0;
                explore_basin(hightmap, visited, i, j, &size);
                basins[count++] = size;
            }

    qsort(basins, count, sizeof(long), compare);

    return basins[0] * basins[1] * basins[2];
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 9!\n");
    printf("* pt. 1: %ld\n", sum_risk_levels(buffer));
    printf("* pt. 2: %ld\n", find_basins(buffer));

    free(buffer);

    return 0;
}