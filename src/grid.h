#ifndef _GRID_H_
#define _GRID_H_

#include "monome.h"
#include "state.h"

#define SG  ss->grid
#define GP  ss->grid.push[i]
#define GPC ss->grid.push[i].common
#define GF  ss->grid.fader[i]
#define GFC ss->grid.fader[i].common

extern void grid_refresh(scene_state_t *ss);
extern void grid_process_key(scene_state_t *ss, u8 x, u8 y, u8 z);

#endif
