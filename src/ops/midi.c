#include "ops/midi.h"

#include "helpers.h"
#include "table.h"
#include "teletype_io.h"

static void op_MID_SYM_DOLLAR_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_MID_SYM_DOLLAR_set(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_MID_E_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_MID_CH_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_MID_N_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_MID_NV_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_MID_V_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_MID_VV_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_MID_CN_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_MID_CV_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_MID_CVV_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);

const tele_op_t op_MID_SYM_DOLLAR = MAKE_GET_SET_OP(MID.$, op_MID_SYM_DOLLAR_get, op_MID_SYM_DOLLAR_set, 1, true);
const tele_op_t op_MID_E   = MAKE_GET_OP(MID.E,   op_MID_E_get,   0, true);
const tele_op_t op_MID_CH  = MAKE_GET_OP(MID.CH,  op_MID_CH_get,  0, true);
const tele_op_t op_MID_N   = MAKE_GET_OP(MID.N,   op_MID_N_get,   0, true);
const tele_op_t op_MID_NV  = MAKE_GET_OP(MID.NV,  op_MID_NV_get,  0, true);
const tele_op_t op_MID_V   = MAKE_GET_OP(MID.V,   op_MID_V_get,   0, true);
const tele_op_t op_MID_VV  = MAKE_GET_OP(MID.VV,  op_MID_VV_get,  0, true);
const tele_op_t op_MID_CN  = MAKE_GET_OP(MID.CN,  op_MID_CN_get,  0, true);
const tele_op_t op_MID_CV  = MAKE_GET_OP(MID.CV,  op_MID_CV_get,  0, true);
const tele_op_t op_MID_CVV = MAKE_GET_OP(MID.CVV, op_MID_CVV_get, 0, true);

static void op_MID_SYM_DOLLAR_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t event = cs_pop(cs);
    int16_t script = -1;
    
    switch (event) {
        case 0:
            script = ss->midi.on_script = script;
            if (script != ss->midi.off_script ||
                script != ss->midi.cc_script ||
                script != ss->midi.clk_script ||
                script != ss->midi.start_script ||
                script != ss->midi.stop_script ||
                script != ss->midi.continue_script)
                script = -1;
            break;
        case 1:
            script = ss->midi.on_script;
            break;
        case 2:
            script = ss->midi.off_script;
            break;
        case 3:
            script = ss->midi.cc_script;
            break;
        case 4:
            script = ss->midi.clk_script;
            break;
        case 5:
            script = ss->midi.start_script;
            break;
        case 6:
            script = ss->midi.stop_script;
            break;
        case 7:
            script = ss->midi.continue_script;
            break;
        default:
            break;
    }
    
    cs_push(cs, script == -1 ? script : script + 1);
}

static void op_MID_SYM_DOLLAR_set(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t event = cs_pop(cs);
    s16 script = cs_pop(cs) - 1;
    if (script < 0 || script > INIT_SCRIPT) script = -1;
    
    switch (event) {
        case 0:
            ss->midi.on_script = script;
            ss->midi.off_script = script;
            ss->midi.cc_script = script;
            ss->midi.clk_script = script;
            ss->midi.start_script = script;
            ss->midi.stop_script = script;
            ss->midi.continue_script = script;
            break;
        case 1:
            ss->midi.on_script = script;
            break;
        case 2:
            ss->midi.off_script = script;
            break;
        case 3:
            ss->midi.cc_script = script;
            break;
        case 4:
            ss->midi.clk_script = script;
            break;
        case 5:
            ss->midi.start_script = script;
            break;
        case 6:
            ss->midi.stop_script = script;
            break;
        case 7:
            ss->midi.continue_script = script;
            break;
        default:
            break;
    }
}

static void op_MID_E_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    cs_push(cs, ss->midi.last_event_type);
}

static void op_MID_CH_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    cs_push(cs, ss->midi.last_channel);
}

static void op_MID_N_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    cs_push(cs, ss->midi.last_note);
}

static void op_MID_NV_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    cs_push(cs, table_n[ss->midi.last_note]);
}

static void op_MID_V_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    cs_push(cs, ss->midi.last_velocity);
}

static void op_MID_VV_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    cs_push(cs, ss->midi.last_velocity * 129);
}

static void op_MID_CN_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    cs_push(cs, ss->midi.last_controller);
}

static void op_MID_CV_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    cs_push(cs, ss->midi.last_cc);
}

static void op_MID_CVV_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    cs_push(cs, ss->midi.last_cc * 129);
}
