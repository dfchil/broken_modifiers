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
  // pvr_poly_cxt_col_mod(&cxt, PVR_LIST_OP_POLY);
  // cxt.gen.culling = PVR_CULLING_NONE;
  // pvr_poly_mod_hdr_t mod_poly_hdr;
  // pvr_poly_mod_compile(&mod_poly_hdr, &cxt);

  pvr_poly_cxt_col(&cxt, PVR_LIST_OP_POLY);
  cxt.gen.culling = PVR_CULLING_NONE;
  pvr_poly_compile(&mod_poly_hdr, &cxt);

  pvr_dr_init(&dr_state);
  vert_p = (pvr_vertex_t *)pvr_dr_target(dr_state);
  *((pvr_poly_hdr_t *)vert_p) = mod_poly_hdr;
  for (int i = 0; i < 4; i++) {
    // printf("i: %d\n", i);
    pvr_dr_commit(vert_p);
    vert_p = (pvr_vertex_t *)pvr_dr_target(dr_state);

    float x = i < 2 ? 100.0f : 640.0f - 100.0f;
    float y = i % 2 == 0 ? 480.0f - 100.0f : 100.0f;

    // printf("i: %d, x: %.3f\n", i, x);
    // printf("i: %d, y: %.3f\n", i, y);

    vert_p->flags = PVR_CMD_VERTEX;
    vert_p->x = x;
    vert_p->y = y;
    vert_p->z = 0;
    vert_p->argb = 0xFFFFFFFF;
    // vert_p->oargb = 0xFFFFFFFF;
    vert_p->u = 0;
    vert_p->v = 0;

    // vert_p->argb0 = 0xFFFFFFFF;
    // vert_p->argb1 = 0x7fF7f7f0;
    // vert_p->d1 = 0;
    // vert_p->d2 = 0;
  }
  // printf("\n\n");

  vert_p->flags = PVR_CMD_VERTEX_EOL;
  pvr_dr_commit(vert_p);
  // pvr_dr_finish();

  pvr_list_finish();

  // pvr_list_begin(PVR_LIST_PT_POLY);
  // pvr_list_finish();

  // pvr_list_begin(PVR_LIST_TR_MOD);
  // pvr_dr_init(&dr_state);
  // pvr_mod_hdr_t mod_hdr;
  // pvr_mod_compile(&mod_hdr, PVR_LIST_TR_MOD, PVR_MODIFIER_INCLUDE_LAST_POLY,
  //                 PVR_CULLING_CCW);
  // vert_p = (pvr_vertex_pcm_t *)pvr_dr_target(dr_state);
  // *((pvr_mod_hdr_t *)vert_p) = mod_hdr;
  // pvr_dr_commit(vert_p);
  // pvr_modifier_vol_t *modh_p = (pvr_modifier_vol_t *)pvr_dr_target(dr_state);
  // modh_p->flags = PVR_CMD_MODIFIER;
  // modh_p->ax = 200;
  // modh_p->ay = 200;
  // modh_p->az = 1;
  // modh_p->bx = 640 - 200;
  // modh_p->by = 200;
  // modh_p->bz = 1;
  // modh_p->cx = 640 - 200;
  // pvr_dr_commit(modh_p);
  // modh_p = (pvr_modifier_vol_t *)pvr_dr_target(dr_state);
  // pvr_modifier_vol_t *modh_p2 = (pvr_modifier_vol_t *)((int)modh_p - 32);

  // modh_p2->cy = 480 - 200;
  // modh_p2->cz = 1;
  // pvr_dr_commit(modh_p);
  // pvr_dr_finish();
  // pvr_list_finish();

  pvr_scene_finish();
}
