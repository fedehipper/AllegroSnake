#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <errno.h>
#include <stdbool.h>


#define POS_X_INI 150
#define POS_Y_INI 100

#define INC_X_INI -1
#define INC_Y_INI 0

#define PAUSA 150

#define TEC_ARRIBA KEY_W
#define TEC_ABAJO KEY_S
#define TEC_IZQDA KEY_A
#define TEC_DCHA KEY_D

int posX, posY; // posiciones actuales
int incX, incY; // incremento de la posicion
int futX, futY; // posiciones futuras

int tecla = 0;



int main(void) {
	allegro_init();
	install_keyboard();
	install_timer();
	set_color_depth(32);
	request_refresh_rate(70);




//	BITMAP *bmp = create_bitmap(640, 480);
//	clear_bitmap(bmp);

	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0) != 0) {
		set_gfx_mode(GFX_AUTODETECT_WINDOWED, 0, 0, 0, 0);
		allegro_message("Incapaz de entrar a modo grafico\n%s\n", allegro_error);
		return 1;
	}

	rect(screen, 10, 10, 630, 470, palette_color[15]);

	do {
		futX = posX + incX;
		futY = posY + incY;

		line(screen, posX, posY, futX, futY, palette_color[15]);
		posX = futX;
		posY = futY;

		if(keypressed()) {
			tecla = readkey() >> 8;
			switch(tecla) {
			case TEC_ARRIBA:
				incX = 0;
				incY = -1;
				break;
			case TEC_ABAJO:
				incX = 0;
				incY = 1;
				break;
			case TEC_IZQDA:
				incX = -1;
				incY = 0;
				break;
			case TEC_DCHA:
				incX = 1;
				incY = 0;
				break;
			}
		}
		rest(PAUSA);

	}
	while(TRUE);


	readkey();

//	int a,w,s,d;
//	a = 10;
//	w = 10;
//	s = 10;
//	d = 10;
//
//
//	while(!key[KEY_ESC]) {
//
//
//		if(key[KEY_A]) rectfill(screen, a++, w, d, s, palette_color[15]);
//		if(key[KEY_W]) rectfill(screen, a, w++, d, s, palette_color[15]);
//		if(key[KEY_D]) rectfill(screen, a, w, d++, s, palette_color[15]);
//		if(key[KEY_S]) rectfill(screen, a, w, d, s++, palette_color[15]);
//
//		readkey();
//
//
//
//	}
//	do
//	{
//	  /*Actualizar reloj y pantalla, mover nave, etc */
//	}
//	while  ( ! keypressed () );
//	teclaPulsada = readkey();
//
//	remove_keyboard();
	//destroy_bitmap(bmp);

	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
