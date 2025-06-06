#include <arch/arch.h>
#include <drxlax/game/controller/dreamcast.h>
#include <drxlax/render/core.h>
#include <stdio.h>

static struct {
  uint32_t end_of_sequence : 1;
  uint32_t shut_down : 1;
  uint32_t : 30;
} flags;

int detect_shutdown_combo(controller_state_t *cstate) {
  if ((cstate->START & BUTTON_DOWN) && (cstate->A & BUTTON_DOWN)) {
    if ((cstate->START == BUTTON_DOWN_THIS_FRAME) ||
        (cstate->A == BUTTON_DOWN_THIS_FRAME)) {
      return 1;
    }
  }
  return 0;
}

void core_flag_shutdown(void) { flags.shut_down = 1; }

int check_c1_exit(void) {
  if (flags.shut_down) {
    return 1;
  }
  return 0;
}

void core_loop(void) {
  while (true) {    
    dc_ctrlrs_map_state();
    controller_state_t **cstates = get_ctrlr_states();
    for (int i = 0; i < MAPLE_PORT_COUNT; i++) {
      if (detect_shutdown_combo(cstates[i])) {
        core_flag_shutdown();
      }
    }
    if (check_c1_exit()) {
      break;
    }
    render_frame();
  }
}
