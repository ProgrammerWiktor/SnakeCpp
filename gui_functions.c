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


void draw_background(ALLEGRO_BITMAP *board_image)
{
    al_clear_to_color(al_map_rgb(83, 184, 116));
    al_draw_bitmap(board_image, BORDER, BORDER, 0);
    al_draw_rectangle(BORDER, BORDER, WIDTH-BORDER, HEIGHT-BORDER, al_map_rgb(0, 0, 0), 2);
}

void draw_points(ALLEGRO_FONT *font, int points)
{
    al_draw_textf(font, al_map_rgb(0, 0, 0), BORDER, 10, 0, "Punkty: %d", points);
}

void display_the_result(ALLEGRO_FONT *font, ALLEGRO_FONT *font2, int points)
{
    const int window_size_x = 700;
    const int window_size_y = 400;
    const int button_size_x = 200;
    const int button_size_y = 80;
    const int window_position_x = (WIDTH-window_size_x)/2;
    const int window_position_y = (HEIGHT-window_size_y)/2;
    const int button_position_x = WIDTH/4;
    const int button_position_y = HEIGHT/1.7;

    al_draw_filled_rounded_rectangle(window_position_x, window_position_y, window_position_x+window_size_x, window_position_y+window_size_y, 10, 10, al_map_rgb(230, 230, 230));
    al_draw_rounded_rectangle(window_position_x, window_position_y, window_position_x+window_size_x, window_position_y+window_size_y, 10, 10, al_map_rgb(0, 0, 0), 1);

    al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH/2, HEIGHT/3, ALLEGRO_ALIGN_CENTER, "Zakończyłeś grę z wynikiem:");
    al_draw_textf(font2, al_map_rgb(0, 0, 0), WIDTH/2, HEIGHT/2.25, ALLEGRO_ALIGN_CENTER, "%d", points);

    al_draw_filled_rounded_rectangle(button_position_x, button_position_y, button_position_x+button_size_x, button_position_y+button_size_y, 15, 15, al_map_rgb(182, 255, 117));
    al_draw_rounded_rectangle(button_position_x, button_position_y, button_position_x+button_size_x, button_position_y+button_size_y, 15, 15, al_map_rgb(116, 156, 81), 1);
    al_draw_text(font, al_map_rgb(0, 0, 0), button_position_x+button_size_x/2, button_position_y+button_size_y/2-25/2, ALLEGRO_ALIGN_CENTER, "Menu");

    al_draw_filled_rounded_rectangle(WIDTH-button_position_x-button_size_x, button_position_y, WIDTH-button_position_x, button_position_y+button_size_y, 15, 15, al_map_rgb(182, 255, 117));
    al_draw_rounded_rectangle(WIDTH-button_position_x-button_size_x, button_position_y, WIDTH-button_position_x, button_position_y+button_size_y, 15, 15, al_map_rgb(116, 156, 81), 1);
    al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH-button_position_x-button_size_x/2, button_position_y+button_size_y/2-25/2, ALLEGRO_ALIGN_CENTER, "Jeszcze raz!");
}

void display_the_menu(ALLEGRO_FONT *font, ALLEGRO_FONT *font2, ALLEGRO_BITMAP *menu_image, bool are_obstacles_enabled, bool is_faster_speed_enabled, bool is_acceleration_enabled, bool are_portals_enabled)
{
    const int button_size_x = 200;
    const int button_size_y = 80;
    const int button_position_x = 50;
    const int button_position_y = 60;


    al_draw_bitmap(menu_image, 0, 0, 0);

    al_draw_text(font2, al_map_rgb(0, 0, 0), WIDTH-100, HEIGHT-75, ALLEGRO_ALIGN_CENTER, "Snake");

    al_draw_filled_rounded_rectangle(button_position_x, button_position_y, button_position_x+button_size_x, button_position_y+button_size_y, 15, 15, al_map_rgb(182, 255, 117));
    al_draw_rounded_rectangle(button_position_x, button_position_y, button_position_x+button_size_x, button_position_y+button_size_y, 15, 15, al_map_rgb(116, 156, 81), 2);
    al_draw_text(font, al_map_rgb(0, 0, 0), button_position_x+button_size_x/2, button_position_y+button_size_y/2-25/2, ALLEGRO_ALIGN_CENTER, "Zagraj");

    al_draw_filled_rounded_rectangle(button_position_x, button_position_y+100, button_position_x+button_size_x, button_position_y+button_size_y+100, 15, 15, al_map_rgb(182, 255, 117));
    al_draw_text(font, al_map_rgb(0, 0, 0), button_position_x+button_size_x/2, button_position_y+button_size_y/2-25/2+100, ALLEGRO_ALIGN_CENTER, "Przeszkody");

    if (are_obstacles_enabled)
        al_draw_rounded_rectangle(button_position_x, button_position_y+100, button_position_x+button_size_x, button_position_y+button_size_y+100, 15, 15, al_map_rgb(80, 158, 11), 4);
    else
        al_draw_rounded_rectangle(button_position_x, button_position_y+100, button_position_x+button_size_x, button_position_y+button_size_y+100, 15, 15, al_map_rgb(207, 41, 19), 4);

    al_draw_filled_rounded_rectangle(button_position_x, button_position_y+200, button_position_x+button_size_x, button_position_y+button_size_y+200, 15, 15, al_map_rgb(182, 255, 117));
    al_draw_text(font, al_map_rgb(0, 0, 0), button_position_x+button_size_x/2, button_position_y+button_size_y/2-25/2+200, ALLEGRO_ALIGN_CENTER, "Szybkość");

    if (is_faster_speed_enabled)
        al_draw_rounded_rectangle(button_position_x, button_position_y+200, button_position_x+button_size_x, button_position_y+button_size_y+200, 15, 15, al_map_rgb(80, 158, 11), 4);
    else
        al_draw_rounded_rectangle(button_position_x, button_position_y+200, button_position_x+button_size_x, button_position_y+button_size_y+200, 15, 15, al_map_rgb(207, 41, 19), 4);

    al_draw_filled_rounded_rectangle(button_position_x, button_position_y+300, button_position_x+button_size_x, button_position_y+button_size_y+300, 15, 15, al_map_rgb(182, 255, 117));
    al_draw_text(font, al_map_rgb(0, 0, 0), button_position_x+button_size_x/2, button_position_y+button_size_y/2-25/2+300, ALLEGRO_ALIGN_CENTER, "Przyspieszenie");

    if (is_acceleration_enabled)
        al_draw_rounded_rectangle(button_position_x, button_position_y+300, button_position_x+button_size_x, button_position_y+button_size_y+300, 15, 15, al_map_rgb(80, 158, 11), 4);
    else
        al_draw_rounded_rectangle(button_position_x, button_position_y+300, button_position_x+button_size_x, button_position_y+button_size_y+300, 15, 15, al_map_rgb(207, 41, 19), 4);

    al_draw_filled_rounded_rectangle(button_position_x, button_position_y+400, button_position_x+button_size_x, button_position_y+button_size_y+400, 15, 15, al_map_rgb(182, 255, 117));
    al_draw_text(font, al_map_rgb(0, 0, 0), button_position_x+button_size_x/2, button_position_y+button_size_y/2-25/2+400, ALLEGRO_ALIGN_CENTER, "Portale");

    if (are_portals_enabled)
        al_draw_rounded_rectangle(button_position_x, button_position_y+400, button_position_x+button_size_x, button_position_y+button_size_y+400, 15, 15, al_map_rgb(80, 158, 11), 4);
    else
        al_draw_rounded_rectangle(button_position_x, button_position_y+400, button_position_x+button_size_x, button_position_y+button_size_y+400, 15, 15, al_map_rgb(207, 41, 19), 4);

    al_draw_filled_rounded_rectangle(button_position_x, button_position_y+500, button_position_x+button_size_x, button_position_y+button_size_y+500, 15, 15, al_map_rgb(182, 255, 117));
    al_draw_rounded_rectangle(button_position_x, button_position_y+500, button_position_x+button_size_x, button_position_y+button_size_y+500, 15, 15, al_map_rgb(116, 156, 81), 2);
    al_draw_text(font, al_map_rgb(0, 0, 0), button_position_x+button_size_x/2, button_position_y+button_size_y/2-25/2+500, ALLEGRO_ALIGN_CENTER, "Wyjdź");
}
