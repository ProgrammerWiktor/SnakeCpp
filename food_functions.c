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


void generate_food(struct struct_food *food, struct struct_snake *snake, bool are_obstacles_enabled, bool are_portals_enabled, struct struct_obstacles obstacles[], struct struct_portals portals[], int snakeX, int snakeY)
{
    srand(time(0));

    struct struct_snake *now = snake;
    bool check_required;

    do
    {
        food->x = BORDER + rand()%((WIDTH-BORDER*2)/SNAKE_SIZE) * SNAKE_SIZE;
        food->y = BORDER + rand()%((HEIGHT-BORDER*2)/SNAKE_SIZE) * SNAKE_SIZE;

        check_required = false;

        if (snakeX == food->x && snakeY == food->y)
        {
            check_required = true;
            continue;
        }

        while (now != NULL)
        {
            if (now->x == food->x && now->y == food->y)
            {
                check_required = true;
                continue;
            }

            now = now->next;
        }


        if (are_obstacles_enabled)
        {
            for (int i=0; i<NUMBER_OF_OBSTACLES; i++)
            {
                if (obstacles[i].x == food->x && obstacles[i].y == food->y)
                {
                    check_required = true;
                    continue;
                }
            }
        }

        if (are_portals_enabled)
        {
            if ((food->x == portals[0].x && food->y == portals[0].y) || (food->x == portals[1].x && food->y == portals[1].y))
            {
                check_required = true;
                continue;
            }
        }
    } while (check_required);
}

void draw_food(struct struct_food food, ALLEGRO_BITMAP *apple_image)
{
    al_draw_scaled_bitmap(apple_image, 0, 0, 128, 128, food.x, food.y, SNAKE_SIZE, SNAKE_SIZE, 0);
}
