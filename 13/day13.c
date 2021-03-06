#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "../file.c"
#include "../strings.c"

#define MAX_SIZE 1500
#define MAX_COMMANDS 15

#define FIRST_STEP 1
#define ALL_STEPS 0

typedef struct Command
{
    char axis;
    long fold;
} Command;

size_t count_dots(bool array[][MAX_SIZE], size_t height, size_t width)
{
    size_t count = 0;
    for (size_t i = 0; i <= height; ++i)
        for (size_t j = 0; j <= width; ++j)
            if (array[i][j])
                ++count;

    return count;
}

long fold_paper(char *buffer, int mode)
{
    bool paper_sheet[MAX_SIZE][MAX_SIZE] = {0};
    size_t width = 0, height = 0;

    // read dot coordinates and mark them on the paper sheet
    long x, y;
    while (isdigit(*buffer))
    {
        x = strtol(buffer, &buffer, 10);
        ++buffer;
        y = strtol(buffer, &buffer, 10);
        ++buffer;
        
        paper_sheet[y][x] = true;

        width = width > x ? width : x;
        height = height > y ? height : y;
    }

    // decode folding commands and store them in an array od structs
    Command commands[MAX_COMMANDS] = {0};
    size_t commands_count = 0;

    buffer = find_letter(buffer);
    while (*buffer)
    {
        buffer = strchr(buffer, '=');
        commands[commands_count].axis = *(buffer - 1);
        commands[commands_count].fold = strtol(buffer + 1, &buffer, 10);
        ++commands_count;
        ++buffer;
    }

    // execute the commands
    size_t steps = mode == FIRST_STEP ? 1 : commands_count;
    for (size_t i = 0; i < steps; ++i)
    {
        for (size_t row = 0; row <= height; ++row)
        {
            for (size_t col = 0; col <= width; ++col)
            {
                switch (commands[i].axis)
                {
                case 'x':
                    if (col > commands[i].fold && paper_sheet[row][col] == true)
                    {
                        size_t n_col = commands[i].fold - (col - commands[i].fold);
                        paper_sheet[row][n_col] = true;
                    }
                    break;
                case 'y':
                    if (row > commands[i].fold && paper_sheet[row][col] == true)
                    {
                        size_t n_row = commands[i].fold - (row - commands[i].fold);
                        paper_sheet[n_row][col] = true;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        if (commands[i].axis == 'x')
            width = commands[i].fold;
        else
            height = commands[i].fold;
    }

    // print the sheet
    if (mode == ALL_STEPS)
        for (size_t i = 0; i <= height; ++i)
        {
            for (size_t j = 0; j <= width; ++j)
                printf("%c ", paper_sheet[i][j] ? 'X' : ' ');
            printf("\n");
        }

    return count_dots(paper_sheet, height, width);
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 13!\n");
    printf("* pt. 1: %ld\n", fold_paper(buffer, FIRST_STEP));
    printf("* pt. 2:\n");
    fold_paper(buffer, ALL_STEPS);

    free(buffer);

    return 0;
}