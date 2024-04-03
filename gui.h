#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED


/// Funkcja wyświetlająca tło gry.
///
/// Funkcja koloruje najpierw okno na szaro.
/// Następnie rysuje planszę gry.
/// Na końcu rysuje obramówkę planszy gry
/// @param board_image Deklaracja wskaźnika na obraz planszy
void draw_background(ALLEGRO_BITMAP *board_image);


/// Funkcja wyświetlająca zdobyte punkty.
///
/// Zadaniem funkcji jest wypisanie w odpowiednim miejscu na ekranie ilośći zdobytych punktów.
/// @param font Deklaracja wskaźnika na czcionkę
/// @param points Deklaracja zmiennej z ilością punktów
void draw_points(ALLEGRO_FONT *font, int points);


/// Funkcja wyświetlająca okienko z wynikiem.
///
/// Narysowanie wypełnionego i zaokrąglonego kwadratu, który pełni rolę okienka na treść
/// Następnie narysowanie do niego obramówki.
/// Po tym wyświetlenie napisu wraz z liczbą punktów.
/// Narysowane zostają również przyciski - menu oraz jeszcze raz! wraz z treścią
/// @param font Deklaracja wskaźnika na czcionkę
/// @param font2 Deklaracja wskaźnika na czcionkę numer 2
/// @param points Deklaracja zmiennej z ilością punktów
void display_the_result(ALLEGRO_FONT *font, ALLEGRO_FONT *font2, int points);


/// Funkcja wyświetlająca menu.
///
/// Wyświetlane jest tło w postaci obrazu, na którym napisany jest tytuł gry oraz rysowane są przyciski takie jak: zagraj, przeszkody, szybkość, przyśpieszenie, portale i wyjdź.
/// Przycisk przeszkody ma obramówkę czerwoną gdy przeszkody nie są aktywne, a zieloną gdy przeszkody są aktywne.
/// Tak samo jest dla przycisku szybkośći, przyśpieszenia oraz portali.
/// @param font Deklaracja wskaźnika na czcionkę
/// @param font2 Deklaracja wskaźnika na czcionkę numer 2
/// @param menu_image Wskaźnik na zdjęcie menu
/// @param are_obstacles_enabled Zmienna przechowująca informację czy przeszkody są aktywne
/// @param is_faster_speed_enabled Zmienna przechowująca informację czy większa szybkość jest aktywna
/// @param is_acceleration_enabled Zmienna przechowująca informację czy przyśpieszenie jest aktywne
/// @param are_portals_enabled Zmienna przechowująca informację czy portale są aktywne
void display_the_menu(ALLEGRO_FONT *font, ALLEGRO_FONT *font2, ALLEGRO_BITMAP *menu_image, bool are_obstacles_enabled, bool is_faster_speed_enabled, bool is_acceleration_enabled, bool are_portals_enabled);


#endif // GUI_H_INCLUDED
