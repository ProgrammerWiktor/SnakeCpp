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


void restart_game(struct struct_snake **snake, int *snakeX, int *snakeY, int *points, int *direction, int *status)
{
    while (*snake)
    {
        struct struct_snake *next = (*snake)->next;
        free(*snake);
        *snake = next;
    }

    *snakeX = WIDTH/2;
    *snakeY = HEIGHT/2;
    *points = 0;
    *direction = 0;
    *status = 1;
}
