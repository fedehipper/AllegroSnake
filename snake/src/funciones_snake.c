#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include "funciones_draw.h"


#define LIMITE_SNAKE 2560
#define ESCALA 10
#define TAMANIO_INICIAL 4
#define TOTAL_FRUTAS 2556
#define MAX_DIGITOS_PUNTAJE 4
#define FLECHA_COORDENADA_X 23


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
	snake[0].imagen = 'Y';

	for(i = 0 ; i < tam ; i++) {
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	campo[fruta.y][fruta.x] = '%';
}

void leer_puntaje_record(int * nivel, FILE * archivo, int *puntaje_record) {
	if(archivo != NULL) {
		fscanf(archivo, "%d", puntaje_record);
		fclose(archivo);
	}
	else
		*puntaje_record = 0;
}

void instalar_sonidos(void) {
	int driver_digi = 1, driver_midi = 0;
	detect_digi_driver(driver_digi);
	detect_midi_driver(driver_midi);
	reserve_voices(5, 5);
	install_sound(driver_digi, driver_midi, "cfg_path");
	set_volume(200, 100);
}

void inicio(int *tam, char campo[ALTO][ANCHO], int *nivel, int * puntaje_record, FILE * archivo) {
	allegro_init();
	install_keyboard();
	install_mouse();
	install_timer();

	set_gfx_mode(GFX_SAFE, ANCHO * 10, ALTO * 10, 0, 0);
	show_mouse(screen);

	instalar_sonidos();

	seleccionar_nivel(campo, nivel);
	leer_puntaje_record(nivel, archivo, puntaje_record);

	crear_cuerpo();
	crear_comida();
	crear_cabeza(KEY_RIGHT);

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
	while(true) {
		tecla = readkey() >> 8;
		if(tecla == KEY_ENTER) break;
	}
}

void pausa(int tecla, SAMPLE * sonido_pausa) {
	play_sample(sonido_pausa, 200, 150, 1000, 0);
	while(true) {
		tecla = readkey() >> 8;
		if(tecla == KEY_P) {
			play_sample(sonido_pausa, 200, 150, 1000, 0);
			break;
		}
	}
}

bool es_tecla_de_direccion(int tecla) {
	return tecla == KEY_UP || tecla == KEY_DOWN || tecla == KEY_RIGHT || tecla == KEY_LEFT;
}

int input(char campo[ALTO][ANCHO], int tam, int *tecla, int *muerto, int record, SAMPLE *s_comer, SAMPLE *s_pausa, SAMPLE *s_impacto, int *tecla_anterior) {
	if(*muerto == 0) {
		if(snake[0].x == 0 || snake[0].x == ANCHO - 1 || snake[0].y == 0 || snake[0].y == ALTO - 1) *muerto = 1;
	}

	if(*muerto == 0) {
		int i;
		for(i = 1 ; i < tam && *muerto == 0 ; i++)
			if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) *muerto = 1;
	}

	if(*muerto) play_sample(s_impacto, 200, 150, 1000, 0);

	if(*muerto == 0) {
		if(snake[0].x == fruta.x && snake[0].y == fruta.y) {
			play_sample(s_comer, 200, 150, 1000, 0);

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

			if(es_tecla_de_direccion(*tecla)) {
				*tecla_anterior = *tecla;
			}

			*tecla = readkey() >> 8;

			if(*tecla == KEY_P) pausa(*tecla, s_pausa);

			int mov_x = 0, mov_y = 0;

			if(*tecla == KEY_DOWN && snake[0].mod_y != -1) mov_y = 1;
			if(*tecla == KEY_UP && snake[0].mod_y != 1) mov_y = -1;
			if(*tecla == KEY_LEFT && snake[0].mod_x != 1) mov_x = -1;
			if(*tecla == KEY_RIGHT && snake[0].mod_x != -1) mov_x = 1;
			if(mov_x != 0 || mov_y != 0)
				asignar_movimiento(mov_x, mov_y);
		}
	}
	else {
		if(tam - TAMANIO_INICIAL == TOTAL_FRUTAS) {
			textprintf_centre_ex(screen, font, 325, 190, 15, 0, "YOU WIN!");
		} else {
			textprintf_centre_ex(screen, font, 325, 190, 15, 0, "GAME OVER");
			textprintf_centre_ex(screen, font, 325, 210, 15, 0, "SCORE: %d", tam - TAMANIO_INICIAL);
			textprintf_centre_ex(screen, font, 325, 220, 15, 0, "RECORD: %d", record);
		}
		exit_snake();
	}
	return tam;
}

void loop(char campo[ALTO][ANCHO], int tam, int puntaje_record, FILE * archivo, int *nivel) {
	int muerto = 0, pausa = 0, tecla = KEY_RIGHT, tecla_anterior = KEY_RIGHT;

	switch(*nivel) {
		case 1 : pausa = 300;
		break;
		case 2 : pausa = 150;
		break;
		case 3 : pausa = 50;
		break;
	}

	SAMPLE * sonido_comer = load_sample("comer.wav");
	SAMPLE * sonido_pausa = load_sample("pause.wav");
	SAMPLE * sonido_impacto = load_sample("impact.wav");

	do {
		draw(campo, puntaje_record, tam - TAMANIO_INICIAL, tecla, &tecla_anterior);
		tam = input(campo, tam, &tecla, &muerto, puntaje_record, sonido_comer, sonido_pausa, sonido_impacto, &tecla_anterior);
		update(campo, tam, muerto);
		rest(pausa);
	} while (muerto == 0);

	int puntaje_actual = tam - 4;

	archivo = fopen("puntaje_record.txt", "w");
	(puntaje_record <= puntaje_actual) ? fprintf(archivo, "%d", puntaje_actual) : fprintf(archivo, "%d", puntaje_record);

	fclose(archivo);
}
