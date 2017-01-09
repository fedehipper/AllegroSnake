#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "funciones_snake.h"

int main(void) {
	int tam;
	char campo[40][64];
	int puntaje_record;
	allegro_init();

	BITMAP * pantalla = create_bitmap(640, 400);
	clear_bitmap(pantalla);

	FILE * archivo;
	archivo = fopen("puntaje_record.txt", "r");

	int nivel = 0;
	inicio(&tam, campo, &nivel, &puntaje_record, archivo, pantalla);
	loop(campo, tam, puntaje_record, archivo, &nivel, pantalla);

	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
