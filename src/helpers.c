#include "helpers.h"

#include <string.h>

#include "table.h"
#include "util.h"

int16_t normalise_value(int16_t min, int16_t max, int16_t wrap, int16_t value) {
    if (value >= min && value <= max) return value;

    if (wrap) {
        if (value < min)
            return max;
        else
            return min;
    }
    else {
        if (value < min)
            return min;
        else
            return max;
    }
}

const char *to_voltage(int16_t i) {
    static char n[3], v[7];
    int16_t a = 0, b = 0;

    if (i > table_v[8]) {
        i -= table_v[8];
        a += 8;
    }

    if (i > table_v[4]) {
        i -= table_v[4];
        a += 4;
    }

    if (i > table_v[2]) {
        i -= table_v[2];
        a += 2;
    }

    if (i > table_v[1]) {
        i -= table_v[1];
        a += 1;
    }

    if (i > table_vv[64]) {
        i -= table_vv[64];
        b += 64;
    }

    if (i > table_vv[32]) {
        i -= table_vv[32];
        b += 32;
    }

    if (i > table_vv[16]) {
        i -= table_vv[16];
        b += 16;
    }

    if (i > table_vv[8]) {
        i -= table_vv[8];
        b += 8;
    }

    if (i > table_vv[4]) {
        i -= table_vv[4];
        b += 4;
    }

    if (i > table_vv[2]) {
        i -= table_vv[2];
        b++;
    }

    if (i > table_vv[1]) {
        i -= table_vv[1];
        b++;
    }

    b++;

    itoa(a, n, 10);
    strcpy(v, n);
    strcat(v, ".");
    itoa(b, n, 10);
    strcat(v, n);
    strcat(v, "V");

    return v;
}

int16_t bit_reverse(int16_t unreversed, int8_t bits_to_reverse) {
    int16_t reversed = 0;
    for (int i = 0; i < bits_to_reverse; i++) {
        if ((unreversed & (1 << i)))
            reversed |= 1 << ((bits_to_reverse - 1) - i);
    }
    return reversed;
}

int16_t rev_bitstring_to_int(const char *token) {
    int8_t length = strlen(token);
    int16_t value = 0;
    for (int8_t i = 0; i < length; i++) {
        if (token[i] == '1') { value += 1 << i; }
    }
    return value;
}

void itoa_hex(uint16_t value, char *out) {
    static char num[] = "0123456789ABCDEF";

    out[0] = 'X';
    uint8_t v, index = 1, dont_ignore_zeros = 0;

    for (int8_t i = 3; i >= 0; i--) {
        v = (value >> (i << 2)) & 0xf;
        if (dont_ignore_zeros || v) {
            out[index++] = num[v];
            dont_ignore_zeros = 1;
        }
    }

    if (!dont_ignore_zeros) out[index++] = '0';
    out[index] = '\0';
}

void itoa_bin(uint16_t value, char *out) {
    out[0] = 'B';
    uint8_t v, index = 1, dont_ignore_zeros = 0;

    for (int8_t i = 15; i >= 0; i--) {
        v = (value >> i) & 1;
        if (dont_ignore_zeros || v) {
            out[index++] = '0' + v;
            dont_ignore_zeros = 1;
        }
    }

    if (!dont_ignore_zeros) out[index++] = '0';
    out[index] = '\0';
}

void itoa_rbin(uint16_t value, char *out) {
    out[0] = 'R';
    uint8_t v, index = 1;

    for (int8_t i = 0; i < 16; i++) {
        v = (value >> i) & 1;
        out[index++] = '0' + v;
    }

    index = 0;
    for (int8_t i = 16; i > 0; i--) {
        if (out[i] == '1') {
            index = i;
            break;
        }
    }
    if (index == 0) {
        index = 1;
        out[index] = '0';
    }
    out[index + 1] = '\0';
}
