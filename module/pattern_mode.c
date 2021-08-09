#include "pattern_mode.h"
#include "teletype_io.h"

static uint8_t pattern_offset = 0;
static uint8_t dirty = 0;

void set_pattern_mode(void) {}
void process_pattern_keys(uint8_t key, uint8_t mod_key, bool is_held_key) {}
void process_pattern_knob(uint16_t knob, uint8_t mod_key) {}
uint8_t get_pattern_offset(void) { return pattern_offset; }
void set_pattern_offset(uint8_t offset) { pattern_offset = offset; }
void set_pattern_selected_value(uint8_t pattern, uint8_t offset) {}
void pattern_up(void) {}
void pattern_down(void) {}
void note_nudge(int8_t semitones) {}

// teletype_io.h
void tele_pattern_updated() { 
    dirty = 1;
}

uint8_t screen_refresh_pattern(void) {
  if (!dirty) return 0;
  dirty = 0;
  return 1;
}
