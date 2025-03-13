#include <glib.h>
#include <gio/gio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MPRIS_BUS_NAME "org.mpris.MediaPlayer2.spotify"  /* Change as needed */
#define OUTPUT_FILENAME "/home/ericliu/.config/eww/scripts/media-image.jpg"

int fetch(const gchar* artUrl) {
	/* Use libcurl to download the image */
	CURL *curl_handle;
	FILE *fp;

	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();
	if (!curl_handle) {
		fprintf(stderr, "Failed to initialize curl.\n");
		curl_global_cleanup();
		return 1;
	}
	fp = fopen(OUTPUT_FILENAME, "wb");
	if (!fp) {
		perror("fopen");
		curl_easy_cleanup(curl_handle);
		curl_global_cleanup();
		return 1;
	}

	curl_easy_setopt(curl_handle, CURLOPT_URL, artUrl);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);

	CURLcode res = curl_easy_perform(curl_handle);
	if(res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	}

	fclose(fp);
	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();

	return 0;
}

int main() {
	GError *error = NULL;
	GDBusConnection *connection;
	GDBusProxy *proxy;
	GVariant *result, *metadata_variant;
	const gchar *artUrl = NULL;

	/* Connect to the session bus */
	connection = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);
	if (!connection) {
		g_printerr("Failed to connect to session bus: %s\n", error->message);
		g_error_free(error);
		return 1;
	}

	/* Create a proxy for the MPRIS player's properties.
	Change "org.mpris.MediaPlayer2.player" to your player's bus name if needed.
	Most players will have a bus name like "org.mpris.MediaPlayer2.spotify" or "org.mpris.MediaPlayer2.vlc". */
	proxy = g_dbus_proxy_new_sync(
		connection,
		G_DBUS_PROXY_FLAGS_NONE,
		NULL,
		MPRIS_BUS_NAME,
		"/org/mpris/MediaPlayer2",
		"org.freedesktop.DBus.Properties",
		NULL,
		&error
	);

	if (!proxy) {
		g_printerr("Failed to create proxy: %s\n", error->message);
		g_error_free(error);
		g_object_unref(connection);
		return 1;
	}

	/* Call the Get method for the Metadata property on the org.mpris.MediaPlayer2.Player interface */
	result = g_dbus_proxy_call_sync(
		proxy,
		"Get",
		g_variant_new("(ss)", "org.mpris.MediaPlayer2.Player", "Metadata"),
		G_DBUS_CALL_FLAGS_NONE,
		-1,
		NULL,
		&error
	);

	if (!result) {
		g_printerr("Failed to get metadata: %s\n", error->message);
		g_error_free(error);
		g_object_unref(proxy);
		g_object_unref(connection);
		return 1;
	}

	/* Unpack the result. It is a variant containing the metadata dictionary */
	g_variant_get(result, "(v)", &metadata_variant);

	/* The metadata is a dictionary. Look for the "mpris:artUrl" entry */
	GVariant *artUrlVariant = g_variant_lookup_value(metadata_variant, "mpris:artUrl", G_VARIANT_TYPE_STRING);
	if (!artUrlVariant) {
		g_printerr("No art URL found in metadata.\n");
		g_variant_unref(metadata_variant);
		g_variant_unref(result);
		g_object_unref(proxy);
		g_object_unref(connection);
		return 1;
	}
	artUrl = g_variant_get_string(artUrlVariant, NULL);
	g_variant_unref(artUrlVariant);


	if (!artUrl) {
		g_printerr("No art URL found in metadata.\n");
		g_variant_unref(metadata_variant);
		g_variant_unref(result);
		g_object_unref(proxy);
		g_object_unref(connection);
		return 1;
	}

	/* Clean up */
	g_variant_unref(metadata_variant);
	g_variant_unref(result);
	g_object_unref(proxy);
	g_object_unref(connection);

	if (fetch(artUrl) != 0) {
		g_print("Failed to fetch image\n");
		return 1;
	}

	g_print("%s\n", OUTPUT_FILENAME);

	return 0;
}
