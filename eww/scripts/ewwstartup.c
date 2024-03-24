#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ewwtoggle.h"

int main(int argc, char** argv) {
	FILE* fp;
	char buffer[100];
	int monitors;

	if (argc != 2) {
		fprintf(stderr,"Usage:\n	ewwstartup <window>\n");
		fprintf(stderr, "Avaliable windows:\n	bar, media, desktop, volumehover, volumewindow");
		exit(EXIT_FAILURE);
	}
	readCommand(fp,"hyprctl -j monitors | jq length",buffer);
	sscanf(buffer, "%d", &monitors);

	if (strcmp(argv[1], "bar") == 0) {
		if (monitors > 1) {
			system("eww open bar");
			system("eww open baralt");
		} else {
			system("eww open baralt");
		}
		return 0;
	}

	if (strcmp(argv[1], "media") == 0) {
		if (monitors > 1) {
			toggle("mediawindow");
			toggle("mediawindowalt");
		} else {
			toggle("mediawindowalt");
		}
		return 0;
	}

	if (strcmp(argv[1], "desktop") == 0) {
		if (monitors > 1) {
			toggle("desktop");
			toggle("desktopalt");
		} else {
			toggle("desktopalt");
		}
		return 0;
	}

	if (strcmp(argv[1], "volume") == 0) {
		if (monitors > 1) {
			toggle("volumewindow");
			toggle("volumewindowalt");
		} else {
			toggle("volumewindowalt");
		}
		return 0;
	}

	if (strcmp(argv[1], "volumehover") == 0) {
		if (monitors > 1) {
			toggle("volumehover");
			toggle("volumehoveralt");
		} else {
			toggle("volumehoveralt");
		}
		return 0;
	}
}
