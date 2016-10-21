
#ifndef SRC_BITS_H_
#define SRC_BITS_H_



typedef int tipo_snake[10][10];

tipo_snake vivora =
   {{15,15,15,15,15,15,15,15,15},
    {15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
    {15,15,15,15,15,15,15,15,15}};

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

tipo_snake fruta_bits =
   {{0 ,0 ,0 ,15,15,15, 0 ,0 ,0 },
    {0 ,0 ,0 ,15,15,15, 0 ,0 ,0 },
	{0 ,0 ,0 ,15,15,15, 0 ,0 ,0 },
	{15,15,15, 0 ,0 ,0 ,15,15,15},
    {15,15,15, 0, 0, 0, 15,15,15},
    {15,15,15, 0, 0, 0, 15,15,15},
	{0, 0, 0 ,15,15,15, 0, 0, 0 },
    {0, 0 ,0 ,15,15,15, 0, 0, 0 },
    {0 ,0 ,0 ,15,15,15, 0, 0, 0 }};

tipo_snake cabeza_a_derecha =
   {{15,15,15,15,15,15,15,15,15},
    {15,15,15,15,15,0 ,0 ,15,15},
	{15,15,15,15,15,0 ,0 ,0 ,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,0 ,0 ,0 ,15},
	{15,15,15,15,15,0 ,0 ,15,15},
    {15,15,15,15,15,15,15,15,15}};

tipo_snake cabeza_a_izquierda =
   {{15,15,15,15,15,15,15,15,15},
    {15,15,0 ,0 ,15,15,15,15,15},
	{15,0 ,0 ,0 ,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,0 ,0 ,0 ,15,15,15,15,15},
	{15,15,0 ,0 ,15,15,15,15,15},
    {15,15,15,15,15,15,15,15,15}};

tipo_snake cabeza_arriba =
   {{15,15,15,15,15,15,15,15,15},
    {15,15,0 ,15,15,15,0 ,15,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
    {15,15,15,15,15,15,15,15,15}};

tipo_snake cabeza_abajo =
   {{15,15,15,15,15,15,15,15,15},
    {15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,15,15,15,15,15,15,15,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,0 ,0 ,15,15,15,0 ,0 ,15},
	{15,15,0 ,15,15,15,0 ,15,15},
    {15,15,15,15,15,15,15,15,15}};



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


#endif /* SRC_BITS_H_ */
