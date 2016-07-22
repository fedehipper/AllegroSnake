#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "funciones_snake.h"

int main(void) {

	int tam = 0;
	char campo[39][63];

	inicio(&tam, campo);
	loop(campo, tam);


	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
