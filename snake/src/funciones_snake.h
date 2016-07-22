
#ifndef SRC_FUNCIONES_SNAKE_H_
#define SRC_FUNCIONES_SNAKE_H_



#define V 39
#define H 63
#define N 100

void inicio(int *tam, char campo[V][H]);
void intro_datos(char campo[V][H], int tam);
void intro_campo(char campo[V][H]);
void draw(char campo[V][H]);
void loop(char campo[V][H], int tam);
void input(char campo[V][H], int *tam, int *muerto);
void update(char campo[V][H], int tam);
void intro_datos_nuevos(char campo[V][H], int tam);

#endif /* SRC_FUNCIONES_SNAKE_H_ */
