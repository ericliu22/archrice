#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readCommand.h"

int main(int argc, char** argv) {
	FILE* fp;
	char buffer[100];
	int monitors;

	if (argc != 2) {
		printf("Usage:\n	ewwstartup <window>\n");
		printf("Avaliable windows:\n	bar, spotify, desktop");
		return 0;
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

	if (strcmp(argv[1], "spotify") == 0) {
		if (monitors > 1) {
			system("~/scripts/ewwtoggle spotifywindow");
			system("~/scripts/ewwtoggle spotifywindowalt");
		} else {
			system("~/scripts/ewwtoggle spotifywindowalt");
		}
		return 0;
	}

	if (strcmp(argv[1], "desktop") == 0) {
		if (monitors > 1) {
			system("~/scripts/ewwtoggle desktop");
			system("~/scripts/ewwtoggle desktopalt");
		} else {
			system("~/scripts/ewwtoggle desktopalt");
		}
		return 0;
	}

	if (strcmp(argv[1], "volume") == 0) {
		if (monitors > 1) {
			system("~/scripts/ewwtoggle volumewindow");
			system("~/scripts/ewwtoggle volumewindowalt");
		} else {
			system("~/scripts/ewwtoggle volumewindowalt");
		}
		return 0;
	}
}
