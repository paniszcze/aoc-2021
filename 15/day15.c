#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "../file.c"

#define WIDTH 100
#define HEIGHT 100
#define DIRECTIONS 4
#define MAX_VALUE 9

long directions[DIRECTIONS][2] =
{
    {-1,  0},
    { 0, -1},
    { 1,  0},
    { 0,  1}
};

typedef struct Node
{
    size_t risk;
    bool visited;
    bool enqueued;
} Node;

void get_input(long map[][WIDTH])
{
    char *buffer = read_file("input.txt");
    char *ptr = buffer;

    for (size_t i = 0; i < HEIGHT; ++i)
    {
        for (size_t j = 0; j < WIDTH; ++j)
            map[i][j] = *ptr++ - '0';
        ++ptr;
    }

    free(buffer);
}

void initialize_risk_levels(const size_t ratio, Node risk_levels[][WIDTH * ratio])
{
    for (size_t i = 0; i < HEIGHT * ratio; ++i)
    {
        for (size_t j = 0; j < WIDTH * ratio; ++j)
        {
            risk_levels[i][j].risk = ULONG_MAX;
            risk_levels[i][j].visited = false;
            risk_levels[i][j].enqueued = false;
        }
    }
}

void update_neighbours(size_t ratio,
                       long map[][WIDTH],
                       Node risk_levels[][WIDTH * ratio],
                       size_t row,
                       size_t col)
{
    for (size_t i = 0; i < DIRECTIONS; ++i)
    {
        size_t n_row = row + directions[i][0];
        size_t n_col = col + directions[i][1];
        if (0 <= n_row && n_row < HEIGHT * ratio && 0 <= n_col && n_col < WIDTH * ratio)
            if (!risk_levels[n_row][n_col].visited)
            {
                size_t indx_a = n_row % HEIGHT;
                size_t indx_b = n_col % WIDTH;
                long n_value = map[indx_a][indx_b] + n_row / HEIGHT + n_col / WIDTH;
                n_value = ((n_value - 1) % MAX_VALUE) + 1;
                size_t tentative_risk = risk_levels[row][col].risk + n_value;
                if (tentative_risk < risk_levels[n_row][n_col].risk)
                {
                    risk_levels[n_row][n_col].risk = tentative_risk;
                    risk_levels[n_row][n_col].enqueued = true;
                }
            }
    }

    risk_levels[row][col].visited = true;
    risk_levels[row][col].enqueued = false;
}

void find_next_node(size_t ratio,
                    Node risk_levels[][WIDTH * ratio],
                    size_t *row,
                    size_t *col)
{
    size_t lowest = ULONG_MAX;
    for (size_t i = 0; i < HEIGHT * ratio; ++i)
        for (size_t j = 0; j < WIDTH * ratio; ++j)
        {
            if (risk_levels[i][j].enqueued && !risk_levels[i][j].visited && risk_levels[i][j].risk < lowest)
            {
                lowest = risk_levels[i][j].risk;
                *row = i;
                *col = j;
            }
        }
}

long find_lowest_risk(const size_t ratio)
{
    // store risk levels from input in an array of structs
    long map[HEIGHT][WIDTH];
    get_input(map);

    // initialize array of risk levels and set the tentative risk of the initial point to zero
    Node risk_levels[HEIGHT * ratio][WIDTH * ratio];
    initialize_risk_levels(ratio, risk_levels);
    risk_levels[0][0].risk = 0;

    // find the safest path
    size_t row = 0, col = 0;
    while (!risk_levels[HEIGHT * ratio - 1][WIDTH * ratio - 1].visited)
    {
        update_neighbours(ratio, map, risk_levels, row, col);
        find_next_node(ratio, risk_levels, &row, &col);
    }

    return risk_levels[HEIGHT * ratio - 1][WIDTH * ratio - 1].risk;
}

int main()
{
    printf("Day 15!\n");
    printf("* pt. 1: %ld\n", find_lowest_risk(1));
    printf("* pt. 2: %ld\n", find_lowest_risk(5));

    return 0;
}