#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

/// Deklaracja struktury snake'a.
///
/// Zawiera ona współrzędne x i y oraz wskaźnik na nastepną strukturę.
/// @param x Współrzędna x
/// @param y Współrzędna y
/// @param direction Kierunek, w jakim w danym momencie porusza się snake
/// @param next Wskaźnik na następną strukturę
struct struct_snake
{
    int x;
    int y;
    int direction;
    struct struct_snake *next;
};


/// Deklaracja struktry jedzenia.
///
/// Zawiera ona współrzędne x i y jedzenia.
/// @param x Współrzędna x
/// @param y Współrzędna y
struct struct_food
{
    int x;
    int y;
};


/// Deklaracja struktury przeszkód.
///
/// Zawiera ona współrzędne x i y przeszkód.
/// @param x Współrzędna x
/// @param y Współrzędna y
struct struct_obstacles
{
    int x;
    int y;
};


/// Deklaracja struktury portali.
///
/// @param x Współrzędna x
/// @param y Współrzędna y
struct struct_portals
{
    int x;
    int y;
};


#endif // STRUCTURES_H_INCLUDED
