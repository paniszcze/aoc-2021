#include <stdio.h>
#include <stdlib.h>
#include "../file.c"

#define VERSION 1
#define VALUE 0

#define BITS_CAP 1024
#define BITS_PER_BYTE 8
#define VER_BITS 3
#define TYP_BITS 3
#define PFX_BITS 1
#define VAL_BITS 4
#define LID_BITS 1
#define LEN_BITS 15
#define NUM_BITS 11

int8_t hex_str_to_dec(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return -1;
}

void print_bitstream(u_int8_t n)
{
    for (size_t i = 0; i < BITS_PER_BYTE; ++i)
        printf("%d", (n >> (BITS_PER_BYTE - i - 1)) & 1);
}

u_int64_t read_nbits(u_int8_t *bits, size_t *pos, size_t n)
{
    u_int64_t value = 0;

    for (size_t i = 0; i < n; ++i)
    {
        value |= ((bits[*pos >> 3] >> (BITS_PER_BYTE - *pos % BITS_PER_BYTE - 1)) & 1) <<
                 (n - i - 1);
        ++(*pos);
    }

    return value;
}

u_int64_t read_value(u_int8_t *bits, size_t *pos)
{
    u_int64_t prefix = 1, value = 0;
    do {
        prefix = read_nbits(bits, pos, PFX_BITS);
        value = (value | read_nbits(bits, pos, VAL_BITS)) << VAL_BITS;
    } while (prefix != 0);
    value >>= VAL_BITS;
    printf(">> val %llu\n", value);

    return value;
}

u_int64_t calculate(u_int64_t type_id, u_int64_t value, u_int64_t tmp_value)
{
    switch (type_id)
    {
    case 0:
        value += tmp_value;
        break;
    case 1:
        value *= tmp_value;
        break;
    case 2:
        value = value < tmp_value ? value : tmp_value;
        break;
    case 3:
        value = value > tmp_value ? value : tmp_value;
        break;
    case 5:
        value = value > tmp_value ? 1 : 0;
        break;
    case 6:
        value = value < tmp_value ? 1 : 0;
        break;    
    case 7:
        value = value == tmp_value ? 1 : 0;
        break;
    default:
        break;
    }

    printf("-- curr val %llu\n", value);
    return value;
}

void pad_pos(size_t *pos)
{
    while (*pos % 4 != 0)
        ++(*pos);
}

u_int64_t read_packet(u_int8_t *bits,
                 size_t *pos,
                 size_t *last_pos,
                 u_int64_t *version_sum,
                 u_int64_t *curr_value,
                 u_int64_t *final_value)
{
    if (*pos > *last_pos)
        return 0;

    u_int64_t version = read_nbits(bits, pos, VER_BITS);
    *version_sum += version;

    u_int64_t type_id = read_nbits(bits, pos, TYP_BITS);
    printf("type %llu, ver %llu\n", type_id, version);

    if (type_id == 4)
    {
        *curr_value = read_value(bits, pos);
    }
    else
    {
        u_int64_t length_id = read_nbits(bits, pos, LID_BITS);

        if (length_id == 0)
        {
            u_int64_t lenght = read_nbits(bits, pos, LEN_BITS);
            u_int64_t end = *pos + lenght;
            // printf("-- len %llu\n", lenght);
            while (*pos < end && *pos <= *last_pos)
            {
                u_int64_t tmp_value = read_packet(bits, pos, last_pos, version_sum, curr_value, final_value);
                *curr_value = calculate(type_id, *curr_value, tmp_value);
            }
        }
        else
        {
            u_int64_t packet_num = read_nbits(bits, pos, NUM_BITS);
            // printf("-- num %llu\n", packet_num);
            for (u_int64_t i = 0; i < packet_num; ++i)
            {
                u_int64_t tmp_value = read_packet(bits, pos, last_pos, version_sum, curr_value, final_value);
                *curr_value = calculate(type_id, *curr_value, tmp_value);
                if (*pos > *last_pos)
                    break;
            }
        }
    }

    if (*pos > *last_pos)
        pad_pos(pos);

    return 0;
}

u_int64_t decode_transmission(char *buffer, int mode)
{
    for (size_t k = 0; k < 8; ++k)
    {

    size_t hex_count = 0;
    u_int8_t bits[BITS_CAP] = {0};

    // convert hex string into binary and store the bitstrem in an array of U8
    while (*buffer != '\n' && *buffer != 0)
    {
        size_t byte_indx = hex_count >> 1;
        bits[byte_indx] |= hex_str_to_dec(*buffer++) & 0b1111;
        if (++hex_count & 1)
            bits[byte_indx] <<= 4;
    }

    size_t bytes_count = hex_count >> 1;

    // print the bitstream
    for (size_t i = 0; i < bytes_count; ++i)
        print_bitstream(bits[i]);
    printf("\n");

    // find position where 0's start on the righthand side to make sure not to decode padding
    size_t last_pos = bytes_count * BITS_PER_BYTE - 1, pos = last_pos;
    while (read_nbits(bits, &pos, 1) == 0)
    {
        --last_pos;
        pos = last_pos;
    }

    // decode the transmission
    u_int64_t version_sum = 0, curr_value = 0, final_value;
    pos = 0;

    while (pos <= last_pos)
    {
        read_packet(bits, &pos, &last_pos, &version_sum, &curr_value, &final_value);
        printf("======= sum %llu\n", version_sum);
    }

    ++buffer;
    }

    return 0;
}

int main()
{
    char *buffer = read_file("samples.txt");

    printf("Day 16!\n");
    printf("* pt. 1: %llu\n", decode_transmission(buffer, VERSION));
    // printf("* pt. 2: %lu\n", decode_transmission(buffer, VALUE));

    free(buffer);

    return 0;
}