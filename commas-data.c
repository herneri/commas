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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void commas_row_add(struct commas_column **column, char *data, const int index) {
	struct commas_rows_list *new_node = NULL;
	struct commas_rows_list *temp = NULL;

	if (index > ((*column)->total + 1) || index <= 0) {
		return;
	}

	new_node = (struct commas_rows_list *) malloc(sizeof(struct commas_rows_list));
	if (new_node == NULL) {
		return;
	}

	(*column)->total++;
	new_node->data = data;
	new_node->next = NULL;
	new_node->previous = NULL;

	if ((*column)->total == 1) {
		(*column)->head = new_node;
		(*column)->tail = new_node;
		return;
	} else if (index == 1) {
		(*column)->head->previous = new_node;
		new_node->next = (*column)->head;
		(*column)->head = new_node;
		return;
	}

	if (index == (*column)->total) {
		(*column)->tail->next = new_node;
		new_node->previous = (*column)->tail;
		(*column)->tail = new_node;
		return;
	}

	if (index < ((*column)->total / 2)) {
		temp = (*column)->head;
		for (int i = 1; i < index; i++) {
			temp = temp->next;
		}

		temp->next = new_node;
		new_node->previous = temp;
		return;
	}

	temp = (*column)->tail;
	for (int i = (*column)->total; i > index; i--) {
		temp = temp->previous;
	}

	new_node->next = temp->next;
	new_node->previous = temp;
	temp->next->previous = new_node;
	temp->next = new_node;
	return;
}

struct commas_rows_list *commas_row_get(struct commas_column *column, const int index) {
	struct commas_rows_list *result = column->head;

	if (index <= 0 || index > column->total || column->head == NULL) {
		return NULL;
	}

	if (index == 1) {
		return result;
	} else if (index == column->total) {
		return column->tail;
	}

	if (index < (column->total / 2)) {
		for (int i = 1; i < index; i++) {
			result = result->next;
		}

		return result;
	}

	result = column->tail;
	for (int i = column->total; i > index; i--) {
		result = result->previous;
	}

	return result;
}
