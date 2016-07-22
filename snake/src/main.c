//#include <stdio.h>
//#include <stdlib.h>
//#include <allegro.h>
//#include <stdbool.h>
//
//#define POS_X_INI 32
//#define POS_Y_INI 20
//#define INC_X_INI 1
//#define INC_Y_INI 0
//
//#define PAUSA 100
//#define ESCALA 10
//
//#define ANCHO_TROZO 10
//#define ALTO_TROZO 10
//
//#define MAX_FILAS 40
//#define MAX_COLS 64
//
//
//int mapa[MAX_FILAS][MAX_COLS] = {{0}};
//
//bool toca_pared(int pos_x, int pos_y) {
//	return pos_x >= 63 || pos_x < 1 || pos_y >= 39 || pos_y < 1;
//}
//
//BITMAP *ladrilloFondo, *comida, *jugador;
//
//typedef int tipoSnake[ANCHO_TROZO][ALTO_TROZO];
//
//tipoSnake vivora =
//   {{0,15,15,15,15,15,15,15,0},
//    {15,15,0,0,0,0,0,15,15},
//	{15,0,0,0,0,0,0,0,15},
//	{15,0,0,15,15,15,0,0,15},
//    {15,0,0,15,15,15,0,0,15},
//    {15,0,0,15,15,15,0,0,15},
//	{15,0,0,0,0,0,0,0,15},
//    {15,15,0,0,0,0,0,15,15},
//    {0,15,15,15,15,15,15,15,0}};
//
//void crear_snake() {
//	int i, j;
//	jugador = create_bitmap(10, 10);
//	clear_bitmap(jugador);
//	for(i = 0; i < ANCHO_TROZO; i++)
//		for (j = 0; j < ALTO_TROZO; j++)
//			putpixel(jugador, i, j, palette_color[vivora[j][i]]);
//}
//
//void dibujar_mapa() {
//	clear_bitmap(screen);
//	rect(screen, 10, 10, 630, 390, palette_color[15]);
//}
//
//int main(void) {
//	int tecla;
//	int pos_x, pos_y;
//	int inc_x, inc_y;
//	allegro_init();
//	install_keyboard();
//	install_timer();
//
//	set_gfx_mode(GFX_SAFE, 640, 400, 0, 0);
//	crear_snake();
//
//	dibujar_mapa();
//
//	pos_x = POS_X_INI;
//	pos_y = POS_Y_INI;
//
//	inc_x = INC_X_INI;
//	inc_y = INC_Y_INI;
//
//	do {
//		dibujar_mapa();
//		draw_sprite(screen, jugador, pos_x * ESCALA, pos_y * ESCALA);
//
//		if(toca_pared(pos_x, pos_y)) {
//			allegro_message("Game Over");
//			break;
//		}
//
//		if(keypressed()) {
//			tecla = readkey() >> 8;
//			switch(tecla) {
//			  case KEY_W:
//				  inc_x = 0; inc_y = -1;  break;
//			  case KEY_S:
//				  inc_x = 0; inc_y = 1;  break;
//			  case KEY_A:
//				  inc_x = -1; inc_y = 0;  break;
//			  case KEY_D:
//				  inc_x = 1; inc_y = 0;  break;
//			}
//		}
//
//		pos_x += inc_x;
//		pos_y += inc_y;
//
//		rest(PAUSA);
//	  }
//	  while(TRUE && tecla != KEY_ESC);
//
//	  readkey();
//	  return EXIT_SUCCESS;
//}
//END_OF_MAIN();

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <allegro.h>



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

int kbhit(void)
{
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

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

void inicio(int *tam, char campo[V][H]);
void intro_datos(char campo[V][H], int tam);
void intro_campo(char campo[V][H]);
void draw(char campo[V][H]);
void loop(char campo[V][H], int tam);
void input(char campo[V][H], int *tam, int *muerto);
void update(char campo[V][H], int tam);
void intro_datos2(char campo[V][H], int tam);


BITMAP *ladrilloFondo, *comida, *jugador;

typedef int tipoSnake[10][10];

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
	for(i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			putpixel(jugador, i, j, palette_color[vivora[j][i]]);
}

void dibujar_bordes() {
	rect(screen, 10, 10, 630, 390, palette_color[15]);
}


int main(void) {

	allegro_init();
	set_gfx_mode(GFX_SAFE, 640, 400, 0, 0);
	crear_snake();

	int tam;
	char campo[V][H];

	inicio(&tam, campo);// iniciar todos nuestros elementos
	loop(campo, tam);

	return 0;
}
END_OF_MAIN();

void draw(char campo[V][H]) {
	int i,j;

	for(i = 0 ; i < V; i++) {
		for(j = 0; j < H ; j++) {
			if(campo[i][j] != ' ')
				draw_sprite(screen, jugador, j * 10, i * 10);
		}
	}

}


void intro_campo(char campo[V][H]) {
	dibujar_bordes();
	int i, j;
	for(i = 0; i < V; i++)
		for(j = 0; j < H; j++)
			campo[i][j] = ' ';
}

// mete todos los datos en la metriz campo
void intro_datos(char campo[V][H], int tam) {
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

void inicio(int *tam, char campo[V][H]) {
	// la cabeza de nuestra serpiente
	int i;
	snake[0].x = 32;
	snake[0].y = 10;

	// tamanio de la serpiente
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


void loop(char campo[V][H], int tam) {
	int muerto = 0;
	do {
		draw(campo);
		input(campo, &tam, &muerto);
		update(campo, tam);

		sleep(1);
	}while (muerto == 0);
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
			// abajo
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

void update(char campo[V][H], int tam) {
// borrar todos los datos de la matriz
	intro_campo(campo);

	// introducir los nuevos datos

	intro_datos2(campo, tam);
}

void intro_datos2(char campo[V][H], int tam) {
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

	// ahora con la fruta
	campo[fruta.y][fruta.x] = '%';


}
