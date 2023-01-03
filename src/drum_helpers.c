#include "drum_helpers.h"
#include "table.h"
#include <stdio.h>

static int wrap(int const k, int const lower_bound, int const upper_bound)
{
    int range = upper_bound - lower_bound + 1;
    int kx = ((k - lower_bound) % range);
    if (kx < 0)
        return upper_bound + 1 + kx;
    else
        return lower_bound + kx;
}


static char get_byte(const char* a, int n) {
    return a[n / 8];
}

static int get_bit(const char* a, int k) {
    char byte = get_byte(a, k);
    int bit_index = 7 - (k % 8);

    return (byte & (1 << bit_index)) != 0;
}


// 8 / 3 3 2
// 16/ 6 6 4
// 24 / 9 9 6
// 32/ 12 12 8
// 40 / 15 15 10
// 48 / 18 18 12
// 56 / 21 21 14
// 64/ 24 24 16

// banks
// 0: increasing intensity random
// 1: BD
// 2: SD
// 3: CH
// 4: OH/CY



int tresillo(int bank, int pattern1, int pattern2, int len, int step) {

    if (len < 8) return 0;
    if (step < 1) return 0;

    const char* table1;
    const char* table2;

    switch (bank) {
        case 0: 
            if (pattern1 > 32 || pattern2 > 32 ) return 0;
            table1 = table_t_r_e[pattern1];
            table2 = table_t_r_e[pattern2];
            break;
        case 1:
            if (pattern1 > 215 || pattern2 > 215 ) return 0;
            table1 = table_dr_bd[pattern1];
            table2 = table_dr_bd[pattern2];
            break;
        case 2:
            if (pattern1 > 215 || pattern2 > 215 ) return 0;
            table1 = table_dr_sd[pattern1];
            table2 = table_dr_sd[pattern2];
            break;
        case 3:
            if (pattern1 > 215 || pattern2 > 215 ) return 0;
            table1 = table_dr_ch[pattern1];
            table2 = table_dr_ch[pattern2];
            break;
        case 4:
            if (pattern1 > 215 || pattern2 > 215 ) return 0;
            table1 = table_dr_oh[pattern1];
            table2 = table_dr_oh[pattern2];
            break;
    }

    
    int multiplier = len / 8;

    int three = 3 * multiplier;
    int wrapped_step = wrap(step, 1, multiplier * 8);

    
    if (wrapped_step <= three) {
        return get_bit(table1, wrapped_step - 1);
    } else if (wrapped_step <= three * 2) {
        return get_bit(table1, wrapped_step - three - 1);
    }

    return get_bit(table2, wrapped_step - (three * 2) - 1);  
}

int drum(int bank, int pattern, int step) {

    if (bank < 0 || bank > 4) return 0;
    if (step < 1) return 0;

    const char* table;

    switch (bank) {
        case 0: 
            if (pattern > 32) return 0;
            table = table_t_r_e[pattern];
            break;
        case 1:
            if (pattern > 215) return 0;
            table = table_dr_bd[pattern];
            break;
        case 2:
            if (pattern > 215) return 0;
            table = table_dr_sd[pattern];
            break;
        case 3:
            if (pattern > 215) return 0;
            table = table_dr_ch[pattern];
            break;
        case 4:
            if (pattern > 215) return 0;
            table = table_dr_oh[pattern];
            break;
    }

    int wrapped_step = wrap(step, 1, 16);

    return get_bit(table, wrapped_step - 1);  
}

int velocity(int pattern, int step) {

    if (step < 1) return 0;
    if (pattern < 0 || pattern > 9) return 0;

    const uint8_t* table = table_vel_helper[pattern];
    int wrapped_step = wrap(step, 1, 16);
    return table[wrapped_step - 1];
}