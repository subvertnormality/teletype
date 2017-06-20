#include "grid.h"
#include "state.h"
#include "teletype.h"

void set_grid_led(scene_state_t *ss, u8 x, u8 y, s8 value) {
    ss->grid.leds[x + (y << 4)] = value;
    ss->grid.refresh = true;
}

void grid_refresh(scene_state_t *ss) {
	u16 led_count = monome_size_x() * monome_size_y();
	for (u16 i = 0; i < led_count; i++) monomeLedBuffer[i] = 0;
	
	for (u8 i = 0; i < GRID_PUSH_COUNT; i++) {
		if (ss->grid.push[i].enabled) {
			for (u8 x = ss->grid.push[i].x; x < (ss->grid.push[i].x + ss->grid.push[i].w); x++)
				for (u8 y = ss->grid.push[i].y; y < (ss->grid.push[i].y + ss->grid.push[i].h); y++)
					monomeLedBuffer[x + (y << 4)] = ss->grid.push[i].state ? 15 : ss->grid.push[i].background;
		}
	}
	
	for (u16 i = 0; i < led_count; i++) if (ss->grid.leds[i] >= 0) monomeLedBuffer[i] = ss->grid.leds[i];
	ss->grid.refresh = 0;
}

void grid_process_key(scene_state_t *ss, u8 x, u8 y, u8 z) {
	for (u8 i = 0; i < GRID_PUSH_COUNT; i++) {
		if (ss->grid.push[i].enabled && x >= ss->grid.push[i].x && x < (ss->grid.push[i].x + ss->grid.push[i].w) &&
		    y >= ss->grid.push[i].y && y < (ss->grid.push[i].y + ss->grid.push[i].h)) {
			ss->grid.push[i].state = z;
			if (ss->grid.push[i].script != -2) run_script(ss, ss->grid.push[i].script - 1);
			ss->grid.refresh = 1;
		}
	}
}
