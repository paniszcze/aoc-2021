#include <stdlib.h>
#include <ctype.h>

typedef struct Word
{
    char *start;
    size_t size;
} Word;

char *find_digit(char *ptr)
{
    while (!isdigit(*ptr) && *ptr != 0)
        ++ptr;
    return ptr;
}

char *find_letter(char *ptr)
{
    while (!isalpha(*ptr) && *ptr != 0)
        ++ptr;
    return ptr;
}

char *find_space(char *ptr)
{
    while (!isspace(*ptr) && *ptr != 0)
        ++ptr;
    return ptr;
}