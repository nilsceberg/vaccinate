#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct metrics {
	bool ok;
	int lines;
	int characters;
} metrics_t;

metrics_t process_file(char* filename) {
	metrics_t metrics;
	memset(&metrics, 0, sizeof(metrics));

	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		perror("couldn't open file");
		return metrics;
	}

	char c;
	while (fread(&c, 1, 1, f) != 0) {
		if (c == '\n') metrics.lines++;
		else metrics.characters++;
	}
	metrics.lines++;

	metrics.ok = true;

	fclose(f);
	return metrics;
}

void print_metrics(metrics_t* metrics) {
	printf("characters: %d\n", metrics->characters);
	printf("lines: %d\n", metrics->lines);
	printf("mean c/l: %f\n", metrics->characters / (double)metrics->lines);
}

int main(int argv, char** args) {
	for (int i=1; i<argv; ++i) {
		printf("-- %s --\n", args[i]);

		metrics_t metrics = process_file(args[i]);
		print_metrics(&metrics);
		printf("\n");
	}
}
