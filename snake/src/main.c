#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "funciones_snake.h"

int main(void) {

	int tam;
	char campo[40][64];

	inicio(&tam, campo);
	loop(campo, tam);


	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
