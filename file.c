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