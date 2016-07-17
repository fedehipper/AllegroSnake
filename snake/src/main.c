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

	int x = 150;
	int y = 150;
	while(!key[KEY_ESC]) {

		if(getpixel(bmp, x, y)) continue;

		putpixel(bmp, x , y, 16);
		blit(bmp, screen, 0,0,0,0, 300, 300);
		x = key[KEY_ESC];

	}
	printf("Hola");


	remove_keyboard();
	destroy_bitmap(bmp);
	allegro_exit();
	return EXIT_SUCCESS;
}
