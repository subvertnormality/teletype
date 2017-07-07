#ifndef _GRID_H_
#define _GRID_H_

#include "monome.h"
#include "state.h"

#define SG ss->grid
#define GB ss->grid.button[i]
#define GBC ss->grid.button[i].common
#define GF ss->grid.fader[i]
#define GFC ss->grid.fader[i].common
#define GXY ss->grid.xypad[i]
#define GXYC ss->grid.xypad[i].common

#define GET_AND_CLAMP(value, min, max) \
    s16 value = cs_pop(cs);            \
    if (value < (min))                 \
        value = (min);                 \
    else if (value > (max))            \
        value = (max);

#define GET_LEVEL(level)    \
    s16 level = cs_pop(cs); \
    if (level < LED_OFF)    \
        level = LED_OFF;    \
    else if (level > 15)    \
        level = 15;

extern void grid_refresh(scene_state_t *ss);
extern void grid_process_key(scene_state_t *ss, u8 x, u8 y, u8 z);

#endif
