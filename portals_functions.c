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

void draw_portals(struct struct_portals portals[], ALLEGRO_BITMAP *portal_image)
{
    al_draw_bitmap(portal_image, portals[0].x, portals[0].y, 0);
    al_draw_bitmap(portal_image, portals[1].x, portals[1].y, 0);
}

void generate_portals(struct struct_portals portals[], struct struct_snake *snake, bool are_obstacles_enabled, struct struct_obstacles obstacles[], int snakeX, int snakeY)
{
    srand(time(0));

    struct struct_snake *now = snake;
    bool check_required;

    do
    {
        portals[0].x = (BORDER + SNAKE_SIZE) + rand()%((WIDTH-SNAKE_SIZE*2-BORDER*2)/SNAKE_SIZE) * SNAKE_SIZE;
        portals[0].y = (BORDER + SNAKE_SIZE) + rand()%((HEIGHT-SNAKE_SIZE*2-BORDER*2)/SNAKE_SIZE) * SNAKE_SIZE;

        portals[1].x = (BORDER + SNAKE_SIZE) + rand()%((WIDTH-SNAKE_SIZE*2-BORDER*2)/SNAKE_SIZE) * SNAKE_SIZE;
        portals[1].y = (BORDER + SNAKE_SIZE) + rand()%((HEIGHT-SNAKE_SIZE*2-BORDER*2)/SNAKE_SIZE) * SNAKE_SIZE;

        check_required = false;

        if (portals[0].x == portals[1].x && portals[0].y == portals[1].y)
        {
            check_required = true;
            continue;
        }

        if ((snakeX == portals[0].x && snakeY == portals[0].y) || (snakeX == portals[1].x && snakeY == portals[1].y))
        {
            check_required = true;
            continue;
        }

        while (now != NULL)
        {
            if ((now->x == portals[0].x && now->y == portals[0].y) || (now->x == portals[1].x && now->y == portals[1].y))
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
                if ((obstacles[i].x == portals[0].x && obstacles[i].y == portals[0].y) || (obstacles[i].x == portals[1].x && obstacles[i].y == portals[1].y))
                {
                    check_required = true;
                    continue;
                }
            }
        }
    } while (check_required);
}
