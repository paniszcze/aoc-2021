#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../array.c"
#include "../file.c"

#define WIDTH 10
#define HEIGHT 10

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

long func()
{
    long risk_map[HEIGHT][WIDTH] = {0};
    get_input(risk_map);
    
    print_array(HEIGHT, WIDTH, risk_map);

    bool visited[HEIGHT][WIDTH] = {0};

    return 0;
}

int main()
{
    printf("Day 15!\n");
    printf("* pt. 1: %ld\n", func());
    // printf("* pt. 2: %ld\n", func(buffer));

    return 0;
}