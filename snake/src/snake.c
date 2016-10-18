#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

#define FLECHA_COORDENADA_X 23
#define RETRASO_ATENUAR_TITULO 50
#define ALTO 40
#define ANCHO 64
#define LIMITE_SNAKE 2560
#define ESCALA 10
#define TAMANIO_INICIAL 4
#define TOTAL_FRUTAS 2556
#define MAX_DIGITOS_PUNTAJE 4

typedef int tipo_snake[10][10];

tipo_snake vivora =
   {{15,15,15,15,15,15,15,15,15},
    {15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
    {15,15,15,15,15,15,15,15,15}};

tipo_snake fruta_bits =
   {{0,0,0,15,15,15,0,0,0},
    {0,0,0,15,15,15,0,0,0},
	{0,0,0,15,15,15,0,0,0},
	{15,15,15,0,0,0,15,15,15},
    {15,15,15,0,0,0,15,15,15},
    {15,15,15,0,0,0,15,15,15},
	{0,0,0,15,15,15,0,0,0},
    {0,0,0,15,15,15,0,0,0},
    {0,0,0,15,15,15,0,0,0}};

tipo_snake flecha_seleccion =
   {{0 ,0 ,0 ,0 ,15,0 ,0 ,0 ,0 },
	{0 ,0 ,0 ,0 ,0 ,15,0 ,0 ,0 },
	{0 ,0 ,0 ,0 ,0 ,0 ,15,0 ,0 },
	{0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,0 },
    {15,15,15,15,15,15,15,15,15},
    {0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,0 },
    {0 ,0 ,0 ,0 ,0 ,0 ,15,0 ,0 },
	{0 ,0 ,0 ,0 ,0 ,15,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,15,0 ,0 ,0 ,0 }};

tipo_snake cabeza_a_derecha =
   {{15,15,15,15,15,15,15,15,15},
    {15,15,15,15,15,0 ,0 ,15,15},
	{15,15,15,15,15,0 ,0 ,0 ,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,0 ,0 ,0 ,15},
	{15,15,15,15,15,0 ,0 ,15,15},
    {15,15,15,15,15,15,15,15,15}};

tipo_snake cabeza_a_izquierda =
   {{15,15,15,15,15,15,15,15,15},
    {15,15,0 ,0 ,15,15,15,15,15},
	{15,0 ,0 ,0 ,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,0 ,0 ,0 ,15,15,15,15,15},
	{15,15,0 ,0 ,15,15,15,15,15},
    {15,15,15,15,15,15,15,15,15}};

tipo_snake cabeza_arriba =
   {{15,15,15,15,15,15,15,15,15},
    {15,15,0 ,15,15,15,0 ,15,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
    {15,15,15,15,15,15,15,15,15}};

tipo_snake cabeza_abajo =
   {{15,15,15,15,15,15,15,15,15},
    {15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,15,0 ,15,15,15,0 ,15,15},
    {15,15,15,15,15,15,15,15,15}};

typedef struct {
	int x,y;
	int mod_x, mod_y;
	char imagen;
}snk;

typedef struct {
	int x,y;
}frt;

frt fruta;

BITMAP *comida, *jugador, *cabeza, *selector;

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

void crear_cuerpo(void) {
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

void dibujar_bordes(int pos_ancho, int pos_alto) {
	rect(screen, ESCALA, ESCALA, ANCHO * ESCALA - pos_ancho, ALTO * ESCALA - pos_alto, palette_color[15]);
}

bool direccion_vertical(int tecla, int tecla_anterior) {
	return (tecla_anterior == KEY_UP || tecla_anterior == KEY_DOWN) && (tecla == KEY_RIGHT || tecla == KEY_LEFT);
}

bool direccion_horizontal(int tecla, int tecla_anterior) {
	return (tecla_anterior == KEY_RIGHT || tecla_anterior == KEY_LEFT) && (tecla == KEY_UP || tecla == KEY_DOWN);
}

void draw(char campo[ALTO][ANCHO], int puntaje_record, int puntaje_actual, int tecla, int *tecla_anterior) {
	int i,j;
	clear_bitmap(screen);
	dibujar_bordes(10, 10);
	for(i = 0 ; i < ALTO ; i++) {
		for(j = 0 ; j < ANCHO ; j++) {
			if(campo[i][j] == 'X')
				draw_sprite(screen, jugador, j * ESCALA, i * ESCALA);
			if(campo[i][j] == 'Y') {
				if(direccion_vertical(tecla, *tecla_anterior) || direccion_horizontal(tecla, *tecla_anterior)) {
					crear_cabeza(tecla);
				}
				draw_sprite(screen, cabeza, j * ESCALA, i * ESCALA);
			}
			if(campo[i][j] == '%') {
				draw_sprite(screen, comida, j * ESCALA, i * ESCALA);
			}
		}
	}
	textprintf_centre_ex(screen, font, 30, 2, 15, 0, "%d", puntaje_actual);
	textprintf_centre_ex(screen, font, 610, 2, 15, 0, "%d", puntaje_record);
}

void intro_campo(char campo[ALTO][ANCHO]) {
	int i, j;
	for(i = 0; i < ALTO; i++) {
		for(j = 0; j < ANCHO; j++) {
			campo[i][j] = ' ';
		}
	}
}

void intro_datos(char campo[ALTO][ANCHO], int tam, snk *snake) {
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

void crear_selector(void){
	int i, j;
	selector = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(selector);
	for(i = 0 ; i < ESCALA ; i++) {
		for(j = 0 ; j < ESCALA ; j++)
			putpixel(selector, i, j, palette_color[flecha_seleccion[j][i]]);
	}
}

void dibujar_titulo_gusano(int color) {
	textprintf_justify_ex(screen, font, 30, 10, 40, 0, color, 0, " __________");
	textprintf_justify_ex(screen, font, 30, 10, 50, 0, color, 0, "/\\  ______ \\");
	textprintf_justify_ex(screen, font, 30, 10, 60, 0, color, 0, "\\ \\ \\____/\\_\\   __    __   ________   ________   ________   ________");
	textprintf_justify_ex(screen, font, 30, 10, 70, 0, color, 0, " \\ \\ \\  _\\/_/_ /\\ \\  /\\ \\ /\\  _____\\ /\\_____  \\ /\\  ____ \\ /\\  ____ \\");
	textprintf_justify_ex(screen, font, 30, 10, 80, 0, color, 0, "  \\ \\ \\/\\____ \\\\ \\ \\ \\ \\ \\\\ \\ \\____/_\\/_____\\  \\\\ \\ \\__/\\ \\\\ \\ \\_ /\\ \\");
	textprintf_justify_ex(screen, font, 30, 10, 90, 0, color, 0, "   \\ \\ \\/____\\ \\\\ \\ \\ \\ \\ \\\\ \\______ \\ /\\  ____ \\\\ \\ \\ \\ \\ \\\\ \\ \\ \\ \\ \\");
	textprintf_justify_ex(screen, font, 30, 10, 100, 0, color, 0, "    \\ \\ \\_____\\ \\\\ \\ \\_\\_\\ \\\\/______\\ \\\\ \\ \\__/\\ \\\\ \\ \\ \\ \\ \\\\ \\ \\_\\_\\ \\");
	textprintf_justify_ex(screen, font, 30, 10, 110, 0, color, 0, "     \\ \\_________\\\\ \\_______\\ /\\_______\\\\ \\_______\\\\ \\ \\ \\ \\ \\\\ \\_______\\");
	textprintf_justify_ex(screen, font, 30, 10, 120, 0, color, 0, "      \\/_________/ \\/_______/ \\/_______/ \\/_______/ \\/_/  \\/_/ \\________/");
}


void dibujar_niveles(void) {
	textprintf_justify_ex(screen, font, 260, 10, 160, 0, 15, 0, "SELECT LEVEL: ");
	textprintf_justify_ex(screen, font, 260, 10, 180, 0, 15, 0, "EASY");
	textprintf_justify_ex(screen, font, 260, 10, 200, 0, 15, 0, "MEDIUM");
	textprintf_justify_ex(screen, font, 260, 10, 220, 0, 15, 0, "PROFFESIONAL");
}


void dibujar_flecha_selector(char campo[ALTO][ANCHO], int y) {
	int i;
	clear_bitmap(screen);
	dibujar_bordes(10, 10);
	for(i = 18 ; i < FLECHA_COORDENADA_X ; i++) {
		if(campo[23][y] == 'F') {
			draw_sprite(screen, selector, FLECHA_COORDENADA_X * ESCALA, y * ESCALA);
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

void seleccionar_nivel(char campo[ALTO][ANCHO], int *nivel) {
	SAMPLE * sonido_flecha = load_sample("flecha.wav");

	crear_selector();
	int tecla = 0, pos_nivel = 1, flecha_y = 18, color = 13, retraso = 0;
	draw_sprite(screen, selector, 23 * ESCALA, 18 * ESCALA);

	while(true) {
		dibujar_bordes(ESCALA, ESCALA);
		dibujar_niveles();
		dibujar_titulo_gusano(color);
		atenuar_colores_titulo(&color, &retraso);

		if(keypressed()) {
			tecla = readkey() >> 8;
			if(tecla == KEY_ENTER) break;
			play_sample(sonido_flecha, 200, 150, 1000, 0);

			if(tecla == KEY_UP) pos_nivel--;
			if(tecla == KEY_DOWN) pos_nivel++;
			if(pos_nivel > 3) pos_nivel = 1;
			if(pos_nivel < 1) pos_nivel = 3;

			vaciar_flecha_selector(campo);
			switch(pos_nivel) {
				case 1: flecha_y = 18;
				break;
				case 2: flecha_y = 20;
				break;
				case 3: flecha_y = 22;
				break;
			}
			campo[FLECHA_COORDENADA_X][flecha_y] = 'F';
			dibujar_flecha_selector(campo, flecha_y);
			*nivel = pos_nivel;
		}
	}
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

void inicio(int *tam, char campo[ALTO][ANCHO], int *nivel, int * puntaje_record, FILE * archivo, snk *snake) {
	allegro_init();
	install_keyboard();
	install_timer();
	set_gfx_mode(GFX_SAFE, ANCHO * 10, ALTO * 10, 0, 0);
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
	intro_datos(campo, *tam, snake);
}

void intro_datos_nuevos(char campo[ALTO][ANCHO], int tam, snk *snake) {
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

void update(char campo[ALTO][ANCHO], int tam, int muerto, snk *snake) {
	intro_campo(campo);
	if(muerto == 0) intro_datos_nuevos(campo, tam, snake);
}

void asignar_movimiento(int mov_x, int mov_y, snk *snake) {
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

int input(char campo[ALTO][ANCHO], int tam, int *tecla, int *muerto, int record, SAMPLE *s_comer, SAMPLE *s_pausa, SAMPLE *s_impacto, int *tecla_anterior, snk *snake) {
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
				asignar_movimiento(mov_x, mov_y, snake);
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

void loop(char campo[ALTO][ANCHO], int tam, int puntaje_record, FILE * archivo, int *nivel, snk *snake) {
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
		tam = input(campo, tam, &tecla, &muerto, puntaje_record, sonido_comer, sonido_pausa, sonido_impacto, &tecla_anterior, snake);
		update(campo, tam, muerto, snake);
		rest(pausa);
	} while (muerto == 0);

	int puntaje_actual = tam - 4;

	archivo = fopen("puntaje_record.txt", "w");
	(puntaje_record <= puntaje_actual) ? fprintf(archivo, "%d", puntaje_actual) : fprintf(archivo, "%d", puntaje_record);

	fclose(archivo);
}

int main(void) {
	int tam;
	char campo[40][64];
	int puntaje_record;

	FILE * archivo;
	snk snake[LIMITE_SNAKE];
	archivo = fopen("puntaje_record.txt", "r");

	int nivel = 0;
	inicio(&tam, campo, &nivel, &puntaje_record, archivo, snake);
	loop(campo, tam, puntaje_record, archivo, &nivel, snake);

	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
