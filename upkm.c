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
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
/* fcl.h */
#include "../fcl.h"

/* upkm v0.3.1 */

/* Poketty Version 1.3 */
#define VERSION "1.3"

char pokemon_data[24][25];

char to_find[24][25] = {"nombre", "pv", "ataque1", "ataque2", "ataque3", "ataque4",
			"pd1_max", "pd2_max", "pd3_max", "pd4_max", "pd1_min", "pd2_min",
			"pd3_min", "pd4_min", "ataque1_estado", "ataque2_estado",
			"ataque3_estado", "ataque4_estado", "pp1", "pp2", "pp3", "pp4",
			"pociones", "antidotos"};

char new_data[24][25] = {"pikachu", "100", "bola trueno", "placaje", "relampago", "onda trueno",
			"pd1_max", "pd2_max", "pd3_max", "pd4_max", "pd1_min", "pd2_min",
			"pd3_min", "pd4_min", "ataque1_estado", "ataque2_estado",
			"ataque3_estado", "ataque4_estado", "pp1", "pp2", "pp3", "pp4",
			"4", "5"};

char estados_pokemon[3][25] = {"paralizado", "aturdido", "normal"};

int value_string_result[24];

void make_pokemon_status(int start, int lonng)
{
	for (int i = start; i < (lonng+start); i++) {
		int num = rand() % 3;
		strcpy(new_data[i], estados_pokemon[num]);
	}
}

void make_pokemon_pd(int start, int lonng)
{
	for (int i = start; i < (lonng+start); i++) {
		int num = rand() % 50;
		sprintf(new_data[i], "%d", num);
		int num1 = rand() % num;
		sprintf(new_data[i+lonng], "%d", num1);
	}
}

void make_pokemon_pp(int start, int lonng)
{
	for (int i = start; i < (lonng+start); i++) {
		int num = rand() % 40;
		sprintf(new_data[i], "%d", num);
	}
}

void make_pkm(char *input, char *output)
{
	srand(time(NULL));
	make_pokemon_pd(6, 4);
	make_pokemon_pp(18, 4);
	make_pokemon_status(14, 4);
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
				strcpy(pokemon_data[i], new_data[i]);
				printf("Creando campo '%s': OK\n", to_find[i]);
			}
			sprintf(buffer, "%s=%s\n", to_find[i], pokemon_data[i]);
			write(fd, buffer, strlen(buffer));
		}
		close(fd);
	}
}

int upkm(char *input, char *output)
{
	int result = 0;
	char pkm[64];
	if ((get_value_string(input, "pkm", pkm)) == 0 && (strcmp(pkm, VERSION)) == 0) {
		printf("Tu archivo ya es compatible con Poketty %s y no debe ser convertido\n", VERSION);
	}
	else {
		if ((get_value_string(input, "nombre", pkm)) == 0) {
			make_pkm(input, output);
		}
		else {
			printf("El archivo '%s' es incompatible con Poketty 1.0\n", input);
			result--;
		}
	}
	return result;
}
