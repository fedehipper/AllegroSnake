SOURCES = funciones_snake.c main.c
HEADERS = bits.h funciones_snake.h

main : main.o funciones_snake.o
	gcc -o main main.o funciones_snake.o -lalleg

main.o : main.c $(HEADERS)
	gcc -c main.c -lalleg

funciones_snake.o : funciones_snake.c $(HEADERS)
	gcc -c funciones_snake.c
	
clean:
	rm -f main \
		main.o funciones_snake.o

send:
		tar zcvf snake.tar $(SOURCES) $(HEADERS) Makefile


