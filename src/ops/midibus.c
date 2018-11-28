#include "ops/midibus.h"

#include "helpers.h"
#include "ii.h"
#include "teletype.h"
#include "teletype_io.h"

#define MIDIBUS 0x11
#define II_MIDI_PRG 1
#define II_MIDI_CC 2
#define II_MIDI_ON 3
#define II_MIDI_OFF 4
#define II_BUS_SAVE 5
#define II_BUS_LOAD 6

static void op_MIDI_PRG_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_MIDI_CC_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_MIDI_ON_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_MIDI_OFF_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_BUS_SAVE_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_BUS_LOAD_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);

const tele_op_t op_MIDI_PRG = MAKE_GET_OP(MIDI.PRG, op_MIDI_PRG_get, 2, false);
const tele_op_t op_MIDI_CC = MAKE_GET_OP(MIDI.CC, op_MIDI_CC_get, 3, false);
const tele_op_t op_MIDI_ON = MAKE_GET_OP(MIDI.ON, op_MIDI_ON_get, 3, false);
const tele_op_t op_MIDI_OFF = MAKE_GET_OP(MIDI.OFF, op_MIDI_OFF_get, 2, false);

const tele_op_t op_BUS_SAVE = MAKE_GET_OP(BUS.SAVE, op_BUS_SAVE_get, 1, false);
const tele_op_t op_BUS_LOAD = MAKE_GET_OP(BUS.LOAD, op_BUS_LOAD_get, 1, false);

static void op_MIDI_PRG_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs);
    s16 prg = cs_pop(cs);
    uint8_t d[] = { II_MIDI_PRG, ch, prg };
    tele_ii_tx(MIDIBUS, d, 3);
}

static void op_MIDI_CC_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs);
    s16 cc = cs_pop(cs);
    s16 val = cs_pop(cs);
    uint8_t d[] = { II_MIDI_CC, ch, cc, val };
    tele_ii_tx(MIDIBUS, d, 4);
}

static void op_MIDI_ON_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs);
    s16 note = cs_pop(cs);
    s16 vel = cs_pop(cs);
    uint8_t d[] = { II_MIDI_ON, ch, note, vel };
    tele_ii_tx(MIDIBUS, d, 4);
}

static void op_MIDI_OFF_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 ch = cs_pop(cs);
    s16 note = cs_pop(cs);
    uint8_t d[] = { II_MIDI_OFF, ch, note };
    tele_ii_tx(MIDIBUS, d, 3);
}

static void op_BUS_SAVE_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 val = cs_pop(cs);
    uint8_t d[] = { II_BUS_SAVE, val };
    tele_ii_tx(MIDIBUS, d, 2);
}

static void op_BUS_LOAD_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 val = cs_pop(cs);
    uint8_t d[] = { II_BUS_LOAD, val };
    tele_ii_tx(MIDIBUS, d, 2);
}
