#include <stdio.h>
#include <string.h>
#include <math.h>
#include "readCommand.h"

int main(int argc,char** argv) {
	char buffer[1000];
	FILE *fp;

	if (argc < 1) {
		printf("\nError not enough arguments\n");
		return 1;
	}
	if (strcmp("brightness",argv[1]) == 0) {
		double brightnessValue;
		int maxBrightness = 852;
		readCommand(fp,"brightnessctl get",buffer);
		sscanf(buffer, "%lf", &brightnessValue);
		brightnessValue = brightnessValue / maxBrightness * 100;
		int output = (int) round(brightnessValue);
		printf("BRIGHTNESS: %d\n",output);
		return 0;
	}

	if (strcmp("volume",argv[1]) == 0) {
		char secondaryBuffer[200];
		readCommand(fp,"pactl get-sink-mute @DEFAULT_SINK@",buffer);
		sscanf(buffer, "Mute: %s", secondaryBuffer);
		if (strcmp("yes", secondaryBuffer) == 0) {
			printf("0");
			return 0;
		}
		int whatever;
		int volume;
		readCommand(fp,"pactl get-sink-volume @DEFAULT_SINK@",buffer);
		sscanf(buffer, "Volume: front-left: %d / %d%% %s ", &whatever, &volume, secondaryBuffer);
		//Change this to just "%d"
		printf("OUTPUT VOLUME: %d",volume);
		return 0;
	}

	if (strcmp("mic",argv[1]) == 0) {
		char secondaryBuffer[200];
		readCommand(fp,"pactl get-source-mute @DEFAULT_SOURCE@",buffer);
		sscanf(buffer, "Mute: %s", secondaryBuffer);
		if (strcmp("yes", secondaryBuffer) == 0) {
			printf("0");
			return 0;
		}
		int whatever;
		int volume;
		readCommand(fp,"pactl get-source-volume @DEFAULT_SOURCE@",buffer);
		sscanf(buffer, "Volume: front-left: %d / %d%% %s ", &whatever, &volume, secondaryBuffer);
		pclose(fp);
		//Change this to just "%d"
		printf("INPUT VOLUME: %d",volume);
		return 0;
	}
}
