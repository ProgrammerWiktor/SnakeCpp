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


void generate_obstacles(struct struct_obstacles obstacles[], struct struct_food food, int snakeX, int snakeY)
{
    srand(time(0));

    for (int i=0; i<NUMBER_OF_OBSTACLES; i++)
    {
        obstacles[i].x = BORDER + rand()%((WIDTH-BORDER*2)/SNAKE_SIZE) * SNAKE_SIZE;
        obstacles[i].y = BORDER + rand()%((HEIGHT-BORDER*2)/SNAKE_SIZE) * SNAKE_SIZE;

        if (obstacles[i].x == snakeX || obstacles[i].y == snakeY)
        {
            i--;
            continue;
        }

        if (food.x == obstacles[i].x && food.y == obstacles[i].y)
            i--;
    }
}

void draw_obstacles(struct struct_obstacles obstacles[], ALLEGRO_BITMAP *brick_block_image)
{
    for (int i=0; i<NUMBER_OF_OBSTACLES; i++)
    {
        al_draw_scaled_bitmap(brick_block_image, 0, 0, 500, 500, obstacles[i].x, obstacles[i].y, SNAKE_SIZE, SNAKE_SIZE, 0);
    }
}
