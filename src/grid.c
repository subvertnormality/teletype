#include "grid.h"
#include "state.h"
#include "teletype.h"

static bool grid_within_area(u8 x, u8 y, grid_common_t *gc);
static void grid_fill_area(u8 x, u8 y, u8 w, u8 h, u8 level);

void grid_refresh(scene_state_t *ss) {
    s16 size_x = monome_size_x();
    s16 size_y = monome_size_y();

    grid_fill_area(0, 0, size_x, size_y, 0);

    u16 x, y;
    for (u8 i = 0; i < GRID_XYPAD_COUNT; i++) {
        if (GXYC.enabled && SG.group[GXYC.group].enabled) {
            if (GXY.value_x || GXY.value_y) {
                x = GXYC.x + GXY.value_x - 1;
                y = GXYC.y + GXY.value_y - 1;
                grid_fill_area(GXYC.x, y, GXYC.w, 1, GXYC.background);
                grid_fill_area(x, GXYC.y, 1, GXYC.h, GXYC.background);
                grid_fill_area(x, y, 1, 1, 15);
            }
        }
    }

    for (u8 i = 0; i < GRID_FADER_COUNT; i++) {
        if (GFC.enabled && SG.group[GFC.group].enabled) {
            if (GF.dir) {
                grid_fill_area(GFC.x, GFC.y, GFC.w, GFC.h - GF.value - 1, GFC.background);
                grid_fill_area(GFC.x, GFC.y + GFC.h - GF.value - 1, GFC.w, GF.value + 1, 15);
            } else { 
                grid_fill_area(GFC.x, GFC.y, GF.value + 1, GFC.h, 15);
                grid_fill_area(GFC.x + GF.value + 1, GFC.y, GFC.w - GF.value - 1, GFC.h, GFC.background);
            }
        }
    }

    for (u8 i = 0; i < GRID_BUTTON_COUNT; i++)
        if (GBC.enabled && SG.group[GBC.group].enabled) grid_fill_area(GBC.x, GBC.y, GBC.w, GBC.h, GB.state ? 15 : GBC.background);
        
    for (u16 i = 0; i < size_x * size_y; i++) {
        if (SG.leds[i] >= 0)
            monomeLedBuffer[i] = SG.leds[i];
        else if (SG.leds[i] == LED_DIM)
            monomeLedBuffer[i] >>= 1;
        else if (SG.leds[i] == LED_BRI) {
            monomeLedBuffer[i] <<= 1;
            if (monomeLedBuffer[i] > 15) monomeLedBuffer[i] = 15;
            else if (monomeLedBuffer[i] == 0) monomeLedBuffer[i] = 1;
        }
        
        if (monomeLedBuffer[i] < SG.dim)
            monomeLedBuffer[i] = 0;
        else
            monomeLedBuffer[i] -= SG.dim;
    }
    
    if (SG.rotate) {
        u16 total = size_x * size_y;
        u8 temp;
        for (u16 i = 0; i < (total >> 1); i++) {
            temp = monomeLedBuffer[i];
            monomeLedBuffer[i] = monomeLedBuffer[total - i - 1];
            monomeLedBuffer[total - i - 1] = temp;
        }
    }
        
    
    SG.refresh = 0;
}

void grid_process_key(scene_state_t *ss, u8 _x, u8 _y, u8 z) {
    u8 x = SG.rotate ? monome_size_x() - _x - 1 : _x;
    u8 y = SG.rotate ? monome_size_y() - _y - 1 : _y;
    u8 refresh = 0;
    u8 scripts[SCRIPT_COUNT];
    for (u8 i = 0; i < SCRIPT_COUNT; i++) scripts[i] = 0;
    
    for (u8 i = 0; i < GRID_XYPAD_COUNT; i++) {
        if (GXYC.enabled && SG.group[GXYC.group].enabled && grid_within_area(x, y, &GXYC)) {
            GXY.value_x = x - GXYC.x + 1;
            GXY.value_y = y - GXYC.y + 1;
            if (GXYC.script != -1) scripts[GXYC.script] = 1;
            SG.latest_group = GXYC.group;
            if (SG.group[GXYC.group].script != -1) scripts[SG.group[GXYC.group].script] = 1;
            refresh = 1;
        }
    }

    for (u8 i = 0; i < GRID_FADER_COUNT; i++) {
        if (GFC.enabled && SG.group[GFC.group].enabled && grid_within_area(x, y, &GFC)) {
            GF.value = GF.dir ? GFC.h + GFC.y - y - 1 : x - GFC.x;
            if (GFC.script != -1) scripts[GFC.script] = 1;
            SG.latest_fader = i;
            SG.latest_group = GFC.group;
            if (SG.group[GFC.group].script != -1) scripts[SG.group[GFC.group].script] = 1;
            refresh = 1;
        }
    }

    for (u8 i = 0; i < GRID_BUTTON_COUNT; i++) {
        if (GBC.enabled && SG.group[GBC.group].enabled && grid_within_area(x, y, &GBC)) {
            if (GB.latch) {
                if (z) {
                    GB.state = !GB.state;
                    if (GBC.script != -1) scripts[GBC.script] = 1;
                }
            } else {
                GB.state = z;
                if (GBC.script != -1) scripts[GBC.script] = 1;
            }
            SG.latest_button = i;
            SG.latest_group = GBC.group;
            if (SG.group[GBC.group].script != -1) scripts[SG.group[GBC.group].script] = 1;
            refresh = 1;
        }
    }
    
    for (u8 i = 0; i < SCRIPT_COUNT; i++)
        if (scripts[i]) run_script(ss, i);

    SG.refresh = refresh;
}

bool grid_within_area(u8 x, u8 y, grid_common_t *gc) {
    return x >= gc->x && x < (gc->x + gc->w) && y >= gc->y && y < (gc->y + gc->h);
}

void grid_fill_area(u8 x, u8 y, u8 w, u8 h, u8 level) {
    s16 size_x = monome_size_x();
    s16 size_y = monome_size_y();

    if (level == LED_OFF) return;
    
    if (level == LED_DIM) {
        for (u16 _x = max(0, x); _x < min(size_x, x + w); _x++)
            for (u16 _y = max(0, y); _y < min(size_y, y + h); _y++)
                monomeLedBuffer[_x + _y * size_x] >>= 1;

    } else if (level == LED_BRI) {
        for (u16 _x = max(0, x); _x < min(size_x, x + w); _x++)
            for (u16 _y = max(0, y); _y < min(size_y, y + h); _y++) {
                monomeLedBuffer[_x + _y * size_x] <<= 1; 
                if (monomeLedBuffer[_x + _y * size_x] > 15) monomeLedBuffer[_x + _y * size_x] = 15;
            }
        
    } else {
        for (u16 _x = max(0, x); _x < min(size_x, x + w); _x++)
            for (u16 _y = max(0, y); _y < min(size_y, y + h); _y++)
                monomeLedBuffer[_x + _y * size_x] = level;
    }
}
