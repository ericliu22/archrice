#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wayland-client.h>
#include <wayland-client-protocol.h>

static void registry_handler(void *data, struct wl_registry *registry,
                             uint32_t name, const char *interface, uint32_t version) {
    if (strcmp(interface, "wl_output") == 0) {
        int *monitor_count = (int *)data;
        (*monitor_count)++;
        // Optionally, you can bind the output here:
        // struct wl_output *output = wl_registry_bind(registry, name, &wl_output_interface, version);
    }
}

static void registry_remover(void *data, struct wl_registry *registry, uint32_t name) {
    // This function is called when a global is removed. In many cases you can leave it empty.
}


int main(int argc, char** argv) {

	struct wl_display *display = wl_display_connect(NULL);
	if (!display) {
	fprintf(stderr, "Failed to connect to Wayland display\n");
	return EXIT_FAILURE;
	}

	struct wl_registry *registry = wl_display_get_registry(display);
	int monitor_count = 0;

	static const struct wl_registry_listener registry_listener = {
		.global = registry_handler,
		.global_remove = registry_remover,
	};

	wl_registry_add_listener(registry, &registry_listener, &monitor_count);

	// Perform a roundtrip to process the registry events
	wl_display_roundtrip(display);

	// Clean up
	wl_registry_destroy(registry);
	wl_display_disconnect(display);

	const char* input = argv[1];
	FILE* fp;
	char window[128];
	char buffer[128];
	char second_buffer[128];
	char command[128];
	int isOpen = 0;

	if (argc != 2) {
		fprintf(stderr, "Usage:\n	eww_toggle <window>\n");
		return EXIT_FAILURE;
	}

	if (monitor_count == 1) {
		sprintf(window, "%salt", input);
	} else {
		sprintf(window, "%s", input);
	}

	fp = popen("eww active-windows | awk '{print $2}'", "r");
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		sscanf(buffer, "%s", second_buffer);
		if (strcmp(window, second_buffer) == 0) {
			isOpen = 1;
			break;
		}
	}
	pclose(fp);

	if (isOpen) {
		sprintf(command, "eww close %s", window);
	} else {
		sprintf(command, "eww open %s", window);
	}
	system(command);
	return EXIT_SUCCESS;
}
