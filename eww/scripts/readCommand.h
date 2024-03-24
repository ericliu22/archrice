#include <stdlib.h>
#include <stdio.h>

void popenError(FILE* fp) {
	if (fp == NULL) {
		fprintf(stderr,"Error running popen\n");
		exit(EXIT_FAILURE);
	}
}

void readCommand(FILE* fp, char* command, char* buffer) {
	fp = popen(command, "r");
	popenError(fp);
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
	}
	pclose(fp);
}
