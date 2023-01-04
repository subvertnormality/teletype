#ifndef _TABLE_H_
#define _TABLE_H_

#include "music.h"

// use the same note table (from libavr32) as ansible
#define table_n ET
#define nb_nbx_scale_presets 20
extern const int16_t table_v[11];
extern const int16_t table_vv[100];
extern const int16_t table_hzv[76];
extern const int16_t table_exp[256];
extern const uint16_t table_nr[32];
extern const uint8_t table_n_s[9][7];
extern const uint8_t table_n_c[13][4];
extern const uint8_t table_n_cs[9][7];
extern const uint16_t table_n_b[nb_nbx_scale_presets];
extern const char table_t_r_e[33][3];
extern const char table_dr_bd[216][2];
extern const char table_dr_sd[216][2];
extern const char table_dr_ch[216][2];
extern const char table_dr_oh[216][2];
extern const uint8_t table_vel_helper[10][16];

#endif
