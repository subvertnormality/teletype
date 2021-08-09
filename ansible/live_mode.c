#include "live_mode.h"

// teletype
#include "teletype_io.h"

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

uint8_t get_live_sub_mode() {
    return 0;
}

void set_live_submode(u8 submode) {}

void select_dash_screen(uint8_t screen) {}

void print_dashboard_value(uint8_t index, int16_t value) {}

int16_t get_dashboard_value(uint8_t index) {
    return 0;
}

void set_grid_updated(void) {}

void set_mutes_updated() {}

void history_next(void) {}
void history_prev(void) {}
void execute_line(void) {}
void process_live_keys(uint8_t key, uint8_t mod_key, bool is_held_key,
                       bool is_release, scene_state_t *ss) {}

void set_vars_updated(void) {
    dirty = 1;
}

void set_dash_updated() {}

uint8_t screen_refresh_live() {
  if (!dirty) return 0;
  dirty = 0;
  return 1;
}
