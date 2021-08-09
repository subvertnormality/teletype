#include "line_editor.h"

char empty = 0;

void line_editor_set(line_editor_t *le, const char value[LINE_EDITOR_SIZE]) {}
void line_editor_set_command(line_editor_t *le, const tele_command_t *command) {}
char *line_editor_get(line_editor_t *le) { return &empty; }
bool line_editor_process_keys(line_editor_t *le, uint8_t key, uint8_t mod_key,
                              bool is_key_held) { return 1; }
void line_editor_draw(line_editor_t *le, char prefix, region *reg) {}
