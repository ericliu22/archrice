#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "readCommand.h"

int main(int argc, char** argv) {
	FILE* fp;
	char buffer[1000];
	char secondaryBuffer[1000];
	char command[1000];
	char alt[1000];
	int isOpen = 0;

	if (argc != 2) {
		printf("Usage:\n	ewwtoggle <window>\n");
		return 0;
	}

	sprintf(alt,"*%s",argv[1]);
	fp = popen("eww windows", "r");
	popenError(fp);
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		sscanf(buffer, "%[^\t\n]", secondaryBuffer);
		if (strcmp(argv[1],secondaryBuffer) == 0) {
			break;
		}
		if (strcmp(alt,secondaryBuffer) == 0) {
			isOpen = 1;
			break;
		}
	}
	pclose(fp);

	if (isOpen) {
		sprintf(command, "eww close %s", argv[1]);
	} else {
		sprintf(command, "eww open %s", argv[1]);
	}
	system(command);
}
