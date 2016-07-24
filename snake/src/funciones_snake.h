#ifndef SRC_FUNCIONES_SNAKE_H_
#define SRC_FUNCIONES_SNAKE_H_

#define ALTO 40
#define ANCHO 64

void inicio(int *tam, char campo[ALTO][ANCHO]);
void intro_datos(char campo[ALTO][ANCHO], int tam);
void intro_campo(char campo[ALTO][ANCHO]);
void draw(char campo[ALTO][ANCHO]);
void loop(char campo[ALTO][ANCHO], int tam);
int input(char campo[ALTO][ANCHO], int tam, int *muerto);
void update(char campo[ALTO][ANCHO], int tam);
void intro_datos_nuevos(char campo[ALTO][ANCHO], int tam);

#endif
