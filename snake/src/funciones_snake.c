#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "bits.h"

#define ALTO 40
#define ANCHO 64
#define LIMITE_SNAKE 2560
#define ESCALA 10

typedef struct {
	int x,y;
	int mod_x, mod_y;
	char imagen;
}snk;

typedef struct {
	int x,y;
}frt;

snk snake[LIMITE_SNAKE];

frt fruta;

BITMAP *comida, *jugador, *cabeza;

void crear_snake() {
	int i, j;
	jugador = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(jugador);
	for(i = 0 ; i < ESCALA ; i++) {
		for (j = 0 ; j < ESCALA ; j++) {
			putpixel(jugador, i, j, palette_color[vivora[j][i]]);
		}
	}
}

int size_ancho() {
	int i = 0;
	while(snake[i].x > 0)
		i++;
	return i;
}

int size_alto() {
	int i = 0;
	while(snake[i].y > 0)
		i++;
	return i;
}

int include_ancho(int valor_x) {
	int i = 0;
	while(snake[i].x > 0) {
		if(snake[i].x == valor_x)
			break;
		else
			i++;
	}
	if(size_ancho() > i) return 1;
	else return 0;
}


int include_alto(int valor_y) {
	int i = 0;
	while(snake[i].y > 0) {
		if(snake[i].y == valor_y)
			break;
		else
			i++;
	}
	if(size_alto() > i) return 1;
	else return 0;
}


void crear_comida() {
	int i, j;
	comida = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(comida);
	for(i = 0 ; i < ESCALA ; i++) {
		for (j = 0 ; j < ESCALA ; j++) {
			putpixel(comida, i, j, palette_color[fruta_bits[j][i]]);
		}
	}
}

void dibujar_bordes() {
	rect(screen, ESCALA, ESCALA, 630, 390, palette_color[15]);
}

void draw(char campo[ALTO][ANCHO]) {
	int i,j;
	clear_bitmap(screen);
	dibujar_bordes();
	for(i = 0 ; i < ALTO ; i++) {
		for(j = 0 ; j < ANCHO ; j++) {
			if(campo[i][j] != ' ' && campo[i][j] != '%')
				draw_sprite(screen, jugador, j * ESCALA, i * ESCALA);
			if(campo[i][j] == '%')
				draw_sprite(screen, comida, j * ESCALA, i * ESCALA);
		}
	}
}

void intro_campo(char campo[ALTO][ANCHO]) {
	int i, j;
	for(i = 0; i < ALTO; i++) {
		for(j = 0; j < ANCHO; j++) {
			campo[i][j] = ' ';
		}
	}
}

// mete todos los datos en la matriz campo
void intro_datos(char campo[ALTO][ANCHO], int tam) {
	int i;
	for(i = 1 ; i < tam ; i++) {
		snake[i].x = snake[i - 1].x - 1;
		snake[i].y = snake[i - 1].y;
		snake[i].imagen ='X';
	}
	snake[0].imagen = 'X';

	for(i = 0; i < tam ; i++) {
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	campo[fruta.y][fruta.x] = '%';
}

void inicio(int *tam, char campo[ALTO][ANCHO]) {
	allegro_init();
	install_keyboard();
	install_timer();
	set_gfx_mode(GFX_SAFE, 640, 400, 0, 0);
	crear_snake();
	crear_comida();

	snake[0].x = 32;
	snake[0].y = 10;

	*tam = 4;
	srand(time(NULL));

	fruta.x = rand() % (ANCHO - 2) + 1;
	fruta.y = rand() % (ALTO - 2) + 1;

	int i;
	for(i = 0; i < *tam ; i++) {
		snake[i].mod_x = 1;
		snake[i].mod_y = 0;
	}
	intro_campo(campo);
	intro_datos(campo, *tam);
}

void intro_datos_nuevos(char campo[ALTO][ANCHO], int tam) {
	// crear la persecucion de los elementos del cuerpo a si mismo
	int i;
	for(i = tam - 1 ; i > 0 ; i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}
	snake[0].x += snake[0].mod_x;
	snake[0].y += snake[0].mod_y;
	for(i = 0 ; i < tam ; i++) {
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	campo[fruta.y][fruta.x] = '%';
}

void update(char campo[ALTO][ANCHO], int tam, int muerto) {
	intro_campo(campo);
	if(muerto == 0) intro_datos_nuevos(campo, tam);
}

int input(char campo[ALTO][ANCHO], int tam, int *muerto) {
	int tecla = 0;
	if(*muerto == 0) {
		if(snake[0].x == 0 || snake[0].x == ANCHO - 1 || snake[0].y == 0 || snake[0].y == ALTO - 1) {
			*muerto = 1;
		}
	}

	if(*muerto == 0) {
		int i;
		for(i = 1 ; i < tam && *muerto == 0 ; i++) {
			if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
				*muerto = 1;
			}
		}
	}

	if(*muerto == 0) {
		if(snake[0].x == fruta.x && snake[0].y == fruta.y) {
			tam += 1;
			snake[tam - 1].imagen = 'X';

			do {
				fruta.x = rand() % (ANCHO - 2) + 1;
				fruta.y = rand() % (ALTO - 2) + 1;
			} while (include_ancho(fruta.x) && include_alto(fruta.y));
		}
	}

	if(*muerto == 0) {
		if(keypressed()) {
			tecla = readkey() >> 8;

			if(tecla == KEY_DOWN && snake[0].mod_y != -1) {
				snake[0].mod_x = 0;
				snake[0].mod_y = 1;
			}
			if(tecla == KEY_UP && snake[0].mod_y != 1) {
				snake[0].mod_x = 0;
				snake[0].mod_y = -1;
			}
			if(tecla == KEY_LEFT && snake[0].mod_x != 1) {
				snake[0].mod_x = -1;
				snake[0].mod_y = 0;
			}
			if(tecla == KEY_RIGHT && snake[0].mod_x != -1) {
				snake[0].mod_x = 1;
				snake[0].mod_y = 0;
			}
		}
	}
	else allegro_message("GAME OVER");
	return tam;
}

void loop(char campo[ALTO][ANCHO], int tam) {
	int muerto = 0;
	frt fruta_anterior;
	int pausa = 250;
	do {
		draw(campo);
		fruta_anterior = fruta;
		tam = input(campo, tam, &muerto);

		update(campo, tam, muerto);

//		if(fruta.x != fruta_anterior.x && fruta.y != fruta_anterior.y) {
//			if(pausa > 400) pausa -= 5;
//			if(pausa <= 400 && pausa > 250) pausa -= 2;
//			else pausa -= 1;
//		}
		rest(pausa);
	} while (muerto == 0);
}
