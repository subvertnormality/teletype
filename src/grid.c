#include "grid.h"
#include "state.h"
#include "teletype.h"

static bool grid_within_area(u8 x, u8 y, grid_common_t *gc);

void set_grid_led(scene_state_t *ss, u8 x, u8 y, s8 value) {
    ss->grid.leds[x + (y << 4)] = value;
    ss->grid.refresh = true;
}

void grid_refresh(scene_state_t *ss) {
    u16 led_count = monome_size_x() * monome_size_y();
    for (u16 i = 0; i < led_count; i++) monomeLedBuffer[i] = 0;

    for (u8 i = 0; i < GRID_PUSH_COUNT; i++) {
        if (ss->grid.push[i].common.enabled) {
            for (u8 x = ss->grid.push[i].common.x;
                 x < (ss->grid.push[i].common.x + ss->grid.push[i].common.w);
                 x++)
                for (u8 y = ss->grid.push[i].common.y;
                     y <
                     (ss->grid.push[i].common.y + ss->grid.push[i].common.h);
                     y++)
                    monomeLedBuffer[x + (y << 4)] =
                        ss->grid.push[i].state ? 15
                                               : ss->grid.push[i].background;
        }
    }

    for (u16 i = 0; i < led_count; i++)
        if (ss->grid.leds[i] >= 0) monomeLedBuffer[i] = ss->grid.leds[i];
    ss->grid.refresh = 0;
}

void grid_process_key(scene_state_t *ss, u8 x, u8 y, u8 z) {
    u8 refresh = 0;
    for (u8 i = 0; i < GRID_PUSH_COUNT; i++) {
        if (ss->grid.push[i].common.enabled &&
            grid_within_area(x, y, &ss->grid.push[i].common)) {
            ss->grid.push[i].state = z;
            if (ss->grid.push[i].script != -2)
                run_script(ss, ss->grid.push[i].script - 1);
            refresh = 1;
        }
    }
    for (u8 i = 0; i < GRID_FADER_COUNT; i++) {
        if (ss->grid.fader[i].common.enabled &&
            grid_within_area(x, y, &ss->grid.fader[i].common)) {
            if (!ss->grid.fader[i].script)
                run_script(ss, ss->grid.fader[i].script - 1);
            refresh = 1;
        }
    }
    ss->grid.refresh = refresh;
}

bool grid_within_area(u8 x, u8 y, grid_common_t *gc) {
    return x >= gc->x && x < (gc->x + gc->w) && y >= gc->y &&
           y < (gc->y + gc->h);
}