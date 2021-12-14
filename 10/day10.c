#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../file.c"

#define LINES 110
#define STACK_CAPACITY 115
#define BRACKET_TYPES 4

#define CORRUPTED 1
#define INCOMPLETE 0

bool is_open(char ch, size_t *bracket)
{
    char *brackets = "([{<)]}>";
    size_t i = 0;
    while (i < 2 * BRACKET_TYPES && brackets[i] != ch)
        ++i;
    *bracket = i % BRACKET_TYPES;
    return i < BRACKET_TYPES;
}

int compare(const void *a, const void *b)
{
    return *(long *)b - *(long *)a;
}

long score_lines(char *buffer, int mode)
{
    long scores_corrupted[BRACKET_TYPES] = {3, 57, 1197, 25137};
    long scores_incomplete[BRACKET_TYPES] = {1, 2, 3, 4};
    long score_corrupted = 0, score_incomplete = 0;

    long scores_buffer[LINES + 10] = {0};
    size_t scores_count = 0;

    for (size_t i = 0; i < LINES; ++i)
    {
        size_t stack[STACK_CAPACITY] = {0};
        long stack_top = 0;
        bool found_error = false;

        while (*buffer != '\n' && *buffer != 0 && !found_error)
        {
            size_t bracket_type;
            if (is_open(*buffer, &bracket_type))
            {
                stack[stack_top++] = bracket_type;
            }
            else
            {
                if (stack_top <= 0 || stack[stack_top - 1] != bracket_type)
                {
                    score_corrupted += scores_corrupted[bracket_type];
                    found_error = true;
                }
                else
                    --stack_top;
            }
            ++buffer;
        }

        if (!mode && !found_error)
        {
            printf("%lu: ", stack_top);

            long score_incomplete_tmp = 0;

            for (size_t i = 0; i < stack_top; ++i)
            {
                printf("%lu ", stack[stack_top - 1 - i]);
                score_incomplete_tmp *= 5;
                score_incomplete_tmp += scores_incomplete[stack[stack_top - 1 - i]];
            }
                printf("%lu ", stack[0]);

            printf("- %lu\n", score_incomplete_tmp);
            scores_buffer[scores_count++] = score_incomplete_tmp;
        }

        while (!isspace(*buffer))
            ++buffer;
        ++buffer;
    }
            printf("cnt %lu\n", scores_count);

    qsort(scores_buffer, scores_count, sizeof(long), compare);
    score_incomplete = scores_buffer[scores_count >> 1];

    return mode ? score_corrupted : score_incomplete;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 10!\n");
    printf("* pt. 1: %ld\n", score_lines(buffer, CORRUPTED));
    printf("* pt. 2: %ld\n", score_lines(buffer, INCOMPLETE));

    free(buffer);

    return 0;
}