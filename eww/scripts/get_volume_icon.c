#include <stdio.h>
#include <string.h>
#include <pulse/proplist.h>
#include <pulse/volume.h>
#include "volume_fetcher.h"

static int exit_status = 1;

/* Returns an icon based on the volume percentage */
static const char* icon_volume(double volume) {
    if (volume == 0) {
        return "";
    }
    else if (volume > 0 && volume < 50) {
        return "";
    }
    else {
        return "";
    }
}

/* Callback for the default sink info */
static void icon_sink_info_callback(const pa_sink_info *i, int eol, void *userdata) {
    if (eol > 0)
        return;
    if (i) {
        if (i->mute) {
            printf("󰝟\n");
            exit_status = 0;
        } else {
            pa_volume_t vol = pa_cvolume_avg(&i->volume);
            double volume_percentage = ((double)vol / PA_VOLUME_NORM) * 100.0;
            const char* form_factor = pa_proplist_gets(i->proplist, PA_PROP_DEVICE_FORM_FACTOR);
            const char* icon;
            if (form_factor) {
                if (strcmp(form_factor, "speaker") == 0)
                    icon = icon_volume(volume_percentage);
                else if (strcmp(form_factor, "headphone") == 0)
                    icon = "";
                else
                    icon = icon_volume(volume_percentage);
            } else {
                icon = icon_volume(volume_percentage);
            }
            printf("%s\n", icon);
            exit_status = 0;
        }
    }
}

int main() {
    get_default_sink_info(icon_sink_info_callback, NULL);
    return exit_status;
}
