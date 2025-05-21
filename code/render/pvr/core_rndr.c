#include <dc/pvr.h>
#include <stdio.h>

void render_frame(void) {
  pvr_dr_state_t dr_state;
  pvr_vertex_pcm_t *vert_p;
  pvr_poly_cxt_t cxt;
  pvr_poly_mod_hdr_t mod_poly_hdr;

  pvr_wait_ready();
  pvr_scene_begin();
  pvr_list_begin(PVR_LIST_TR_POLY);
  pvr_poly_cxt_col_mod(&cxt, PVR_LIST_TR_POLY);
  pvr_poly_mod_compile(&mod_poly_hdr, &cxt);

  pvr_dr_init(&dr_state);
  vert_p = (pvr_vertex_pcm_t *)pvr_dr_target(dr_state);
  *((pvr_poly_mod_hdr_t *)vert_p) = mod_poly_hdr;
  for (int i = 0; i < 4; i++) {
    pvr_dr_commit(vert_p);
    vert_p = (pvr_vertex_pcm_t *)pvr_dr_target(dr_state);

    float x = i < 2 ? 100.0f : 640.0f - 100.0f;
    float y = i % 2 == 0 ? 480.0f - 100.0f : 100.0f;

    vert_p->flags = PVR_CMD_VERTEX;
    vert_p->x = x;
    vert_p->y = y;
    vert_p->z = 0.1f;
    vert_p->argb0 = 0x7fFFFFFF;
    vert_p->argb1 = 0xffffff00;
  }

  vert_p->flags = PVR_CMD_VERTEX_EOL;
  pvr_dr_commit(vert_p);
  pvr_dr_finish();
  pvr_list_finish();

  pvr_list_begin(PVR_LIST_TR_MOD);
  pvr_dr_init(&dr_state);
  pvr_mod_hdr_t mod_hdr;
  pvr_mod_compile(&mod_hdr, PVR_LIST_TR_MOD, PVR_MODIFIER_INCLUDE_LAST_POLY,
                  PVR_CULLING_NONE);
  vert_p = (pvr_vertex_pcm_t *)pvr_dr_target(dr_state);
  *((pvr_mod_hdr_t *)vert_p) = mod_hdr;
  pvr_dr_commit(vert_p);
  pvr_modifier_vol_t *modh_p = (pvr_modifier_vol_t *)pvr_dr_target(dr_state);
  modh_p->flags = PVR_CMD_VERTEX_EOL;
  modh_p->ax = 200;
  modh_p->ay = 480 - 200;
  modh_p->az = 1.0f;
  modh_p->bx = 200;
  modh_p->by = 200;
  modh_p->bz = 1.0f;
  modh_p->cx = 640 - 200;
  pvr_dr_commit(modh_p);
  modh_p = (pvr_modifier_vol_t *)pvr_dr_target(dr_state);
  pvr_modifier_vol_t *modh_p2 = (pvr_modifier_vol_t *)((int)modh_p - 32);

  modh_p2->cy = 200;
  modh_p2->cz = 1.0f;
  pvr_dr_commit(modh_p);



  modh_p = (pvr_modifier_vol_t *)pvr_dr_target(dr_state);
  modh_p->flags = PVR_CMD_VERTEX_EOL;
  modh_p->ax = 200;
  modh_p->ay = 480 - 200;
  modh_p->az = 1.0f;
  modh_p->bx = 640 - 200;
  modh_p->by = 200;
  modh_p->bz = 1.0f;
  modh_p->cx = 640 - 200;
  pvr_dr_commit(modh_p);
  modh_p = (pvr_modifier_vol_t *)pvr_dr_target(dr_state);
  modh_p2 = (pvr_modifier_vol_t *)((int)modh_p - 32);

  modh_p2->cy = 480 - 200;
  modh_p2->cz = 1.0f;
  pvr_dr_commit(modh_p);

  pvr_dr_finish();

  // pvr_list_finish();

  pvr_scene_finish();
}
