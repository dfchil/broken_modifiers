#include <dc/pvr.h>
#include <stdio.h>

void render_frame(void) {
  pvr_dr_state_t dr_state;
  pvr_vertex_t *vert_p;
  pvr_poly_cxt_t cxt;
  pvr_poly_hdr_t mod_poly_hdr;

  pvr_wait_ready();
  pvr_scene_begin();
  pvr_list_begin(PVR_LIST_OP_POLY);

  pvr_poly_cxt_col(&cxt, PVR_LIST_OP_POLY);
  cxt.gen.culling = PVR_CULLING_NONE;
  pvr_poly_compile(&mod_poly_hdr, &cxt);

  pvr_dr_init(&dr_state);
  vert_p = (pvr_vertex_t *)pvr_dr_target(dr_state);
  *((pvr_poly_hdr_t *)vert_p) = mod_poly_hdr;
  for (int i = 0; i < 4; i++) {
    pvr_dr_commit(vert_p);
    vert_p = (pvr_vertex_t *)pvr_dr_target(dr_state);

    float x = i < 2 ? 100.0f : 640.0f - 100.0f;
    float y = i % 2 == 0 ? 480.0f - 100.0f : 100.0f;

    vert_p->flags = PVR_CMD_VERTEX;
    vert_p->argb = 0xFFFFFFFF;
    vert_p->x = x;
    vert_p->y = y;
    vert_p->z = 0;
  }
  vert_p->flags = PVR_CMD_VERTEX_EOL;
  pvr_dr_commit(vert_p);
  pvr_list_finish();
  pvr_scene_finish();
}
