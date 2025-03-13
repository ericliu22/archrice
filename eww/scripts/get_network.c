#include <stdio.h>
#include <string.h>
#include <libnm/NetworkManager.h>

int main() {
	GError* error = NULL;
	NMClient* client;

	/* Create a new NMClient instance */
	client = nm_client_new(NULL, &error);
	if (!client) {
		fprintf(stderr, "Error creating NMClient: %s\n", error->message);
		g_error_free(error);
		return 1;
	}

	/* Retrieve active connections */
	const GPtrArray* active_conns = nm_client_get_active_connections(client);
	gboolean valid_connection_found = FALSE;

	if (!(active_conns) || active_conns->len <= 0) {
		printf("Disconnected\n");
		g_object_unref(client);
		return 0;
	}
	for (guint i = 0; i < active_conns->len; i++) {
		NMActiveConnection* active_conn = g_ptr_array_index(active_conns, i);
		const char* conn_name = nm_active_connection_get_id(active_conn);
		const char* type = nm_active_connection_get_connection_type(active_conn);
		/* Ignore loopback and docker connections */
		if (strcmp(type, "bridge") == 0 || strcmp(type, "loopback") == 0) {
			continue;
		}
		if (conn_name) {
			printf("%s\n", conn_name);
			valid_connection_found = TRUE;
			break;
		}
	}

	if (!valid_connection_found) {
		printf("Disconnected\n");
	}

	g_object_unref(client);
	return 0;
}
