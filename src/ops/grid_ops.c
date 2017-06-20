#include "ops/grid_ops.h"

#include "grid.h"
#include "helpers.h"
#include "monome.h"
#include "teletype_io.h"

/*
if OP is different on where it's used 
(update something with extra value if first, return something with no extra value otherwise)
use MAKE_GET_SET_OP with number of parameters without the extra value and set return to true
but you can't use this unless the difference between get and set is really just one parameter... :(

if OP always sets something (doesn't return)
use MAKE_GET_OP with the actual number of parameters and set return to false

if OP always returns something
use MAKE_GET_OP with the actual number of parameters and set return to true
*/

static void op_LED_get(const void *data, scene_state_t *ss, exec_state_t *es,
                      command_state_t *cs);
static void op_LED_set(const void *data, scene_state_t *ss, exec_state_t *es,
                      command_state_t *cs);
static void op_GPUSH_get(const void *data, scene_state_t *ss, exec_state_t *es,
                      command_state_t *cs);
static void op_GPUSH_ON_get(const void *data, scene_state_t *ss, exec_state_t *es,
                      command_state_t *cs);
					  
// clang-format off
const tele_op_t op_LED = MAKE_GET_SET_OP(LED, op_LED_get, op_LED_set, 2, true);
const tele_op_t op_GPUSH = MAKE_GET_OP(GPUSH, op_GPUSH_get, 7, true);
const tele_op_t op_GPUSH_ON = MAKE_GET_OP(GPUSH.ON, op_GPUSH_ON_get, 1, true);
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
	
    ss->grid.push[id].enabled = true;
	ss->grid.push[id].x = x;
	ss->grid.push[id].y = y;
	ss->grid.push[id].w = w;
	ss->grid.push[id].h = h;
	ss->grid.push[id].background = background;
	ss->grid.push[id].script = script;
	ss->grid.push[id].state = 0;
}

static void op_GPUSH_ON_get(const void *NOTUSED(data), scene_state_t *ss,
                      exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t id = cs_pop(cs);
    cs_push(cs, ss->grid.push[id].state);
}

