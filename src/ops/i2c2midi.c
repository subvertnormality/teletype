#include "ops/i2c2midi.h"

#include "helpers.h"
#include "teletype.h"
#include "teletype_io.h"

// clang-format off

static void op_I2M_CH_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CH_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_TIME_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_TIME_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_SHIFT_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_SHIFT_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_NOTE_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_NOTE_O_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_N2_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_NO2_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_REP_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_REP_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_RAT_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_RAT_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_ADD_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_RM_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_CLR_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_L_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_L_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_INV_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_INV_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_INS_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_DEL_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_SET_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_STRUM_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_STRUM_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_ROT_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_C_REV_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CC_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CC2_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CCV_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CCV2_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CC_OFF_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CC_OFF_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CC_SLEW_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CC_SLEW_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CC_SET_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_NRPN_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_NRPN_OFF_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_NRPN_OFF_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_NRPN_SLEW_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_NRPN_SLEW_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_NRPN_SET_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_NRPN_SET_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_PRG_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_PB_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_AT_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CLK_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_START_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_STOP_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_CONT_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_CH_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_CH_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_LATCH_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_NOTE_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_VEL_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_CC_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_LCH_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_LN_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_LV_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_LO_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_LC_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_I2M_Q_LCC_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);

const tele_op_t op_I2M_CH        = MAKE_GET_SET_OP(I2M.CH, op_I2M_CH_get, op_I2M_CH_set, 0, true);
const tele_op_t op_I2M_TIME      = MAKE_GET_SET_OP(I2M.TIME, op_I2M_TIME_get, op_I2M_TIME_set, 0, true);
const tele_op_t op_I2M_SHIFT     = MAKE_GET_SET_OP(I2M.SHIFT, op_I2M_SHIFT_get, op_I2M_SHIFT_set, 0, true);
const tele_op_t op_I2M_NOTE      = MAKE_GET_OP(I2M.NOTE, op_I2M_NOTE_get, 2, false);
const tele_op_t op_I2M_N         = MAKE_ALIAS_OP(I2M.N, op_I2M_NOTE_get, NULL, 2, false);
const tele_op_t op_I2M_NOTE_O    = MAKE_GET_OP(I2M.NOTE.O, op_I2M_NOTE_O_get, 1, false);
const tele_op_t op_I2M_NO        = MAKE_ALIAS_OP(I2M.NO, op_I2M_NOTE_O_get, NULL, 1, false);
const tele_op_t op_I2M_N2        = MAKE_GET_OP(I2M.N2, op_I2M_N2_get, 3, false);
const tele_op_t op_I2M_NO2       = MAKE_GET_OP(I2M.NO2, op_I2M_NO2_get, 2, false);
const tele_op_t op_I2M_REP       = MAKE_GET_SET_OP(I2M.REP, op_I2M_REP_get, op_I2M_REP_set, 0, true);
const tele_op_t op_I2M_RAT       = MAKE_GET_SET_OP(I2M.RAT, op_I2M_RAT_get, op_I2M_RAT_set, 0, true);
const tele_op_t op_I2M_C         = MAKE_GET_OP(I2M.C, op_I2M_C_get, 3, false);
const tele_op_t op_I2M_C_ADD     = MAKE_GET_OP(I2M.C.ADD, op_I2M_C_ADD_get, 3, false);
const tele_op_t op_I2M_C_PLUS    = MAKE_ALIAS_OP(I2M.C.+, op_I2M_C_ADD_get, NULL, 3, false);
const tele_op_t op_I2M_C_RM      = MAKE_GET_OP(I2M.C.RM, op_I2M_C_RM_get, 2, false);
const tele_op_t op_I2M_C_MINUS   = MAKE_ALIAS_OP(I2M.C.-, op_I2M_C_RM_get, NULL, 2, false);
const tele_op_t op_I2M_C_CLR     = MAKE_GET_OP(I2M.C.CLR, op_I2M_C_CLR_get, 1, false);
const tele_op_t op_I2M_C_L       = MAKE_GET_SET_OP(I2M.C.L, op_I2M_C_L_get, op_I2M_C_L_set, 1, true);
const tele_op_t op_I2M_C_INV     = MAKE_GET_SET_OP(I2M.C.INV, op_I2M_C_INV_get, op_I2M_C_INV_set, 1, true);
const tele_op_t op_I2M_C_INS     = MAKE_GET_OP(I2M.C.INS, op_I2M_C_INS_get, 4, false);
const tele_op_t op_I2M_C_DEL     = MAKE_GET_OP(I2M.C.DEL, op_I2M_C_DEL_get, 2, false);
const tele_op_t op_I2M_C_SET     = MAKE_GET_OP(I2M.C.SET, op_I2M_C_SET_get, 4, false);
const tele_op_t op_I2M_C_STRUM   = MAKE_GET_SET_OP(I2M.C.STRUM, op_I2M_C_STRUM_get, op_I2M_C_STRUM_set, 1, true);
const tele_op_t op_I2M_C_ROT     = MAKE_GET_OP(I2M.C.ROT, op_I2M_C_ROT_get, 2, false);
const tele_op_t op_I2M_C_REV     = MAKE_GET_OP(I2M.C.REV, op_I2M_C_REV_get, 1, false);
const tele_op_t op_I2M_CC        = MAKE_GET_OP(I2M.CC, op_I2M_CC_get, 2, false);
const tele_op_t op_I2M_CC2       = MAKE_GET_OP(I2M.CC2, op_I2M_CC2_get, 3, false);
const tele_op_t op_I2M_CCV       = MAKE_GET_OP(I2M.CCV, op_I2M_CCV_get, 2, false);
const tele_op_t op_I2M_CCV2      = MAKE_GET_OP(I2M.CCV2, op_I2M_CCV2_get, 3, false);
const tele_op_t op_I2M_CC_OFF    = MAKE_GET_SET_OP(I2M.CC.OFF, op_I2M_CC_OFF_get, op_I2M_CC_OFF_set, 1, true);
const tele_op_t op_I2M_CC_SLEW   = MAKE_GET_SET_OP(I2M.CC.SLEW, op_I2M_CC_SLEW_get, op_I2M_CC_SLEW_set, 1, true);
const tele_op_t op_I2M_CC_SET    = MAKE_GET_OP(I2M.CC.SET, op_I2M_CC_SET_get, 2, false);
const tele_op_t op_I2M_NRPN      = MAKE_GET_OP(I2M.NRPN, op_I2M_NRPN_get, 3, false);
const tele_op_t op_I2M_NRPN_OFF  = MAKE_GET_SET_OP(I2M.NRPN.OFF, op_I2M_NRPN_OFF_get, op_I2M_NRPN_OFF_set, 2, true);
const tele_op_t op_I2M_NRPN_SLEW = MAKE_GET_SET_OP(I2M.NRPN.SLEW, op_I2M_NRPN_SLEW_get, op_I2M_NRPN_SLEW_set, 2, true);
const tele_op_t op_I2M_NRPN_SET  = MAKE_GET_OP(I2M.NRPN.SET, op_I2M_NRPN_SET_get, 3, false);
const tele_op_t op_I2M_PRG       = MAKE_GET_OP(I2M.PRG, op_I2M_PRG_get, 1, false);
const tele_op_t op_I2M_PB        = MAKE_GET_OP(I2M.PB, op_I2M_PB_get, 1, false);
const tele_op_t op_I2M_AT        = MAKE_GET_OP(I2M.AT, op_I2M_AT_get, 1, false);
const tele_op_t op_I2M_CLK       = MAKE_GET_OP(I2M.CLK, op_I2M_CLK_get, 0, false);
const tele_op_t op_I2M_START     = MAKE_GET_OP(I2M.START, op_I2M_START_get, 0, false);
const tele_op_t op_I2M_STOP      = MAKE_GET_OP(I2M.STOP, op_I2M_STOP_get, 0, false);
const tele_op_t op_I2M_CONT      = MAKE_GET_OP(I2M.CONT, op_I2M_CONT_get, 0, false);
const tele_op_t op_I2M_Q_CH      = MAKE_GET_SET_OP(I2M.Q.CH, op_I2M_Q_CH_get, op_I2M_Q_CH_set, 0, true);
const tele_op_t op_I2M_Q_LATCH   = MAKE_GET_OP(I2M.Q.LATCH, op_I2M_Q_LATCH_set, 1, false);
const tele_op_t op_I2M_Q_NOTE    = MAKE_GET_OP(I2M.Q.NOTE, op_I2M_Q_NOTE_get, 1, true);
const tele_op_t op_I2M_Q_N       = MAKE_ALIAS_OP(I2M.Q.N, op_I2M_Q_NOTE_get, NULL, 1, true);
const tele_op_t op_I2M_Q_VEL     = MAKE_GET_OP(I2M.Q.VEL, op_I2M_Q_VEL_get, 1, true);
const tele_op_t op_I2M_Q_V       = MAKE_ALIAS_OP(I2M.Q.V, op_I2M_Q_VEL_get, NULL, 1, true);
const tele_op_t op_I2M_Q_CC      = MAKE_GET_OP(I2M.Q.CC, op_I2M_Q_CC_get, 1, true);
const tele_op_t op_I2M_Q_LCH     = MAKE_GET_OP(I2M.Q.LCH, op_I2M_Q_LCH_get, 0, true);
const tele_op_t op_I2M_Q_LN      = MAKE_GET_OP(I2M.Q.LN, op_I2M_Q_LN_get, 0, true);
const tele_op_t op_I2M_Q_LV      = MAKE_GET_OP(I2M.Q.LV, op_I2M_Q_LV_get, 0, true);
const tele_op_t op_I2M_Q_LO      = MAKE_GET_OP(I2M.Q.LO, op_I2M_Q_LO_get, 0, true);
const tele_op_t op_I2M_Q_LC      = MAKE_GET_OP(I2M.Q.LC, op_I2M_Q_LC_get, 0, true);
const tele_op_t op_I2M_Q_LCC     = MAKE_GET_OP(I2M.Q.LCC, op_I2M_Q_LCC_get, 0, true);


// clang-format on

#define I2C2MIDI 0x3F
#define MAX_CHANNEL 32

static u8 midi_channel = 0, q_channel = 0;
static u8 d[6];

#define SEND_CMD(cmd) \
    d[0] = cmd; \
    tele_ii_tx(I2C2MIDI, d, 1);

#define SEND_B(cmd, b) \
    d[0] = cmd; \
    d[1] = b;   \
    tele_ii_tx(I2C2MIDI, d, 2);

#define SEND_B2(cmd, b1, b2) \
    d[0] = cmd; \
    d[1] = b1;  \
    d[2] = b2;  \
    tele_ii_tx(I2C2MIDI, d, 3);

#define SEND_B3(cmd, b1, b2, b3) \
    d[0] = cmd; \
    d[1] = b1;  \
    d[2] = b2;  \
    d[3] = b3;  \
    tele_ii_tx(I2C2MIDI, d, 4);

#define SEND_B4(cmd, b1, b2, b3, b4) \
    d[0] = cmd; \
    d[1] = b1;  \
    d[2] = b2;  \
    d[3] = b3;  \
    d[4] = b4;  \
    tele_ii_tx(I2C2MIDI, d, 5);

#define SEND_B5(cmd, b1, b2, b3, b4, b5) \
    d[0] = cmd; \
    d[1] = b1;  \
    d[2] = b2;  \
    d[3] = b3;  \
    d[4] = b4;  \
    d[5] = b5;  \
    tele_ii_tx(I2C2MIDI, d, 6);

#define RECEIVE_AND_PUSH_S8 \
    d[0] = 0; \
    tele_ii_rx(I2C2MIDI, d, 1); \
    cs_push(cs, (s8)d[0]);

#define RECEIVE_AND_PUSH_S16 \
    d[0] = d[1] = 0; \
    tele_ii_rx(I2C2MIDI, d, 2); \
    cs_push(cs, (d[0] << 8) + d[1]);

#define RECEIVE_AND_PUSH_S16_7 \
    d[0] = d[1] = 0; \
    tele_ii_rx(I2C2MIDI, d, 2); \
    cs_push(cs, (d[0] << 7) + d[1]);

#define RETURN_IF_OUT_OF_RANGE(value, min, max) \
    if ((value) < min || (value) > max) return;
    
#define CLAMP_TO_RANGE(value, min, max) \
    if (value < min) value = min; \
    else if (value > max) value = max;

    
//implementation

static void op_I2M_CH_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    cs_push(cs, midi_channel + 1);
}

static void op_I2M_CH_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 channel = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(channel, 1, MAX_CHANNEL);
    midi_channel = channel - 1;
}

static void op_I2M_TIME_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(1);
    RECEIVE_AND_PUSH_S16;
}

static void op_I2M_TIME_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 time = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(time, 0, 32767);
    SEND_B2(2, time >> 8, time & 0xff);
}

static void op_I2M_SHIFT_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(3);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_SHIFT_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 shift = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(shift, -127, 127);
    SEND_B(4, shift);
}

static void op_I2M_NOTE_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 note = cs_pop(cs);
    s16 velocity = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(note, 0, 127);
    CLAMP_TO_RANGE(velocity, 0, 127);
    SEND_B3(20, midi_channel, note, velocity);
}

static void op_I2M_NOTE_O_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 note = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(note, 0, 127);
    SEND_B2(21, midi_channel, note);
}

static void op_I2M_N2_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 channel = cs_pop(cs);
    s16 note = cs_pop(cs);
    s16 velocity = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(channel, 1, MAX_CHANNEL);
    RETURN_IF_OUT_OF_RANGE(note, 0, 127);
    CLAMP_TO_RANGE(velocity, 0, 127);
    SEND_B3(20, channel - 1, note, velocity);
}

static void op_I2M_NO2_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 channel = cs_pop(cs);
    s16 note = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(channel, 1, MAX_CHANNEL);
    RETURN_IF_OUT_OF_RANGE(note, 0, 127);
    SEND_B2(21, channel - 1, note);
}

static void op_I2M_REP_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(5);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_REP_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 rep = cs_pop(cs);
    SEND_B(6, rep);
}

static void op_I2M_RAT_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(7);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_RAT_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 rat = cs_pop(cs);
    SEND_B(8, rat);
}

static void op_I2M_C_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    s16 note = cs_pop(cs);
    s16 velocity = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(note, 0, 127);
    CLAMP_TO_RANGE(velocity, 0, 127);
    SEND_B4(30, midi_channel, chord, note, velocity);
}

static void op_I2M_C_ADD_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    s16 note = cs_pop(cs);
    s16 vel = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(note, 0, 127);
    SEND_B3(31, chord, note, vel);
}

static void op_I2M_C_RM_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    s16 note = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(note, 0, 127);
    SEND_B2(32, chord, note);
}

static void op_I2M_C_CLR_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    SEND_B(33, chord);
}

static void op_I2M_C_L_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    SEND_B(34, chord);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_C_L_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    s16 length = cs_pop(cs);
    SEND_B2(35, chord, length);
}

static void op_I2M_C_INV_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    SEND_B(36, chord);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_C_INV_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    s16 inversion = cs_pop(cs);
    SEND_B2(37, chord, inversion);
}

static void op_I2M_C_INS_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    s16 index = cs_pop(cs);
    s16 note = cs_pop(cs);
    s16 vel = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(note, 0, 127);
    SEND_B4(152, chord, index, note, vel);
}

static void op_I2M_C_DEL_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    s16 index = cs_pop(cs);
    SEND_B2(153, chord, index);
}

static void op_I2M_C_SET_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    s16 index = cs_pop(cs);
    s16 note = cs_pop(cs);
    s16 vel = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(note, 0, 127);
    SEND_B4(154, chord, index, note, vel);
}

static void op_I2M_C_STRUM_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    SEND_B(150, chord);
    RECEIVE_AND_PUSH_S16;
}

static void op_I2M_C_STRUM_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    s16 strum = cs_pop(cs);
    CLAMP_TO_RANGE(strum, 0, 32767);
    SEND_B3(151, chord, strum >> 8, strum & 0xff);
}

static void op_I2M_C_REV_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    SEND_B(38, chord);
}

static void op_I2M_C_ROT_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 chord = cs_pop(cs);
    s16 rot = cs_pop(cs);
    SEND_B2(39, chord, rot);
}

static void op_I2M_CC_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 controller = cs_pop(cs);
    s16 cc = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(controller, 0, 127);
    CLAMP_TO_RANGE(cc, 0, 127);
    cc *= 129;
    SEND_B4(40, midi_channel, controller, cc >> 7, cc & 0x7f);
}

static void op_I2M_CC2_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 channel = cs_pop(cs);
    s16 controller = cs_pop(cs);
    s16 cc = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(channel, 1, MAX_CHANNEL);
    RETURN_IF_OUT_OF_RANGE(controller, 0, 127);
    CLAMP_TO_RANGE(cc, 0, 127);
    cc *= 129;
    SEND_B4(40, channel - 1, controller, cc >> 7, cc & 0x7f);
}

static void op_I2M_CCV_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 controller = cs_pop(cs);
    s16 cc = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(controller, 0, 127);
    CLAMP_TO_RANGE(cc, 0, 16384);
    SEND_B4(40, midi_channel, controller, cc >> 7, cc & 0x7f);
}

static void op_I2M_CCV2_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 channel = cs_pop(cs);
    s16 controller = cs_pop(cs);
    s16 cc = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(channel, 1, MAX_CHANNEL);
    RETURN_IF_OUT_OF_RANGE(controller, 0, 127);
    CLAMP_TO_RANGE(cc, 0, 16384);
    SEND_B4(40, channel - 1, controller, cc >> 7, cc & 0x7f);
}

static void op_I2M_CC_OFF_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 controller = cs_pop(cs);
    if (controller < 0 || controller > 127) {
        cs_push(cs, 0);
    } else {
        SEND_B2(41, midi_channel, controller);
        d[0] = d[1] = 0;
        tele_ii_rx(I2C2MIDI, d, 2);
        s16 offset = (d[0] << 7) + d[1];
        offset = (offset << 1) / 129;
        offset = (offset >> 1) + (offset & 1);
        cs_push(cs, offset);
    }
}

static void op_I2M_CC_OFF_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 controller = cs_pop(cs);
    s16 offset = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(controller, 0, 127);
    CLAMP_TO_RANGE(offset, -127, 127);
    offset *= 129;
    SEND_B4(42, midi_channel, controller, offset >> 7, offset & 0x7f);
}

static void op_I2M_CC_SLEW_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 controller = cs_pop(cs);
    if (controller < 0 || controller > 127) {
        cs_push(cs, 0);
    } else {
        SEND_B2(43, midi_channel, controller);
        RECEIVE_AND_PUSH_S16;
    }
}

static void op_I2M_CC_SLEW_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 controller = cs_pop(cs);
    s16 slew = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(controller, 0, 127);
    RETURN_IF_OUT_OF_RANGE(slew, 0, 32767);
    SEND_B4(44, midi_channel, controller, slew >> 8, slew & 0xff);
}

static void op_I2M_CC_SET_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 controller = cs_pop(cs);
    s16 cc = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(controller, 0, 127);
    CLAMP_TO_RANGE(cc, 0, 127);
    cc *= 129;
    SEND_B4(45, midi_channel, controller, cc >> 7, cc & 0x7f);
}

static void op_I2M_NRPN_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 msb = cs_pop(cs);
    s16 lsb = cs_pop(cs);
    s16 value = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(msb, 0, 127);
    RETURN_IF_OUT_OF_RANGE(lsb, 0, 127);
    CLAMP_TO_RANGE(value, 0, 16384);
    SEND_B5(50, midi_channel, msb, lsb, value >> 7, value & 0x7f);
}

static void op_I2M_NRPN_OFF_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 msb = cs_pop(cs);
    s16 lsb = cs_pop(cs);
    if (msb < 0 || msb > 127 || lsb < 0 || lsb > 127) {
        cs_push(cs, 0);
    } else {
        SEND_B3(51, midi_channel, msb, lsb);
        RECEIVE_AND_PUSH_S16_7;
    }
}

static void op_I2M_NRPN_OFF_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 msb = cs_pop(cs);
    s16 lsb = cs_pop(cs);
    s16 offset = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(msb, 0, 127);
    RETURN_IF_OUT_OF_RANGE(lsb, 0, 127);
    CLAMP_TO_RANGE(offset, -16384, 16384);
    SEND_B5(52, midi_channel, msb, lsb, offset >> 7, offset & 0x7f);
}

static void op_I2M_NRPN_SLEW_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 msb = cs_pop(cs);
    s16 lsb = cs_pop(cs);
    if (msb < 0 || msb > 127 || lsb < 0 || lsb > 127) {
        cs_push(cs, 0);
    } else {
        SEND_B3(53, midi_channel, msb, lsb);
        RECEIVE_AND_PUSH_S16;
    }
}

static void op_I2M_NRPN_SLEW_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 msb = cs_pop(cs);
    s16 lsb = cs_pop(cs);
    s16 slew = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(msb, 0, 127);
    RETURN_IF_OUT_OF_RANGE(lsb, 0, 127);
    RETURN_IF_OUT_OF_RANGE(slew, 0, 32767);
    SEND_B5(54, midi_channel, msb, lsb, slew >> 8, slew & 0xff);
}

static void op_I2M_NRPN_SET_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 msb = cs_pop(cs);
    s16 lsb = cs_pop(cs);
    s16 value = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(msb, 0, 127);
    RETURN_IF_OUT_OF_RANGE(lsb, 0, 127);
    CLAMP_TO_RANGE(value, -16384, 16384);
    SEND_B5(55, midi_channel, msb, lsb, value >> 7, value & 0x7f);
}

static void op_I2M_PRG_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 prg = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(prg, 0, 127);
    SEND_B2(60, midi_channel, prg);
}

static void op_I2M_PB_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 pb = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(pb, 0, 16384);
    SEND_B3(61, midi_channel, pb >> 7, pb & 0x7f);
}

static void op_I2M_AT_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 at = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(at, 0, 127);
    SEND_B2(62, midi_channel, at);
}

static void op_I2M_CLK_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(63);
}

static void op_I2M_START_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(64);
}

static void op_I2M_STOP_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(65);
}

static void op_I2M_CONT_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(66);
}

static void op_I2M_Q_CH_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    cs_push(cs, q_channel + 1);
}

static void op_I2M_Q_CH_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 channel = cs_pop(cs);
    RETURN_IF_OUT_OF_RANGE(channel, 1, MAX_CHANNEL);
    q_channel = channel - 1;
}

static void op_I2M_Q_LATCH_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 latch = cs_pop(cs);
    SEND_B(100, latch);
}

static void op_I2M_Q_NOTE_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 index = cs_pop(cs);
    SEND_B2(110, q_channel, index);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_Q_VEL_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 index = cs_pop(cs);
    SEND_B2(111, q_channel, index);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_Q_CC_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    s16 controller = cs_pop(cs);
    
    if (controller < 0 || controller > 127) {
        cs_push(cs, 0);
    } else {
        SEND_B2(120, q_channel, controller);
        RECEIVE_AND_PUSH_S8;
    }
}

static void op_I2M_Q_LCH_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(130);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_Q_LN_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(131);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_Q_LV_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(132);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_Q_LO_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(133);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_Q_LC_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(134);
    RECEIVE_AND_PUSH_S8;
}

static void op_I2M_Q_LCC_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs) {
    SEND_CMD(135);
    RECEIVE_AND_PUSH_S8;
}
