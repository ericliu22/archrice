#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "readCommand.h"

int toggle(char* window) {
	FILE* fp;
	char buffer[1000];
	char secondaryBuffer[1000];
	char command[1000];
	char alt[1000];
	int isOpen = 0;

	fp = popen("eww active-windows | awk '{print $2}'", "r");
	popenError(fp);
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		sscanf(buffer, "%s", secondaryBuffer);
		if (strcmp(window,secondaryBuffer) == 0) {
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
	return 0;
}
