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
#define TAMANIO_INICIAL 4

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

frt espacios_vacios[LIMITE_SNAKE];

void inicializar_espacios_vacios(void) {
	int i;
	for(i = 0 ; i < LIMITE_SNAKE ; i++) {
		espacios_vacios[i].x = 0;
		espacios_vacios[i].y = 0;
	}
}

int llenar_espacios(char campo[ALTO][ANCHO]) {
	int i, j, tamanio = 0;
	for(j = 1 ; j < ALTO - 1 ; j++) {
		for(i = 1 ; i < ANCHO - 1 ; i++) {
			if(campo[j][i] == ' ') {
				espacios_vacios[tamanio].x = i;
				espacios_vacios[tamanio].y = j;
				tamanio++;
			}
		}
	}
	return tamanio;
}

void crear_snake(void) {
	int i, j;
	jugador = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(jugador);
	for(i = 0 ; i < ESCALA ; i++) {
		for (j = 0 ; j < ESCALA ; j++) {
			putpixel(jugador, i, j, palette_color[vivora[j][i]]);
		}
	}
}

void crear_comida(void) {
	int i, j;
	comida = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(comida);
	for(i = 0 ; i < ESCALA ; i++) {
		for (j = 0 ; j < ESCALA ; j++) {
			putpixel(comida, i, j, palette_color[fruta_bits[j][i]]);
		}
	}
}

void dibujar_bordes(void) {
	rect(screen, ESCALA, ESCALA, ANCHO * 10 - 10, ALTO * 10 - 10, palette_color[15]);
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
	set_gfx_mode(GFX_SAFE, ANCHO * 10, ALTO * 10, 0, 0);

	crear_snake();
	crear_comida();

	snake[0].x = 32;
	snake[0].y = 10;

	*tam = TAMANIO_INICIAL;
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
	if(muerto == 0) {
		intro_datos_nuevos(campo, tam);
	}
}

void asignar_movimiento(int mov_x, int mov_y) {
	snake[0].mod_x = mov_x;
	snake[0].mod_y = mov_y;
}

int input(char campo[ALTO][ANCHO], int tam, int *muerto, int puntaje_record) {
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

			inicializar_espacios_vacios();
			int posicion = rand() % llenar_espacios(campo);

			fruta.x = espacios_vacios[posicion].x;
			fruta.y = espacios_vacios[posicion].y;
		}
	}

	if(*muerto == 0) {
		if(keypressed()) {
			tecla = readkey() >> 8;

			if(tecla == KEY_P) {
				readkey();
			}

			if(tecla == KEY_DOWN && snake[0].mod_y != -1) {
				asignar_movimiento(0, 1);
			}
			if(tecla == KEY_UP && snake[0].mod_y != 1) {
				asignar_movimiento(0, -1);
			}
			if(tecla == KEY_LEFT && snake[0].mod_x != 1) {
				asignar_movimiento(-1, 0);
			}
			if(tecla == KEY_RIGHT && snake[0].mod_x != -1) {
				asignar_movimiento(1, 0);
			}
		}
	}
	else {
		textprintf_centre_ex(screen, font, 325, 190, 15, 0, "GAME OVER");
		textprintf_centre_ex(screen, font, 325, 200, 15, 0, "TU PUNTAJE: %d", tam - TAMANIO_INICIAL);
		textprintf_centre_ex(screen, font, 325, 210, 15, 0, "PUNTAJE RECORD: %d", puntaje_record);
		readkey();
	}
	return tam;
}

void loop(char campo[ALTO][ANCHO], int tam, int puntaje_record, FILE * archivo) {
	int muerto = 0;
	int pausa = 250;
	int veces = 0;

	do {
		draw(campo);
		tam = input(campo, tam, &muerto, puntaje_record);

		update(campo, tam, muerto);

		if(veces > 10) {
			veces = 0;
			pausa -= 1;
		}
		rest(pausa);
	} while (muerto == 0);

	int puntaje_actual = tam - 4;
	archivo = fopen("puntaje_record.txt", "w");
	if(puntaje_record <= puntaje_actual)
		fprintf(archivo, "%d", puntaje_actual);
	else
		fprintf(archivo, "%d", puntaje_record);
	fclose(archivo);
}
