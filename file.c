#include <stdio.h>
#include <stdlib.h>

size_t get_file_size(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fclose(fp);
    return size;
}

char *read_file(const char *filename)
{
    size_t size = get_file_size(filename);
    char *buffer = malloc(sizeof(char) * size + 1);

    FILE *fp = fopen(filename, "r");
    fread(buffer, 1, size, fp);
    fclose(fp);

    return buffer;
}

long *read_numbers_from_file(const char *filename, size_t *count, int radix)
{
    char *buffer = read_file(filename);
    char *ptr = buffer;

    while (*ptr != 0)
    {
        while (!isdigit(*ptr)) ++ptr;
        while (isdigit(*ptr)) ++ptr;
        ++ptr;
        ++(*count);
    }

    long *numbers = malloc(sizeof(long) * *count);
    ptr = buffer;
    for (size_t i = 0; i < *count; ++i)
    {
        while (!isdigit(*ptr)) ++ptr;
        numbers[i] = strtol(ptr, &ptr, radix);
    }

    free(buffer);

    return numbers;
}