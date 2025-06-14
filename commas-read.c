/*
	Copyright 2025 Eric Hernandez

	This file is part of commas.

	commas is free software: you can redistribute it and/or modify it under the terms of the GNU General
	Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

	commas is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with commas. If not, see <https://www.gnu.org/licenses/>.
*/

#include "commas-data.h"
#include "commas-read.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct commas_column **commas_load(const char *csv_path) {
	struct commas_column **loaded_data = NULL;
	FILE *csv_file = NULL;

	char *buffer = NULL;
	size_t buffer_size = 255;

	/*
		Titles are counted with commas, but the last title ends with a newline.
		Therefore, the last title must be automatically accounted for to avoid
		another logical comparison for the newline character.
	*/
	int title_count = 1;
	int title_row_length = 0;

	csv_file = fopen(csv_path, "r");
	if (csv_file == NULL) {
		return NULL;
	}

	/*
		The number of titles will be counted first. This
		is done to allocate the approriate size of memory
		at once to avoid memory fragmentation when reallocating.
	*/
	if (getline(&buffer, &buffer_size, csv_file) == -1) {
		return NULL;
	}

	if (buffer_size == 0) {
		return NULL;
	}

	title_row_length = strlen(buffer);
	for (int i = 0; i < title_row_length; i++) {
		if (buffer[i] == ',') {
			title_count++;
		}
	}

	loaded_data = malloc(sizeof(struct commas_column *) * title_count);

	for (int i = 0; i < title_count; i++) {
		loaded_data[i] = malloc(sizeof(struct commas_column));
	}

	/* Now, the titles will be assigned in commas_column structures. */
	rewind(csv_file);
	getline(&buffer, &buffer_size, csv_file);
	
	loaded_data[0]->name = strdup(strtok(buffer, ","));
	for (int i = 1; i < title_count; i++) {
		loaded_data[i]->name = strdup(strtok(NULL, ","));
	}

	/* Finally, the remaining CSV data will be appended into their approriate rows. */
	while (getline(&buffer, &buffer_size, csv_file) != -1) {
		char *data = strdup(strtok(buffer, ","));
		if (data != NULL) {
			commas_row_add(&loaded_data[0], 1, data);
		}

		for (int i = 1; i < title_count; i++) {
			data = strdup(strtok(NULL, ","));
			if (data != NULL) {
				commas_row_add(&loaded_data[i], loaded_data[i]->total + 1, data);
			}
		}
	}

	free(buffer);
	fclose(csv_file);
	return loaded_data;
}
