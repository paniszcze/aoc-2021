#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../file.c"

#define BOARD_SIZE 5
#define MAX_COUNT 128

#define WIN 1
#define LOOSE 0

typedef struct Number
{
    long value;
    bool marked;
} Number;

typedef struct Board
{
    Number number[BOARD_SIZE][BOARD_SIZE];
    bool won;
} Board;

void print_board(Board *board)
{
    for (size_t row = 0; row < BOARD_SIZE; ++row)
    {
        for (size_t col = 0; col < BOARD_SIZE; ++col)
        {
            if (!board->number[row][col].marked)
                printf("%2ld ", board->number[row][col].value);
            else
                printf(" x ");
        }
        printf("\n");
    }
}

int mark_number(Board *board, long number)
{
    for (size_t row = 0; row < BOARD_SIZE; ++row)
    {
        for (size_t col = 0; col < BOARD_SIZE; ++col)
        {
            if (board->number[row][col].value == number)
            {
                board->number[row][col].marked = true;
                return 1;
            }
        }
    }
    return 0;
}

bool check_win(Board *board)
{
    for (size_t row = 0; row < BOARD_SIZE; ++row)
    {
        size_t sum_marked_row = 0;
        size_t sum_marked_col = 0;
        for (size_t col = 0; col < BOARD_SIZE; ++col)
        {
            if (board->number[row][col].marked == true)
                ++sum_marked_col;
            if (sum_marked_col == BOARD_SIZE)
            {
                board->won = true;
                return board->won;
            }

            if (board->number[col][row].marked == true)
                ++sum_marked_row;
        }
        if (sum_marked_row == BOARD_SIZE)
        {
            board->won = true;
            return board->won;
        }
    }
    return board->won;
}

long sum_unmarked(Board *board)
{
    long sum = 0;
    for (size_t row = 0; row < BOARD_SIZE; ++row)
    {
        for (size_t col = 0; col < BOARD_SIZE; ++col)
        {
            if (board->number[row][col].marked == false)
                sum += board->number[row][col].value;
        }
    }
    return sum;
}

long bingo(char *buffer, int mode)
{
    char *end = buffer;
    long numbers[MAX_COUNT];
    size_t nums_count = 0;

    while (*buffer != '\n')
    {
        numbers[nums_count] = strtol(buffer, &end, 10);
        buffer = end;
        ++buffer;
        if (*buffer != 0)
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
                boards[boards_count].won = false;
                buffer = end;
            }
        }
        if (*buffer != 0)
            ++boards_count;
    }

    size_t boards_left = boards_count;
    for (size_t i = 0; i < nums_count; ++i)
    {
        for (size_t j = 0; j < boards_count; ++j)
        {
            if (mark_number(&boards[j], numbers[i]) &&
                !boards[j].won &&
                check_win(&boards[j]))
            {
                if (mode)
                    return sum_unmarked(&boards[j]) * numbers[i];
                else
                {
                    --boards_left;
                    if (boards_left == 0)
                        return sum_unmarked(&boards[j]) * numbers[i];
                }
            }
        }
    }

    return 0;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 4!\n");
    printf("* pt. 1: %ld\n", bingo(buffer, WIN));
    printf("* pt. 2: %ld\n", bingo(buffer, LOOSE));

    free(buffer);

    return 0;
}