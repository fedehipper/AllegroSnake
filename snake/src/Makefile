SOURCES = funciones_snake.c snake.c
HEADERS = bits.h funciones_snake.h

snake : snake.o funciones_snake.o
	gcc -o snake snake.o funciones_snake.o -lalleg

snake.o : snake.c $(HEADERS)
	gcc -c snake.c -lalleg

funciones_snake.o : funciones_snake.c $(HEADERS)
	gcc -c funciones_snake.c
	
clean:
	rm -f snake \
		snake.o funciones_snake.o puntaje_record.txt

send:
		tar zcvf snake.tar $(SOURCES) $(HEADERS) Makefile


