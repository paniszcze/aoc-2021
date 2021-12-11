#include <stdlib.h>
#include <ctype.h>

char *find_digit(char *ptr)
{
    while (!isdigit(*ptr) && *ptr != 0)
    {
        ++ptr;
    }
    return ptr;
}