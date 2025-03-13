#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void toggle(char* window) {
}

int main(int argc, char** argv) {

	const char* window = argv[1];
	FILE* fp;
	char buffer[128];
	char second_buffer[64];
	char command[128];
	int isOpen = 0;

	if (argc != 2) {
		fprintf(stderr, "Usage:\n	ewwtoggle <window>\n");
		return EXIT_FAILURE;
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
