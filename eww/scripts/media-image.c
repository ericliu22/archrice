#include <stdlib.h>
#include <stdio.h>
#include "readCommand.h"

int main() {
	FILE* fp;
	char buffer[1000];
	char imageUrl[1000];
	char command[1000];


	fp = popen("playerctl metadata mpris:artUrl", "r");
	popenError(fp);
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
	}
	sscanf(buffer,"%[^\t\n]", imageUrl);
	pclose(fp);
	sprintf(command, "curl %s -so /home/ericliu/.config/eww/scripts/media-image.jpg", imageUrl);
	system(command);
	printf("scripts/media-image.jpg");
}
