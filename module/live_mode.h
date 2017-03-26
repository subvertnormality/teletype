#ifndef _LIVE_MODE_H_
#define _LIVE_MODE_H_

#include "stdbool.h"
#include "stdint.h"

void set_live_mode(void);
void process_live_keys(uint8_t key, uint8_t mod_key, bool is_held_key);
void screen_refresh_live(void);

#endif
