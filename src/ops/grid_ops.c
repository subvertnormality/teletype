#include "ops/grid_ops.h"

#include "grid.h"
#include "helpers.h"
#include "monome.h"
#include "teletype_io.h"

static void op_LED_get(const void *data, scene_state_t *ss, exec_state_t *es,
                      command_state_t *cs);
static void op_LED_set(const void *data, scene_state_t *ss, exec_state_t *es,
                      command_state_t *cs);

// clang-format off
const tele_op_t op_LED = MAKE_GET_SET_OP(LED, op_LED_get, op_LED_set, 2, true);
// clang-format on

static void op_LED_get(const void *NOTUSED(data), scene_state_t *ss,
                      exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);

    cs_push(cs, ss->grid_leds[(y << 4) + x]);
}

static void op_LED_set(const void *NOTUSED(data), scene_state_t *ss,
                      exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t x = cs_pop(cs);
    int16_t y = cs_pop(cs);
    int16_t level = cs_pop(cs);
    
    set_grid_led(ss, x, y, level);
}
