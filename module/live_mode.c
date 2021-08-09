#include "live_mode.h"

// teletype
#include "teletype_io.h"

screen_grid_mode grid_mode = GRID_MODE_OFF;
uint8_t grid_page = 0;
uint8_t grid_show_controls = 0;

static uint8_t dirty = 0;

// teletype_io.h
void tele_has_delays(bool has_delays) {}
void tele_has_stack(bool has_stack) {}
void tele_mute() {}

void set_slew_icon(bool display) {}
void set_metro_icon(bool display) {}
void init_live_mode(void) {}
void set_live_mode(void) {}
void set_live_submode(u8 submode) {}
void set_grid_updated(void) {}
void history_next(void) {}
void history_prev(void) {}
void execute_line(void) {}
void process_live_keys(uint8_t key, uint8_t mod_key, bool is_held_key,
                       bool is_release, scene_state_t *ss) {}

void set_vars_updated(void) {
    dirty = 1;
}

uint8_t screen_refresh_live(scene_state_t *ss) {
  if (!dirty) return 0;
  dirty = 0;
  return 1;
}
