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
#define TOTAL_FRUTAS 2556
#define MAX_DIGITOS_PUNTAJE 4

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
		for (j = 0 ; j < ESCALA ; j++)
			putpixel(jugador, i, j, palette_color[vivora[j][i]]);
	}
}

void crear_comida(void) {
	int i, j;
	comida = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(comida);
	for(i = 0 ; i < ESCALA ; i++) {
		for (j = 0 ; j < ESCALA ; j++)
			putpixel(comida, i, j, palette_color[fruta_bits[j][i]]);
	}
}

void dibujar_bordes(void) {
	rect(screen, ESCALA, ESCALA, ANCHO * 10 - 10, ALTO * 10 - 10, palette_color[15]);
}

void draw(char campo[ALTO][ANCHO], int puntaje_record, int puntaje_actual) {
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
	textprintf_centre_ex(screen, font, 30, 2, 15, 0, "%d", puntaje_actual);
	textprintf_centre_ex(screen, font, 610, 2, 15, 0, "%d", puntaje_record);
}

void intro_campo(char campo[ALTO][ANCHO]) {
	int i, j;
	for(i = 0; i < ALTO; i++) {
		for(j = 0; j < ANCHO; j++)
			campo[i][j] = ' ';
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

void seleccionar_nivel(char campo[ALTO][ANCHO], int *nivel) {
	while(1) {
		dibujar_bordes();
		textprintf_justify_ex(screen, font, 30, 10, 20, 0, 15, 0, "SELECT LEVEL: ");
		textprintf_justify_ex(screen, font, 30, 10, 40, 0, 15, 0, "1 EASY");
		textprintf_justify_ex(screen, font, 30, 10, 60, 0, 15, 0, "2 MEDIUM");
		textprintf_justify_ex(screen, font, 30, 10, 80, 0, 15, 0, "3 PROFFESIONAL");
		int tecla = 0;
		if(keypressed()) {
			tecla = readkey() >> 8;
			switch (tecla) {
				case KEY_1: case KEY_1_PAD: *nivel = 1;
				break;
				case KEY_2: case KEY_2_PAD: *nivel = 2;
				break;
				case KEY_3: case KEY_3_PAD: *nivel = 3;
				break;
				default:
					textprintf_centre_ex(screen, font, 325, 190, 15, 0, "AGAIN SELECT A VALID LEVEL ...");
					continue;
				break;
			}
			break;
		}
	}
}

void leer_puntaje_record(int * nivel, FILE * archivo, int *puntaje_record) {
	if(archivo != NULL)
		fscanf(archivo, "%d", puntaje_record);
	else
		*puntaje_record = 0;
	fclose(archivo);
}

void inicio(int *tam, char campo[ALTO][ANCHO], int *nivel, int * puntaje_record, FILE * archivo) {
	allegro_init();
	install_keyboard();
	install_timer();
	set_gfx_mode(GFX_SAFE, ANCHO * 10, ALTO * 10, 0, 0);

	seleccionar_nivel(campo, nivel);
	leer_puntaje_record(nivel, archivo, puntaje_record);

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

	for(i = 0 ; i < tam ; i++)
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	campo[fruta.y][fruta.x] = '%';
}

void update(char campo[ALTO][ANCHO], int tam, int muerto) {
	intro_campo(campo);
	if(muerto == 0) intro_datos_nuevos(campo, tam);
}

void asignar_movimiento(int mov_x, int mov_y) {
	snake[0].mod_x = mov_x;
	snake[0].mod_y = mov_y;
}

void exit_snake(void) {
	int tecla = 0;
	textprintf_centre_ex(screen, font, 325, 250, 15, 0, "Press the [Enter] key to exit ...");
	while(1) {
		tecla = readkey() >> 8;
		if(tecla == KEY_ENTER) break;
	}
}

int input(char campo[ALTO][ANCHO], int tam, int *muerto, int puntaje_record) {
	int tecla = 0;
	if(*muerto == 0) {
		if(snake[0].x == 0 || snake[0].x == ANCHO - 1 || snake[0].y == 0 || snake[0].y == ALTO - 1) *muerto = 1;
	}

	if(*muerto == 0) {
		int i;
		for(i = 1 ; i < tam && *muerto == 0 ; i++)
			if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) *muerto = 1;
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

			if(tecla == KEY_P) readkey();

			int mov_x = 0, mov_y = 0;

			if(tecla == KEY_DOWN && snake[0].mod_y != -1) mov_y = 1;
			if(tecla == KEY_UP && snake[0].mod_y != 1) mov_y = -1;
			if(tecla == KEY_LEFT && snake[0].mod_x != 1) mov_x = -1;
			if(tecla == KEY_RIGHT && snake[0].mod_x != -1) mov_x = 1;

			asignar_movimiento(mov_x, mov_y);
		}
	}
	else {
		if(tam - TAMANIO_INICIAL == TOTAL_FRUTAS) {
			textprintf_centre_ex(screen, font, 325, 190, 15, 0, "YOU WIN!");
		} else {
			textprintf_centre_ex(screen, font, 325, 190, 15, 0, "GAME OVER");
			textprintf_centre_ex(screen, font, 325, 210, 15, 0, "SCORE: %d", tam - TAMANIO_INICIAL);
			textprintf_centre_ex(screen, font, 325, 220, 15, 0, "RECORD: %d", puntaje_record);
		}
		exit_snake();
	}
	return tam;
}

void loop(char campo[ALTO][ANCHO], int tam, int puntaje_record, FILE * archivo, int *nivel) {
	int muerto = 0, pausa = 0;

	switch(*nivel) {
		case 1 :
			pausa = 300;
			break;
		case 2 :
			pausa = 200;
			break;
		case 3 :
			pausa = 100;
			break;
	}

	do {
		draw(campo, puntaje_record, tam - TAMANIO_INICIAL);
		tam = input(campo, tam, &muerto, puntaje_record);
		update(campo, tam, muerto);
		rest(pausa);
	} while (muerto == 0);

	int puntaje_actual = tam - 4;

	archivo = fopen("puntaje_record.txt", "w");
	(puntaje_record <= puntaje_actual) ? fprintf(archivo, "%d", puntaje_actual) : fprintf(archivo, "%d", puntaje_record);

	fclose(archivo);
}
