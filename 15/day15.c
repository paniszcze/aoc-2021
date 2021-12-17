#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "../array.c"
#include "../file.c"

#define WIDTH 10
#define HEIGHT 10
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
    char *buffer = read_file("sample.txt");
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
                // ... (save node in some kind of a structure if updated)
            }
    }

    visited[row][col] = true;
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
    // while (!visited[HEIGHT - 1][WIDTH - 1])
    // {
    //     // ... (find next node to update upon)
    //     update_neighbours(risk_map, risk_level, visited, 0, 0);
    // }
    for (size_t i = 0; i < HEIGHT; ++i)
        for (size_t j = 0; j < WIDTH; ++j)
            update_neighbours(risk_map, risk_level, visited, i, j);

    for (size_t i = 0; i < HEIGHT; ++i)
    {
        for (size_t j = 0; j < WIDTH; ++j)
            printf("%3lu ", risk_level[i][j]);
        printf("\n");
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