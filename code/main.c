#include <dc/video.h>
#include <drxlax/game/core.h>
#include <kos.h>


#ifdef DCPROF
#include "../profilers/dcprof/profiler.h"
#endif

KOS_INIT_FLAGS(INIT_DEFAULT);

#ifdef DEBUG
#include <arch/gdb.h>
#endif

#include <dc/pvr.h>
#include <drxlax/game/core.h>

#ifdef DEBUG
#include <dc/perf_monitor.h>
#endif

static pvr_init_params_t pvr_params = {
    {PVR_BINSIZE_16, PVR_BINSIZE_16, PVR_BINSIZE_16, PVR_BINSIZE_16,
     PVR_BINSIZE_0},
    1024 * 1024, // Vertex buffer size
    0,           // No DMA
    0,           // Set horisontal FSAA
    0,           // Translucent Autosort enabled.
    1,           // Extra OPBs
    0,           // No extra PTs
};


int main(__unused int argc, __unused char **argv) {
#ifdef DEBUG
  gdb_init();
#endif
  pvr_init(&pvr_params);
  vid_set_mode(DM_640x480, PM_RGB888P);
  pvr_set_bg_color(0.0, 0.0, 64.0f / 255.0f);
  core_loop();
  pvr_shutdown();
  arch_exit();
}
