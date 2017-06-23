#include "ops/grid_ops.h"

#include "grid.h"
#include "helpers.h"
#include "monome.h"
#include "teletype_io.h"

static void op_LED_get(const void *data, scene_state_t *ss, exec_state_t *es,
                       command_state_t *cs);
static void op_LED_set(const void *data, scene_state_t *ss, exec_state_t *es,
                       command_state_t *cs);
static void op_GPUSH_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_GPUSH_ON_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);

static void op_GPUSH_ON_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_GFDR_VAL_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_GFDR_VAL_set(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_GFDR_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);

// clang-format off
const tele_op_t op_LED = MAKE_GET_SET_OP(LED, op_LED_get, op_LED_set, 2, true);
const tele_op_t op_GPUSH = MAKE_GET_OP(GPUSH, op_GPUSH_get, 7, true);
const tele_op_t op_GPUSH_ON = MAKE_GET_OP(GPUSH.ON, op_GPUSH_ON_get, 1, true);
const tele_op_t op_GFDR = MAKE_GET_OP(GFDR, op_GFDR_get, 8, true);
const tele_op_t op_GFDR_VAL = MAKE_GET_SET_OP(GFDR.VAL, op_GFDR_VAL_get, op_GFDR_VAL_set, 1, true);
// clang-format on

static void op_LED_get(const void *NOTUSED(data), scene_state_t *ss,
                       exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);

    cs_push(cs, ss->grid.leds[(y << 4) + x]);
}

static void op_LED_set(const void *NOTUSED(data), scene_state_t *ss,
                       exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    int16_t level = cs_pop(cs);

    set_grid_led(ss, x, y, level);
}

static void op_GPUSH_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t id = cs_pop(cs);
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    int16_t w = cs_pop(cs);
    int16_t h = cs_pop(cs);
    int16_t background = cs_pop(cs);
    int16_t script = cs_pop(cs);

    ss->grid.push[id].common.enabled = true;
    ss->grid.push[id].common.x = x;
    ss->grid.push[id].common.y = y;
    ss->grid.push[id].common.w = w;
    ss->grid.push[id].common.h = h;
    ss->grid.push[id].background = background;
    ss->grid.push[id].script = script;
    ss->grid.push[id].state = 0;
    ss->grid.refresh = 1;
}

static void op_GPUSH_ON_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t id = cs_pop(cs);
    cs_push(cs, ss->grid.push[id].state);
}

static void op_GFDR_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t id = cs_pop(cs);
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    int16_t w = cs_pop(cs);
    int16_t h = cs_pop(cs);
    int16_t background = cs_pop(cs);
    int16_t dir = cs_pop(cs);
    int16_t script = cs_pop(cs);

    ss->grid.fader[id].common.enabled = true;
    ss->grid.fader[id].common.x = x;
    ss->grid.fader[id].common.y = y;
    ss->grid.fader[id].common.w = w;
    ss->grid.fader[id].common.h = h;
    ss->grid.fader[id].background = background;
    ss->grid.fader[id].dir = dir;
    ss->grid.fader[id].script = script;
    ss->grid.fader[id].value = 0;
    ss->grid.refresh = 1;
}

static void op_GFDR_VAL_get(const void *NOTUSED(data), scene_state_t *ss,
                       exec_state_t *NOTUSED(es), command_state_t *cs) {
    int8_t id = cs_pop(cs);

    int16_t value = (u32)ss->grid.fader[id].value * 16383 / 
        (u32)((ss->grid.fader[id].dir ? ss->grid.fader[id].common.h : ss->grid.fader[id].common.w) - 1);
    cs_push(cs, value);
}

static void op_GFDR_VAL_set(const void *NOTUSED(data), scene_state_t *ss,
                       exec_state_t *NOTUSED(es), command_state_t *cs) {
    int8_t id = cs_pop(cs);
    int8_t value = cs_pop(cs);

    ss->grid.fader[id].value = value;
    ss->grid.refresh = 1;
}

