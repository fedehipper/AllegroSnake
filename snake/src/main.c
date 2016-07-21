#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

  /* Posiciones X e Y iniciales */
#define POS_X_INI 16
#define POS_Y_INI 10

#define INC_X_INI  1
#define INC_Y_INI  0

  /* Pausa en milisegundos entre un "fotograma" y otro */
#define PAUSA 350

  /* Teclas predefinidas */
#define TEC_ARRIBA KEY_W
#define TEC_ABAJO  KEY_S
#define TEC_IZQDA  KEY_A
#define TEC_DCHA   KEY_D

int posX, posY;  /* Posicion actual */
int incX, incY;  /* Incremento de la posicion */

  /* Terminado: Si ha chocado o comida todas las frutas */
int terminado;

  /* La tecla pulsada */
int tecla;

  /* Escala: relacion entre tama�o de mapa y de pantalla */
#define ESCALA 10

  /* Ancho y alto de los sprites */
#define ANCHOSPRITE 10
#define ALTOSPRITE  10

  /* Y el mapa que representa a la pantalla */
  /* Como usaremos modo grafico de 320x200 puntos */
  /* y una escala de 10, el tablero medira 32x20 */
#define MAXFILAS 40
#define MAXCOLS  64

char mapa[MAXFILAS][MAXCOLS]={};

int numFrutas = 7;

  /* Nuestros sprites */
BITMAP *ladrilloFondo, *comida, *jugador;


typedef int tipoSprite[ANCHOSPRITE][ALTOSPRITE];
                         /* El sprite en si: matriz de 30x30 bytes */

tipoSprite spriteJugador =
   {{0,15,15,15,15,15,15,15,0},
    {15,0,0,0,0,0,0,0,15},
	{15,0,0,0,0,0,0,0,15},
	{15,0,0,0,0,0,0,0,15},
    {15,0,0,0,0,0,0,0,15},
    {15,0,0,0,0,0,0,0,15},
    {15,0,0,0,0,0,0,0,15},
    {0,15,15,15,15,15,15,15,0}
   };



void crearSnake() {
  int i, j;
  jugador = create_bitmap(10, 10);
  clear_bitmap(jugador);
  for(i=0; i<ANCHOSPRITE; i++)
    for (j=0; j<ALTOSPRITE; j++)
      putpixel(jugador, i, j, palette_color[spriteJugador[j][i]]);
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
    draw_sprite (screen, jugador, posX * ESCALA, posY * ESCALA);

    terminado = FALSE;

    if (mapa[posY][posX] == 'X') {
    	allegro_message("Game Over");
    	terminado = TRUE;
    }

    if (terminado) break;

    if ( keypressed() ) {
        tecla = readkey() >> 8;
        switch (tecla) {
          case TEC_ARRIBA:
            incX =  0; incY = -1;  break;
          case TEC_ABAJO:
            incX =  0; incY =  1;  break;
          case TEC_IZQDA:
            incX = -1; incY =  0;  break;
          case TEC_DCHA:
            incX =  1; incY =  0;  break;
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
