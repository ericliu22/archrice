#include <stdio.h>
#include <string.h>
#include "readCommand.h"


//hello
int main(int argc, char** argv) {
	FILE* fp;
	char buffer[1000];
	char secondaryBuffer[1000];
	if (argc < 1) {
		printf("Error not enough arguments");
		return 0;
	}
	if (strcmp(argv[1], "volume") == 0) {
		fp = popen("pactl get-default-sink", "r");
		popenError(fp);
		while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		}
		pclose(fp);
		if ('b' == buffer[0]) {
			printf("");
			return 0;
		}

		int volume;
		readCommand(fp,"pactl get-sink-volume @DEFAULT_SINK@ | grep -o '..[0-9]%' | grep -o -m 1 '..[0-9]'",buffer);
		sscanf(buffer, "%d", &volume);

		if (volume == 0) {
			printf("\n");
		}
		else if (volume > 0 && volume < 50) {
			printf("\n");
		}
		else if (volume >= 50) {
			printf("\n");
		}
		return 0;
	}

	if (strcmp(argv[1], "mic") == 0) {
		readCommand(fp,"pactl get-source-mute @DEFAULT_SOURCE@",buffer);
		char secondaryBuffer[10];
		sscanf(buffer, "Mute: %s", secondaryBuffer);
		if (strcmp("yes",secondaryBuffer) == 0) {
			printf("\n");
		} else {
			printf("\n");
		}
		pclose(fp);
		return 0;
	}

	if (strcmp(argv[1], "brightness") == 0) {
		printf("\n");
		return 0;
	}

	if (strcmp(argv[1], "battery") == 0) {
		fp = popen("upower -i `upower -e | grep BAT` | grep state","r");
		popenError(fp);
		while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		}
		pclose(fp);
		char secondaryBuffer[50];
		sscanf(buffer, "	state: %s", secondaryBuffer);
		if (strcmp("charging",secondaryBuffer) == 0 || strcmp("fully-charged",secondaryBuffer) == 0) {
			printf("\n");
			return 0;
		}
		readCommand(fp,"upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep percentage | grep -o '..[(0-9)]%'",buffer);
		int battery;
		sscanf(buffer, "%d%%", &battery);

		if (battery < 30) {
			printf("\n");
		} else if (battery < 60) {
			printf("\n");
		} else if (battery < 80) {
			printf("\n");
		} else {
			printf("\n");
		}
		return 0;
	}

	if (strcmp(argv[1], "network") == 0) {
		fp = popen("nmcli -f NAME c show --active", "r");
		char secondaryBuffer[50];
		popenError(fp);
		for (int i=0;i<2;i++) {
			fgets(buffer, sizeof(buffer), fp);
		}
		sscanf(buffer, "%s", secondaryBuffer);
		if (strcmp("lo",secondaryBuffer) == 0 || strcmp("docker0",secondaryBuffer) == 0) {
			printf(" \n");
		} else {
			printf(" \n");
		}
		pclose(fp);
		return 0;
	}
}
