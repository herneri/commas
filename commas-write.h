/*
	Copyright 2025 Eric Hernandez

	This file is part of commas.

	commas is free software: you can redistribute it and/or modify it under the terms of the GNU General
	Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

	commas is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with commas. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef COM_WRITE_H
#define COM_WRITE_H

/*
	Write all CSV data to a file. This DOES NOT free the data, it must be done
	explicitly through commas_unload(). This overwrites the text stored in the
	file at the output_path.
*/
void commas_write_data(char *output_path, struct commas_csv *csv_data);

#endif /* COM_WRITE_H */
