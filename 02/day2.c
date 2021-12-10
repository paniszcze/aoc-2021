#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../file.c"

#define PART1 0
#define PART2 1

long follow_instructions(char *buffer, int part)
{
    long value = -1, position = 0, depth = 0, aim = 0;
    char *end = buffer;
    char command;

    while (*end != 0 && value != 0)
    {
        while (isspace(*buffer)) ++buffer;
        command = *buffer;

        while (isalpha(*buffer)) ++buffer;
        value = strtol(buffer, &end, 10);
        buffer = end;

        if (part == PART1)
        {
            if (command == 'f')
            {
                position += value;
            }
            else if (command == 'u') depth -= value;
            else if (command == 'd') depth += value;
        }
        else
        {
            if (command == 'f')
            {
                position += value;
                depth += value * aim;
            }
            else if (command == 'u') aim -= value;
            else if (command == 'd') aim += value;
        }
    }

    return position * depth;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 2!\n");
    printf("* pt. 1: %ld\n", follow_instructions(buffer, PART1));
    printf("* pt. 2: %ld\n", follow_instructions(buffer, PART2));

    free(buffer);

    return 0;
}