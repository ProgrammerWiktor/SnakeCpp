#ifndef PORTALS_H_INCLUDED
#define PORTALS_H_INCLUDED


/// Funkcja rysująca portale.
///
/// Zadaniem funkcji jest narysiwanie dówch portalów.
/// @param portals[] Tablica struktur zawierających współrzędne portali
/// @param portal_image Wskaźnik na obraz portalu
void draw_portals(struct struct_portals portals[], ALLEGRO_BITMAP *portal_image);


/// Funkcja losująca współrzędne portali.
///
/// Najpierw ustawiany jest punkt startowy generatora pseudolosowego.
/// Tworzony jest wskaźnik o nazwie now oraz zmienna, która będzie przechowywać informację czy należy ponownie sprawdzić położenie portali.
/// Losowane są współrzędne dwóch portali.
/// Następnie sprawdzane jest czy nie kolidują one z samym sobą, głową snakea, ciałem snakea oraz z przeszkodami.
/// Jeżeli tak się stanie to zmienna check_required przyjmuje wartość true i losowanie portali przebiega od nowa.
/// @param portals[] Tablica struktur zawierających współrzędne portali
/// @param snake Wskaźnik na pierwszy element listy snake'a
/// @param are_obstacles_enabled Zmienna zawierająca informację czy przeszkody są aktywne
/// @param obstacles[] Tablica struktur zawierająca współrzędne przeszkód
/// @param snakeX Zmienna przechowująca współrzędną X głowy snakea
/// @param snakeY Zmienna przechowująca współrzędną Y głowy snakea
void generate_portals(struct struct_portals portals[], struct struct_snake *snake, bool are_obstacles_enabled, struct struct_obstacles obstacles[], int snakeX, int snakeY);


#endif // PORTALS_H_INCLUDED
