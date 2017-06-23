// clang-format off

#include "grid.h"
#include "state.h"
#include "teletype.h"

#define SG ss->grid
#define GP ss->grid.push[i]
#define GPC ss->grid.push[i].common
#define GF ss->grid.fader[i]
#define GFC ss->grid.fader[i].common

static bool grid_within_area(u8 x, u8 y, grid_common_t *gc);
static void grid_fill_area(u8 x, u8 y, u8 w, u8 h, u8 level);

void set_grid_led(scene_state_t *ss, u8 x, u8 y, s8 value) {
    SG.leds[x + (y << 4)] = value;
    SG.refresh = true;
}

void grid_refresh(scene_state_t *ss) {
    grid_fill_area(0, 0, 16, 16, 0);

    for (u8 i = 0; i < GRID_PUSH_COUNT; i++) {
        if (GPC.enabled) grid_fill_area(GPC.x, GPC.y, GPC.w, GPC.h, GP.state ? 15 : GP.background);
    }
        
    for (u8 i = 0; i < GRID_FADER_COUNT; i++) {
        if (GFC.enabled) {
            if (GF.dir) {
                grid_fill_area(GFC.x, GFC.y + GFC.w - GF.value - 1, GFC.w, GF.value + 1, 15);
                grid_fill_area(GFC.x, GFC.y, GFC.w, GFC.h - GF.value - 1, GF.background);
            } else {
                grid_fill_area(GFC.x, GFC.y, GF.value + 1, GFC.h, 15);
                grid_fill_area(GFC.x + GF.value + 1, GFC.y, GFC.w - GF.value - 1, GFC.h, GF.background);
            }
        }
    }

    for (u16 i = 0; i < monome_size_x() * monome_size_y(); i++) if (SG.leds[i] >= 0) monomeLedBuffer[i] = SG.leds[i];
    SG.refresh = 0;
}

void grid_process_key(scene_state_t *ss, u8 x, u8 y, u8 z) {
    u8 refresh = 0;
    
    for (u8 i = 0; i < GRID_PUSH_COUNT; i++) {
        if (GPC.enabled && grid_within_area(x, y, &GPC)) {
            GP.state = z;
            if (GP.script) run_script(ss, GP.script - 1);
            refresh = 1;
        }
    }
    
    for (u8 i = 0; i < GRID_FADER_COUNT; i++) {
        if (GFC.enabled && grid_within_area(x, y, &GFC)) {
            GF.value = GF.dir ? y - GFC.y : x - GFC.x;
            if (GF.script) run_script(ss, GF.script - 1);
            refresh = 1;
        }
    }
    
    SG.refresh = refresh;
}

bool grid_within_area(u8 x, u8 y, grid_common_t *gc) {
    return x >= gc->x && x < (gc->x + gc->w) && y >= gc->y && y < (gc->y + gc->h);
}

void grid_fill_area(u8 x, u8 y, u8 w, u8 h, u8 level) {
    u16 led_count = monome_size_x() * monome_size_y();
    u16 led;
    for (u16 _x = x; _x < x + w; _x++)
        for (u16 _y = y; _y < y + h; _y++) {
            led = _x + (_y << 4);
            if (led < led_count) monomeLedBuffer[led] = level;
        }
}

// clang-format on