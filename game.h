#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


/// Funkcja restartująca grę.
///
/// W pętli while usuwany jest każdy element listy aż będzie ona pusta.
/// Następnie do zmiennych potrzebnych aby zrestartować grę, przypisywane są wartości początkowe.
/// @param snake Podwójny wskaźnik na pierwszy element listy snake'a
/// @param snakeX Wskaźnik na współrzędną x głowy snake'a
/// @param snakeY Wskaźnik na współrzędną y głowy snake'a
/// @param points Wskaźnik na zmienną przechowującą liczbę punktów
/// @param direction Wskaźnik na zmienną przechowującą kierunek poruszania się snake'a
/// @param status Wskaźnik na zmienną ze statusem gry
void restart_game(struct struct_snake **snake, int *snakeX, int *snakeY, int *points, int *direction, int *status);


#endif // GAME_H_INCLUDED
