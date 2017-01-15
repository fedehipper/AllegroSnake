#ifndef SRC_FUNCIONES_DRAW_H_
#define SRC_FUNCIONES_DRAW_H_
#define ALTO 40
#define ANCHO 64

void crear_cuerpo(void);
void crear_caracter(char tecla_caracter);
void crear_selector(void);
void crear_comida(int numero_fruta_ramdom);
void crear_cabeza(int tecla_dir);
void dibujar_bordes(int pos_ancho, int pos_alto, BITMAP *pantalla);
void draw(char campo[ALTO][ANCHO], int puntaje_record, int puntaje_actual, int tecla, int *tecla_anterior, BITMAP *pantalla);
void dibujar_titulo_gusano(int color, BITMAP *pantalla);
void dibujar_niveles(BITMAP *pantalla);
void atenuar_colores_titulo(int *color, int *retraso);
void seleccionar_nivel(char campo[ALTO][ANCHO], int *nivel, BITMAP *pantalla);
void game_over(BITMAP *pantalla);
void you_win(BITMAP *pantalla);


#endif /* SRC_FUNCIONES_DRAW_H_ */
