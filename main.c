#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "structures.h"
#include "obstacles.h"
#include "food.h"
#include "snake.h"
#include "gui.h"
#include "game.h"
#include "portals.h"

#define WIDTH 1000
#define HEIGHT 700
#define SNAKE_SIZE 30
#define BORDER 50
#define NUMBER_OF_OBSTACLES 10


/// Funkcja główna main.
///
/// Na początku inicjowane są porzebne komponenty tupu ekran, koleja, czasomerz, czcionki.
/// Sprawdzane jest powodzenie inicjalizacji Allegro 5 i w przypadku gdy to nie nastąpi poprawnie wyświetlane jest powiadomienie oraz zakończenie programu.
/// Tworzone jest okno gry o podanych wielkościach i położeniu oraz jego nazwa.
/// Następują również inicjalizacje funkcji rysujących kształty, klawiatury, obsługi czcionek i czcionek typu True Type Fonts oraz innych ich funkcjonalności.
/// Tworzona jest kolejka wydarzeń, czasomierz, który będzie odpowiadał za odświeżanie gry oraz ładowane są czcionki o określonych wielkościach.
/// Rejestrowane są źródła zdarzeń - klawiatury, okna i czasomierza.
/// Ładowane są wszystkie dźwięki gry.
/// Następnie inicjowane są potrzebne zmienne, obiekt struktury jedzenia, wskaźnik o nazwie snake oraz tablica struktur portali.
/// Do listy dowawana jest pierwsza pozycja snake'a.
/// Losowana jest pierwsza pozycja jedzenia oraz uruchamiany jest czasomierz.
/// W pętli, która będzie wykonywać się przez cały czas działania programu tworzony jest event oraz następuje pobranie z samej góry kolejki event'u, który trafił do niej jako pierwszy i nasępnie wpisanie go do obiektu event.
/// Tworzony jest stan klawiatury oraz zapisywany jest jej stan w strukturze wskazywanej przez KeyState.
/// W warunku obsługiwane jest wyłączenie gry poprzez przycisk X oraz po wystąpieniu event'u czasomierza przypisanie do redraw prawdy.
/// W następnych warunkach określany jest stan gry taki jak menu, gra i wynik oraz uruchamiane są odpowiednie funkcje dla każego stanu.
/// Podczas statusu menu wyświetlane jest tło oraz przyciski. Użytkownik może wybrać kliknięciem myszki co chce dalej zrobić.
/// Podczas statusu gry obsługiwana jest klawiatura. W zależności od tego jaki przycisk kliknął użytkownik odpowiednia wartość kierunku ruchu jest przypisywana do zmiennej.
/// Jeżeli redraw jest prawdą i kolejka jest pusta wykonywane są następne funkcje.
/// Wywoływane jest rysowanie tła, liczby punktów, jedzenia i uruchamiana jest funkcja move dzięki, której snake może się poruszać.
/// Następnie sprawdzane są warunki takie jak natrafienie snake'a na ścianę, na samego siebie lub na jedzenie.
/// W dwóch pierwszych przypadkach jeżeli funkcje zwrócą prawdę dalsze funkcje nie są wywoływane.
/// Jeżeli snake natrafi na jedzenie nie jest usuwany jego ogon jak to dzieje się normalnie podczas jego ruchu.
/// Dodawane są punkty i snake jest rysowany.
/// Jeżeli użytkownik przegra, inicjowany jest status wyniku.
/// Następuje wtedy wyświetlenie końcowego podsumowania o grze oraz program czeka na kliknięcie myszą odpowiedniego przycisku.
/// Jeżeli nastąpi wyjście z gry niszczone są elementy takie jak okno, sterwonik klawiatury, czasomierz, kolejka, czcionki, bitmapy, dźwięki aby zwolnić pamięć.
int main()
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *font2;

    if (!al_init())
    {
        al_show_native_message_box(NULL, "Error", "Gra napotka³a niespodziewany problem", "Nie uda³o siê zainicjalizowaæ biblioteki Allegro 5", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    display = al_create_display(WIDTH, HEIGHT);
    al_set_window_position(display, 250, 40);
    al_set_window_title(display, "Snake");

    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();

    ALLEGRO_BITMAP *menu_image = al_load_bitmap("images/snake_menu.png");
    ALLEGRO_BITMAP *apple_image = al_load_bitmap("images/apple.png");
    ALLEGRO_BITMAP *brick_block_image = al_load_bitmap("images/brick_block.png");
    ALLEGRO_BITMAP *board_image = al_load_bitmap("images/board.png");

    ALLEGRO_BITMAP *snake_head_up = al_load_bitmap("images/snake_head_up.png");
    ALLEGRO_BITMAP *snake_head_right = al_load_bitmap("images/snake_head_right.png");
    ALLEGRO_BITMAP *snake_head_down = al_load_bitmap("images/snake_head_down.png");
    ALLEGRO_BITMAP *snake_head_left = al_load_bitmap("images/snake_head_left.png");
    ALLEGRO_BITMAP *snake_tail_up = al_load_bitmap("images/snake_tail_up.png");
    ALLEGRO_BITMAP *snake_tail_right = al_load_bitmap("images/snake_tail_right.png");
    ALLEGRO_BITMAP *snake_tail_down = al_load_bitmap("images/snake_tail_down.png");
    ALLEGRO_BITMAP *snake_tail_left = al_load_bitmap("images/snake_tail_left.png");
    ALLEGRO_BITMAP *snake_little_up = al_load_bitmap("images/snake_little_up.png");
    ALLEGRO_BITMAP *snake_little_right = al_load_bitmap("images/snake_little_right.png");
    ALLEGRO_BITMAP *snake_little_down = al_load_bitmap("images/snake_little_down.png");
    ALLEGRO_BITMAP *snake_little_left = al_load_bitmap("images/snake_little_left.png");
    ALLEGRO_BITMAP *portal_image = al_load_bitmap("images/portal.png");

    al_reserve_samples(5);

    ALLEGRO_SAMPLE *backgroud_music = al_load_sample("sounds/Battleship.ogg");
    ALLEGRO_SAMPLE *apple_crunch_sound = al_load_sample("sounds/apple_crunch.wav");
    ALLEGRO_SAMPLE *punch_sound = al_load_sample("sounds/punch.wav");
    ALLEGRO_SAMPLE *confirmation_sound = al_load_sample("sounds/confirmation.wav");
    ALLEGRO_SAMPLE *portal_sound = al_load_sample("sounds/portal.wav");

    queue = al_create_event_queue();
    timer = al_create_timer(1.0/6);
    font = al_load_font("fonts/Roboto-Regular.ttf", 25, 0);
    font2 = al_load_font("fonts/Roboto-Bold.ttf", 40, 0);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());



    int working = true;
    int points = 0;
    enum directions {UP = 1, RIGHT, BOTTOM, LEFT};
    int direction = 0;
    int snakeX = WIDTH/2;
    int snakeY = HEIGHT/2;
    int redraw = true;
    int status = 0;
    bool are_obstacles_enabled = false;
    bool is_faster_speed_enabled = false;
    bool is_arrow_cursor_activated = false;
    bool is_acceleration_enabled = false;
    bool are_portals_enabled = false;


    struct struct_food food;
    struct struct_obstacles obstacles[NUMBER_OF_OBSTACLES];
    struct struct_portals portals[2];

    struct struct_snake *snake = NULL;
    snake = push(snakeX, snakeY, direction, snake);

    al_play_sample(backgroud_music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);

    al_start_timer(timer);

    while (working)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        ALLEGRO_KEYBOARD_STATE KeyState;
        al_get_keyboard_state(&KeyState);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            working = false;

        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        if (status == 0)
        {
            int mouse_x, mouse_y;

            const int button_size_x = 200;
            const int button_size_y = 80;
            const int button_position_x = 50;
            const int button_position_y = 60;

            is_arrow_cursor_activated = false;

            display_the_menu(font, font2, menu_image, are_obstacles_enabled, is_faster_speed_enabled, is_acceleration_enabled, are_portals_enabled);

            if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
            }


            if (mouse_x >= button_position_x && mouse_x <= button_position_x+button_size_x)
            {
                if (mouse_y >= button_position_y && mouse_y <= button_position_y+button_size_y)
                {
                    is_arrow_cursor_activated = true;

                    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    {
                        al_play_sample(confirmation_sound, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                        restart_game(&snake, &snakeX, &snakeY, &points, &direction, &status);

                        generate_food(&food, snake, are_obstacles_enabled, are_portals_enabled, obstacles, portals, snakeX, snakeY);

                        snake = push(snakeX, snakeY, direction, snake);

                        if (are_obstacles_enabled)
                                generate_obstacles(obstacles, food, snakeX, snakeY);

                        if (are_portals_enabled)
                            generate_portals(portals, snake, are_obstacles_enabled, obstacles, snakeX, snakeY);
                    }
                }
            }

            if (mouse_x >= button_position_x && mouse_x <= button_position_x+button_size_x)
            {
                if (mouse_y >= button_position_y+100 && mouse_y <= button_position_y+button_size_y+100)
                {
                    is_arrow_cursor_activated = true;

                    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    {
                        al_play_sample(confirmation_sound, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                        if (!are_obstacles_enabled)
                            are_obstacles_enabled = true;
                        else
                            are_obstacles_enabled = false;
                    }
                }
            }

            if (mouse_x >= button_position_x && mouse_x <= button_position_x+button_size_x)
            {
                if (mouse_y >= button_position_y+200 && mouse_y <= button_position_y+button_size_y+200)
                {
                    is_arrow_cursor_activated = true;

                    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    {
                        al_play_sample(confirmation_sound, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                        if (!is_faster_speed_enabled)
                        {
                            is_faster_speed_enabled = true;

                            al_set_timer_speed(timer, 1.0/15);
                        }
                        else
                        {
                            is_faster_speed_enabled = false;

                            al_set_timer_speed(timer, 1.0/6);
                        }
                    }
                }
            }

            if (mouse_x >= button_position_x && mouse_x <= button_position_x+button_size_x)
            {
                if (mouse_y >= button_position_y+300 && mouse_y <= button_position_y+button_size_y+300)
                {
                    is_arrow_cursor_activated = true;

                    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    {
                        al_play_sample(confirmation_sound, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                        if (!is_acceleration_enabled)
                            is_acceleration_enabled = true;
                        else
                            is_acceleration_enabled = false;
                    }
                }
            }

            if (mouse_x >= button_position_x && mouse_x <= button_position_x+button_size_x)
            {
                if (mouse_y >= button_position_y+400 && mouse_y <= button_position_y+button_size_y+400)
                {
                    is_arrow_cursor_activated = true;

                    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    {
                        al_play_sample(confirmation_sound, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                        if (!are_portals_enabled)
                            are_portals_enabled = true;
                        else
                            are_portals_enabled = false;
                    }
                }
            }

            if (mouse_x >= button_position_x && mouse_x <= button_position_x+button_size_x)
            {
                if (mouse_y >= button_position_y+500 && mouse_y <= button_position_y+button_size_y+500)
                {
                    is_arrow_cursor_activated = true;

                    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    {
                        working = false;
                    }
                }
            }

            if (is_arrow_cursor_activated)
                al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
            else
                al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);

        }
        else if (status == 1)
        {
            al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);

            if ((al_key_down(&KeyState, ALLEGRO_KEY_UP) || al_key_down(&KeyState, ALLEGRO_KEY_W)) && direction != BOTTOM)
                direction = UP;
            else if ((al_key_down(&KeyState, ALLEGRO_KEY_RIGHT) || al_key_down(&KeyState, ALLEGRO_KEY_D)) && direction != LEFT)
                direction = RIGHT;
            else if ((al_key_down(&KeyState, ALLEGRO_KEY_DOWN) || al_key_down(&KeyState, ALLEGRO_KEY_S)) && direction != UP)
                direction = BOTTOM;
            else if ((al_key_down(&KeyState, ALLEGRO_KEY_LEFT) || al_key_down(&KeyState, ALLEGRO_KEY_A)) && direction != RIGHT)
                direction = LEFT;


            if (redraw && al_is_event_queue_empty(queue))
            {
                redraw = false;

                draw_background(board_image);
                draw_points(font, points);

                draw_food(food, apple_image);

                move(direction, &snakeX, &snakeY, are_portals_enabled, portals, portal_sound);

                if (are_obstacles_enabled)
                {
                    draw_obstacles(obstacles, brick_block_image);

                    if (check_for_collision_with_obstacles(snakeX, snakeY, obstacles, &status))
                    {
                        al_play_sample(punch_sound, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        continue;
                    }
                }

                if (are_portals_enabled)
                {
                    draw_portals(portals, portal_image);
                }

                if (check_for_collision_with_border(snakeX, snakeY, &status))
                {
                    al_play_sample(punch_sound, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    continue;
                }

                if (check_for_collision_with_body(snake, snakeX, snakeY, &status, points))
                {
                    al_play_sample(punch_sound, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    continue;
                }


                if (check_for_collision_with_food(snakeX, snakeY, food))
                {
                    points++;
                    al_play_sample(apple_crunch_sound, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                    if (is_acceleration_enabled)
                    {
                        if (is_faster_speed_enabled)
                            al_set_timer_speed(timer, 1.0/(15 + points));
                        else
                            al_set_timer_speed(timer, 1.0/(6 + points));
                    }

                    if (are_portals_enabled)
                    {
                        if (points%2 == 0 && points != 0)
                            generate_portals(portals, snake, are_obstacles_enabled, obstacles, snakeX, snakeY);
                    }

                    generate_food(&food, snake, are_obstacles_enabled, are_portals_enabled, obstacles, portals, snakeX, snakeY);
                }
                else
                {
                    pop_back(&snake);
                }

                snake = push(snakeX, snakeY, direction, snake);

                draw_snake(snake, snake_head_up, snake_head_right, snake_head_down, snake_head_left, snake_tail_up, snake_tail_right, snake_tail_down, snake_tail_left, snake_little_up, snake_little_right, snake_little_down, snake_little_left);
            }
        }
        else if (status == 2)
        {
            int mouse_x;
            int mouse_y;

            const int button_size_x = 200;
            const int button_size_y = 80;
            const int button_position_x = WIDTH/4;
            const int button_position_y = HEIGHT/1.7;

            is_arrow_cursor_activated = false;

            if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
            }

            if (mouse_x >= WIDTH-button_position_x-button_size_x && mouse_x <= WIDTH-button_position_x)
            {
                if (mouse_y >= button_position_y && mouse_y <= button_position_y+button_size_y)
                {
                    is_arrow_cursor_activated = true;

                    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    {
                        al_play_sample(confirmation_sound, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                        restart_game(&snake, &snakeX, &snakeY, &points, &direction, &status);

                        generate_food(&food, snake, are_obstacles_enabled, are_portals_enabled, obstacles, portals, snakeX, snakeY);

                        snake = push(snakeX, snakeY, direction, snake);

                        if (are_obstacles_enabled)
                            generate_obstacles(obstacles, food, snakeX, snakeY);

                        if (are_portals_enabled)
                            generate_portals(portals, snake, are_obstacles_enabled, obstacles, snakeX, snakeY);

                        if (is_faster_speed_enabled)
                            al_set_timer_speed(timer, 1.0/15);
                        else
                            al_set_timer_speed(timer, 1.0/6);
                    }
                }
            }

            if (mouse_x >= button_position_x && mouse_x <= button_position_x+button_size_x)
            {
                if (mouse_y >= button_position_y && mouse_y <= button_position_y+button_size_y)
                {
                    is_arrow_cursor_activated = true;

                    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    {
                        al_play_sample(confirmation_sound, 4.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                        status = 0;

                        if (is_faster_speed_enabled)
                            al_set_timer_speed(timer, 1.0/15);
                        else
                            al_set_timer_speed(timer, 1.0/6);
                    }
                }
            }

            if (is_arrow_cursor_activated)
                al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
            else
                al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);


            draw_background(board_image);
            draw_food(food, apple_image);
            draw_snake(snake, snake_head_up, snake_head_right,snake_head_down, snake_head_left, snake_tail_up, snake_tail_right, snake_tail_down, snake_tail_left, snake_little_up, snake_little_right, snake_little_down, snake_little_left);

            if (are_obstacles_enabled)
                draw_obstacles(obstacles, brick_block_image);

            if (are_portals_enabled)
                draw_portals(portals, portal_image);

            display_the_result(font, font2, points);
        }

        al_flip_display();
    }

    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_font(font);
    al_destroy_font(font2);
    al_destroy_bitmap(menu_image);
    al_destroy_bitmap(apple_image);
    al_destroy_bitmap(brick_block_image);
    al_destroy_bitmap(board_image);
    al_destroy_bitmap(snake_head_up);
    al_destroy_bitmap(snake_head_right);
    al_destroy_bitmap(snake_head_down);
    al_destroy_bitmap(snake_head_left);
    al_destroy_bitmap(snake_tail_up);
    al_destroy_bitmap(snake_tail_right);
    al_destroy_bitmap(snake_tail_down);
    al_destroy_bitmap(snake_tail_left);
    al_destroy_bitmap(snake_little_up);
    al_destroy_bitmap(snake_little_right);
    al_destroy_bitmap(snake_little_down);
    al_destroy_bitmap(snake_little_left);
    al_destroy_bitmap(portal_image);
    al_destroy_sample(backgroud_music);
    al_destroy_sample(apple_crunch_sound);
    al_destroy_sample(punch_sound);
    al_destroy_sample(confirmation_sound);
    al_destroy_sample(portal_sound);

    return 0;
}
