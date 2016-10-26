#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

#define ESCALA 10
#define ALTO_CHAR 15
#define ANCHO_CHAR 13
#define ALTO 40
#define ANCHO 64
#define FLECHA_COORDENADA_X 23
#define POS_SELECT_LEVEL 140
#define RETRASO_ATENUAR_TITULO 50
#define LIMITE_SNAKE 2560
#define ESCALA 10
#define TAMANIO_INICIAL 4
#define TOTAL_FRUTAS 2556
#define MAX_DIGITOS_PUNTAJE 4
#define FLECHA_COORDENADA_X 23
#define CANTIDAD_FRUTAS 6



typedef int tipo_snake[10][10];

tipo_snake vivora =
   {{0 ,15,15,15,15,15,15,15,0 },
    {15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
    {0 ,15,15,15,15,15,15,15,0 }};

tipo_snake flecha_seleccion =
   {{0 ,0 ,0 ,0 ,15,0 ,0 ,0 ,0 },
	{0 ,0 ,0 ,0 ,0 ,15,0 ,0 ,0 },
	{0 ,0 ,0 ,0 ,0 ,0 ,15,0 ,0 },
	{0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,0 },
    {15,15,15,15,15,15,15,15,15},
    {0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,0 },
    {0 ,0 ,0 ,0 ,0 ,0 ,15,0 ,0 },
	{0 ,0 ,0 ,0 ,0 ,15,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,15,0 ,0 ,0 ,0 }};

tipo_snake fruta_uno =
   {{0 ,0 ,0 ,0 ,15,0 ,0 ,0 ,0 },
	{0 ,0 ,0 ,15,0 ,15,0 ,0 ,0 },
	{0 ,0 ,15,0 ,0 ,0 ,15,0 ,0 },
	{0 ,15,0 ,15,0 ,15,0 ,15,0 },
    {15,0 ,0 ,0 ,15,0 ,0 ,0 ,15},
    {0 ,15,0 ,15,0 ,15,0 ,15,0 },
    {0 ,0 ,15,0 ,0 ,0 ,15,0 ,0 },
	{0 ,0 ,0 ,15,0 ,15,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,15,0 ,0 ,0 ,0 }};


tipo_snake fruta_dos =
   {{0 ,0 ,0 ,15,15,15, 0 ,0 ,0 },
    {0 ,0 ,0 ,15,15,15, 0 ,0 ,0 },
	{0 ,0 ,0 ,15,15,15, 0 ,0 ,0 },
	{15,15,15, 0 ,0 ,0 ,15,15,15},
    {15,15,15, 0, 0, 0, 15,15,15},
    {15,15,15, 0, 0, 0, 15,15,15},
	{0, 0, 0 ,15,15,15, 0, 0, 0 },
    {0, 0 ,0 ,15,15,15, 0, 0, 0 },
    {0 ,0 ,0 ,15,15,15, 0, 0, 0 }};

tipo_snake fruta_tres =
   {{0 ,0 ,0 ,15,15,15,0 ,0 ,0 },
	{0 ,0 ,15,15,15,15,15,0 ,0 },
	{0 ,15,15,0 ,15,0 ,15,15,0 },
	{15,15,0 ,0 ,0 ,0 ,0 ,15,15},
	{15,15,15,0 ,0 ,0 ,15,15,15},
    {15,15,0 ,0 ,0 ,0 ,0 ,15,15},
    {0 ,15,15,0 ,15,0 ,15,15,0 },
	{0 ,0 ,15,15,15,15,15,0 ,0 },
    {0 ,0 ,0 ,15,15,15,0 ,0 ,0 }};

tipo_snake fruta_cuatro =
   {{0 ,0 ,0 ,15,15,15,0 ,0 ,0 },
	{0 ,0 ,15,15,15,15,15,0 ,0 },
	{0 ,15,0 ,0 ,15,0 ,0 ,15,0 },
	{15,15,0 ,15,15,15,0 ,15,15},
	{15,15,15,15,15,15,15,15,15},
    {15,15,0 ,15,15,15,0 ,15,15},
    {0 ,15,0 ,0 ,15,0 ,0 ,15,0 },
	{0 ,0 ,15,15,15,15,15,0 ,0 },
    {0 ,0 ,0 ,15,15,15,0 ,0 ,0 }};

tipo_snake fruta_cinco =
   {{0 ,0 ,0 ,0 ,15,0 ,0 ,0 ,0 },
	{0 ,0 ,0 ,15,15,15,0 ,0 ,0 },
	{0 ,0 ,15,15,15,15,15,0 ,0 },
	{0 ,15,15,15,15,15,15,15,0 },
	{15,15,15,15,15,15,15,15,15},
    {0 ,15,15,15,15,15,15,15,0 },
	{0 ,0 ,15,15,15,15,15,0 ,0 },
	{0 ,0 ,0 ,15,15,15,0 ,0 ,0 },
    {0 ,0 ,0 ,0 ,15,0 ,0 ,0 ,0 }};

tipo_snake fruta_seis =
   {{15,15,15,0 ,0 ,0 ,15,15,15},
	{15,15,15,0 ,0 ,0 ,15,15,15},
	{15,15,15,0 ,0 ,0 ,15,15,15},
	{0 ,0 ,0 ,15,15,15,0 ,0 ,0 },
    {0 ,0 ,0 ,15,15,15,0 ,0 ,0 },
    {0 ,0 ,0 ,15,15,15,0 ,0 ,0 },
    {15,15,15,0 ,0 ,0 ,15,15,15},
	{15,15,15,0 ,0 ,0 ,15,15,15},
    {15,15,15,0 ,0 ,0 ,15,15,15}};

tipo_snake cabeza_a_derecha =
   {{0 ,15,15,15,15,15,15,15,0 },
    {15,15,15,15,15,0 ,0 ,15,15},
	{15,15,15,15,15,0 ,0 ,0 ,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,0 ,0 ,0 ,15},
	{15,15,15,15,15,0 ,0 ,15,15},
    {0 ,15,15,15,15,15,15,15,0 }};

tipo_snake cabeza_a_izquierda =
   {{0 ,15,15,15,15,15,15,15,0 },
    {15,15,0 ,0 ,15,15,15,15,15},
	{15,0 ,0 ,0 ,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,0 ,0 ,0 ,15,15,15,15,15},
	{15,15,0 ,0 ,15,15,15,15,15},
    {0 ,15,15,15,15,15,15,15,0 }};

tipo_snake cabeza_arriba =
   {{0 ,15,15,15,15,15,15,15,0 },
    {15,15,0 ,15,15,15,0 ,15,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
    {0 ,15,15,15,15,15,15,15,0 }};

tipo_snake cabeza_abajo =
   {{0 ,15,15,15,15,15,15,15,0 },
    {15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,15,0 ,15,15,15,0 ,15,15},
    {0 ,15,15,15,15,15,15,15,0 }};



typedef int tipo_char[15][13];

tipo_char t_caracter_s =
		 {{0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,15,15 },
		  {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 }};

tipo_char t_caracter_e =
		 {{15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		  {15,15,15,0 ,0 ,0, 0 ,0 ,0 ,0 ,0 ,0 ,0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0, 0 ,0 ,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15}};

tipo_char t_caracter_l =
		 {{15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15}};

tipo_char t_caracter_c =
		 {{0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, 0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 }};


tipo_char t_caracter_v =
		 {{15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {0 ,15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15,0 },
		  {0 ,15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15,0 },
		  {0 ,15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15,0 },
		  {0 ,0 ,15,15,15,0 ,0 ,0 ,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,0 ,0 ,0 ,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,0 ,0 ,0 ,15,15,15,0 ,0 },
		  {0 ,0 ,0 ,15,15,15,0 ,15,15,15,0 ,0 ,0 },
		  {0 ,0 ,0 ,15,15,15,0 ,15,15,15,0 ,0 ,0 },
		  {0 ,0 ,0 ,15,15,15,0 ,15,15,15,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,15,15,15,15,15,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,15,15,15,15,15,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,15,15,15,15,15,0 ,0 ,0 ,0 }};


tipo_char t_caracter_t =
		 {{15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 }};

tipo_char t_caracter_o =
		 {{0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 }};

tipo_char t_caracter_r =
		 {{15,15,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0, 0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,15,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15,15,0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15,0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15}};

tipo_char t_caracter_g =
		 {{0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		  {15,15,15,0 ,0 ,0 ,0 ,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,15,15,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,15,15,15,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,15,15,15,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 }};

tipo_char t_caracter_a =
		 {{0 ,0 ,0 ,0 ,15,15,15,15,15,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,15,15,15,15,15,15,15,0 ,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,15,15,15,15,0 ,0 ,0 ,15,15,15,15,0 },
		  {15,15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15}};

tipo_char t_caracter_m =
		 {{15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15,15},
		  {15,15,15,15,15,0 ,0 ,0 ,15,15,15,15,15},
		  {15,15,15,15,15,15,0 ,15,15,15,15,15,15},
		  {15,15,15,0 ,15,15,15,15,15,0 ,15,15,15},
		  {15,15,15,0 ,0 ,15,15,15,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,15,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15}};

tipo_char t_caracter_y =
		 {{15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {0 ,15,15,15,15,15,15,15,15,15,15,15,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 }};

tipo_char t_caracter_u =
		 {{15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 },
		  {0 ,0 ,15,15,15,15,15,15,15,15,15,0 ,0 }};

tipo_char t_caracter_w =
		 {{15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,15,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,15,15,15,0 ,0 ,15,15,15},
		  {15,15,15,0 ,15,15,15,15,15,0 ,15,15,15},
		  {15,15,15,15,15,15,0 ,15,15,15,15,15,15},
		  {15,15,15,15,15,0 ,0 ,0 ,15,15,15,15,15},
		  {15,15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15}};

tipo_char t_caracter_i =
		 {{15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15},
		  {15,15,15,15,15,15,15,15,15,15,15,15,15}};

tipo_char t_caracter_n =
		 {{15,15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,15,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,15,15,15,0 ,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,15,15,15,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,15,15,15,0 ,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,15,15,15,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,15,15,15,0 ,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,15,15,15,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,15,15,15,0 ,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,15,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,15,15,15,15,15},
		  {15,15,15,0 ,0 ,0 ,0 ,0 ,0 ,15,15,15,15}};

tipo_char t_caracter_exclamacion =
		 {{0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,15,15,15,15,15,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,15,15,15,15,15,15,15,0 ,0 ,0 },
		  {0 ,0 ,0 ,15,15,15,15,15,15,15,0 ,0 ,0 },
		  {0 ,0 ,0 ,15,15,15,15,15,15,15,0 ,0 ,0 },
		  {0 ,0 ,0 ,15,15,15,15,15,15,15,0 ,0 ,0 },
		  {0 ,0 ,0 ,15,15,15,15,15,15,15,0 ,0 ,0 },
		  {0 ,0 ,0 ,15,15,15,15,15,15,15,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,15,15,15,15,15,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 },
		  {0 ,0 ,0 ,0 ,0 ,15,15,15,0 ,0 ,0 ,0 ,0 }};


typedef struct {
	int x,y;
	int mod_x, mod_y;
	char imagen;
}snk;

typedef struct {
	int x,y;
}frt;

snk snake[LIMITE_SNAKE];

frt fruta;

frt espacios_vacios[LIMITE_SNAKE];

BITMAP *comida, *jugador, *cabeza, *selector, *caracter;

bool direccion_vertical(int tecla, int tecla_anterior) {
	return (tecla_anterior == KEY_UP || tecla_anterior == KEY_DOWN) && (tecla == KEY_RIGHT || tecla == KEY_LEFT);
}

bool direccion_horizontal(int tecla, int tecla_anterior) {
	return (tecla_anterior == KEY_RIGHT || tecla_anterior == KEY_LEFT) && (tecla == KEY_UP || tecla == KEY_DOWN);
}

void crear_cuerpo(void) {
	int i, j;
	jugador = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(jugador);
	for(i = 0 ; i < ESCALA ; i++) {
		for (j = 0 ; j < ESCALA ; j++)
			putpixel(jugador, i, j, palette_color[vivora[j][i]]);
	}
}

void crear_caracter(char tecla_caracter) {
	int i, j;
	caracter = create_bitmap(ANCHO_CHAR, ALTO_CHAR);
	clear_bitmap(caracter);
	for(i = 0 ; i < ANCHO_CHAR ; i++) {
		for (j = 0 ; j < ALTO_CHAR ; j++) {
			switch(tecla_caracter) {
				case 's': putpixel(caracter, i, j, palette_color[t_caracter_s[j][i]]);
				break;
				case 'e': putpixel(caracter, i, j, palette_color[t_caracter_e[j][i]]);
				break;
				case 'l': putpixel(caracter, i, j, palette_color[t_caracter_l[j][i]]);
				break;
				case 'c': putpixel(caracter, i, j, palette_color[t_caracter_c[j][i]]);
				break;
				case 't': putpixel(caracter, i, j, palette_color[t_caracter_t[j][i]]);
				break;
				case 'v': putpixel(caracter, i, j, palette_color[t_caracter_v[j][i]]);
				break;
				case 'o': putpixel(caracter, i, j, palette_color[t_caracter_o[j][i]]);
				break;
				case 'g': putpixel(caracter, i, j, palette_color[t_caracter_g[j][i]]);
				break;
				case 'a': putpixel(caracter, i, j, palette_color[t_caracter_a[j][i]]);
				break;
				case 'm': putpixel(caracter, i, j, palette_color[t_caracter_m[j][i]]);
				break;
				case 'r': putpixel(caracter, i, j, palette_color[t_caracter_r[j][i]]);
				break;
				case 'y': putpixel(caracter, i, j, palette_color[t_caracter_y[j][i]]);
				break;
				case 'u': putpixel(caracter, i, j, palette_color[t_caracter_u[j][i]]);
				break;
				case 'w': putpixel(caracter, i, j, palette_color[t_caracter_w[j][i]]);
				break;
				case 'i': putpixel(caracter, i, j, palette_color[t_caracter_i[j][i]]);
				break;
				case 'n': putpixel(caracter, i, j, palette_color[t_caracter_n[j][i]]);
				break;
				case '!': putpixel(caracter, i, j, palette_color[t_caracter_exclamacion[j][i]]);
				break;
			}
		}
	}
}

void crear_selector(void) {
	int i, j;
	selector = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(selector);
	for(i = 0 ; i < ESCALA ; i++) {
		for(j = 0 ; j < ESCALA ; j++)
			putpixel(selector, i, j, palette_color[flecha_seleccion[j][i]]);
	}
}

void crear_comida(int numero_fruta_random) {
	int i, j;
	comida = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(comida);

	for(i = 0 ; i < ESCALA ; i++) {
		for (j = 0 ; j < ESCALA ; j++) {
			switch(numero_fruta_random) {
				case 1: putpixel(comida, i, j, palette_color[fruta_uno[j][i]]);
				break;
				case 2: putpixel(comida, i, j, palette_color[fruta_dos[j][i]]);
				break;
				case 3: putpixel(comida, i, j, palette_color[fruta_tres[j][i]]);
				break;
				case 4: putpixel(comida, i, j, palette_color[fruta_cuatro[j][i]]);
				break;
				case 5: putpixel(comida, i, j, palette_color[fruta_cinco[j][i]]);
				break;
				case 6: putpixel(comida, i, j, palette_color[fruta_seis[j][i]]);
				break;
			}
		}
	}
}

void crear_cabeza(int tecla_dir) {
	int i, j;
	cabeza = create_bitmap(ESCALA, ESCALA);
	clear_bitmap(cabeza);
	for(i = 0 ; i < ESCALA ; i++) {
		for(j = 0 ; j < ESCALA ; j++) {
			switch(tecla_dir) {
				case KEY_UP: putpixel(cabeza, i, j, palette_color[cabeza_arriba[j][i]]);
				break;
				case KEY_DOWN: putpixel(cabeza, i, j, palette_color[cabeza_abajo[j][i]]);
				break;
				case KEY_RIGHT: putpixel(cabeza, i, j, palette_color[cabeza_a_derecha[j][i]]);
				break;
				case KEY_LEFT: putpixel(cabeza, i, j, palette_color[cabeza_a_izquierda[j][i]]);
				break;
			}
		}
	}
}

void dibujar_bordes(int pos_ancho, int pos_alto) {
	rect(screen, ESCALA, ESCALA, ANCHO * ESCALA - pos_ancho, ALTO * ESCALA - pos_alto, palette_color[15]);
}


void draw(char campo[ALTO][ANCHO], int puntaje_record, int puntaje_actual, int tecla, int *tecla_anterior) {
	int i,j;
	clear_bitmap(screen);
	dibujar_bordes(10, 10);
	for(i = 0 ; i < ALTO ; i++) {
		for(j = 0 ; j < ANCHO ; j++) {
			if(campo[i][j] == 'X')
				draw_sprite(screen, jugador, j * ESCALA, i * ESCALA);
			if(campo[i][j] == 'Y') {
				if(direccion_vertical(tecla, *tecla_anterior) || direccion_horizontal(tecla, *tecla_anterior)) {
					crear_cabeza(tecla);
				}
				draw_sprite(screen, cabeza, j * ESCALA, i * ESCALA);
			}
			if(campo[i][j] == '%') {
				draw_sprite(screen, comida, j * ESCALA, i * ESCALA);
			}
		}
	}
	textprintf_centre_ex(screen, font, 30, 2, 15, 0, "%d", puntaje_actual);
	textprintf_centre_ex(screen, font, 610, 2, 15, 0, "%d", puntaje_record);
}

void dibujar_titulo_gusano(int color) {
	textprintf_justify_ex(screen, font, 30, 10, 20, 0, color, 0, " __________");
	textprintf_justify_ex(screen, font, 30, 10, 30, 0, color, 0, "/\\  ______ \\");
	textprintf_justify_ex(screen, font, 30, 10, 40, 0, color, 0, "\\ \\ \\____/\\_\\   __    __   ________   ________   ________   ________");
	textprintf_justify_ex(screen, font, 30, 10, 50, 0, color, 0, " \\ \\ \\  _\\/_/_ /\\ \\  /\\ \\ /\\  _____\\ /\\_____  \\ /\\  ____ \\ /\\  ____ \\");
	textprintf_justify_ex(screen, font, 30, 10, 60, 0, color, 0, "  \\ \\ \\/\\____ \\\\ \\ \\ \\ \\ \\\\ \\ \\____/_\\/_____\\  \\\\ \\ \\__/\\ \\\\ \\ \\_ /\\ \\");
	textprintf_justify_ex(screen, font, 30, 10, 70, 0, color, 0, "   \\ \\ \\/____\\ \\\\ \\ \\ \\ \\ \\\\ \\______ \\ /\\  ____ \\\\ \\ \\ \\ \\ \\\\ \\ \\ \\ \\ \\");
	textprintf_justify_ex(screen, font, 30, 10, 80, 0, color, 0, "    \\ \\ \\_____\\ \\\\ \\ \\_\\_\\ \\\\/______\\ \\\\ \\ \\__/\\ \\\\ \\ \\ \\ \\ \\\\ \\ \\_\\_\\ \\");
	textprintf_justify_ex(screen, font, 30, 10, 90, 0, color, 0, "     \\ \\_________\\\\ \\_______\\ /\\_______\\\\ \\_______\\\\ \\ \\ \\ \\ \\\\ \\_______\\");
	textprintf_justify_ex(screen, font, 30, 10, 100, 0, color, 0, "      \\/_________/ \\/_______/ \\/_______/ \\/_______/ \\/_/  \\/_/ \\________/");
}

void dibujar_string(char * un_string, int *espacio) {
	int i = 0;
	for(i = 0 ; i < strlen(un_string) ; i++) {
		crear_caracter(un_string[i]);
		draw_character_ex(screen, caracter, *espacio, POS_SELECT_LEVEL, 15, 0);
		*espacio += ANCHO_CHAR + 1;
	}
	*espacio += ANCHO_CHAR;
}

void dibujar_niveles(void) {
	int espacio_char = 250;
	dibujar_string("select", &espacio_char);
	dibujar_string("level", &espacio_char);
	textprintf_justify_ex(screen, font, 260, 10, 180, 0, 15, 0, "EASY");
	textprintf_justify_ex(screen, font, 260, 10, 200, 0, 15, 0, "MEDIUM");
	textprintf_justify_ex(screen, font, 260, 10, 220, 0, 15, 0, "PROFFESIONAL");
}


void dibujar_flecha_selector(char campo[ALTO][ANCHO], int y) {
	int i;
	clear_bitmap(screen);
	dibujar_bordes(10, 10);
	for(i = 18 ; i < FLECHA_COORDENADA_X ; i++) {
		if(campo[23][y] == 'F') {
			draw_sprite(screen, selector, FLECHA_COORDENADA_X * ESCALA, y * ESCALA);
		}
	}
}

void vaciar_flecha_selector(char campo[ALTO][ANCHO]) {
	campo[FLECHA_COORDENADA_X][18] = ' ';
	campo[FLECHA_COORDENADA_X][20] = ' ';
	campo[FLECHA_COORDENADA_X][22] = ' ';
}

void atenuar_colores_titulo(int *color, int *retraso) {
	(*retraso)++;
	rest(RETRASO_ATENUAR_TITULO);
	if(*retraso > 10 && *retraso < 20) *color = 15;
	if(*retraso < 10 && *retraso > 0) *color = 25;
	if(*retraso > 20) *retraso = 0;
}

void seleccionar_nivel(char campo[ALTO][ANCHO], int *nivel) {
	SAMPLE * sonido_flecha;
	sonido_flecha = load_sample("s_flecha.wav");
	crear_selector();
	int tecla = 0, pos_nivel = 1, flecha_y = 18, color = 15, retraso = 0;
	draw_sprite(screen, selector, 23 * ESCALA, 18 * ESCALA);

	while(true) {
		dibujar_bordes(ESCALA, ESCALA);
		dibujar_niveles();
		dibujar_titulo_gusano(color);
		atenuar_colores_titulo(&color, &retraso);

		if(keypressed()) {
			tecla = readkey() >> 8;
			*nivel = pos_nivel;
			if(tecla == KEY_ENTER) break;

			play_sample(sonido_flecha, 200, 150, 1000, 0);

			if(tecla == KEY_UP) pos_nivel--;
			if(tecla == KEY_DOWN) pos_nivel++;
			if(pos_nivel > 3) pos_nivel = 1;
			if(pos_nivel < 1) pos_nivel = 3;

			vaciar_flecha_selector(campo);
			switch(pos_nivel) {
				case 1: flecha_y = 18;
				break;
				case 2: flecha_y = 20;
				break;
				case 3: flecha_y = 22;
				break;
			}
			campo[FLECHA_COORDENADA_X][flecha_y] = 'F';
			dibujar_flecha_selector(campo, flecha_y);
		}
	}
}

void game_over(void) {
	int espacio_char = 260;
	dibujar_string("game", &espacio_char);
	dibujar_string("over", &espacio_char);
}

void you_win(void) {
	int espacio_char = 260;
	dibujar_string("you", &espacio_char);
	dibujar_string("win!", &espacio_char);
}

void inicializar_espacios_vacios(void) {
	int i;
	for(i = 0 ; i < LIMITE_SNAKE ; i++) {
		espacios_vacios[i].x = 0;
		espacios_vacios[i].y = 0;
	}
}

int llenar_espacios(char campo[ALTO][ANCHO]) {
	int i, j, tamanio = 0;
	for(j = 1 ; j < ALTO - 1 ; j++) {
		for(i = 1 ; i < ANCHO - 1 ; i++) {
			if(campo[j][i] == ' ') {
				espacios_vacios[tamanio].x = i;
				espacios_vacios[tamanio].y = j;
				tamanio++;
			}
		}
	}
	return tamanio;
}

void intro_campo(char campo[ALTO][ANCHO]) {
	int i, j;
	for(i = 0; i < ALTO; i++) {
		for(j = 0; j < ANCHO; j++) {
			campo[i][j] = ' ';
		}
	}
}

void intro_datos(char campo[ALTO][ANCHO], int tam) {
	int i;
	for(i = 1 ; i < tam ; i++) {
		snake[i].x = snake[i - 1].x - 1;
		snake[i].y = snake[i - 1].y;
		snake[i].imagen ='X';
	}
	snake[0].imagen = 'Y';

	for(i = 0 ; i < tam ; i++) {
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	campo[fruta.y][fruta.x] = '%';
}

void leer_puntaje_record(int * nivel, FILE * archivo, int *puntaje_record) {
	if(archivo != NULL) {
		fscanf(archivo, "%d", puntaje_record);
		fclose(archivo);
	}
	else
		*puntaje_record = 0;
}

void instalar_sonidos(void) {
	int driver_digi = 1, driver_midi = 0;
	detect_digi_driver(driver_digi);
	detect_midi_driver(driver_midi);
	reserve_voices(5, 5);
	install_sound(driver_digi, driver_midi, "cfg_path");
	set_volume(200, 100);
}

void inicio(int *tam, char campo[ALTO][ANCHO], int *nivel, int * puntaje_record, FILE * archivo) {
	allegro_init();
	install_keyboard();
	install_mouse();
	install_timer();

	set_gfx_mode(GFX_SAFE, ANCHO * 10, ALTO * 10, 0, 0);
	show_mouse(screen);

	instalar_sonidos();

	seleccionar_nivel(campo, nivel);
	leer_puntaje_record(nivel, archivo, puntaje_record);

	crear_cuerpo();
	srand(time(NULL));
	crear_comida(rand() % CANTIDAD_FRUTAS + 1);
	crear_cabeza(KEY_RIGHT);

	snake[0].x = 32;
	snake[0].y = 10;

	*tam = TAMANIO_INICIAL;

	fruta.x = rand() % (ANCHO - 2) + 1;
	fruta.y = rand() % (ALTO - 2) + 1;

	int i;
	for(i = 0; i < *tam ; i++) {
		snake[i].mod_x = 1;
		snake[i].mod_y = 0;
	}
	intro_campo(campo);
	intro_datos(campo, *tam);
}

void intro_datos_nuevos(char campo[ALTO][ANCHO], int tam) {
	int i;
	for(i = tam - 1 ; i > 0 ; i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	snake[0].x += snake[0].mod_x;
	snake[0].y += snake[0].mod_y;

	for(i = 0 ; i < tam ; i++)
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	campo[fruta.y][fruta.x] = '%';
}

void update(char campo[ALTO][ANCHO], int tam, int muerto) {
	intro_campo(campo);
	if(muerto == 0) intro_datos_nuevos(campo, tam);
}

void asignar_movimiento(int mov_x, int mov_y) {
	snake[0].mod_x = mov_x;
	snake[0].mod_y = mov_y;
}

void exit_snake(void) {
	int tecla = 0;
	textprintf_centre_ex(screen, font, 325, 250, 15, 0, "Press the [Enter] key to exit ...");
	while(true) {
		tecla = readkey() >> 8;
		if(tecla == KEY_ENTER) break;
	}
}

void pausa(int tecla, SAMPLE * sonido_pausa) {
	play_sample(sonido_pausa, 200, 150, 1000, 0);
	while(true) {
		tecla = readkey() >> 8;
		if(tecla == KEY_P) {
			play_sample(sonido_pausa, 200, 150, 1000, 0);
			break;
		}
	}
}

bool es_tecla_de_direccion(int tecla) {
	return tecla == KEY_UP || tecla == KEY_DOWN || tecla == KEY_RIGHT || tecla == KEY_LEFT;
}

int input(char campo[ALTO][ANCHO], int tam, int *tecla, int *muerto, int record, SAMPLE *s_comer, SAMPLE *s_pausa, SAMPLE *s_impacto, int *tecla_anterior) {
	if(*muerto == 0) {
		if(snake[0].x == 0 || snake[0].x == ANCHO - 1 || snake[0].y == 0 || snake[0].y == ALTO - 1) *muerto = 1;
	}

	if(*muerto == 0) {
		int i;
		for(i = 1 ; i < tam && *muerto == 0 ; i++)
			if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) *muerto = 1;
	}

	if(*muerto) play_sample(s_impacto, 200, 150, 1000, 0);

	if(*muerto == 0) {
		if(snake[0].x == fruta.x && snake[0].y == fruta.y) {
			play_sample(s_comer, 200, 150, 1000, 0);

			crear_comida(rand() % CANTIDAD_FRUTAS + 1);

			tam += 1;
			snake[tam - 1].imagen = 'X';

			inicializar_espacios_vacios();
			int posicion = rand() % llenar_espacios(campo);

			fruta.x = espacios_vacios[posicion].x;
			fruta.y = espacios_vacios[posicion].y;
		}
	}

	if(*muerto == 0) {
		if(keypressed()) {
			if(es_tecla_de_direccion(*tecla)) *tecla_anterior = *tecla;

			*tecla = readkey() >> 8;

			if(*tecla == KEY_P) pausa(*tecla, s_pausa);

			int mov_x = 0, mov_y = 0;

			if(*tecla == KEY_DOWN && snake[0].mod_y != -1) mov_y = 1;
			if(*tecla == KEY_UP && snake[0].mod_y != 1) mov_y = -1;
			if(*tecla == KEY_LEFT && snake[0].mod_x != 1) mov_x = -1;
			if(*tecla == KEY_RIGHT && snake[0].mod_x != -1) mov_x = 1;
			if(mov_x != 0 || mov_y != 0)
				asignar_movimiento(mov_x, mov_y);
		}
	}
	else {
		if(tam - TAMANIO_INICIAL == TOTAL_FRUTAS) {
			you_win();
		} else {
			game_over();
			textprintf_centre_ex(screen, font, 325, 210, 15, 0, "SCORE: %d", tam - TAMANIO_INICIAL);
			textprintf_centre_ex(screen, font, 325, 220, 15, 0, "RECORD: %d", record);
		}
		exit_snake();
	}
	return tam;
}

void asignar_pausa(int *pausa, int nivel) {
	switch(nivel) {
		case 1 : *pausa = 300;
		break;
		case 2 : *pausa = 150;
		break;
		case 3 : *pausa = 50;
		break;
	}
}

void loop(char campo[ALTO][ANCHO], int tam, int puntaje_record, FILE * archivo, int *nivel) {
	int muerto = 0, pausa = 0, tecla = KEY_RIGHT, tecla_anterior = KEY_RIGHT;

	asignar_pausa(&pausa, *nivel);

	SAMPLE * sonido_comer = load_sample("comer.wav");
	SAMPLE * sonido_pausa = load_sample("pause.wav");
	SAMPLE * sonido_impacto = load_sample("impact.wav");

	do {
		draw(campo, puntaje_record, tam - TAMANIO_INICIAL, tecla, &tecla_anterior);
		tam = input(campo, tam, &tecla, &muerto, puntaje_record, sonido_comer, sonido_pausa, sonido_impacto, &tecla_anterior);
		update(campo, tam, muerto);
		rest(pausa);
	} while (muerto == 0);

	int puntaje_actual = tam - 4;

	archivo = fopen("puntaje_record.txt", "w");
	(puntaje_record <= puntaje_actual) ? fprintf(archivo, "%d", puntaje_actual) : fprintf(archivo, "%d", puntaje_record);

	fclose(archivo);
}

int main(void) {
	int tam;
	char campo[40][64];
	int puntaje_record;

	FILE * archivo;
	archivo = fopen("puntaje_record.txt", "r");

	int nivel = 0;
	inicio(&tam, campo, &nivel, &puntaje_record, archivo);
	loop(campo, tam, puntaje_record, archivo, &nivel);

	allegro_exit();
	return EXIT_SUCCESS;
}
END_OF_MAIN();
