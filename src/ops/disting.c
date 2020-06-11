#include "ops/disting.h"
#include "ii.h"
#include "helpers.h"
#include "teletype_io.h"

static void op_EX_1_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_2_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_3_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_4_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_LOAD_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SAVE_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_RESET_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_ALG_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_ALG_set(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_CTRL_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_PARAM_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_REC_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_PLAY_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_AL_P_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_AL_CLK_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_M_CH_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_M_N_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_M_O_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_M_PB_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_M_CC_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_M_PRG_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_M_CLK_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_M_START_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_M_STOP_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_M_CONT_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SB_CH_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SB_N_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SB_O_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SB_PB_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SB_CC_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SB_PRG_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SB_CLK_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SB_START_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SB_STOP_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_SB_CONT_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_VOX_P_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_VOX_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_VOX_O_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);

// clang-format off
                         
const tele_op_t op_EX_1        = MAKE_GET_OP(EX.1,        op_EX_1_get,      0, false);
const tele_op_t op_EX_2        = MAKE_GET_OP(EX.2,        op_EX_2_get,      0, false);
const tele_op_t op_EX_3        = MAKE_GET_OP(EX.3,        op_EX_3_get,      0, false);
const tele_op_t op_EX_4        = MAKE_GET_OP(EX.4,        op_EX_4_get,      0, false);
const tele_op_t op_EX_LOAD     = MAKE_GET_OP(EX.LOAD,     op_EX_LOAD_get,   1, false);
const tele_op_t op_EX_SAVE     = MAKE_GET_OP(EX.SAVE,     op_EX_SAVE_get,   1, false);
const tele_op_t op_EX_RESET    = MAKE_GET_OP(EX.RESET,    op_EX_RESET_get,  0, false);
const tele_op_t op_EX_ALG      = MAKE_GET_SET_OP(EX.ALG, op_EX_ALG_get, op_EX_ALG_set, 0, true);
const tele_op_t op_EX_CTRL     = MAKE_GET_OP(EX.CTRL,     op_EX_CTRL_get,   2, false);
const tele_op_t op_EX_PARAM    = MAKE_GET_OP(EX.PARAM,    op_EX_PARAM_get,  2, false);
const tele_op_t op_EX_REC      = MAKE_GET_OP(EX.REC,      op_EX_REC_get,    1, false);
const tele_op_t op_EX_PLAY     = MAKE_GET_OP(EX.PLAY,     op_EX_PLAY_get,   1, false);
const tele_op_t op_EX_AL_P     = MAKE_GET_OP(EX.AL.P,     op_EX_AL_P_get,   1, false);
const tele_op_t op_EX_AL_CLK   = MAKE_GET_OP(EX.AL.CLK,   op_EX_AL_CLK_get, 0, false);

const tele_op_t op_EX_M_CH     = MAKE_GET_OP(EX.M.CH,     op_EX_M_CH_get,    1, false);
const tele_op_t op_EX_M_N      = MAKE_GET_OP(EX.M.N,      op_EX_M_N_get,     2, false);
const tele_op_t op_EX_M_O      = MAKE_GET_OP(EX.M.O,      op_EX_M_O_get,     1, false);
const tele_op_t op_EX_M_PB     = MAKE_GET_OP(EX.M.PB,     op_EX_M_PB_get,    1, false);
const tele_op_t op_EX_M_CC     = MAKE_GET_OP(EX.M.CC,     op_EX_M_CC_get,    2, false);
const tele_op_t op_EX_M_PRG    = MAKE_GET_OP(EX.M.PRG,    op_EX_M_PRG_get,   1, false);
const tele_op_t op_EX_M_CLK    = MAKE_GET_OP(EX.M.CLK,    op_EX_M_CLK_get,   0, false);
const tele_op_t op_EX_M_START  = MAKE_GET_OP(EX.M.START,  op_EX_M_START_get, 0, false);
const tele_op_t op_EX_M_STOP   = MAKE_GET_OP(EX.M.STOP,   op_EX_M_STOP_get,  0, false);
const tele_op_t op_EX_M_CONT   = MAKE_GET_OP(EX.M.CONT,   op_EX_M_CONT_get,  0, false);

const tele_op_t op_EX_SB_CH    = MAKE_GET_OP(EX.SB.CH,    op_EX_SB_CH_get,    1, false);
const tele_op_t op_EX_SB_N     = MAKE_GET_OP(EX.SB.N,     op_EX_SB_N_get,     2, false);
const tele_op_t op_EX_SB_O     = MAKE_GET_OP(EX.SB.O,     op_EX_SB_O_get,     1, false);
const tele_op_t op_EX_SB_PB    = MAKE_GET_OP(EX.SB.PB,    op_EX_SB_PB_get,    1, false);
const tele_op_t op_EX_SB_CC    = MAKE_GET_OP(EX.SB.CC,    op_EX_SB_CC_get,    2, false);
const tele_op_t op_EX_SB_PRG   = MAKE_GET_OP(EX.SB.PRG,   op_EX_SB_PRG_get,   1, false);
const tele_op_t op_EX_SB_CLK   = MAKE_GET_OP(EX.SB.CLK,   op_EX_SB_CLK_get,   0, false);
const tele_op_t op_EX_SB_START = MAKE_GET_OP(EX.SB.START, op_EX_SB_START_get, 0, false);
const tele_op_t op_EX_SB_STOP  = MAKE_GET_OP(EX.SB.STOP,  op_EX_SB_STOP_get,  0, false);
const tele_op_t op_EX_SB_CONT  = MAKE_GET_OP(EX.SB.CONT,  op_EX_SB_CONT_get,  0, false);

const tele_op_t op_EX_VOX      = MAKE_GET_OP(EX.VOX,      op_EX_VOX_get,      3, false);
const tele_op_t op_EX_VOX_P    = MAKE_GET_OP(EX.VOX.P,    op_EX_VOX_P_get,    2, false);
const tele_op_t op_EX_VOX_O    = MAKE_GET_OP(EX.VOX.O,    op_EX_VOX_O_get,    1, false);

const tele_op_t op_EX_L  = MAKE_ALIAS_OP(EX.L,  op_EX_LOAD_get,  NULL, 1, false);
const tele_op_t op_EX_S  = MAKE_ALIAS_OP(EX.S,  op_EX_SAVE_get,  NULL, 1, false);
const tele_op_t op_EX_A  = MAKE_ALIAS_OP(EX.A,  op_EX_ALG_get, op_EX_ALG_set, 0, true);
const tele_op_t op_EX_C  = MAKE_ALIAS_OP(EX.C,  op_EX_CTRL_get,  NULL, 2, false);
const tele_op_t op_EX_P  = MAKE_ALIAS_OP(EX.P,  op_EX_PARAM_get, NULL, 2, false);
const tele_op_t op_EX_V  = MAKE_ALIAS_OP(EX.V,  op_EX_VOX_get,   NULL, 3, false);
const tele_op_t op_EX_VP = MAKE_ALIAS_OP(EX.VP, op_EX_VOX_P_get, NULL, 2, false);
const tele_op_t op_EX_VO = MAKE_ALIAS_OP(EX.VO, op_EX_VOX_O_get, NULL, 1, false);

// clang-format on

static u8 unit = 0;
static u8 midi_channel = 0;
static u8 sb_channel = 0;
static u8 data[4];

static inline void send1(u8 cmd) {
    data[0] = cmd;
    tele_ii_tx(DISTING_EX_1 + unit, data, 1);
}

static inline void send2(u8 cmd, u8 b1) {
    data[0] = cmd;
    data[1] = b1;
    tele_ii_tx(DISTING_EX_1 + unit, data, 2);
}

static inline void send3(u8 cmd, u8 b1, u8 b2) {
    data[0] = cmd;
    data[1] = b1;
    data[2] = b2;
    tele_ii_tx(DISTING_EX_1 + unit, data, 3);
}

static inline void send4(u8 cmd, u8 b1, u8 b2, u8 b3) {
    data[0] = cmd;
    data[1] = b1;
    data[2] = b2;
    data[3] = b3;
    tele_ii_tx(DISTING_EX_1 + unit, data, 4);
}

static void op_EX_1_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    unit = 0;
}

static void op_EX_2_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    unit = 1;
}

static void op_EX_3_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    unit = 2;
}

static void op_EX_4_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    unit = 3;
}

static void op_EX_LOAD_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 preset = cs_pop(cs);
    send2(0x40, preset);
}

static void op_EX_SAVE_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 preset = cs_pop(cs);
    send2(0x41, preset);
}

static void op_EX_RESET_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send1(0x42);
}

static void op_EX_ALG_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send1(0x45);
    
    data[0] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 1);
    cs_push(cs, data[0]);
}

static void op_EX_ALG_set(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 algo = cs_pop(cs);
    send2(0x44, algo);
}

static void op_EX_CTRL_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 controller = cs_pop(cs);
    u16 value = cs_pop(cs);
    send4(0x11, controller, value >> 8, value);
}

static void op_EX_PARAM_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    u16 value = cs_pop(cs);
    send4(0x46, param, value >> 8, value);
}

static void op_EX_REC_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send2(0x4B, cs_pop(cs) ? 1 : 0);
}

static void op_EX_PLAY_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send2(0x4C, cs_pop(cs) ? 1 : 0);
}

static void op_EX_AL_P_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 pitch = cs_pop(cs);
    send3(0x4D, pitch >> 8, pitch);
}

static void op_EX_AL_CLK_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send1(0x4E);
}

static void op_EX_M_CH_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs) - 1;
    if (ch < 0 || ch > 15) return;
    midi_channel = ch;
}

static void op_EX_M_N_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 note = cs_pop(cs);
    u16 velocity = cs_pop(cs);
    if (note > 127) note = 127;
    if (velocity > 127) velocity = 127;
    send4(0x4F, 9 + midi_channel, note, velocity);
}

static void op_EX_M_O_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 note = cs_pop(cs);
    if (note > 127) note = 127;
    send4(0x4F, 8 + midi_channel, note, 0);
}

static void op_EX_M_PB_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 bend = cs_pop(cs);
    send4(0x4F, 0xE + midi_channel, bend, bend >> 8);
}

static void op_EX_M_CC_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 controller = cs_pop(cs);
    u16 value = cs_pop(cs);
    if (controller > 127) controller = 127;
    if (value > 127) value = 127;
    send4(0x4F, 0xB + midi_channel, controller, value);
}

static void op_EX_M_PRG_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 program = cs_pop(cs);
    if (program > 127) program = 127;
    send3(0x4F, 0xC + midi_channel, program);
}

static void op_EX_M_CLK_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x4F, 0xC + midi_channel, 0xF8);
}

static void op_EX_M_START_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x4F, 0xC + midi_channel, 0xFA);
}

static void op_EX_M_STOP_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x4F, 0xC + midi_channel, 0xFC);
}

static void op_EX_M_CONT_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x4F, 0xC + midi_channel, 0xFB);
}

static void op_EX_SB_CH_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs) - 1;
    if (ch < 0 || ch > 15) return;
    sb_channel = ch;
}

static void op_EX_SB_N_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 note = cs_pop(cs);
    u16 velocity = cs_pop(cs);
    if (note > 127) note = 127;
    if (velocity > 127) velocity = 127;
    send4(0x50, 9 + sb_channel, note, velocity);
}

static void op_EX_SB_O_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 note = cs_pop(cs);
    if (note > 127) note = 127;
    send4(0x50, 8 + sb_channel, note, 0);
}

static void op_EX_SB_PB_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 bend = cs_pop(cs);
    send4(0x50, 0xE + sb_channel, bend, bend >> 8);
}

static void op_EX_SB_CC_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 controller = cs_pop(cs);
    u16 value = cs_pop(cs);
    if (controller > 127) controller = 127;
    if (value > 127) value = 127;
    send4(0x50, 0xB + sb_channel, controller, value);
}

static void op_EX_SB_PRG_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 program = cs_pop(cs);
    if (program > 127) program = 127;
    send3(0x50, 0xC + sb_channel, program);
}

static void op_EX_SB_CLK_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x50, 0xC + sb_channel, 0xF8);
}

static void op_EX_SB_START_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x50, 0xC + sb_channel, 0xFA);
}

static void op_EX_SB_STOP_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x50, 0xC + sb_channel, 0xFC);
}

static void op_EX_SB_CONT_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x50, 0xC + sb_channel, 0xFB);
}

static void op_EX_VOX_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 voice = cs_pop(cs) - 1;
    u16 pitch = cs_pop(cs);
    u16 velocity = cs_pop(cs);
    if (voice < 0) return;
    
    send4(0x51, voice, pitch >> 8, pitch);
    send4(0x52, voice, velocity >> 8, velocity);
}

static void op_EX_VOX_P_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 voice = cs_pop(cs) - 1;
    u16 pitch = cs_pop(cs);
    if (voice < 0) return;

    send4(0x51, voice, pitch >> 8, pitch);
}

static void op_EX_VOX_O_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 voice = cs_pop(cs) - 1;
    if (voice < -1) return;
    
    if (voice == -1)
        send1(0x57);
    else
        send2(0x53, voice);
}
