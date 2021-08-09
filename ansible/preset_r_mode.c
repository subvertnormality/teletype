#include "preset_r_mode.h"
#include "flash.h"
#include "globals.h"

void set_preset_r_mode(uint8_t preset) {}

void process_preset_r_load() {
    do_preset_read();
}

void preset_line_down(void) {}
void preset_line_up(void) {}
void process_preset_r_keys(uint8_t key, uint8_t mod_key, bool is_held_key) {}
uint8_t screen_refresh_preset_r(void) { return 0; }

static uint8_t preset_last;

uint8_t get_preset() {
    return preset_last;
}

void process_preset_r_preset(uint8_t preset) {
    if (preset != preset_last) {
        preset_select = preset;
        preset_last = preset;
    }
}

static void do_preset_read(void) {
    ss_grid_init(&scene_state);
    flash_read(preset_select, &scene_state, &scene_text, 1, 1, 1);
    flash_update_last_saved_scene(preset_select);
    ss_set_scene(&scene_state, preset_select);

    set_dash_updated();
    scene_state.initializing = true;
    run_script(&scene_state, INIT_SCRIPT);
    scene_state.initializing = false;

    set_last_mode();
}

