#ifndef SRC_FUNCIONES_SNAKE_H_
#define SRC_FUNCIONES_SNAKE_H_

#define ALTO 40
#define ANCHO 64

void inicio(int *tam, char campo[ALTO][ANCHO], int *nivel, int * puntaje_record, FILE * archivo, BITMAP *pantalla);
void loop(char campo[ALTO][ANCHO], int tam, int puntaje_record, FILE * archivo, int * nivel, BITMAP * pantalla);

#endif
