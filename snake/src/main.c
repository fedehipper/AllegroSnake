#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <errno.h>
#include <stdbool.h>


int main(void) {
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	request_refresh_rate(70);

//	BITMAP *bmp = create_bitmap(640, 480);
//	clear_bitmap(bmp);

	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);


	line(screen, 10, 10, 630, 10, palette_color[15]);
	line(screen, 10, 470, 10, 10, palette_color[15]);
	line(screen, 630, 470, 630, 10, palette_color[15]);
	line(screen, 630, 470, 10, 470, palette_color[15]);



	int a,w,s,d;
	a = 10;
	w = 10;
	s = 10;
	d = 10;


	while(!key[KEY_ESC]) {


		if(key[KEY_A]) rectfill(screen, a++, w, d, s, palette_color[15]);
		if(key[KEY_W]) rectfill(screen, a, w++, d, s, palette_color[15]);
		if(key[KEY_D]) rectfill(screen, a, w, d++, s, palette_color[15]);
		if(key[KEY_S]) rectfill(screen, a, w, d, s++, palette_color[15]);

		readkey();



	}

	remove_keyboard();
	//destroy_bitmap(bmp);

	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
