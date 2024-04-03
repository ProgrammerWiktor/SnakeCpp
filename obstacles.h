#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED


/// Funkcja losująca współrzędne przeszkód.
///
/// Na początku uruchamiany jest generator liczb pseudolosowych.
/// Następnie wykonuje się pętla, podczas której losowane są współrzędne przeszkód.
/// Jeżeli jednak przeszkoda wylosuje się w miejscu gdzie jest snake lub jedzenie, to losowanie przeszkody następuje ponownie.
/// @param obstacles[] Tablica struktur zawierająca współrzędne przeszkód
/// @param food Struktura zawierająca współrzędne jedzenia
/// @param snakeX Wskaźnik na współrzędną x głowy snake'a
/// @param snakeY Wskaźnik na współrzędną y głowy snake'a
void generate_obstacles(struct struct_obstacles obstacles[], struct struct_food food, int snakeX, int snakeY);


/// Funkcja rysująca przeszkody.
///
/// W pętli rysowane są przeszkody.
/// @param obstacles[] Tablica struktur zawierająca współrzędne przeszkód
/// @param brick_block_image Deklaracja wskaźnika na obraz przeszkody
void draw_obstacles(struct struct_obstacles obstacles[], ALLEGRO_BITMAP *brick_block_image);



#endif // OBSTACLES_H_INCLUDED
