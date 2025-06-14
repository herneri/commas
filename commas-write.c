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

#include <stdio.h>
#include <stdlib.h>

void commas_write_data(char *output_path, struct commas_csv *csv_data) {
	FILE *output_file = fopen(output_path, "w");

	if (output_file == NULL) {
		return;
	} else if (csv_data == NULL) {
		fclose(output_file);
		return;
	}

	/* Write the column titles to the file first. */
	for (int i = 0; i < csv_data->total - 1; i++) {
		fprintf(output_file, "%s,", csv_data->columns[i]->name);
	}

	fprintf(output_file, "%s\n", csv_data->columns[csv_data->total - 1]->name);

	/* Then, horizontially write the rows. */
	for (int j = 1; j <= csv_data->columns[0]->total; j++) {
		for (int i = 0; i < csv_data->total - 1; i++) {
			struct commas_rows_list *row_entry = commas_row_get(csv_data->columns[i], j);
			fprintf(output_file, "%s,", row_entry->data);
		}
		
		struct commas_rows_list *row_entry = commas_row_get(csv_data->columns[csv_data->total - 1], j);
		fprintf(output_file, "%s\n", row_entry->data);
	}

	fclose(output_file);
	return;
}
