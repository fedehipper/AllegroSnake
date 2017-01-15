#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro.h>
#include <time.h>
#include <stdbool.h>
#include "bits.h"

#define ESCALA 10
#define ALTO_CHAR 15
#define ANCHO_CHAR 13
#define ALTO 40
#define ANCHO 64
#define FLECHA_COORDENADA_X 23
#define POS_SELECT_LEVEL 140
#define RETRASO_ATENUAR_TITULO 50

BITMAP *comida, *jugador, *cabeza, *selector, *caracter;

bool direccion_vertical(int tecla, int tecla_anterior) {
	return (tecla_anterior == KEY_UP || tecla_anterior == KEY_DOWN) && (tecla == KEY_RIGHT || tecla == KEY_LEFT);
}

bool direccion_horizontal(int tecla, int tecla_anterior) {
	return (tecla_anterior == KEY_RIGHT || tecla_anterior == KEY_LEFT) && (tecla == KEY_UP || tecla == KEY_DOWN);
}

void crear_cuerpo(void) {
	int i, j;
	jugador = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(jugador);
	for(i = 0 ; i < ESCALA ; i++) {
		for (j = 0 ; j < ESCALA ; j++)
			putpixel(jugador, i, j, palette_color[vivora[j][i]]);
	}
}

void crear_caracter(char tecla_caracter) {
	int i, j;
	caracter = create_bitmap(ANCHO_CHAR, ALTO_CHAR);
	clear_bitmap(caracter);
	for(i = 0 ; i < ANCHO_CHAR ; i++) {
		for (j = 0 ; j < ALTO_CHAR ; j++) {
			switch(tecla_caracter) {
				case 's': putpixel(caracter, i, j, palette_color[t_caracter_s[j][i]]);
				break;
				case 'e': putpixel(caracter, i, j, palette_color[t_caracter_e[j][i]]);
				break;
				case 'l': putpixel(caracter, i, j, palette_color[t_caracter_l[j][i]]);
				break;
				case 'c': putpixel(caracter, i, j, palette_color[t_caracter_c[j][i]]);
				break;
				case 't': putpixel(caracter, i, j, palette_color[t_caracter_t[j][i]]);
				break;
				case 'v': putpixel(caracter, i, j, palette_color[t_caracter_v[j][i]]);
				break;
				case 'o': putpixel(caracter, i, j, palette_color[t_caracter_o[j][i]]);
				break;
				case 'g': putpixel(caracter, i, j, palette_color[t_caracter_g[j][i]]);
				break;
				case 'a': putpixel(caracter, i, j, palette_color[t_caracter_a[j][i]]);
				break;
				case 'm': putpixel(caracter, i, j, palette_color[t_caracter_m[j][i]]);
				break;
				case 'r': putpixel(caracter, i, j, palette_color[t_caracter_r[j][i]]);
				break;
				case 'y': putpixel(caracter, i, j, palette_color[t_caracter_y[j][i]]);
				break;
				case 'u': putpixel(caracter, i, j, palette_color[t_caracter_u[j][i]]);
				break;
				case 'w': putpixel(caracter, i, j, palette_color[t_caracter_w[j][i]]);
				break;
				case 'i': putpixel(caracter, i, j, palette_color[t_caracter_i[j][i]]);
				break;
				case 'n': putpixel(caracter, i, j, palette_color[t_caracter_n[j][i]]);
				break;
				case '!': putpixel(caracter, i, j, palette_color[t_caracter_exclamacion[j][i]]);
				break;
			}
		}
	}
}

void crear_selector(void) {
	int i, j;
	selector = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(selector);
	for(i = 0 ; i < ESCALA ; i++) {
		for(j = 0 ; j < ESCALA ; j++)
			putpixel(selector, i, j, palette_color[flecha_seleccion[j][i]]);
	}
}

void crear_comida(int numero_fruta_random) {
	int i, j;
	comida = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(comida);

	for(i = 0 ; i < ESCALA ; i++) {
		for (j = 0 ; j < ESCALA ; j++) {
			switch(numero_fruta_random) {
				case 1: putpixel(comida, i, j, palette_color[fruta_uno[j][i]]);
				break;
				case 2: putpixel(comida, i, j, palette_color[fruta_dos[j][i]]);
				break;
				case 3: putpixel(comida, i, j, palette_color[fruta_tres[j][i]]);
				break;
				case 4: putpixel(comida, i, j, palette_color[fruta_cuatro[j][i]]);
				break;
				case 5: putpixel(comida, i, j, palette_color[fruta_cinco[j][i]]);
				break;
				case 6: putpixel(comida, i, j, palette_color[fruta_seis[j][i]]);
				break;
			}
		}
	}
}

void crear_cabeza(int tecla_dir) {
	int i, j;
	cabeza = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(cabeza);
	for(i = 0 ; i < ESCALA ; i++) {
		for(j = 0 ; j < ESCALA ; j++) {
			switch(tecla_dir) {
				case KEY_UP: putpixel(cabeza, i, j, palette_color[cabeza_arriba[j][i]]);
				break;
				case KEY_DOWN: putpixel(cabeza, i, j, palette_color[cabeza_abajo[j][i]]);
				break;
				case KEY_RIGHT: putpixel(cabeza, i, j, palette_color[cabeza_a_derecha[j][i]]);
				break;
				case KEY_LEFT: putpixel(cabeza, i, j, palette_color[cabeza_a_izquierda[j][i]]);
				break;
			}
		}
	}
}

void dibujar_bordes(int pos_ancho, int pos_alto, BITMAP *pantalla) {
	rect(pantalla, ESCALA, ESCALA, ANCHO * ESCALA - pos_ancho, ALTO * ESCALA - pos_alto, palette_color[15]);
}


void draw(char campo[ALTO][ANCHO], int puntaje_record, int puntaje_actual, int tecla, int *tecla_anterior, BITMAP *pantalla) {
	int i,j;
	clear_bitmap(pantalla);
	dibujar_bordes(10, 10, pantalla);
	for(i = 0 ; i < ALTO ; i++) {
		for(j = 0 ; j < ANCHO ; j++) {
			if(campo[i][j] == 'X')
				draw_sprite(pantalla, jugador, j * ESCALA, i * ESCALA);
			if(campo[i][j] == 'Y') {
				if(direccion_vertical(tecla, *tecla_anterior) || direccion_horizontal(tecla, *tecla_anterior)) {
					crear_cabeza(tecla);
				}
				draw_sprite(pantalla, cabeza, j * ESCALA, i * ESCALA);
			}
			if(campo[i][j] == '%') {
				draw_sprite(pantalla, comida, j * ESCALA, i * ESCALA);
			}
		}
	}
	textprintf_centre_ex(pantalla, font, 30, 2, 15, 0, "%d", puntaje_actual);
	textprintf_centre_ex(pantalla, font, 610, 2, 15, 0, "%d", puntaje_record);
}

void dibujar_titulo_gusano(int color, BITMAP * pantalla) {
	textprintf_justify_ex(pantalla, font, 30, 10, 20, 16, color, 16, " __________");
	textprintf_justify_ex(pantalla, font, 30, 10, 30, 16, color, 16, "/\\  ______ \\");
	textprintf_justify_ex(pantalla, font, 30, 10, 40, 16, color, 16, "\\ \\ \\____/\\_\\   __    __   ________   ________   ________   ________");
	textprintf_justify_ex(pantalla, font, 30, 10, 50, 16, color, 16, " \\ \\ \\  _\\/_/_ /\\ \\  /\\ \\ /\\  _____\\ /\\_____  \\ /\\  ____ \\ /\\  ____ \\");
	textprintf_justify_ex(pantalla, font, 30, 10, 60, 16, color, 16, "  \\ \\ \\/\\____ \\\\ \\ \\ \\ \\ \\\\ \\ \\____/_\\/_____\\  \\\\ \\ \\__/\\ \\\\ \\ \\_ /\\ \\");
	textprintf_justify_ex(pantalla, font, 30, 10, 70, 16, color, 16, "   \\ \\ \\/____\\ \\\\ \\ \\ \\ \\ \\\\ \\______ \\ /\\  ____ \\\\ \\ \\ \\ \\ \\\\ \\ \\ \\ \\ \\");
	textprintf_justify_ex(pantalla, font, 30, 10, 80, 16, color, 16, "    \\ \\ \\_____\\ \\\\ \\ \\_\\_\\ \\\\/______\\ \\\\ \\ \\__/\\ \\\\ \\ \\ \\ \\ \\\\ \\ \\_\\_\\ \\");
	textprintf_justify_ex(pantalla, font, 30, 10, 90, 16, color, 16, "     \\ \\_________\\\\ \\_______\\ /\\_______\\\\ \\_______\\\\ \\ \\ \\ \\ \\\\ \\_______\\");
	textprintf_justify_ex(pantalla, font, 30, 10, 100, 16, color, 16, "      \\/_________/ \\/_______/ \\/_______/ \\/_______/ \\/_/  \\/_/ \\________/");
}

void dibujar_string(char * un_string, int *espacio, BITMAP * pantalla) {
	int i = 0;
	for(i = 0 ; i < strlen(un_string) ; i++) {
		crear_caracter(un_string[i]);
		draw_character_ex(pantalla, caracter, *espacio, POS_SELECT_LEVEL, 15, 0);
		*espacio += ANCHO_CHAR + 1;
	}
	*espacio += ANCHO_CHAR;
}

void dibujar_niveles(BITMAP *pantalla) {
	int espacio_char = 250;
	dibujar_string("select", &espacio_char, pantalla);
	dibujar_string("level", &espacio_char, pantalla);
	textprintf_justify_ex(pantalla, font, 260, 10, 180, 0, 15, 0, "EASY");
	textprintf_justify_ex(pantalla, font, 260, 10, 200, 0, 15, 0, "MEDIUM");
	textprintf_justify_ex(pantalla, font, 260, 10, 220, 0, 15, 0, "PROFFESIONAL");
}

void dibujar_flecha_selector(char campo[ALTO][ANCHO], int y, BITMAP *pantalla) {
	int i;
	dibujar_bordes(10, 10, pantalla);
	for(i = 18 ; i < FLECHA_COORDENADA_X ; i++) {
		if(campo[23][y] == 'F') {
			draw_sprite(pantalla, selector, FLECHA_COORDENADA_X * ESCALA, y * ESCALA);
		}
	}
}

void vaciar_flecha_selector(char campo[ALTO][ANCHO]) {
	campo[FLECHA_COORDENADA_X][18] = ' ';
	campo[FLECHA_COORDENADA_X][20] = ' ';
	campo[FLECHA_COORDENADA_X][22] = ' ';
}

void atenuar_colores_titulo(int *color, int *retraso) {
	(*retraso)++;
	rest(RETRASO_ATENUAR_TITULO);
	if(*retraso > 10 && *retraso < 20) *color = 15;
	if(*retraso < 10 && *retraso > 0) *color = 25;
	if(*retraso > 20) *retraso = 0;
}

void seleccionar_nivel(char campo[ALTO][ANCHO], int *nivel, BITMAP *pantalla) {
	SAMPLE * sonido_flecha;
	sonido_flecha = load_sample("s_flecha.wav");
	crear_selector();

	int tecla = 0, pos_nivel = 1, flecha_y = 18, color = 15, retraso = 0;
	draw_sprite(pantalla, selector, 23 * ESCALA, 18 * ESCALA);

	while(true) {
		blit(pantalla, screen, 0,0,0,0, ANCHO * 10, ALTO * 10);
		dibujar_bordes(ESCALA, ESCALA, pantalla);
		dibujar_niveles(pantalla);
		dibujar_titulo_gusano(color, pantalla);
		atenuar_colores_titulo(&color, &retraso);

		if(keypressed()) {
			tecla = readkey() >> 8;
			*nivel = pos_nivel;
			if(tecla == KEY_ENTER) break;

			play_sample(sonido_flecha, 200, 150, 1000, 0);

			if(tecla == KEY_UP) pos_nivel--;
			if(tecla == KEY_DOWN) pos_nivel++;
			if(pos_nivel > 3) pos_nivel = 1;
			if(pos_nivel < 1) pos_nivel = 3;

			vaciar_flecha_selector(campo);
			switch(pos_nivel) {
				case 1: {
					rectfill(pantalla, 230, 218, 240, 228, 16);
					rectfill(pantalla, 230, 198, 240, 208, 16);
					flecha_y = 18;
				}
				break;
				case 2: {
					rectfill(pantalla, 230, 218, 240, 228, 16);
					rectfill(pantalla, 230, 178, 240, 188, 16);
					flecha_y = 20;
				}
				break;
				case 3: {
					rectfill(pantalla, 230, 198, 240, 208, 16);
					rectfill(pantalla, 230, 178, 240, 188, 16);
					flecha_y = 22;
				}
				break;
			}
			campo[FLECHA_COORDENADA_X][flecha_y] = 'F';
			dibujar_flecha_selector(campo, flecha_y, pantalla);
		}
	}
}

void game_over(BITMAP *pantalla) {
	int espacio_char = 260;
	dibujar_string("game", &espacio_char, pantalla);
	dibujar_string("over", &espacio_char, pantalla);
}

void you_win(BITMAP *pantalla) {
	int espacio_char = 260;
	dibujar_string("you", &espacio_char, pantalla);
	dibujar_string("win!", &espacio_char, pantalla);
}
