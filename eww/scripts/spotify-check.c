#include <string.h>
#include <stdio.h>
#include "readCommand.h"

void parseString(FILE* fp, char* input) {
	char buffer[1000];
	char output[1000];
	char command[1000];
	char empty[1000];

	sprintf(command, "playerctl -p spotify metadata | grep %s\n",input);
	//For some reason we can't use readCommand() here 
	//No clue why
	fp = popen(command, "r");
	popenError(fp);
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
	}
	sscanf(buffer, "spotify	%s	%[^\t]", empty, output);
	printf("%s",output);
}

int main(int argc, char** argv) {
	FILE* fp;
	char buffer[1000];
	char check[1000];
	if (argc < 1) {
		printf("Not enough arguments");
		return 1;
	}

	readCommand(fp,"pgrep -x spotify",buffer);
	sscanf(buffer,"%s",check);
	if (strcmp(check,"") != 0) {
		parseString(fp, argv[1]);
		return 0;
	}

	printf("");
	return 1;
}
