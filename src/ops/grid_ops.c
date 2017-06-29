#include "ops/grid_ops.h"

#include "grid.h"
#include "helpers.h"
#include "monome.h"
#include "teletype_io.h"

// clang-format off

static void op_G_LED_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_LEDN_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_RECT_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_CLR_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

const tele_op_t op_G_LED = MAKE_GET_OP(G.LED, op_G_LED_get, 3, false);
const tele_op_t op_G_LEDN = MAKE_GET_OP(G.LEDN, op_G_LEDN_get, 2, false);
const tele_op_t op_G_RECT = MAKE_GET_OP(G.RECT, op_G_RECT_get, 6, false);
const tele_op_t op_G_CLR = MAKE_GET_OP(G.CLR, op_G_CLR_get, 0, false);

// in progress

static void op_GPUSH_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_GPUSH_ON_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_GPUSH_ON_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_GFDR_VAL_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_GFDR_VAL_set(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_GFDR_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);

const tele_op_t op_GPUSH = MAKE_GET_OP(GPUSH, op_GPUSH_get, 7, true);
const tele_op_t op_GPUSH_ON = MAKE_GET_OP(GPUSH.ON, op_GPUSH_ON_get, 1, true);
const tele_op_t op_GFDR = MAKE_GET_OP(GFDR, op_GFDR_get, 8, true);
const tele_op_t op_GFDR_VAL = MAKE_GET_SET_OP(GFDR.VAL, op_GFDR_VAL_get, op_GFDR_VAL_set, 1, true);

// clang-format on

static void op_G_LED_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 x = cs_pop(cs) - 1;
    s16 y = cs_pop(cs) - 1;
    GET_LEVEL(level);

    if (x < 0 || x > monome_size_x()) return;
    if (y < 0 || y > monome_size_y()) return;
    
    SG.leds[x + y * monome_size_x()] = level;
    SG.refresh = true;
}

static void op_G_LEDN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs) - 1;
    GET_LEVEL(level);
    
    if (i < 0 || i > GRID_LED_COUNT) return;

    SG.leds[i] = level;
    SG.refresh = true;
}

static void op_G_CLR_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *NOTUSED(cs)) {
    for (u16 i = 0; i < GRID_LED_COUNT; i++) SG.leds[i - 1] = -2;
    SG.refresh = true;
}

static void op_G_RECT_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 x = cs_pop(cs) - 1;
    s16 y = cs_pop(cs) - 1;
    s16 w = cs_pop(cs);
    s16 h = cs_pop(cs);
    GET_LEVEL(fill);
    GET_LEVEL(border);
    
    s16 n;
    s16 size_x = monome_size_x();
    for (s16 col = x + 1; col < x + w - 1; col++)
        for (s16 row = y + 1; row < y + h - 1; row++) {
            n = col + row * size_x;
            if (n >= 0 && n < GRID_LED_COUNT) SG.leds[n] = fill;
        }

    s16 row1 = y * size_x;
    s16 row2 = (y + h - 1) * size_x;
    for (s16 col = x; col < x + w; col++) {
        n = col + row1;
        if (n >= 0 && n < GRID_LED_COUNT) SG.leds[n] = border;
        n = col + row2;
        if (n >= 0 && n < GRID_LED_COUNT) SG.leds[n] = border;
    }

    for (s16 row = y; row < y + h; row++) {
        n = x + row * size_x;
        if (n >= 0 && n < GRID_LED_COUNT) SG.leds[n] = border;
        n = x + w - 1 + row * size_x;
        if (n >= 0 && n < GRID_LED_COUNT) SG.leds[n] = border;
    }

    SG.refresh = true;
}

// in progress

static void op_GPUSH_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t i = cs_pop(cs);
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    int16_t w = cs_pop(cs);
    int16_t h = cs_pop(cs);
    int16_t background = cs_pop(cs);
    int16_t script = cs_pop(cs);

    GPC.enabled = true;
    GPC.x = x;
    GPC.y = y;
    GPC.w = w;
    GPC.h = h;
    GPC.background = background;
    GPC.script = script;
    GP.state = 0;
    SG.refresh = 1;
}

static void op_GPUSH_ON_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t i = cs_pop(cs);
    cs_push(cs, GP.state);
}

static void op_GFDR_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t i = cs_pop(cs);
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    int16_t w = cs_pop(cs);
    int16_t h = cs_pop(cs);
    int16_t background = cs_pop(cs);
    int16_t dir = cs_pop(cs);
    int16_t script = cs_pop(cs);

    GFC.enabled = true;
    GFC.x = x;
    GFC.y = y;
    GFC.w = w;
    GFC.h = h;
    GFC.background = background;
    GFC.script = script;
    GF.dir = dir;
    GF.value = 0;
    SG.refresh = 1;
}

static void op_GFDR_VAL_get(const void *NOTUSED(data), scene_state_t *ss,
                       exec_state_t *NOTUSED(es), command_state_t *cs) {
    int8_t i = cs_pop(cs);

    int16_t value = (u32)GF.value * 16383 / (u32)((GF.dir ? GFC.h : GFC.w) - 1);
    cs_push(cs, value);
}

static void op_GFDR_VAL_set(const void *NOTUSED(data), scene_state_t *ss,
                       exec_state_t *NOTUSED(es), command_state_t *cs) {
    int8_t i = cs_pop(cs);
    int8_t value = cs_pop(cs);

    GF.value = value;
    SG.refresh = 1;
}
