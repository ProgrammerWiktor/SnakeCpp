#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED


/// Funkcja wyświetlająca snake'a.
///
/// Tworzony jest wskaźnik o nazwie now.
/// Inicjowane są zmienne i oraz previous_direction przechowującą poprzedni kierunek elementu snake'a.
/// Pętla while wykonuje się tak długo aż natrafi na NULL.
/// Jeżeli pętla wykonuje się pierwszy raz i nie ma następnego elementu to rysowana jest zaokrąglona głowa snake'a dla jednego elementu.
/// Jeżeli pętla wykonuje się pierwszy raz ale następny element istnieje to rysowana jest głowa i w następnych iteracjach dorysowywane jest ciało i ogon.
/// Ogon jest rysowany przy ostatniej iteracji na podstawie kierunku z poprzedniego elementu snake'a.
/// Do now przypisywany jest wskaźnik na następny element listy, i zwiększa się o 1, a do previous_direction przypisywany jest kierunek elementu snake'a.
/// @param snake Wskaźnik na pierwszy element listy snake'a
/// @param snake_head_up Wskaźnik na obraz głowy snake'a skierowanej w górę
/// @param snake_head_right Wskaźnik na obraz głowy snake'a skierowanej w prawo
/// @param snake_head_down Wskaźnik na obraz głowy snake'a skierowanej w dół
/// @param snake_head_left Wskaźnik na obraz głowy snake'a skierowanej w lewo
/// @param snake_tail_up Wskaźnik na obraz ogona snake'a skierowanego w górę
/// @param snake_tail_right Wskaźnik na obraz ogona snake'a skierowanego w prawo
/// @param snake_tail_down Wskaźnik na obraz ogona snake'a skierowanego w dół
/// @param snake_tail_left Wskaźnik na obraz ogona snake'a skierowanego w lewo
/// @param snake_little_up Wskaźnik na obraz głowy snake'a dla jednego elementu skierowanej w górę
/// @param snake_little_right Wskaźnik na obraz głowy snake'a dla jednego elementu skierowanej w prawo
/// @param snake_little_down Wskaźnik na obraz głowy snake'a dla jednego elementu skierowanej w dół
/// @param snake_little_left Wskaźnik na obraz głowy snake'a dla jednego elementu skierowanej w lewo
void draw_snake(struct struct_snake *snake, ALLEGRO_BITMAP *snake_head_up, ALLEGRO_BITMAP *snake_head_right, ALLEGRO_BITMAP *snake_head_down, ALLEGRO_BITMAP *snake_head_left,
                ALLEGRO_BITMAP *snake_tail_up, ALLEGRO_BITMAP *snake_tail_right, ALLEGRO_BITMAP *snake_tail_down, ALLEGRO_BITMAP *snake_tail_left,
                ALLEGRO_BITMAP *snake_little_up, ALLEGRO_BITMAP *snake_little_right, ALLEGRO_BITMAP *snake_little_down, ALLEGRO_BITMAP *snake_little_left);


/// Funkcja dodająca nowy element do listy.
///
/// Najpierw następuje przydział pamięci na nowy element.
/// Jeżeli przydział pamięci okazał się sukcesem to wykonywane jest przypisanie współrzędnych nowej głowy snake'a oraz kierunku do nowego elementu listy.
/// Przypisywany jest również adres bieżący wskaźnika listy oraz adres nowego elementu.
/// @param snakeX Współrzędna x nowej głowy snake'a
/// @param snakeY Współrzędna y nowej głowy snake'a
/// @param direction Kierunek danego elementu snake'a
/// @param snake Wskaźnik na pierwszy element listy snake'a
/// @returns Zwrócenie poprzedniej wartości wskaźnika listy - parametr snake
struct struct_snake *push(int snakeX, int snakeY, int direction, struct struct_snake *snake);


/// Funkcja usuwająca element z listy.
///
/// Jeżeli lista jest jednoelementowa to następuje przypisanie NULL.
/// W przeciwnym razie tworzony jest wskaźnik o nazwie now.
/// Wykonywana jest pętla, która zatrzyma się dopiero na przedostatnim elemencie listy.
/// W tej pętli do now jest przypisywany wskaźnik na następny element tej listy.
/// Po wykonaniu pętli następuje zwolnienie pamięci przydzielonej przez malloc dla now->next oraz usunięcie now->nastepny poprzez przypisanie NULL.
/// @param snake Podwójny wskaźnik na pierwszy element listy snake'a
void pop_back(struct struct_snake **snake);


/// Funkcja zmieniająca współrzędne głowy snake'a w celu obsługi jego ruchu.
///
/// Jeżeli portale są aktywne to sprawdzane jest czy głowa snakea znalazła się w którymś z nich.
/// Jęśli tak się stanie to tworzone są zmienne przechowywujące współrzędne drugiego portalu.
/// Następnie następuje przypisanie nowej pozycji głowy snakea w zależności od kierunku ruchu.
/// Odtwarzany jest również dźwięk portalu.
/// W przypadku gdy portale nie są aktywne, nową pozycje głowy określa się jako dodanie lub odjęcie wielkośći pojedyńczego bloku snakea.
/// @param direction Zmienna, która przechowuje kierunek w jakim ma poruszać się snake
/// @param snakeX Wskaźnik na współrzędną x nowej głowy snake'a
/// @param snakeY Wskaźnik na współrzędną y nowej głowy snake'a
/// @param are_portals_enabled Zmienna przechowująca informację czy portale są aktywne
/// @param portals[] Tablica struktur zawierająca współrzędne portali
/// @param portal_sound Dźwięk portalu
void move(int direction, int *snakeX, int *snakeY, bool are_portals_enabled, struct struct_portals portals[], ALLEGRO_SAMPLE *portal_sound);


/// Funkcja sprawdzająca czy natrafiono na jedzenie.
///
/// Następuje sprawdzenie czy głowa snake'a ma takie same współrzędne jak współrzędne jedzenia.
/// Jeżeli to nastąpi to jest zwracana odpowiednia wartość.
/// @param snakeX Wskaźnik na współrzędną x nowej głowy snake'a
/// @param snakeY Wskaźnik na współrzędną y nowej głowy snake'a
/// @param food Wskaźnik na strukturę jedzenia
/// @returns Zwrócenie prawdy jeżeli natrafiono na jedzeie lub fałszu jeżeli nie natrafiono
bool check_for_collision_with_food(int snakeX, int snakeY, struct struct_food food);


/// Funkcja sprawdzająca czy przekroczono ścianę.
///
/// Jeżeli snake przekroczył współrzędne określające położenie ściany to zamieniany jest status gry na wyświetlanie końcowego wyniku oraz zwracana jest wartość.
/// @param snakeX Wskaźnik na współrzędną x nowej głowy snake'a
/// @param snakeY Wskaźnik na współrzędną y nowej głowy snake'a
/// @param status Wskaźnik na zmienną przechowującą stan gry
/// @returns Zwrócenie prawdy jeżeli natrafiono na ścianę lub fałszu jeżeli to się nie stało
bool check_for_collision_with_border(int snakeX, int snakeY, int *status);


/// Funkcja sprawdzająca czy snake natrafił na swoje ciało.
///
/// Utworzenie wskaźnika o nazwie now.
/// Pętla będzie wykonywać się tak długo aż natrafi na NULL.
/// Następuje w niej sprawdzenie czy glowa snake'a natrafiła na ciało poprzez porównanie każdych współrzędnych ciała ze współrzędnymi jedzenia.
/// Następuje również sprawdzenie czy ilość punktów nie jest równa 0, ponieważ wtedy nie ma możliwości natrafienia snake'a na swoje ciało.
/// Jeżeli porównanie wypadnie pozytywnie to następuje zmiana statusu gry na wyświetlanie wyniku końcowego oraz zwrócenie wartości.
/// @param snake Wskaźnik na pierwszy element listy snake'a
/// @param snakeY Wskaźnik na współrzędną y nowej głowy snake'a
/// @param status Wskaźnik na zmienną przechowującą stan gry
/// @param points Deklaracja zmiennej z ilością punktów
/// @returns Zwrócenie prawdy jeżeli snake natrafił na własne ciało lub fałszu jeżeli to się nie stało
bool check_for_collision_with_body(struct struct_snake *snake, int snakeX, int snakeY, int *status, int points);


/// Funkcja sprawdzająca czy snake natrafił na przeszkodę.
///
/// W pętli sprawdzane jest czy współrzędne przeszkód są takie same jak współrzędne głowy snake'a.
/// Jeżeli tak się stanie to status jest zmieniany na 2 oraz zwracana jest prawda. W przeciwnym przypadku zwracany jest fałsz.
/// @param snakeX Wskaźnik na współrzędną x głowy snake'a
/// @param snakeY Wskaźnik na współrzędną y głowy snake'a
/// @param obstacles[] Tablica struktur zawierająca współrzędne przeszkód
/// @param status Wskaźnik na zmienną ze statusem gry
/// @returns Zwrócenie prawdy jeżeli snake natrafił na przeszkodę lub fałszu w przeciwnym przypadku
bool check_for_collision_with_obstacles(int snakeX, int snakeY, struct struct_obstacles obstacles[], int *status);


#endif // SNAKE_H_INCLUDED
