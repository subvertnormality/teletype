#include "ops/cvm.h"
#include "helpers.h"
#include "ii.h"
#include "teletype.h"
#include "teletype_io.h"

static void op_CVM_get(const void *data, scene_state_t *ss, exec_state_t *es,
                      command_state_t *cs);

static u8 d[2];

// clang-format off

#define CVM 0x32

#define SEND(cmd, b) \
    d[0] = cmd; \
    d[1] = b;   \
    tele_ii_tx(CVM, d, 2);

#define RECEIVE_AND_PUSH \
    d[0] = d[1] = 0; \
    tele_ii_rx(CVM, d, 2); \
    cs_push(cs, (d[0] << 8) + d[1]);


const tele_op_t op_CVM = MAKE_GET_OP(CVM, op_CVM_get, 1, true);

static void op_CVM_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    s8 jack = cs_pop(cs) - 1;
    SEND(1, jack);
    RECEIVE_AND_PUSH;

}