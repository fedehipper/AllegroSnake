#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#define POS_X_INI 32
#define POS_Y_INI 20

#define INC_X_INI 1
#define INC_Y_INI 0

#define PAUSA 350

#define ARRIBA KEY_W
#define ABAJO KEY_S
#define IZQUIERDA KEY_A
#define DERECHA KEY_D

int posX, posY;
int incX, incY;
int tecla;

#define ESCALA 10

#define ANCHOTROZO 10
#define ALTOTROZO 10

#define MAXFILAS 40
#define MAXCOLS 64

char mapa[MAXFILAS][MAXCOLS] = {
  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "X                                                              X",
  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
};

int numFrutas = 7;

BITMAP *ladrilloFondo, *comida, *jugador;

typedef int tipoSnake[ANCHOTROZO][ALTOTROZO];

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

void crearSnake() {
  int i, j;
  jugador = create_bitmap(10, 10);
  clear_bitmap(jugador);
  for(i = 0; i < ANCHOTROZO; i++)
    for (j = 0; j < ALTOTROZO; j++)
      putpixel(jugador, i, j, palette_color[vivora[j][i]]);
}


void dibujarMapa() {
	clear_bitmap(screen);
	rect(screen, 10, 10, 630, 390, palette_color[15]);
}

int main(void) {
  allegro_init();
  install_keyboard();
  install_timer();

  set_gfx_mode(GFX_SAFE, 640, 400, 0, 0);
  crearSnake();
  dibujarMapa();

  posX = POS_X_INI;
  posY = POS_Y_INI;

  incX = INC_X_INI;
  incY = INC_Y_INI;

  do {
    dibujarMapa();
    draw_sprite(screen, jugador, posX * ESCALA, posY * ESCALA);

    if (mapa[posY][posX] == 'X') {
    	allegro_message("Game Over");
    	break;
    }

    if (keypressed()) {
        tecla = readkey() >> 8;
        switch (tecla) {
          case ARRIBA:
        	  incX = 0; incY = -1;  break;
          case ABAJO:
        	  incX = 0; incY = 1;  break;
          case IZQUIERDA:
        	  incX = -1; incY = 0;  break;
          case DERECHA:
        	  incX = 1; incY = 0;  break;
        }
    }

    posX += incX;
    posY += incY;

    rest (PAUSA);
  }
  while (TRUE);

  readkey();
  return EXIT_SUCCESS;
}

END_OF_MAIN();
