#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
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

typedef struct Node
{
    long value;
    size_t risk;
    bool visited;
    bool enqueued;
} Node;

void get_input(Node map[][WIDTH])
{
    char *buffer = read_file("input.txt");
    char *ptr = buffer;

    for (size_t i = 0; i < HEIGHT; ++i)
    {
        for (size_t j = 0; j < WIDTH; ++j)
        {
            map[i][j].value = *ptr++ - '0';
            map[i][j].risk = ULONG_MAX;
            map[i][j].visited = false;
            map[i][j].enqueued = false;
        }
        ++ptr;
    }

    free(buffer);
}

void update_neighbours(Node map[][WIDTH],
                       size_t row,
                       size_t col)
{
    for (size_t i = 0; i < DIRECTIONS; ++i)
    {
        size_t n_row = row + directions[i][0];
        size_t n_col = col + directions[i][1];
        if (0 <= n_row && n_row < HEIGHT && 0 <= n_col && n_col < WIDTH)
            if (!map[n_row][n_col].visited)
            {
                size_t tentative_risk = map[row][col].risk + map[n_row][n_col].value;
                if (tentative_risk < map[n_row][n_col].risk)
                {
                    map[n_row][n_col].risk = tentative_risk;
                    map[n_row][n_col].enqueued = true;
                }
            }
    }

    map[row][col].visited = true;
    map[row][col].enqueued = false;
}

void find_next_node(Node map[][WIDTH],
                    size_t *row,
                    size_t *col)
{
    size_t lowest = ULONG_MAX;
    for (size_t i = 0; i < HEIGHT; ++i)
        for (size_t j = 0; j < WIDTH; ++j)
        {
            if (map[i][j].enqueued && !map[i][j].visited && map[i][j].risk < lowest)
            {
                lowest = map[i][j].risk;
                *row = i;
                *col = j;
            }
        }
}

long find_lowest_risk()
{
    // store risk levels from input in an map
    Node map[HEIGHT][WIDTH] = {0};
    get_input(map);

    // set the tentative risk of all nodes to maximal value (except the initial point)
    map[0][0].risk = 0;

    // find the safest path
    size_t row = 0, col = 0;
    while (!map[HEIGHT - 1][WIDTH - 1].visited)
    {
        update_neighbours(map, row, col);
        find_next_node(map, &row, &col);
    }

    return map[HEIGHT - 1][WIDTH - 1].risk;
}

int main()
{
    printf("Day 15!\n");
    printf("* pt. 1: %ld\n", find_lowest_risk());
    // printf("* pt. 2: %ld\n", find_lowest_risk());

    return 0;
}