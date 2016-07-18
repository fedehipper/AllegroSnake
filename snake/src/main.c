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

	BITMAP *bmp = create_bitmap(300, 300);
	clear_bitmap(bmp);

	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);


	line(screen, 10, 10, 630, 10, palette_color[15]);
	line(screen, 10, 470, 10, 10, palette_color[15]);
	line(screen, 10, 470, 10, 10, palette_color[15]);




	while(!key[KEY_ESC]) {


	}


	remove_keyboard();
	destroy_bitmap(bmp);
	allegro_exit();
	return EXIT_SUCCESS;
}
