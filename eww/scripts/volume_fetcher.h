#ifndef VOLUME_FETCHER_H
#define VOLUME_FETCHER_H

#include <pulse/pulseaudio.h>

/* Define a callback type that will be called with the sink info */
typedef void (*sink_info_callback_t)(const pa_sink_info* i, int eol, void* userdata);

/* This function connects to PulseAudio, fetches info for the default sink,
   and invokes the provided callback. It blocks until the info is received. */
int get_default_sink_info(sink_info_callback_t callback, void* userdata);

typedef void (*source_info_callback_t)(const pa_source_info* i, int eol, void* userdata);

int get_default_source_info(source_info_callback_t callback, void* userdata);
#endif
