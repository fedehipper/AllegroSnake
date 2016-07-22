#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdbool.h>

#define POS_X_INI 32
#define POS_Y_INI 20
#define INC_X_INI 1
#define INC_Y_INI 0

#define PAUSA 100
int tecla;

#define ESCALA 10

#define ANCHO_TROZO 10
#define ALTO_TROZO 10

#define MAX_FILAS 40
#define MAX_COLS 64

int mapa[MAX_FILAS][MAX_COLS] = {{0}};

bool toca_pared(int pos_x, int pos_y) {
	return pos_x >= 63 || pos_x < 1 || pos_y >= 39 || pos_y < 1;
}

BITMAP *ladrilloFondo, *comida, *jugador;

typedef int tipoSnake[ANCHO_TROZO][ALTO_TROZO];

tipoSnake vivora =
   {{0,15,15,15,15,15,15,15,0},
    {15,15,0,0,0,0,0,15,15},
	{15,0,0,0,0,0,0,0,15},
	{15,0,0,15,15,15,0,0,15},
    {15,0,0,15,15,15,0,0,15},
    {15,0,0,15,15,15,0,0,15},
	{15,0,0,0,0,0,0,0,15},
    {15,15,0,0,0,0,0,15,15},
    {0,15,15,15,15,15,15,15,0}};

void crear_snake() {
	int i, j;
	jugador = create_bitmap(10, 10);
	clear_bitmap(jugador);
	for(i = 0; i < ANCHO_TROZO; i++)
		for (j = 0; j < ALTO_TROZO; j++)
			putpixel(jugador, i, j, palette_color[vivora[j][i]]);
}

void dibujar_mapa() {
	clear_bitmap(screen);
	rect(screen, 10, 10, 630, 390, palette_color[15]);
}

int main(void) {
	int pos_x, pos_y;
	int inc_x, inc_y;
	allegro_init();
	install_keyboard();
	install_timer();

	set_gfx_mode(GFX_SAFE, 640, 400, 0, 0);
	crear_snake();

	dibujar_mapa();

	pos_x = POS_X_INI;
	pos_y = POS_Y_INI;

	inc_x = INC_X_INI;
	inc_y = INC_Y_INI;

	do {
		dibujar_mapa();
		draw_sprite(screen, jugador, pos_x * ESCALA, pos_y * ESCALA);

		if (toca_pared(pos_x, pos_y)) {
			allegro_message("Game Over");
			break;
		}

		if (keypressed()) {
			tecla = readkey() >> 8;
			switch (tecla) {
			  case KEY_W:
				  inc_x = 0; inc_y = -1;  break;
			  case KEY_S:
				  inc_x = 0; inc_y = 1;  break;
			  case KEY_A:
				  inc_x = -1; inc_y = 0;  break;
			  case KEY_D:
				  inc_x = 1; inc_y = 0;  break;
			}
		}

		pos_x += inc_x;
		pos_y += inc_y;

		rest (PAUSA);
	  }
	  while (TRUE && tecla != KEY_ESC);

	  readkey();
	  return EXIT_SUCCESS;
}
END_OF_MAIN();
