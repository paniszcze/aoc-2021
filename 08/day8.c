#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file.c"
#include "../strings.c"

#define DIGITS 10
#define OUTPUT 4

// Segments pattern: 0b0absdefg
// Digits with unique segments count:
#define ONE     0b00010010  // 2
#define FOUR    0b00111010  // 4
#define SEVEN   0b01010010  // 3
#define EIGHT   0b01111111  // 7

// Five-segment digits:
#define TWO     0b01011101
#define THREE   0b01011011
#define FIVE    0b01101011

// Six-segment digits:
#define ZERO    0b01110111
#define SIX     0b01101111
#define NINE    0b01111011

typedef struct Digit
{
    u_int8_t bitmask;
    size_t segments;
    long value;
} Digit;

size_t count_unique(char *buffer)
{
    size_t count = 0, len;
    char *begin = buffer;

    while (*begin != 0)
    {
        begin = strchr(begin, '|');
        while (*begin != '\n' && *begin != 0)
        {
            begin = find_letter(begin);
            len = find_space(begin) - begin;
            if (len == 2 || len == 3 || len == 4 || len == 7)
                ++count;
            begin += len;
        }
    }

    return count;
}

void set_bitmask(Digit *digit, char ch)
{
    if (ch == 'a')
        digit->bitmask |= 0b01000000;
    else if (ch == 'b')
        digit->bitmask |= 0b00100000;
    else if (ch == 'c')
        digit->bitmask |= 0b00010000;
    else if (ch == 'd')
        digit->bitmask |= 0b00001000;
    else if (ch == 'e')
        digit->bitmask |= 0b00000100;
    else if (ch == 'f')
        digit->bitmask |= 0b00000010;
    else if (ch == 'g')
        digit->bitmask |= 0b00000001;
}

size_t count_set_bits(u_int8_t bitmask)
{
    long count = 0;
    while (bitmask)
    {
        count += bitmask & 1;
        bitmask >>= 1;
    }
    return count;
}

long sum_output(char *buffer)
{
    long sum = 0;

    while (*buffer != 0)
    {
        Digit digits[DIGITS + OUTPUT] = {{0}};

        // convert letter sequences to bitmasks and assign values to unique patterns
        for (size_t i = 0; i < DIGITS + OUTPUT; ++i)
        {
            buffer = find_letter(buffer);
            while (isalpha(*buffer))
            {
                set_bitmask(&digits[i], *buffer++);
                digits[i].segments = count_set_bits(digits[i].bitmask);
            }
            if (digits[i].segments == 2)
                digits[i].value = 1;
            else if (digits[i].segments == 4)
                digits[i].value = 4;
            else if (digits[i].segments == 3)
                digits[i].value = 7;
            else if (digits[i].segments == 7)
                digits[i].value = 8;
            else
                digits[i].value = -1;
        }

        u_int8_t subtrahend_4_7 = 0;
        u_int8_t subtrahend_1 = 0;
        for (size_t i = 0; i < DIGITS; ++i)
        {
            if (digits[i].value == 4)
                subtrahend_4_7 |= digits[i].bitmask;
            else if (digits[i].value == 7)
                subtrahend_4_7 |= digits[i].bitmask;
            else if (digits[i].value == 1)
                subtrahend_1 |= digits[i].bitmask;
        }
        // find digit 9, 2
        for (size_t i = 0; i < DIGITS + OUTPUT; ++i)
        {
            if ((digits[i].value == -1) &&
                (digits[i].segments == 6) &&
                (count_set_bits(digits[i].bitmask ^ subtrahend_4_7) == 1))
            {
                digits[i].value = 9;
            }
            if ((digits[i].value == -1) &&
                (digits[i].segments == 5) &&
                (count_set_bits(digits[i].bitmask ^ subtrahend_4_7) == 4))
            {
                digits[i].value = 2;
            }
        }
        // find digit 3 and 5, 0 and 6
        for (size_t i = 0; i < DIGITS + OUTPUT; ++i)
        {
            if ((digits[i].value == -1) && (digits[i].segments == 5))
            {
                if (count_set_bits(digits[i].bitmask ^ subtrahend_1) == 3)
                    digits[i].value = 3;
                else
                    digits[i].value = 5;
            }
            if ((digits[i].value == -1) && (digits[i].segments == 6))
            {
                if (count_set_bits(digits[i].bitmask ^ subtrahend_1) == 4)
                    digits[i].value = 0;
                else
                    digits[i].value = 6;
            }
        }

        sum += digits[DIGITS].value * 1000 + digits[DIGITS + 1].value * 100 +
               digits[DIGITS + 2].value * 10 + digits[DIGITS + 3].value;
    }

    return sum;
}

int main()
{
    char *buffer = read_file("input.txt");

    printf("Day 8!\n");
    printf("* pt. 1: %lu\n", count_unique(buffer));
    printf("* pt. 2: %lu\n", sum_output(buffer));

    free(buffer);

    return 0;
}