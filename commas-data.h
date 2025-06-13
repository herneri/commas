/*
	Copyright 2025 Eric Hernandez

	This file is part of commas.

	commas is free software: you can redistribute it and/or modify it under the terms of the GNU General
	Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

	commas is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with commas. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef COM_DATA_H
#define COM_DATA_H

/*
	A double linked list node containing the data of
	a specific row under a specific column.
*/
struct commas_rows_list {
	char *data;
	struct commas_rows_list *previous;
	struct commas_rows_list *next;
};

/*
	A column with pointers to the head
	and tail of its rows list.
*/
struct commas_column {
	char *name;
	struct commas_rows_list *head;
	struct commas_rows_list *tail;
	int total;
};

/* Adds a row at the specified index under a certain column. */
void commas_row_add(struct commas_column **column, const int index, const char *data);

/* Retrieves the row struct stored at the specific index under a column. */
struct commas_rows_list *commas_row_get(struct commas_column *column, const int index);

/* Changes the data at the location specified for a specific column. */
void commas_row_update(struct commas_column **column, const int index, const char *data);

/* Deletes a row from a column, which shifts all rows upwards; therefore, the meaning of the data is changed. */
void commas_row_delete(struct commas_column **column, const int index);

#endif /* COM_DATA_H */
