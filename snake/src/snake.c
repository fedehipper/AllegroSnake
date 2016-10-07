#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "funciones_snake.h"

int main(void) {
	int tam;
	char campo[40][64];
	int puntaje_record;

	FILE * archivo;
	archivo = fopen("puntaje_record.txt", "r");

	int nivel = 0;
	inicio(&tam, campo, &nivel, &puntaje_record, archivo);
	loop(campo, tam, puntaje_record, archivo, &nivel);

	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
