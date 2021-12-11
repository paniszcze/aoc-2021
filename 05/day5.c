#include <stdio.h>
#include <stdlib.h>
#include "../file.c"
#include "../strings.c"

#define ABS(x) (((x) < 0) ? -(x) : (x))

#define SIZE 1000

#define STRAIGHT 1
#define DIAGONAL 0

void draw_straight_line(long map[SIZE][SIZE], long x1, long y1, long x2, long y2)
{
    if (x1 == x2)
    {
        long y = y1 < y2 ? y1 : y2;
        long dy = ABS(y1 - y2);
        for (size_t i = 0; i <= dy; ++i)
            map[y + i][x1] += 1;
    }
    else if (y1 == y2)
    {
        long x = x1 < x2 ? x1 : x2;
        long dx = ABS(x1 - x2);
        for (size_t i = 0; i <= dx; ++i)
            map[y1][x + i] += 1;
    }
}

void draw_line(long map[SIZE][SIZE], long x1, long y1, long x2, long y2)
{
    if (x1 == x2 || y1 == y2)
        draw_straight_line(map, x1, y1, x2, y2);

    long dx = ABS(x1 - x2);
    if (x1 < x2 && y1 < y2)
        for (size_t i = 0; i <= dx; ++i)
            map[y1 + i][x1 + i] += 1;
    if (x1 < x2 && y1 > y2)
        for (size_t i = 0; i <= dx; ++i)
            map[y1 - i][x1 + i] += 1;
    if (x1 > x2 && y1 < y2)
        for (size_t i = 0; i <= dx; ++i)
            map[y1 + i][x1 - i] += 1;
    if (x1 > x2 && y1 > y2)
        for (size_t i = 0; i <= dx; ++i)
            map[y1 - i][x1 - i] += 1;
}

void print_map(long map[SIZE][SIZE])
{
    for (size_t i = 0; i < SIZE; ++i)
    {
        for (size_t j = 0; j < SIZE; ++j)
        {
            if (map[i][j] == 0)
                printf(".");
            else
                printf("%ld", map[i][j]);
        }
        printf("\n");
    }
}

long find_hotspots(char *buffer, long bound, int mode)
{
    char *end = buffer;
    long x1, y1, x2, y2;

    long map[SIZE][SIZE] = {0};

    while (*buffer != 0)
    {
        buffer = find_digit(buffer);
        x1 = strtol(buffer, &buffer, 10);
        buffer = find_digit(buffer);
        y1 = strtol(buffer, &buffer, 10);
        buffer = find_digit(buffer);
        x2 = strtol(buffer, &buffer, 10);
        buffer = find_digit(buffer);
        y2 = strtol(buffer, &buffer, 10);
        ++buffer;

        if (mode)
            draw_straight_line(map, x1, y1, x2, y2);
        else
            draw_line(map, x1, y1, x2, y2);
    }

    size_t count = 0;
    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
            if (map[j][i] >= bound)
                ++count;

    return count;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 5!\n");
    printf("* pt. 1: %ld\n", find_hotspots(buffer, 2L, STRAIGHT));
    printf("* pt. 2: %ld\n", find_hotspots(buffer, 2L, DIAGONAL));

    free(buffer);

    return 0;
}