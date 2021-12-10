#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../file.c"

#define BOARD_SIZE 5
#define MAX_COUNT 100

typedef struct Number
{
    long value;
    bool marked;
} Number;

typedef struct Board
{
    Number number[BOARD_SIZE][BOARD_SIZE];
} Board;

void print_board(Board board)
{
    for (size_t row = 0; row < BOARD_SIZE; ++row)
    {
        for (size_t col = 0; col < BOARD_SIZE; ++col)
        {
            if (!board.number[row][col].marked)
                printf("%2ld ", board.number[row][col].value);
            else
                printf(" x ");
        }
        printf("\n");
    }
}

long bingo(char *buffer)
{
    char *end = buffer;
    long numbers[MAX_COUNT];
    size_t nums_count = 0;

    while (*buffer != '\n')
    {
        numbers[nums_count] = strtol(buffer, &end, 10);
        buffer = end;
        ++buffer;
        ++nums_count;
    }

    Board boards[MAX_COUNT];
    size_t boards_count = 0;
    while (*buffer != 0)
    {
        for (size_t i = 0; i < BOARD_SIZE; ++i)
        {
            for (size_t j = 0; j < BOARD_SIZE; ++j)
            {
                while (isspace(*buffer)) ++buffer;
                boards[boards_count].number[i][j].value = strtol(buffer, &end, 10);
                boards[boards_count].number[i][j].marked = false;
                buffer = end;
            }
        }
        ++boards_count;
    }

    for (size_t i = 0; i < nums_count; ++i)
    {
        printf("%ld ", numbers[i]);
    }
    printf("\n");

    print_board(boards[2]);

    return 0;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 4!\n");
    printf("* pt. 1: %ld\n", bingo(buffer));
    // printf("* pt. 2: %ld\n", bingo(buffer));

    free(buffer);

    return 0;
}