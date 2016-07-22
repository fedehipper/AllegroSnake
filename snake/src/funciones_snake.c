#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "bits.h"

#define V 40
#define H 64
#define N 100

typedef struct {
	int x,y;
	int ModX, ModY;
	char imagen;
}snk;

typedef struct {
	int x,y;
}frt;

// vector de estructuras
snk snake[N];

frt fruta;

BITMAP *ladrilloFondo, *comida, *jugador, *cabeza;

void crear_snake() {
	int i, j;
	jugador = create_bitmap(10, 10);
	clear_bitmap(jugador);
	for(i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			putpixel(jugador, i, j, palette_color[vivora[j][i]]);
}

void crear_cabeza() {
	int i, j;
	cabeza = create_bitmap(10, 10);
	clear_bitmap(cabeza);
	for(i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			putpixel(cabeza, i, j, palette_color[cabeza_bits[j][i]]);
}

void crear_comida() {
	int i, j;
	comida = create_bitmap(10, 10);
	clear_bitmap(comida);
	for(i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			putpixel(comida, i, j, palette_color[fruta_bits[j][i]]);
}

void dibujar_bordes() {
	rect(screen, 10, 10, 630, 390, palette_color[15]);
}

int kbhit(void) {
	struct termios oldt, newt;
	int ch;
	int oldf;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}

void draw(char campo[V][H]) {
	int i,j;
	clear_bitmap(screen);
	dibujar_bordes();
	for(i = 0 ; i < V; i++) {
		for(j = 0; j < H ; j++) {
			if(campo[i][j] != ' ' && campo[i][j] != '%' && campo[i][j] != 'O')
				draw_sprite(screen, jugador, j * 10, i * 10);
			if(campo[i][j] == '%')
				draw_sprite(screen, comida, j * 10, i * 10);
			if(campo[i][j] == 'O')
				draw_sprite(screen, cabeza, j * 10, i * 10);
		}
	}
}

void intro_campo(char campo[V][H]) {
	int i, j;
	for(i = 0; i < V; i++)
		for(j = 0; j < H; j++)
			campo[i][j] = ' ';
}

// mete todos los datos en la matriz campo
void intro_datos(char campo[V][H], int tam) {
	int i;
	for(i = 1 ; i < tam ; i++) {
		snake[i].x = snake[i - 1].x - 1;
		snake[i].y = snake[i - 1].y;
		snake[i].imagen ='X';
	}
	snake[0].imagen = 'O';

	for(i = 0; i < tam ; i++) {
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	campo[fruta.y][fruta.x] = '%';
}

void inicio(int *tam, char campo[V][H]) {
	allegro_init();
	set_gfx_mode(GFX_SAFE, 640, 400, 0, 0);

	crear_snake();
	crear_comida();
	crear_cabeza();

	// la cabeza de la serpiente
	int i;
	snake[0].x = 32;
	snake[0].y = 10;

	// tamanio de la serpiente inicial
	*tam = 4;

	// semilla de la aleatoriedad
	srand(time(NULL));

	fruta.x = rand() % (H - 1);
	fruta.y = rand() % (V - 1);

	while(fruta.x == 0) {
		fruta.x = rand() % (H - 1);
	}

	while(fruta.y == 0) {
		fruta.y = rand() % (V - 1);
	}

	for(i = 0; i < *tam ; i++) {
		snake[i].ModX = 1;
		snake[i].ModY = 0;
	}

	intro_campo(campo);
	intro_datos(campo, *tam);
}

void intro_datos_nuevos(char campo[V][H], int tam) {
	// crear la persecucion de los elementos del cuerpo a si mismo
	int i;
	for(i = tam - 1; i > 0 ; i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}
	snake[0].x += snake[0].ModX;
	snake[0].y += snake[0].ModY;
	for(i = 0 ; i < tam ; i++) {
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	campo[fruta.y][fruta.x] = '%';
}

void update(char campo[V][H], int tam) {
	// borrar todos los datos de la matriz
	intro_campo(campo);
	// introducir los nuevos datos
	intro_datos_nuevos(campo, tam);
}

void input(char campo[V][H], int *tam, int *muerto) {

	// comprobar si se muere la snake
	if(snake[0].x == 0 || snake[0].x == H - 1 || snake[0].y == 0 || snake[0].y == V - 1) {
		*muerto = 1;
	}
	int i;
	for(i = 1 ; i < *tam && *muerto == 0 ; i++) {
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			*muerto = 1;
		}
	}

	// comprobar si se come la fruta
	if(snake[0].x == fruta.x && snake[0].y == fruta.y) {
		*tam += 1;
		// regenerar la fruta y agrandar la serpiente
		snake[*tam - 1].imagen = 'X';

		fruta.x = rand() % (H - 1);
		fruta.y = rand() % (V - 1);

		while(fruta.x == 0) {
			fruta.x = rand() % (H - 1);
		}
		while(fruta.y == 0) {
			fruta.y = rand() % (V - 1);
		}
	}

	// comprobar la tecla que se pulsa
	char key;
	if(*muerto == 0) {
		if(kbhit() == 1) {
			key = getchar();

			if(key == 's' && snake[0].ModY != -1) {
				snake[0].ModX = 0;
				snake[0].ModY = 1;
		   }
			if(key == 'w'  && snake[0].ModY != 1) {
				snake[0].ModX = 0;
				snake[0].ModY = -1;
			}
			if(key == 'a'  && snake[0].ModX != 1) {
				snake[0].ModX = -1;
				snake[0].ModY = 0;
			}
			if(key == 'd'  && snake[0].ModX != -1) {
				snake[0].ModX = 1;
				snake[0].ModY = 0;
			}
		}
	}
}

void loop(char campo[V][H], int tam) {
	int muerto = 0;
	do {
		draw(campo);
		input(campo, &tam, &muerto);
		update(campo, tam);

		sleep(1);
	} while (muerto == 0);
}
