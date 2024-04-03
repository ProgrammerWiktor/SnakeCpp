#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED


/// Funkcja losująca położenie jedzenia.
///
/// Najpierw ustawiany jest punkt startowy generatora pseudolosowego.
/// Tworzony jest wskaźnik o nazwie now oraz zmienna, która będzie przechowywać informację czy należy ponownie sprawdzić położenie jedzenia.
/// W pętli losowana jest pozycja jedzenia, a następnie sprawdzane jest czy nie koliduje ona z ciałem snakea, przeszkodami oraz z portalami.
/// Jeżeli tak by się stało to zmienna check_required jest ustawiana na true i jedzenie losowane jest ponownie.
/// @param food Wskaźnik na strukturę jedzenia
/// @param snake Wskaźnik na pierwszy element listy snake'a
/// @param are_obstacles_enabled Zmienna przechowująca informację czy przeszkody są aktywne
/// @param are_portals_enabled Zmienna przechowująca informację czy portale są aktywne
/// @param obstacles[] Tablica struktur zawierająca współrzędne przeszkód
/// @param portals[] Tablica struktur zawierająca współrzędne portali
/// @param snakeX Zmienna przechowującą współrzędną X głowy snakea
/// @param snakeY Zmienna przechowująca współrzędną Y głowy snakea
void generate_food(struct struct_food *food, struct struct_snake *snake, bool are_obstacles_enabled, bool are_portals_enabled, struct struct_obstacles obstacles[], struct struct_portals portals[], int snakeX, int snakeY);


/// Funkcja wyświetlająca jedzenie.
///
/// Zadaniem funkcji jest narysowanie jabłka, które reprezentuje jedzenie.
/// @param food Wskaźnik na strukturę jedzenia
/// @param apple_image Deklaracja wskaźnika na obraz jabłka
void draw_food(struct struct_food food, ALLEGRO_BITMAP *apple_image);



#endif // FOOD_H_INCLUDED
