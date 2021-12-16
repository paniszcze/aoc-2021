#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../file.c"
#include "../strings.c"

#define MAX_CAVES 20
#define MAX_NAME_LEN 10

#define ONCE 1
#define TWICE 0

void find_cave_names(char *buffer,
                     char names[][MAX_NAME_LEN],
                     bool is_big[MAX_CAVES],
                     size_t *count)
{
    memcpy(names[0], "start", strlen("start"));
    memcpy(names[1], "end", strlen("end"));
    *count = 2;

    while (*buffer)
    {
        size_t len = 0;
        buffer = find_letter(buffer);
        char *name_begin = buffer;
        while (isalpha(*buffer++))
        {
            ++len;
        }
        size_t index = 0;
        for (; index < *count; ++index)
        {
            if (strncmp(names[index], name_begin, len) == 0)
            {
                break;
            }
        }
        if (index == *count)
        {
            memcpy(names[index], name_begin, len);
            if (isupper(*name_begin))
                is_big[index] = true;
            ++(*count);
        }
    }
}

size_t find_cave_index(char *name, char names[][MAX_NAME_LEN], size_t count)
{
    size_t index = 0;
    while (strncmp(names[index], name, strlen(name)))
        ++index;

    return index;
}

void track_adjacencies(char *buffer,
                       char names[][MAX_NAME_LEN],
                       size_t count,
                       bool adjacency_matrix[MAX_CAVES][MAX_CAVES])
{
    while (isalpha(*buffer))
    {
        size_t len = 0;
        buffer = find_letter(buffer);
        char *name_begin = buffer;
        while (isalpha(*buffer++))
        {
            ++len;
        }
        char first_cave[len + 1];
        memcpy(first_cave, name_begin, len);
        first_cave[len] = 0;
        size_t index1 = find_cave_index(first_cave, names, count);

        len = 0;
        buffer = find_letter(buffer);
        name_begin = buffer;
        while (isalpha(*buffer++))
        {
            ++len;
        }
        char second_cave[len + 1];
        memcpy(second_cave, name_begin, len);
        second_cave[len] = 0;
        size_t index2 = find_cave_index(second_cave, names, count);

        adjacency_matrix[index1][index2] = true;
        adjacency_matrix[index2][index1] = true;
    }
}

void search_paths(size_t begin, size_t end,
                  size_t caves_count, size_t *paths_count,
                  bool adjacency_matrix[MAX_CAVES][MAX_CAVES],
                  size_t visited[MAX_CAVES],
                  bool is_big[MAX_CAVES])
{
    if (begin == end)
    {
        ++(*paths_count);
        return;
    }

    for (size_t i = 0; i < caves_count; ++i)
    {
        if (adjacency_matrix[begin][i] && ((visited[i] < 1) || is_big[i]))
        {
            visited[i] += 1;
            search_paths(i, 1, caves_count, paths_count, adjacency_matrix, visited, is_big);
            visited[i] -= 1;
        }
    }
}

void search_paths2(size_t begin, size_t end,
                  size_t caves_count, size_t *paths_count,
                  bool adjacency_matrix[MAX_CAVES][MAX_CAVES],
                  size_t visited[MAX_CAVES],
                  bool is_big[MAX_CAVES],
                  bool small_twice,
                  char names[][MAX_NAME_LEN])
{
    if (begin == end)
    {
        // printf("%s\n", names[begin]);
        ++(*paths_count);
        return;
    }

    for (size_t i = 0; i < caves_count; ++i)
    {
        if (adjacency_matrix[begin][i])
        {
            if (is_big[i])
            {
                visited[i] += 1;
                // printf("%s -> ", names[begin]);
                search_paths2(i, 1, caves_count, paths_count, adjacency_matrix, visited, is_big, small_twice, names);
            }
            else if (visited[i] < 1)
            {
                visited[i] += 1;
                // printf("%s -> ", names[begin]);
                search_paths2(i, 1, caves_count, paths_count, adjacency_matrix, visited, is_big, small_twice, names);
                visited[i] -= 1;
            }
            else if (!small_twice && i != 0)
            {
                visited[i] += 1;
                // printf("%s -> ", names[begin]);
                search_paths2(i, 1, caves_count, paths_count, adjacency_matrix, visited, is_big, true, names);
                visited[i] -= 1;
            }
        }
    }
}

long count_possible_paths(char *buffer, int mode)
{
    char cave_names[MAX_CAVES][MAX_NAME_LEN] = {0};
    bool is_big[MAX_CAVES] = {0};
    size_t caves_count = 0;
    find_cave_names(buffer, cave_names, is_big, &caves_count);

    bool adjacency_matrix[MAX_CAVES][MAX_CAVES] = {0};
    size_t visited[MAX_CAVES] = {0};
    track_adjacencies(buffer, cave_names, caves_count, adjacency_matrix);

    size_t paths_count = 0;
    if (mode)
    {
        visited[0] = 1;
        search_paths(0, 1, caves_count, &paths_count, adjacency_matrix, visited, is_big);
    }
    else
    {
        visited[0] = 2;
        search_paths2(0, 1, caves_count, &paths_count, adjacency_matrix, visited, is_big, TWICE, cave_names);
    }


    /****************************************/

    // printf("\nFound %lu caves:\n", caves_count);
    // for (size_t i = 0; i < caves_count; ++i)
    // {
    //     printf("[%2lu / %d / %lu ] %s\n", i, is_big[i], visited[i], cave_names[i]);
    // }

    // printf("\n");
    // for (size_t i = 0; i < caves_count; ++i)
    // {
    //     for (size_t j = 0; j < caves_count; ++j)
    //         printf("%d ", adjacency_matrix[i][j]);
    //     printf("\n");
    // }
    // printf("\n");

    return paths_count;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 12!\n");
    printf("* pt. 1: %ld\n", count_possible_paths(buffer, ONCE));
    printf("* pt. 2: %ld\n", count_possible_paths(buffer, TWICE));

    free(buffer);

    return 0;
}