#include "ops/grid_ops.h"

#include "grid.h"
#include "helpers.h"
#include "monome.h"
#include "teletype_io.h"

void grid_common_init(grid_common_t *gc);

// clang-format off

static void op_G_RST_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_DIM_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_CLR_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

static void op_G_GRP_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GRP_EN_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GRP_C_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GRP_SW_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GRP_SC_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GRPI_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

static void op_G_LED_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_LED_C_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_LEDN_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_LEDN_C_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_REC_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

static void op_G_BTN_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GBTN_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTNX_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTN_EN_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTN_V_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTN_V_set (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTN_L_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTNI_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTNV_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTNL_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTN_SW_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GBTN_V_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GBTN_L_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

const tele_op_t op_G_RST    = MAKE_GET_OP(G.DIM, op_G_RST_get, 0, false);
const tele_op_t op_G_DIM    = MAKE_GET_OP(G.DIM, op_G_DIM_get, 1, false);
const tele_op_t op_G_CLR    = MAKE_GET_OP(G.CLR, op_G_CLR_get, 0, false);

const tele_op_t op_G_GRP    = MAKE_GET_OP(G.GRP, op_G_GRP_get, 1, false);
const tele_op_t op_G_GRP_EN = MAKE_GET_OP(G.GRP.EN, op_G_GRP_EN_get, 2, false);
const tele_op_t op_G_GRP_C  = MAKE_GET_OP(G.GRP.EN, op_G_GRP_C_get, 1, false);
const tele_op_t op_G_GRP_SW = MAKE_GET_OP(G.GRP.SW, op_G_GRP_SW_get, 1, false);
const tele_op_t op_G_GRP_SC = MAKE_GET_OP(G.GRP.SC, op_G_GRP_SC_get, 2, false);
const tele_op_t op_G_GRPI   = MAKE_GET_OP(G.GRPI, op_G_GRPI_get, 1, true);

const tele_op_t op_G_LED    = MAKE_GET_OP(G.LED, op_G_LED_get, 3, false);
const tele_op_t op_G_LED_C  = MAKE_GET_OP(G.LED.C, op_G_LED_C_get, 2, false);
const tele_op_t op_G_LEDN   = MAKE_GET_OP(G.LEDN, op_G_LEDN_get, 2, false);
const tele_op_t op_G_LEDN_C = MAKE_GET_OP(G.LEDN.C, op_G_LEDN_C_get, 1, false);
const tele_op_t op_G_REC    = MAKE_GET_OP(G.REC, op_G_REC_get, 6, false);

const tele_op_t op_G_BTN    = MAKE_GET_OP(G.BTN, op_G_BTN_get, 8, false);
const tele_op_t op_G_GBTN   = MAKE_GET_OP(G.GBTN, op_G_GBTN_get, 9, false);
const tele_op_t op_G_BTNX   = MAKE_GET_OP(G.BTNX, op_G_BTNX_get, 5, false);
const tele_op_t op_G_BTN_EN = MAKE_GET_OP(G.BTN.EN, op_G_BTN_EN_get, 2, false);
const tele_op_t op_G_BTN_V  = MAKE_GET_SET_OP(G.BTN.V, op_G_BTN_V_get, op_G_BTN_V_set, 1, true);
const tele_op_t op_G_BTN_L  = MAKE_GET_OP(G.BTN.L, op_G_BTN_L_get, 2, false);
const tele_op_t op_G_BTNI   = MAKE_GET_OP(G.BTNI, op_G_BTNI_get, 0, true);
const tele_op_t op_G_BTNV   = MAKE_GET_OP(G.BTNV, op_G_BTNV_get, 0, true);
const tele_op_t op_G_BTNL   = MAKE_GET_OP(G.BTNL, op_G_BTNL_get, 1, false);
const tele_op_t op_G_BTN_SW = MAKE_GET_OP(G.BTN.SW, op_G_BTN_SW_get, 1, false);
const tele_op_t op_G_GBTN_V = MAKE_GET_OP(G.GBTN.V, op_G_GBTN_V_get, 2, false);
const tele_op_t op_G_GBTN_L = MAKE_GET_OP(G.GBTN.L, op_G_GBTN_L_get, 3, false);

// in progress

static void op_GFDR_VAL_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_GFDR_VAL_set(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_GFDR_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);

const tele_op_t op_GFDR = MAKE_GET_OP(GFDR, op_GFDR_get, 8, true);
const tele_op_t op_GFDR_VAL = MAKE_GET_SET_OP(GFDR.VAL, op_GFDR_VAL_get, op_GFDR_VAL_set, 1, true);

// clang-format on

static void op_G_RST_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *NOTUSED(cs)) {
    SG.dim = 0;
    SG.fader_min = 0;
    SG.fader_max = 16383;
    
    SG.current_group = 0;
    SG.last_defined_button = 0;
    SG.last_defined_fader = 0;

    SG.latest_group = 0;
    SG.latest_button = 0;
    SG.latest_fader = 0;
    
    for (u16 i = 0; i < GRID_LED_COUNT; i++) {
        SG.leds[i] = LED_OFF;
    }

    for (u8 i = 0; i < GRID_GROUP_COUNT; i++) {
        ss->grid.group[i].enabled = true;
        ss->grid.group[i].script = -1;
    }
    
    for (u8 i = 0; i < GRID_BUTTON_COUNT; i++) {
        grid_common_init(&(SG.button[i].common));
        SG.button[i].latch = 0;
        SG.button[i].state = 0;
    }

    for (u8 i = 0; i < GRID_FADER_COUNT; i++) {
        grid_common_init(&(SG.fader[i].common));
        SG.fader[i].dir = 0;
        SG.fader[i].value = 0;
    }
    
    SG.refresh = true;
}

static void op_G_CLR_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *NOTUSED(cs)) {
    for (u16 i = 0; i < GRID_LED_COUNT; i++) SG.leds[i] = -2;
    SG.refresh = true;
}

static void op_G_DIM_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    GET_AND_CLAMP(dim, 0, 14);
    SG.dim = dim;
    SG.refresh = true;
}

static void op_G_GRP_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs) - 1;
    if (group < 0 || group >= GRID_BUTTON_COUNT) return;
    SG.current_group = group;
}

static void op_G_GRP_EN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs) - 1;
    s16 en = cs_pop(cs);
    if (group < 0 || group >= GRID_BUTTON_COUNT) return;
    SG.group[group].enabled = en;
    SG.refresh = true;
}

static void op_G_GRP_C_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs) - 1;
    if (group < 0 || group >= GRID_BUTTON_COUNT) return;
    
    for (u8 i = 0; i < GRID_BUTTON_COUNT; i++)
        if (GBC.group == group) {
            grid_common_init(&(SG.button[i].common));
            SG.button[i].latch = 0;
            SG.button[i].state = 0;
        }

    for (u8 i = 0; i < GRID_FADER_COUNT; i++)
        if (GFC.group == group) {
            grid_common_init(&(SG.fader[i].common));
            SG.fader[i].dir = 0;
            SG.fader[i].value = 0;
        }
    
    SG.refresh = true;
}

static void op_G_GRP_SW_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs) - 1;
    if (group < 0 || group >= GRID_BUTTON_COUNT) return;
    
    for (u8 i = 0; i < GRID_GROUP_COUNT; i++) SG.group[i].enabled = false;
    SG.group[group].enabled = true;
    
    SG.refresh = true;
}

static void op_G_GRP_SC_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs) - 1;
    s16 script = cs_pop(cs) - 1;
    
    if (group < 0 || group >= GRID_BUTTON_COUNT) return;
    if (script < 0 || script > INIT_SCRIPT) script = -1;
    
    SG.group[group].script = script;
}

static void op_G_GRPI_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, SG.latest_group + 1);
}

static void op_G_LED_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 x = cs_pop(cs) - 1;
    s16 y = cs_pop(cs) - 1;
    GET_LEVEL(level);

    if (x < 0 || x >= monome_size_x()) return;
    if (y < 0 || y >= monome_size_y()) return;
    
    SG.leds[x + y * monome_size_x()] = level;
    SG.refresh = true;
}

static void op_G_LED_C_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 x = cs_pop(cs) - 1;
    s16 y = cs_pop(cs) - 1;

    if (x < 0 || x >= monome_size_x()) return;
    if (y < 0 || y >= monome_size_y()) return;
    
    SG.leds[x + y * monome_size_x()] = LED_OFF;
    SG.refresh = true;
}

static void op_G_LEDN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs) - 1;
    GET_LEVEL(level);

    if (i < 0 || i >= GRID_LED_COUNT) return;

    SG.leds[i] = level;
    SG.refresh = true;
}

static void op_G_LEDN_C_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs) - 1;

    if (i < 0 || i >= GRID_LED_COUNT) return;

    SG.leds[i] = LED_OFF;
    SG.refresh = true;
}

static void op_G_REC_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 x = cs_pop(cs) - 1;
    s16 y = cs_pop(cs) - 1;
    s16 w = cs_pop(cs);
    s16 h = cs_pop(cs);
    GET_LEVEL(fill);
    GET_LEVEL(border);
    
    s16 size_x = monome_size_x();
    s16 size_y = monome_size_y();
    
    for (s16 col = max(0, x + 1); col < min(size_x, x + w) - 1; col++)
        for (s16 row = max(0, y + 1); row < min(size_y, y + h) - 1; row++)
            SG.leds[col + row * size_x] = fill;

    s16 row1 = y * size_x;
    s16 row2 = (y + h - 1) * size_x;
    for (s16 col = max(0, x); col < min(size_x, x + w); col++)
        SG.leds[col + row1] = SG.leds[col + row2] = border;

    for (s16 row = max(0, y); row < min(size_y, y + h); row++)
        SG.leds[x + row * size_x] = SG.leds[x + w - 1 + row * size_x] = border;

    SG.refresh = true;
}

static void op_G_BTN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs) - 1;
    s16 x = cs_pop(cs) - 1;
    s16 y = cs_pop(cs) - 1;
    s16 w = cs_pop(cs);
    s16 h = cs_pop(cs);
    s16 latch = cs_pop(cs);
    GET_LEVEL(level);
    s16 script = cs_pop(cs) - 1;
    
    if (i < 0 || i >= GRID_BUTTON_COUNT) return;
    if (script < 0 || script > INIT_SCRIPT) script = -1;
    
    GBC.enabled = true;
    GBC.group = SG.current_group;
    GBC.x = x;
    GBC.y = y;
    GBC.w = w;
    GBC.h = h;
    GBC.background = level;
    GBC.script = script;
    GB.latch = latch != 0;
    GB.state = 0;
    
    SG.last_defined_button = i;
    SG.refresh = 1;
}

static void op_G_GBTN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs) - 1;
    s16 i = cs_pop(cs) - 1;
    s16 x = cs_pop(cs) - 1;
    s16 y = cs_pop(cs) - 1;
    s16 w = cs_pop(cs);
    s16 h = cs_pop(cs);
    s16 latch = cs_pop(cs);
    GET_LEVEL(level);
    s16 script = cs_pop(cs) - 1;
    
    if (group < 0 || group > GRID_GROUP_COUNT) group = 0;
    if (i < 0 || i >= GRID_BUTTON_COUNT) return;
    if (script < 0 || script > INIT_SCRIPT) script = -1;
    
    GBC.enabled = true;
    GBC.group = group;
    GBC.x = x;
    GBC.y = y;
    GBC.w = w;
    GBC.h = h;
    GBC.background = level;
    GBC.script = script;
    GB.latch = latch;
    GB.state = 0;
    
    SG.last_defined_button = i;
    SG.refresh = 1;
}

static void op_G_BTNX_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 count = cs_pop(cs);
    s16 x_inc = cs_pop(cs);
    s16 y_inc = cs_pop(cs);
    GET_LEVEL(level);
    s16 script_inc = cs_pop(cs);
    
    if (count < 1) return;
    if (count + SG.last_defined_button >= GRID_BUTTON_COUNT) count = GRID_BUTTON_COUNT - SG.last_defined_button - 1;
    
    u8 script;
    u8 inc;
    for (u16 i = SG.last_defined_button + 1; i <= SG.last_defined_button + count; i++) {
        inc = i - SG.last_defined_button;
        GBC.enabled = true;
        GBC.group = ss->grid.button[SG.last_defined_button].common.group;
        GBC.x = ss->grid.button[SG.last_defined_button].common.x + x_inc * inc;
        GBC.y = ss->grid.button[SG.last_defined_button].common.y + y_inc * inc;
        GBC.w = ss->grid.button[SG.last_defined_button].common.w;
        GBC.h = ss->grid.button[SG.last_defined_button].common.h;
        GBC.background = (i - SG.last_defined_button) & 1 ? level : ss->grid.button[SG.last_defined_button].common.background;
        GB.latch = ss->grid.button[SG.last_defined_button].latch;
        GB.state = 0;
        GBC.script = -1;
        script = ss->grid.button[SG.last_defined_button].common.script;
        if (script == -1) continue;
        if (script_inc) script += inc;
        if (script > INIT_SCRIPT) continue;
        GBC.script = script;
    }

    SG.last_defined_button += count;
    SG.refresh = 1;
}

static void op_G_BTN_EN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs) - 1;
    s16 en = cs_pop(cs);
    
    if (i < 0 || i >= GRID_BUTTON_COUNT) return;
    GBC.enabled = en;
    SG.refresh = 1;
}

static void op_G_BTN_V_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs) - 1;
    cs_push(cs, i < 0 || i >= GRID_BUTTON_COUNT ? 0 : GB.state);
}

static void op_G_BTN_V_set(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs) - 1;
    s16 value = cs_pop(cs);
    if (i < 0 || i >= GRID_BUTTON_COUNT) return;
    GB.state = value != 0;
    SG.refresh = 1;
}

static void op_G_BTN_L_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs) - 1;
    GET_LEVEL(level);
    if (i < 0 || i >= GRID_BUTTON_COUNT) return;
    GBC.background = level;
    SG.refresh = 1;
}

static void op_G_BTNI_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, SG.latest_button + 1);
}

static void op_G_BTNV_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, SG.button[SG.latest_button].state);
}

static void op_G_BTNL_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    GET_LEVEL(level);
    SG.button[SG.latest_button].common.background = level;
    SG.refresh = 1;
}

static void op_G_BTN_SW_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 id = cs_pop(cs) - 1;
    if (id < 0 || id >= GRID_BUTTON_COUNT) return;
    
    for (u16 i = 0; i < GRID_BUTTON_COUNT; i++)
        if (GBC.group == SG.button[id].common.group) GB.state = 0;
    
    SG.button[id].state = 1;
    SG.refresh = 1;
}

static void op_G_GBTN_V_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs) - 1;
    s16 value = cs_pop(cs);
    
    if (group < 0 || group > GRID_GROUP_COUNT) return;
    value = value != 0;

    for (u16 i = 0; i < GRID_BUTTON_COUNT; i++)
        if (GBC.group == group) GB.state = value;
    SG.refresh = 1;
}

static void op_G_GBTN_L_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs) - 1;
    GET_LEVEL(odd);
    GET_LEVEL(even);
    
    if (group < 0 || group > GRID_GROUP_COUNT) return;

    u8 is_odd = 1;
    for (u16 i = 0; i < GRID_BUTTON_COUNT; i++)
        if (GBC.group == group) {
            GBC.background = is_odd ? odd : even;
            is_odd = !is_odd;
        }
    SG.refresh = 1;
}

// in progress

static void op_GFDR_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t i = cs_pop(cs) - 1;
    int16_t x = cs_pop(cs) - 1;
    int16_t y = cs_pop(cs) - 1;
    int16_t w = cs_pop(cs);
    int16_t h = cs_pop(cs);
    int16_t background = cs_pop(cs);
    int16_t dir = cs_pop(cs);
    int16_t script = cs_pop(cs) - 1;

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

    //int16_t value = (u32)GF.value * 16383 / (u32)((GF.dir ? GFC.h : GFC.w) - 1);
    cs_push(cs, GF.value);
}

static void op_GFDR_VAL_set(const void *NOTUSED(data), scene_state_t *ss,
                       exec_state_t *NOTUSED(es), command_state_t *cs) {
    int8_t i = cs_pop(cs);
    int8_t value = cs_pop(cs);

    GF.value = value;
    SG.refresh = 1;
}

void grid_common_init(grid_common_t *gc) {
    gc->enabled = false;
    gc->group = 0;
    gc->x = gc->y = 0;
    gc->w = gc->h = 1;
    gc->background = 5;
    gc->script = -1;
}
