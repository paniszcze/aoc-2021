#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "../array.c"
#include "../file.c"

#define WIDTH 100
#define HEIGHT 100
#define DIRECTIONS 4

#define MIN(a,b) ((a) < (b) ? (a) : (b))

long directions[DIRECTIONS][2] =
{
    {-1,  0},
    { 0, -1},
    { 1,  0},
    { 0,  1}
};

void get_input(long array[][WIDTH])
{
    char *buffer = read_file("input.txt");
    char *ptr = buffer;

    for (size_t i = 0; i < HEIGHT; ++i)
    {
        for (size_t j = 0; j < WIDTH; ++j)
            array[i][j] = *ptr++ - '0';
        ++ptr;
    }

    free(buffer);
}

void update_neighbours(long risk_map[][WIDTH],
                       size_t risk_level[][WIDTH],
                       bool visited[][WIDTH],
                       bool enqueued[][WIDTH],
                       size_t row,
                       size_t col)
{
    for (size_t i = 0; i < DIRECTIONS; ++i)
    {
        size_t n_row = row + directions[i][0];
        size_t n_col = col + directions[i][1];
        if (0 <= n_row && n_row < HEIGHT && 0 <= n_col && n_col < WIDTH)
            if (!visited[n_row][n_col])
            {
                size_t tentative_risk = risk_level[row][col] + risk_map[n_row][n_col];
                risk_level[n_row][n_col] = MIN(risk_level[n_row][n_col], tentative_risk);
                enqueued[n_row][n_col] = true;
            }
    }

    visited[row][col] = true;
    enqueued[row][col] = false;
}

void find_next(size_t risk_level[][WIDTH],
               bool visited[][WIDTH],
               bool enqueued[][WIDTH],
               size_t *row,
               size_t *col)
{
    size_t lowest = ULONG_MAX;
    for (size_t i = 0; i < HEIGHT; ++i)
        for (size_t j = 0; j < WIDTH; ++j)
        {
            if (enqueued[i][j] && !visited[i][j] && risk_level[i][j] < lowest)
            {
                lowest = risk_level[i][j];
                *row = i;
                *col = j;
            }
        }
}

long find_lowest_risk()
{
    // store risk levels from input in an array
    long risk_map[HEIGHT][WIDTH] = {0};
    get_input(risk_map);

    // mark all nodes as unvisited
    bool visited[HEIGHT][WIDTH] = {0};

    // set the tentative risk of all nodes to maximal value (except the initial point)
    size_t risk_level[HEIGHT][WIDTH];
    for (size_t i = 0; i < HEIGHT; ++i)
        for (size_t j = 0; j < WIDTH; ++j)
            risk_level[i][j] = ULONG_MAX;
    risk_level[0][0] = 0;

    // find the safest path
    bool enqueued[HEIGHT][WIDTH] = {0};
    size_t row = 0, col = 0;
    while (!visited[HEIGHT - 1][WIDTH - 1])
    {
        update_neighbours(risk_map, risk_level, visited, enqueued, row, col);
        find_next(risk_level, visited, enqueued, &row, &col);
    }

    return risk_level[HEIGHT - 1][WIDTH - 1];
}

int main()
{
    printf("Day 15!\n");
    printf("* pt. 1: %ld\n", find_lowest_risk());
    // printf("* pt. 2: %ld\n", find_lowest_risk());

    return 0;
}