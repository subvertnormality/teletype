#include "grid.h"
#include "state.h"

void set_grid_led(scene_state_t *ss, uint8_t x, uint8_t y, int8_t value) {
    ss->grid_leds[x + (y << 4)] = value;
    ss->grid_refresh = true;
}

void grid_refresh(scene_state_t *ss) {
	u16 led_count = monome_size_x() * monome_size_y();
	for (u16 i = 0; i < led_count; i++) monomeLedBuffer[i] = 0;
	for (u16 i = 0; i < led_count; i++) if (ss->grid_leds[i] >= 0) monomeLedBuffer[i] = ss->grid_leds[i];
	ss->grid_refresh = 0;
}

void grid_process_key(scene_state_t *ss, u8 x, u8 y, u8 z) {
	set_grid_led(ss, x, y, z ? 15 : -1);
}
