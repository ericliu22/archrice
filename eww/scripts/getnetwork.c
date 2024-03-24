#include <string.h>
#include <stdio.h>
#include "readCommand.h"


int main() {
	FILE* fp;
	char buffer[1000];
	fp = popen("nmcli -g NAME c show --active", "r");
	char secondaryBuffer[50];
	popenError(fp);
	fgets(buffer, sizeof(buffer), fp);
	sscanf(buffer, "%[^\t\n]", secondaryBuffer);
	if (strcmp("lo", secondaryBuffer) == 0 || strcmp("docker0", secondaryBuffer) == 0) {
		printf("Disconnected\n");
	} else {
		printf("%s\n", secondaryBuffer);
	}
	pclose(fp);
	return 0;
}
