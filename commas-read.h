/*
	Copyright 2025 Eric Hernandez

	This file is part of commas.

	commas is free software: you can redistribute it and/or modify it under the terms of the GNU General
	Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

	commas is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with commas. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef COM_READ_H
#define COM_READ_H

/*
	Reads data from a CSV file into commas columns and rows
	data structures. This data must be freed when done using
	commas_unload(). Returns a heap-allocated array.
*/
struct commas_column **commas_load(const char *csv_path);

/*
	Load the rows of a column from a file as a column struct.
	The returned struct must be freed using commas_column_free().
*/
struct commas_column *commas_column_get(const char *csv_path, const char *column_name);

#endif /* COMMAS_READ_H */
