#include "volume_fetcher.h"
#include <pulse/operation.h>
#include <stdio.h>
#include <pulse/pulseaudio.h>

/* Global variables used by the library functions */
enum fetch_t {
	SINK,
	SOURCE
};
static pa_mainloop* mainloop = NULL;
static pa_context* context = NULL;
static sink_info_callback_t sink_callback = NULL;
static source_info_callback_t source_callback = NULL;
static void* global_userdata = NULL;
static enum fetch_t fetch_type; 

/* Internal callback which wraps the user-supplied callback */
static void internal_sink_info_callback(pa_context* c, const pa_sink_info* i, int eol, void *userdata) {
	if (sink_callback) {
		sink_callback(i, eol, global_userdata);
	}
	if (eol > 0) {
		pa_mainloop_quit(mainloop, 0);
	}
}

/* Internal callback which wraps the user-supplied callback */
static void internal_source_info_callback(pa_context* c, const pa_source_info* i, int eol, void *userdata) {
	if (source_callback) {
		source_callback(i, eol, global_userdata);
	}
	if (eol > 0) {
		pa_mainloop_quit(mainloop, 0);
	}
}

/* Context state callback; once ready, fetch the default sink info */
static void context_state_callback(pa_context *c, void *userdata) {
	pa_context_state_t state = pa_context_get_state(c);
	switch (state) {
		case PA_CONTEXT_READY: {
			pa_operation* op;
			if (fetch_type == SINK)
				op = pa_context_get_sink_info_by_name(c, "@DEFAULT_SINK@", internal_sink_info_callback, NULL);
			if (fetch_type == SOURCE)
				op = pa_context_get_source_info_by_name(c, "@DEFAULT_SINK@", internal_source_info_callback, NULL);
			if (op)
				pa_operation_unref(op);
			break;
		}
		case PA_CONTEXT_FAILED:
		case PA_CONTEXT_TERMINATED:
			pa_mainloop_quit(mainloop, 1);
			break;
		default:
			break;
	}
}

int get_default_sink_info(sink_info_callback_t callback, void* userdata) {
    sink_callback = callback;
    global_userdata = userdata;
    fetch_type = SINK;
    int ret;

    mainloop = pa_mainloop_new();
    pa_mainloop_api *mainloop_api = pa_mainloop_get_api(mainloop);

    context = pa_context_new(mainloop_api, "Volume Fetcher Library");
    pa_context_set_state_callback(context, context_state_callback, NULL);

    if (pa_context_connect(context, NULL, PA_CONTEXT_NOFLAGS, NULL) < 0) {
        fprintf(stderr, "pa_context_connect() failed\n");
        return -1;
    }

    pa_mainloop_run(mainloop, &ret);

    pa_context_disconnect(context);
    pa_context_unref(context);
    pa_mainloop_free(mainloop);
    return ret;
}

int get_default_source_info(source_info_callback_t callback, void* userdata) {
    source_callback = callback;
    global_userdata = userdata;
    fetch_type = SOURCE;
    int ret;

    mainloop = pa_mainloop_new();
    pa_mainloop_api *mainloop_api = pa_mainloop_get_api(mainloop);

    context = pa_context_new(mainloop_api, "Volume Fetcher Library");
    pa_context_set_state_callback(context, context_state_callback, NULL);

    if (pa_context_connect(context, NULL, PA_CONTEXT_NOFLAGS, NULL) < 0) {
        fprintf(stderr, "pa_context_connect() failed\n");
        return -1;
    }

    pa_mainloop_run(mainloop, &ret);

    pa_context_disconnect(context);
    pa_context_unref(context);
    pa_mainloop_free(mainloop);
    return ret;
}
