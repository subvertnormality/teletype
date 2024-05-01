#include "ops/disting.h"

#include "helpers.h"
#include "ii.h"
#include "teletype.h"
#include "teletype_io.h"

static void mod_EX1_func(scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs,
                         const tele_command_t *post_command);
static void mod_EX2_func(scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs,
                         const tele_command_t *post_command);
static void mod_EX3_func(scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs,
                         const tele_command_t *post_command);
static void mod_EX4_func(scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs,
                         const tele_command_t *post_command);
static void op_EX_get(const void *data, scene_state_t *ss, exec_state_t *es,
                      command_state_t *cs);
static void op_EX_set(const void *data, scene_state_t *ss, exec_state_t *es,
                      command_state_t *cs);
static void op_EX_PRESET_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_PRESET_set(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_SAVE_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_RESET_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_ALG_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_ALG_set(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_CTRL_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_PARAM_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_PARAM_set(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_PV_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_MIN_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_MAX_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_REC_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_PLAY_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_AL_P_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_AL_CLK_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_M_CH_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_M_CH_set(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_M_N_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_M_N_POUND_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_EX_M_NO_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_M_NO_POUND_get(const void *data, scene_state_t *ss,
                                 exec_state_t *es, command_state_t *cs);
static void op_EX_M_CC_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_M_CC_POUND_get(const void *data, scene_state_t *ss,
                                 exec_state_t *es, command_state_t *cs);
static void op_EX_M_PB_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_M_PRG_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_M_CLK_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_M_START_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_EX_M_STOP_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_M_CONT_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_SB_CH_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_SB_CH_set(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_SB_N_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_SB_NO_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_SB_PB_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_SB_CC_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_SB_PRG_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_SB_CLK_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_SB_START_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_EX_SB_STOP_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_EX_SB_CONT_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_EX_VOX_P_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_VOX_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_VOX_O_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_CH_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_CH_set(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_NOTE_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_N_POUND_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_EX_NOTE_O_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_NO_POUND_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_EX_ALLOFF_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_T_get(const void *data, scene_state_t *ss, exec_state_t *es,
                        command_state_t *cs);
static void op_EX_TV_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_LP_REC_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_LP_PLAY_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_EX_LP_REV_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_LP_DOWN_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_EX_LP_CLR_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_EX_LP_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_LP_REVQ_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_EX_LP_DOWNQ_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_EX_A1_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_A1_set(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_A2_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_A2_set(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_A12_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_P1_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_P1_set(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_P2_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_P2_set(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_PV1_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_PV2_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_MIN1_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_MIN2_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_MAX1_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_MAX2_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_PRE1_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_PRE2_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_EX_SAVE1_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_SAVE2_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_EX_Z1_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_Z1_set(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_Z2_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_Z2_set(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_EX_ZO1_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_EX_ZO2_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);

// clang-format off
                   
const tele_mod_t mod_EX1       = MAKE_MOD(EX1, mod_EX1_func, 0);
const tele_mod_t mod_EX2       = MAKE_MOD(EX2, mod_EX2_func, 0);
const tele_mod_t mod_EX3       = MAKE_MOD(EX3, mod_EX3_func, 0);
const tele_mod_t mod_EX4       = MAKE_MOD(EX4, mod_EX4_func, 0);
                   
const tele_op_t op_EX          = MAKE_GET_SET_OP(EX,        op_EX_get,          op_EX_set, 0, true);
const tele_op_t op_EX_PRESET   = MAKE_GET_SET_OP(EX.PRESET, op_EX_PRESET_get,   op_EX_PRESET_set, 0, true);
const tele_op_t op_EX_SAVE     = MAKE_GET_OP(EX.SAVE,       op_EX_SAVE_get,     1, false);
const tele_op_t op_EX_RESET    = MAKE_GET_OP(EX.RESET,      op_EX_RESET_get,    0, false);
const tele_op_t op_EX_ALG      = MAKE_GET_SET_OP(EX.ALG,    op_EX_ALG_get,      op_EX_ALG_set, 0, true);
const tele_op_t op_EX_CTRL     = MAKE_GET_OP(EX.CTRL,       op_EX_CTRL_get,     2, false);
const tele_op_t op_EX_PARAM    = MAKE_GET_SET_OP(EX.PARAM,  op_EX_PARAM_get,    op_EX_PARAM_set, 1, true);
const tele_op_t op_EX_PV       = MAKE_GET_OP(EX.PV,         op_EX_PV_get,       2, false);
const tele_op_t op_EX_MIN      = MAKE_GET_OP(EX.MIN,        op_EX_MIN_get,      1, true);
const tele_op_t op_EX_MAX      = MAKE_GET_OP(EX.MAX,        op_EX_MAX_get,      1, true);
const tele_op_t op_EX_REC      = MAKE_GET_OP(EX.REC,        op_EX_REC_get,      1, false);
const tele_op_t op_EX_PLAY     = MAKE_GET_OP(EX.PLAY,       op_EX_PLAY_get,     1, false);
const tele_op_t op_EX_AL_P     = MAKE_GET_OP(EX.AL.P,       op_EX_AL_P_get,     1, false);
const tele_op_t op_EX_AL_CLK   = MAKE_GET_OP(EX.AL.CLK,     op_EX_AL_CLK_get,   0, false);

const tele_op_t op_EX_M_CH       = MAKE_GET_SET_OP(EX.M.CH, op_EX_M_CH_get, op_EX_M_CH_set, 0, true);
const tele_op_t op_EX_M_N        = MAKE_GET_OP(EX.M.N,      op_EX_M_N_get,        2, false);
const tele_op_t op_EX_M_N_POUND  = MAKE_GET_OP(EX.M.N#,     op_EX_M_N_POUND_get,  3, false);
const tele_op_t op_EX_M_NO       = MAKE_GET_OP(EX.M.NO,     op_EX_M_NO_get,       1, false);
const tele_op_t op_EX_M_NO_POUND = MAKE_GET_OP(EX.M.NO#,    op_EX_M_NO_POUND_get, 2, false);
const tele_op_t op_EX_M_CC       = MAKE_GET_OP(EX.M.CC,     op_EX_M_CC_get,       2, false);
const tele_op_t op_EX_M_CC_POUND = MAKE_GET_OP(EX.M.CC#,    op_EX_M_CC_POUND_get, 3, false);
const tele_op_t op_EX_M_PB       = MAKE_GET_OP(EX.M.PB,     op_EX_M_PB_get,       1, false);
const tele_op_t op_EX_M_PRG      = MAKE_GET_OP(EX.M.PRG,    op_EX_M_PRG_get,      1, false);
const tele_op_t op_EX_M_CLK      = MAKE_GET_OP(EX.M.CLK,    op_EX_M_CLK_get,      0, false);
const tele_op_t op_EX_M_START    = MAKE_GET_OP(EX.M.START,  op_EX_M_START_get,    0, false);
const tele_op_t op_EX_M_STOP     = MAKE_GET_OP(EX.M.STOP,   op_EX_M_STOP_get,     0, false);
const tele_op_t op_EX_M_CONT     = MAKE_GET_OP(EX.M.CONT,   op_EX_M_CONT_get,     0, false);

const tele_op_t op_EX_SB_CH    = MAKE_GET_SET_OP(EX.SB.CH,  op_EX_SB_CH_get,    op_EX_SB_CH_set, 0, true);
const tele_op_t op_EX_SB_N     = MAKE_GET_OP(EX.SB.N,       op_EX_SB_N_get,     2, false);
const tele_op_t op_EX_SB_NO    = MAKE_GET_OP(EX.SB.NO,      op_EX_SB_NO_get,    1, false);
const tele_op_t op_EX_SB_PB    = MAKE_GET_OP(EX.SB.PB,      op_EX_SB_PB_get,    1, false);
const tele_op_t op_EX_SB_CC    = MAKE_GET_OP(EX.SB.CC,      op_EX_SB_CC_get,    2, false);
const tele_op_t op_EX_SB_PRG   = MAKE_GET_OP(EX.SB.PRG,     op_EX_SB_PRG_get,   1, false);
const tele_op_t op_EX_SB_CLK   = MAKE_GET_OP(EX.SB.CLK,     op_EX_SB_CLK_get,   0, false);
const tele_op_t op_EX_SB_START = MAKE_GET_OP(EX.SB.START,   op_EX_SB_START_get, 0, false);
const tele_op_t op_EX_SB_STOP  = MAKE_GET_OP(EX.SB.STOP,    op_EX_SB_STOP_get,  0, false);
const tele_op_t op_EX_SB_CONT  = MAKE_GET_OP(EX.SB.CONT,    op_EX_SB_CONT_get,  0, false);

const tele_op_t op_EX_VOX      = MAKE_GET_OP(EX.VOX,    op_EX_VOX_get,              3, false);
const tele_op_t op_EX_VOX_P    = MAKE_GET_OP(EX.VOX.P,  op_EX_VOX_P_get,            2, false);
const tele_op_t op_EX_VOX_O    = MAKE_GET_OP(EX.VOX.O,  op_EX_VOX_O_get,            1, false);
const tele_op_t op_EX_CH       = MAKE_GET_SET_OP(EX.CH, op_EX_CH_get, op_EX_CH_set, 0, true);
const tele_op_t op_EX_POUND    = MAKE_ALIAS_OP(EX.#,    op_EX_CH_get, op_EX_CH_set, 0, true);
const tele_op_t op_EX_NOTE     = MAKE_GET_OP(EX.NOTE,   op_EX_NOTE_get,             2, false);
const tele_op_t op_EX_N_POUND  = MAKE_GET_OP(EX.N#,     op_EX_N_POUND_get,          3, false);
const tele_op_t op_EX_NOTE_O   = MAKE_GET_OP(EX.NOTE.O, op_EX_NOTE_O_get,           1, false);
const tele_op_t op_EX_NO_POUND = MAKE_GET_OP(EX.NO#,    op_EX_NO_POUND_get,         2, false);
const tele_op_t op_EX_ALLOFF   = MAKE_GET_OP(EX.ALLOFF, op_EX_ALLOFF_get,           0, false);

const tele_op_t op_EX_LP_REC   = MAKE_GET_OP(EX.LP.REC,   op_EX_LP_REC_get,   1, false);
const tele_op_t op_EX_LP_PLAY  = MAKE_GET_OP(EX.LP.PLAY,  op_EX_LP_PLAY_get,  1, false);
const tele_op_t op_EX_LP_REV   = MAKE_GET_OP(EX.LP.REV,   op_EX_LP_REV_get,   1, false);
const tele_op_t op_EX_LP_DOWN  = MAKE_GET_OP(EX.LP.DOWN,  op_EX_LP_DOWN_get,  1, false);
const tele_op_t op_EX_LP_CLR   = MAKE_GET_OP(EX.LP.CLR,   op_EX_LP_CLR_get,   1, false);
const tele_op_t op_EX_LP       = MAKE_GET_OP(EX.LP,       op_EX_LP_get,       1, true);
const tele_op_t op_EX_LP_REVQ  = MAKE_GET_OP(EX.LP.REV?,  op_EX_LP_REVQ_get,  1, true);
const tele_op_t op_EX_LP_DOWNQ = MAKE_GET_OP(EX.LP.DOWN?, op_EX_LP_DOWNQ_get, 1, true);

const tele_op_t op_EX_A1       = MAKE_GET_SET_OP(EX.A1, op_EX_A1_get,    op_EX_A1_set, 0, true);
const tele_op_t op_EX_A2       = MAKE_GET_SET_OP(EX.A2, op_EX_A2_get,    op_EX_A2_set, 0, true);
const tele_op_t op_EX_A12      = MAKE_GET_OP(EX.A12,    op_EX_A12_get,   2, false);
const tele_op_t op_EX_P1       = MAKE_GET_SET_OP(EX.P1, op_EX_P1_get,    op_EX_P1_set, 1, true);
const tele_op_t op_EX_P2       = MAKE_GET_SET_OP(EX.P2, op_EX_P2_get,    op_EX_P2_set, 1, true);
const tele_op_t op_EX_PV1      = MAKE_GET_OP(EX.PV1,    op_EX_PV1_get,   2, false);
const tele_op_t op_EX_PV2      = MAKE_GET_OP(EX.PV2,    op_EX_PV2_get,   2, false);
const tele_op_t op_EX_MIN1     = MAKE_GET_OP(EX.MIN1,   op_EX_MIN1_get,  1, true);
const tele_op_t op_EX_MIN2     = MAKE_GET_OP(EX.MIN2,   op_EX_MIN2_get,  1, true);
const tele_op_t op_EX_MAX1     = MAKE_GET_OP(EX.MAX1,   op_EX_MAX1_get,  1, true);
const tele_op_t op_EX_MAX2     = MAKE_GET_OP(EX.MAX2,   op_EX_MAX2_get,  1, true);
const tele_op_t op_EX_PRE1     = MAKE_GET_OP(EX.PRE1,   op_EX_PRE1_get,  1, false);
const tele_op_t op_EX_PRE2     = MAKE_GET_OP(EX.PRE2,   op_EX_PRE2_get,  1, false);
const tele_op_t op_EX_SAVE1    = MAKE_GET_OP(EX.SAVE1,  op_EX_SAVE1_get, 1, false);
const tele_op_t op_EX_SAVE2    = MAKE_GET_OP(EX.SAVE2,  op_EX_SAVE2_get, 1, false);
const tele_op_t op_EX_Z1       = MAKE_GET_SET_OP(EX.Z1, op_EX_Z1_get,    op_EX_Z1_set, 0, true);
const tele_op_t op_EX_Z2       = MAKE_GET_SET_OP(EX.Z2, op_EX_Z2_get,    op_EX_Z2_set, 0, true);
const tele_op_t op_EX_ZO1      = MAKE_GET_OP(EX.ZO1,    op_EX_ZO1_get,   0, false);
const tele_op_t op_EX_ZO2      = MAKE_GET_OP(EX.ZO2,    op_EX_ZO2_get,   0, false);

const tele_op_t op_EX_PRE = MAKE_ALIAS_OP(EX.PRE, op_EX_PRESET_get, op_EX_PRESET_set, 0, true);
const tele_op_t op_EX_A   = MAKE_ALIAS_OP(EX.A,   op_EX_ALG_get,    op_EX_ALG_set,    0, true);
const tele_op_t op_EX_P   = MAKE_ALIAS_OP(EX.P,   op_EX_PARAM_get,  op_EX_PARAM_set,  1, true);
const tele_op_t op_EX_C   = MAKE_ALIAS_OP(EX.C,   op_EX_CTRL_get,   NULL, 2, false);
const tele_op_t op_EX_V   = MAKE_ALIAS_OP(EX.V,   op_EX_VOX_get,    NULL, 3, false);
const tele_op_t op_EX_VP  = MAKE_ALIAS_OP(EX.VP,  op_EX_VOX_P_get,  NULL, 2, false);
const tele_op_t op_EX_VO  = MAKE_ALIAS_OP(EX.VO,  op_EX_VOX_O_get,  NULL, 1, false);
const tele_op_t op_EX_N   = MAKE_ALIAS_OP(EX.N,   op_EX_NOTE_get,   NULL, 2, false);
const tele_op_t op_EX_NO  = MAKE_ALIAS_OP(EX.NO,  op_EX_NOTE_O_get, NULL, 1, false);
const tele_op_t op_EX_AO  = MAKE_ALIAS_OP(EX.AO,  op_EX_ALLOFF_get, NULL, 0, false);
const tele_op_t op_EX_T   = MAKE_ALIAS_OP(EX.T,   op_EX_T_get,      NULL, 1, false);
const tele_op_t op_EX_TV  = MAKE_ALIAS_OP(EX.TV,  op_EX_TV_get,     NULL, 2, false);

// clang-format on

static u8 unit = 0;
static u8 note_channel = 1;
static u8 midi_channel = 0;
static u8 sb_channel = 0;
static u8 data[5];

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

static inline void send5(u8 cmd, u8 b1, u8 b2, u8 b3, u8 b4) {
    data[0] = cmd;
    data[1] = b1;
    data[2] = b2;
    data[3] = b3;
    data[4] = b4;
    tele_ii_tx(DISTING_EX_1 + unit, data, 5);
}

static void mod_EX1_func(scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs,
                         const tele_command_t *post_command) {
    u8 u = unit;
    unit = 0;
    process_command(ss, es, post_command);
    unit = u;
}

static void mod_EX2_func(scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs,
                         const tele_command_t *post_command) {
    u8 u = unit;
    unit = 1;
    process_command(ss, es, post_command);
    unit = u;
}

static void mod_EX3_func(scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs,
                         const tele_command_t *post_command) {
    u8 u = unit;
    unit = 2;
    process_command(ss, es, post_command);
    unit = u;
}

static void mod_EX4_func(scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs,
                         const tele_command_t *post_command) {
    u8 u = unit;
    unit = 3;
    process_command(ss, es, post_command);
    unit = u;
}

static void op_EX_get(const void *NOTUSED(data), scene_state_t *ss,
                      exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, unit + 1);
}

static void op_EX_set(const void *NOTUSED(data), scene_state_t *ss,
                      exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 u = cs_pop(cs) - 1;
    if (u < 0 || u > 3) return;
    unit = u;
}

static void op_EX_PRESET_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    send1(0x43);

    data[0] = data[1] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 2);

    cs_push(cs, (data[0] << 8) + data[1]);
}

static void op_EX_PRESET_set(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 preset = cs_pop(cs);
    send3(0x40, preset >> 8, preset);
}

static void op_EX_SAVE_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 preset = cs_pop(cs);
    send3(0x41, preset >> 8, preset);
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
    send2(0x48, param);

    data[0] = data[1] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 2);
    u16 value = (data[0] << 8) + data[1];
    cs_push(cs, (s16)value);
}

static void op_EX_PARAM_set(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    u16 value = cs_pop(cs);
    send4(0x46, param, value >> 8, value);
}

static void op_EX_PV_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    u16 value = cs_pop(cs);
    send4(0x47, param, value >> 8, value);
}

static void op_EX_MIN_get(const void *NOTUSED(data), scene_state_t *ss,
                          exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    send2(0x49, param);

    data[0] = data[1] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 2);
    u16 value = (data[0] << 8) + data[1];
    cs_push(cs, (s16)value);
}

static void op_EX_MAX_get(const void *NOTUSED(data), scene_state_t *ss,
                          exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    send2(0x4A, param);

    data[0] = data[1] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 2);
    u16 value = (data[0] << 8) + data[1];
    cs_push(cs, (s16)value);
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
    cs_push(cs, midi_channel + 1);
}

static void op_EX_M_CH_set(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs) - 1;
    if (ch < 0 || ch > 15) return;
    midi_channel = ch;
}

static void op_EX_M_N_get(const void *NOTUSED(data), scene_state_t *ss,
                          exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 note = cs_pop(cs);
    u16 velocity = cs_pop(cs);
    if (note > 127) return;
    if (velocity > 127) velocity = 127;
    send4(0x4F, 0x90 + midi_channel, note, velocity);
}

static void op_EX_M_N_POUND_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    s16 ch = cs_pop(cs) - 1;
    u16 note = cs_pop(cs);
    u16 velocity = cs_pop(cs);
    if (ch < 0 || ch > 15) return;
    if (note > 127) return;
    if (velocity > 127) velocity = 127;
    send4(0x4F, 0x90 + ch, note, velocity);
}

static void op_EX_M_NO_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 note = cs_pop(cs);
    if (note > 127) return;
    send4(0x4F, 0x80 + midi_channel, note, 0);
}

static void op_EX_M_NO_POUND_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    s16 ch = cs_pop(cs) - 1;
    u16 note = cs_pop(cs);
    if (ch < 0 || ch > 15) return;
    if (note > 127) return;
    send4(0x4F, 0x80 + ch, note, 0);
}

static void op_EX_M_CC_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 controller = cs_pop(cs);
    u16 value = cs_pop(cs);
    if (controller > 127) return;
    if (value > 127) value = 127;
    send4(0x4F, 0xB0 + midi_channel, controller, value);
}

static void op_EX_M_CC_POUND_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    s16 ch = cs_pop(cs) - 1;
    u16 controller = cs_pop(cs);
    u16 value = cs_pop(cs);
    if (ch < 0 || ch > 15) return;
    if (controller > 127) return;
    if (value > 127) value = 127;
    send4(0x4F, 0xB0 + ch, controller, value);
}

static void op_EX_M_PB_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 bend = cs_pop(cs);
    send4(0x4F, 0xE0 + midi_channel, bend, bend >> 8);
}

static void op_EX_M_PRG_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 program = cs_pop(cs);
    if (program > 127) return;
    send3(0x4F, 0xC0 + midi_channel, program);
}

static void op_EX_M_CLK_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x4F, 0xF8 + midi_channel, 0xF8);
}

static void op_EX_M_START_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x4F, 0xFA + midi_channel, 0xFA);
}

static void op_EX_M_STOP_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x4F, 0xFC + midi_channel, 0xFC);
}

static void op_EX_M_CONT_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x4F, 0xFB + midi_channel, 0xFB);
}

static void op_EX_SB_CH_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, sb_channel + 1);
}

static void op_EX_SB_CH_set(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs) - 1;
    if (ch < 0 || ch > 15) return;
    sb_channel = ch;
}

static void op_EX_SB_N_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 note = cs_pop(cs);
    u16 velocity = cs_pop(cs);
    if (note > 127) return;
    if (velocity > 127) velocity = 127;
    send4(0x50, 0x90 + sb_channel, note, velocity);
}

static void op_EX_SB_NO_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 note = cs_pop(cs);
    if (note > 127) return;
    send4(0x50, 0x80 + sb_channel, note, 0);
}

static void op_EX_SB_PB_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 bend = cs_pop(cs);
    send4(0x50, 0xE0 + sb_channel, bend, bend >> 8);
}

static void op_EX_SB_CC_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 controller = cs_pop(cs);
    u16 value = cs_pop(cs);
    if (controller > 127) return;
    if (value > 127) value = 127;
    send4(0x50, 0xB0 + sb_channel, controller, value);
}

static void op_EX_SB_PRG_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 program = cs_pop(cs);
    if (program > 127) return;
    send3(0x50, 0xC0 + sb_channel, program);
}

static void op_EX_SB_CLK_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x50, 0xF8 + sb_channel, 0xF8);
}

static void op_EX_SB_START_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x50, 0xFA + sb_channel, 0xFA);
}

static void op_EX_SB_STOP_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x50, 0xFC + sb_channel, 0xFC);
}

static void op_EX_SB_CONT_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x50, 0xFB + sb_channel, 0xFB);
}

static void op_EX_VOX_get(const void *NOTUSED(data), scene_state_t *ss,
                          exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 voice = cs_pop(cs) - 1;
    s16 pitch = cs_pop(cs);
    u16 velocity = cs_pop(cs);
    if (voice < 0) return;

    send4(0x51, voice, (u16)pitch >> 8, pitch);
    send4(0x52, voice, velocity >> 8, velocity);
}

static void op_EX_VOX_P_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 voice = cs_pop(cs) - 1;
    s16 pitch = cs_pop(cs);
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

static u8 calculate_note(s16 pitch) {
    s32 note = (((s32)pitch * 240) / 16384);
    note = note / 2 + (note & 1) + 48;
    if (note < 0)
        note = 0;
    else if (note > 127)
        note = 127;
    return (u8)note;
}

static void op_EX_CH_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, note_channel);
}

static void op_EX_CH_set(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs);
    if (ch < 1 || ch > 16) return;
    note_channel = ch;
}

static void op_EX_NOTE_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 pitch = cs_pop(cs);
    u16 velocity = cs_pop(cs);
    u8 note = calculate_note(pitch);

    send3(0x6A, note_channel, note);
    send5(0x68, note_channel, note, (u16)pitch >> 8, pitch);
    send5(0x69, note_channel, note, velocity >> 8, velocity);
}

static void op_EX_N_POUND_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs);
    s16 pitch = cs_pop(cs);
    u16 velocity = cs_pop(cs);
    u8 note = calculate_note(pitch);
    if (ch < 1 || ch > 16) return;

    send3(0x6A, ch, note);
    send5(0x68, ch, note, (u16)pitch >> 8, pitch);
    send5(0x69, ch, note, velocity >> 8, velocity);
}

static void op_EX_NOTE_O_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 pitch = cs_pop(cs);
    u8 note = calculate_note(pitch);

    send3(0x6A, note_channel, note);
}

static void op_EX_NO_POUND_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs);
    u16 pitch = cs_pop(cs);
    u8 note = calculate_note(pitch);
    if (ch < 1 || ch > 16) return;

    send3(0x6A, ch, note);
}

static void op_EX_ALLOFF_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    send1(0x57);
}

static void op_EX_T_get(const void *NOTUSED(data), scene_state_t *ss,
                        exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 voice = cs_pop(cs) - 1;
    if (voice < 0) return;

    u16 velocity = 8192;
    send4(0x52, voice, velocity >> 8, velocity);
}

static void op_EX_TV_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 voice = cs_pop(cs) - 1;
    u16 velocity = cs_pop(cs);
    if (voice < 0) return;

    send4(0x52, voice, velocity >> 8, velocity);
}

static void op_EX_LP_REC_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 loop = cs_pop(cs);
    if (loop < 1 || loop > 4) return;

    send4(0x6C, 7, 0, loop);
    send4(0x6C, 55, 0, 0);
    send4(0x6C, 55, 0, 1);
    send4(0x6C, 55, 0, 0);
}

static void op_EX_LP_PLAY_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 loop = cs_pop(cs);
    if (loop < 1 || loop > 4) return;

    send4(0x6C, 7, 0, loop);
    send4(0x6C, 56, 0, 0);
    send4(0x6C, 56, 0, 1);
    send4(0x6C, 56, 0, 0);
}

static void op_EX_LP_REV_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 loop = cs_pop(cs);
    if (loop < 1 || loop > 4) return;

    send4(0x6C, 7, 0, loop);
    send4(0x6C, 57, 0, 0);
    send4(0x6C, 57, 0, 1);
    send4(0x6C, 57, 0, 0);
}

static void op_EX_LP_DOWN_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 loop = cs_pop(cs);
    if (loop < 1 || loop > 4) return;

    send4(0x6C, 7, 0, loop);
    send4(0x6C, 58, 0, 0);
    send4(0x6C, 58, 0, 1);
    send4(0x6C, 58, 0, 0);
}

static void op_EX_LP_CLR_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 loop = cs_pop(cs);
    if (loop < 1 || loop > 4) return;

    send4(0x6C, 7, 0, loop);
    send1(0x58);
}

static u8 get_looper_state(u8 loop) {
    send2(0x59, loop);
    data[0] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 1);
    return data[0];
}

static void op_EX_LP_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 loop = cs_pop(cs) - 1;
    if (loop < 0 || loop > 3) {
        cs_push(cs, -1);
        return;
    }

    cs_push(cs, get_looper_state(loop) & 0b1111);
}

static void op_EX_LP_REVQ_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 loop = cs_pop(cs) - 1;
    if (loop < 0 || loop > 3) {
        cs_push(cs, 0);
        return;
    }

    cs_push(cs, get_looper_state(loop) & 0b10000 ? 1 : 0);
}

static void op_EX_LP_DOWNQ_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 loop = cs_pop(cs) - 1;
    if (loop < 0 || loop > 3) {
        cs_push(cs, 0);
        return;
    }

    cs_push(cs, get_looper_state(loop) & 0b100000 ? 1 : 0);
}

static void op_EX_A1_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send2(0x5F, 0);
    data[0] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 1);
    cs_push(cs, data[0] + 1);
}

static void op_EX_A1_set(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 algo = cs_pop(cs);
    if (algo < 1) return;
    send3(0x60, 0, algo - 1);
}

static void op_EX_A2_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send2(0x5F, 1);
    data[0] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 1);
    cs_push(cs, data[0] + 1);
}

static void op_EX_A2_set(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 algo = cs_pop(cs);
    if (algo < 1) return;
    send3(0x60, 1, algo - 1);
}

static void op_EX_A12_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                          exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 algo1 = cs_pop(cs);
    u16 algo2 = cs_pop(cs);
    if (algo1 < 1 || algo2 < 1) return;
    send3(0x62, algo1 - 1, algo2 - 1);
}

static void op_EX_P1_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    send2(0x5A, param);

    data[0] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 1);
    cs_push(cs, (s8)data[0]);
}

static void op_EX_P1_set(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    u16 value = cs_pop(cs);
    send3(0x5D, param, value);
}

static void op_EX_P2_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    send2(0x5A, param | 0b10000);

    data[0] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 1);
    cs_push(cs, (s8)data[0]);
}

static void op_EX_P2_set(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    u16 value = cs_pop(cs);
    send3(0x5D, param | 0b10000, value);
}

static void op_EX_PV1_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                          exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    u16 value = cs_pop(cs);
    send4(0x5E, param, value >> 8, value);
}

static void op_EX_PV2_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                          exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    u16 value = cs_pop(cs);
    send4(0x5E, param | 0b10000, value >> 8, value);
}

static void op_EX_MIN1_get(const void *NOTUSED(data),
                           scene_state_t *NOTUSED(ss),
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    send2(0x5B, param);

    data[0] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 1);
    cs_push(cs, (s8)data[0]);
}

static void op_EX_MIN2_get(const void *NOTUSED(data),
                           scene_state_t *NOTUSED(ss),
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    send2(0x5B, param | 0b10000);

    data[0] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 1);
    cs_push(cs, (s8)data[0]);
}

static void op_EX_MAX1_get(const void *NOTUSED(data),
                           scene_state_t *NOTUSED(ss),
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    send2(0x5C, param);

    data[0] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 1);
    cs_push(cs, (s8)data[0]);
}

static void op_EX_MAX2_get(const void *NOTUSED(data),
                           scene_state_t *NOTUSED(ss),
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    send2(0x5C, param | 0b10000);

    data[0] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 1);
    cs_push(cs, (s8)data[0]);
}

static void op_EX_PRE1_get(const void *NOTUSED(data),
                           scene_state_t *NOTUSED(ss),
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 preset = cs_pop(cs);
    send3(0x63, 0, preset);
}

static void op_EX_PRE2_get(const void *NOTUSED(data),
                           scene_state_t *NOTUSED(ss),
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 preset = cs_pop(cs);
    send3(0x63, 1, preset);
}

static void op_EX_SAVE1_get(const void *NOTUSED(data),
                            scene_state_t *NOTUSED(ss),
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 preset = cs_pop(cs);
    send3(0x64, 0, preset);
}

static void op_EX_SAVE2_get(const void *NOTUSED(data),
                            scene_state_t *NOTUSED(ss),
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 preset = cs_pop(cs);
    send3(0x64, 1, preset);
}

static void op_EX_Z1_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send1(0x66);

    data[0] = data[1] = data[2] = data[3] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 4);
    u16 value = (data[0] << 8) + data[1];
    cs_push(cs, value >> 8);
}

static void op_EX_Z1_set(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    if (param > 127) return;
    send3(0x65, 0, param);
}

static void op_EX_Z2_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    send1(0x66);

    data[0] = data[1] = data[2] = data[3] = 0;
    tele_ii_rx(DISTING_EX_1 + unit, data, 4);
    u16 value = (data[2] << 8) + data[3];
    cs_push(cs, (s16)value >> 8);
}

static void op_EX_Z2_set(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    u16 param = cs_pop(cs);
    if (param > 127) return;
    send3(0x65, 1, param);
}

static void op_EX_ZO1_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                          exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x65, 0, 128);
}

static void op_EX_ZO2_get(const void *NOTUSED(data), scene_state_t *NOTUSED(ss),
                          exec_state_t *NOTUSED(es), command_state_t *cs) {
    send3(0x65, 1, 128);
}
