#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATUS_PATH   "/sys/class/power_supply/BAT0/status"
#define CAPACITY_PATH "/sys/class/power_supply/BAT0/capacity"

int main() {
	FILE *fp;
	int capacity;
	// Read the battery capacity
	fp = fopen(CAPACITY_PATH, "r");
	if (fp == NULL) {
		perror("Error opening battery capacity file");
		return EXIT_FAILURE;
	}
	if (fscanf(fp, "%d", &capacity) != 1) {
		perror("Error reading battery capacity");
		fclose(fp);
		return EXIT_FAILURE;
	}
	fclose(fp);

	printf("%d%%\n", capacity);
	return EXIT_SUCCESS;
}
