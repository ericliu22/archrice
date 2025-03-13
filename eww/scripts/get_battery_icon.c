#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATUS_PATH   "/sys/class/power_supply/BAT0/status"
#define CAPACITY_PATH "/sys/class/power_supply/BAT0/capacity"

int main() {
	FILE *fp;
	char status[32];
	int capacity;

	// Read the battery status
	fp = fopen(STATUS_PATH, "r");
	if (fp == NULL) {
		perror("Error opening battery status file");
		return EXIT_FAILURE;
	}
	if (fgets(status, sizeof(status), fp) == NULL) {
		perror("Error reading battery status");
		fclose(fp);
		return EXIT_FAILURE;
	}
	fclose(fp);
	// Remove newline characters
	status[strcspn(status, "\n")] = '\0';

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

	// Print an icon based on the battery state
	if (strcmp(status, "Charging") == 0 || strcmp(status, "Full") == 0) {
		printf("\n"); // Charging or fully-charged icon
		return EXIT_SUCCESS;
	}

	// Choose icon based on the battery percentage
	if (capacity < 30)
		printf("\n");
	else if (capacity < 60)
		printf("\n");
	else if (capacity < 80)
		printf("\n");
	else
		printf("\n");
	return EXIT_SUCCESS;
}
