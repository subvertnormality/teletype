#include "ops/fader.h"

#include "helpers.h"
#include "ii.h"
#include "teletype.h"
#include "teletype_io.h"
#include "telex.h"

#define FADER_GET_CC 0
#define FADER_NOTE_ON 1
#define FADER_NOTE_OFF 2


static void op_FADER_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_FB_CC_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_FB_ON_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_FB_OFF_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);


const tele_op_t op_FADER = MAKE_GET_OP(FADER, op_FADER_get, 1, true);

const tele_op_t op_FB = MAKE_ALIAS_OP(FB, op_FADER_get, NULL, 1, true);

const tele_op_t op_FB_CC = MAKE_GET_OP(FADER, op_FB_CC_get, 2, true);
const tele_op_t op_FB_ON = MAKE_GET_OP(FADER, op_FB_ON_get, 3, false);
const tele_op_t op_FB_OFF = MAKE_GET_OP(FADER, op_FB_OFF_get, 2, false);


static void op_FADER_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t input = cs_pop(cs);
    // zero-index the input
    input -= 1;
    // return if out of range
    if (input < 0 || input > 15) {
        cs_push(cs, 0);
        return;
    }
    // convert the input to the device and the port
    uint8_t port = input % 16;
    uint8_t device = input / 16;
    uint8_t address = FADER + device;
    ReceiveIt(address, port, cs);
}

static void op_FB_CC_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t channel = cs_pop(cs);
    uint16_t cc = cs_pop(cs);
    // return if out of range
    if (channel < 1 || channel > 15 || cc < 0 || cc > 127) {
        cs_push(cs, 0);
        return;
    }

    // tell the device what value you are going to query
    uint8_t buffer[3];
    buffer[0] = FADER_GET_CC;
    buffer[1] = channel;
    buffer[2] = cc;
    tele_ii_tx(FADER, buffer, 2);
    // now read the value
    buffer[0] = 0;
    buffer[1] = 0;
    tele_ii_rx(address, buffer, 2);
    int16_t value = (buffer[0] << 8) + buffer[1];
    cs_push(cs, value);
}

static void op_FB_ON_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t channel = cs_pop(cs);
    uint16_t note = cs_pop(cs);
    uint16_t velocity = cs_pop(cs);
    // return if out of range
    if (channel < 1 || channel > 15) return;

    uint8_t buffer[4];
    buffer[0] = FADER_NOTE_ON;
    buffer[1] = channel;
    buffer[2] = note;
    buffer[3] = velocity;
    tele_ii_tx(FADER, buffer, 4);
}

static void op_FB_OFF_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t channel = cs_pop(cs);
    uint16_t note = cs_pop(cs);
    uint16_t velocity = cs_pop(cs);
    // return if out of range
    if (channel < 1 || channel > 15) return;

    uint8_t buffer[3];
    buffer[0] = FADER_NOTE_OFF;
    buffer[1] = channel;
    buffer[2] = note;
    tele_ii_tx(FADER, buffer, 3);
}
