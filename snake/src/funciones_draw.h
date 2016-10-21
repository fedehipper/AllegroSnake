#ifndef SRC_FUNCIONES_DRAW_H_
#define SRC_FUNCIONES_DRAW_H_
#define ALTO 40
#define ANCHO 64

void crear_cuerpo(void);
void crear_caracter(char tecla_caracter);
void crear_selector(void);
void crear_comida(int numero_fruta_ramdom);
void crear_cabeza(int tecla_dir);
void dibujar_bordes(int pos_ancho, int pos_alto);
void draw(char campo[ALTO][ANCHO], int puntaje_record, int puntaje_actual, int tecla, int *tecla_anterior);
void dibujar_titulo_gusano(int color);
void dibujar_niveles(void);
void dibujar_flecha_selector(char campo[ALTO][ANCHO], int y);
void vaciar_flecha_selector(char campo[ALTO][ANCHO]);
void atenuar_colores_titulo(int *color, int *retraso);
void seleccionar_nivel(char campo[ALTO][ANCHO], int *nivel);
void game_over(void);
void you_win(void);


#endif /* SRC_FUNCIONES_DRAW_H_ */
