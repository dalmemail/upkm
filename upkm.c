/*
 * Copyright (C) 2016 DalmeGNU [dalmemail@amaya.tk]
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
/* fcl.h */
#include "../fcl.h"

/* upkm v0.1 */

/* Poketty Version 1.3 */
#define VERSION "1.3"

int check_pkm(char *input)
{
	int result = 0;
	char pkm[8];
	get_value_string(input, "pkm", pkm);
	if ((strcmp(pkm, VERSION)) != 0) {
		result++;
	}
	return result;
}

void make_pkm(char *input, char *output)
{
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		printf("Uso: %s input.pkm output.pkm\n", argv[0]);
	}
	else {
		if ((check_pkm(argv[1])) == 0) {
			printf("Tu archivo ya es compatible con Poketty %s y no debe ser convertido\n", VERSION);
		}
		else {
			make_pkm(argv[1], argv[2]);
		}
	}
	return 0;
}
