#include <stdio.h>
#include <pulse/volume.h>
#include "volume_fetcher.h"

static int exit_status = 1;

/* Callback that prints the volume percentage */
static void percentage_sink_info_callback(const pa_sink_info *i, int eol, void *userdata) {
    if (eol > 0)
        return;
    if (i) {
        if (i->mute) {
            printf("Muted\n");
            exit_status = 0;
        } else {
            pa_volume_t vol = pa_cvolume_avg(&i->volume);
            double volume_percentage = ((double)vol / PA_VOLUME_NORM) * 100.0;
            printf("%.0f%%\n", volume_percentage);
            exit_status = 0;
        }
    }
}

int main() {
    get_default_sink_info(percentage_sink_info_callback, NULL);
    return exit_status;
}
