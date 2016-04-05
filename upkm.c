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
#include <fcntl.h>
#include <string.h>
/* fcl.h */
#include "../fcl.h"

/* upkm v0.2 */

/* Poketty Version 1.3 */
#define VERSION "1.3"

char pokemon_data[24][25];

char to_find[24][25] = {"nombre", "pv", "ataque1", "ataque2", "ataque3", "ataque4",
			"pd1_max", "pd2_max", "pd3_max", "pd4_max", "pd1_min", "pd2_min",
			"pd3_min", "pd4_min", "ataque1_estado", "ataque2_estado",
			"ataque3_estado", "ataque4_estado", "pp1", "pp2", "pp3", "pp4",
			"pociones", "antidotos"};

int value_string_result[24];

void make_pkm(char *input, char *output)
{
	creat(output, 0644);
	int fd;
	if ((fd = open(output, O_WRONLY)) < 0) {
		printf("Error: No se puede abrir %s\n", output);
	}
	else {
		char buffer[40];
		sprintf(buffer, "pkm=%s\n", VERSION);
		write(fd, buffer, strlen(buffer));
		for (int i = 0; i < 24; i++) {
			value_string_result[i] = get_value_string(input, to_find[i], pokemon_data[i]);
			if (value_string_result[i] != 0) {
				//cosas
			}
			sprintf(buffer, "%s=%s\n", to_find[i], pokemon_data[i]);
			write(fd, buffer, strlen(buffer));
		}
		close(fd);
	}
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		printf("Uso: %s input.pkm output.pkm\n", argv[0]);
	}
	else {
		char pkm[8];
		if ((get_value_string(argv[1], "pkm", pkm)) == 0 && (strcmp(pkm, VERSION)) == 0) {
			printf("Tu archivo ya es compatible con Poketty %s y no debe ser convertido\n", VERSION);
		}
		else {
			make_pkm(argv[1], argv[2]);
		}
	}
	return 0;
}
