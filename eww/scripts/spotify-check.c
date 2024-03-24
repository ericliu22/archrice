#include <string.h>
#include <stdio.h>
#include "readCommand.h"

int main(int argc, char** argv) {
	FILE* fp;
	char buffer[1000];
	char output[1000];
	char command[1000];
	if (argc < 1) {
		printf("Not enough arguments");
		return 1;
	}


	sprintf(command, "playerctl -a metadata %s",argv[1]);
	fp = popen(command, "r");
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		printf("BUFFER: %s\n", buffer);
		if (strcmp("No player could handle this command",output) == 0) {
			printf("PRINTING NOTHING\n");
			printf("");
		} else {
			sscanf(buffer, "%[^\n]", output);
			printf("PRINTING OUTPUT\n");
			printf("OUTPUT: %s",output);
		}
	}
	pclose(fp);
	return 0;
}
