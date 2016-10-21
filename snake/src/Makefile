SOURCES = funciones_snake.c snake.c funciones_draw.c
HEADERS = bits.h funciones_snake.h funciones_draw.h

snake : snake.o funciones_snake.o funciones_draw.o
	gcc -o snake snake.o funciones_snake.o funciones_draw.o -lalleg

snake.o : snake.c $(HEADERS)
	gcc -c snake.c -lalleg

funciones_snake.o : funciones_snake.c $(HEADERS)
	gcc -c funciones_snake.c

funciones_draw.o : funciones_draw.c $(HEADERS)
	gcc -c funciones_draw.c
	
clean:
	rm -f snake \
		snake.o funciones_snake.o funciones_draw.o puntaje_record.txt

send:
		tar zcvf snake.tar $(SOURCES) $(HEADERS) Makefile


