#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "funciones_snake.h"

int main(void) {
	int tam;
	char campo[40][64];

	FILE * archivo;
	int puntaje_record;
	archivo = fopen("puntaje_record.txt", "r");

	if(archivo != NULL) {
		fscanf(archivo, "%d", &puntaje_record);
		fclose(archivo);
	}
	else
		puntaje_record = 0;

	int nivel = 0;
	inicio(&tam, campo, &nivel);
	loop(campo, tam, puntaje_record, archivo, &nivel);

	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
