#ifndef _GRID_H_
#define _GRID_H_

#include "state.h"
#include "monome.h"

extern void set_grid_led(scene_state_t *ss, uint8_t x, uint8_t y, int8_t value);
extern void grid_refresh(scene_state_t *ss);
extern void grid_process_key(scene_state_t *ss, u8 x, u8 y, u8 z);

#endif
