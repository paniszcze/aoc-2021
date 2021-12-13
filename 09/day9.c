#include <stdio.h>
#include <stdlib.h>
#include "../file.c"

#define WIDTH 10
#define HEIGHT 5

long find_lowpoint(char *buffer)
{
    long hightmap[HEIGHT][WIDTH] = {0};
    long sum = 0;

    for (size_t i = 0; i < HEIGHT; ++i)
    {
        for (size_t j = 0; j < WIDTH; ++j)
            hightmap[i][j] = *buffer++ - '0';
        ++buffer;
    }

    for (size_t i = 0; i < HEIGHT; ++i)
    {
        for (size_t j = 0; j < WIDTH; ++j)
        {
            if (i == 0)
            {
                if (j == 0)
                {

                }
                else if (j == WIDTH - 1)
                {

                }
                else
                {

                }
            }
            else if (i == HEIGHT - 1)
            {
                if (j == 0)
                {

                }
                else if (j == WIDTH - 1)
                {

                }
                else
                {
                    
                }
            }
            else
            {
                if (j == 0)
                {

                }
                else if (j == WIDTH - 1)
                {

                }
                else
                {
                    
                }
            }
        }
    }

    return 1;
}

int main()
{
    char *buffer = read_file("sample.txt");

    printf("Day 9!\n");
    printf("* pt. 1: %ld\n", find_lowpoint(buffer));
    // printf("* pt. 2: %ld\n", lava(buffer));

    free(buffer);

    return 0;
}