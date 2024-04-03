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


void draw_snake(struct struct_snake *snake, ALLEGRO_BITMAP *snake_head_up, ALLEGRO_BITMAP *snake_head_right, ALLEGRO_BITMAP *snake_head_down, ALLEGRO_BITMAP *snake_head_left,
                ALLEGRO_BITMAP *snake_tail_up, ALLEGRO_BITMAP *snake_tail_right, ALLEGRO_BITMAP *snake_tail_down, ALLEGRO_BITMAP *snake_tail_left,
                ALLEGRO_BITMAP *snake_little_up, ALLEGRO_BITMAP *snake_little_right, ALLEGRO_BITMAP *snake_little_down, ALLEGRO_BITMAP *snake_little_left)
{
    struct struct_snake *now = snake;
    int i=0;
    int previous_direction = now->direction;

    while (now != NULL)
    {
        if (i==0 && now->next == NULL)
        {
            if (now->direction == 0 || now->direction == 1)
                al_draw_bitmap(snake_little_up, now->x, now->y, 0);
            else if (now->direction == 2)
                al_draw_bitmap(snake_little_right, now->x, now->y, 0);
            else if (now->direction == 3)
                al_draw_bitmap(snake_little_down, now->x, now->y, 0);
            else
                al_draw_bitmap(snake_little_left, now->x, now->y, 0);
        }
        else if (i==0)
        {
            if (now->direction == 0 || now->direction == 1)
                al_draw_bitmap(snake_head_up, now->x, now->y, 0);
            else if (now->direction == 2)
                al_draw_bitmap(snake_head_right, now->x, now->y, 0);
            else if (now->direction == 3)
                al_draw_bitmap(snake_head_down, now->x, now->y, 0);
            else
                al_draw_bitmap(snake_head_left, now->x, now->y, 0);
        }
        else if (now->next == NULL)
        {
            if (previous_direction == 1)
                al_draw_bitmap(snake_tail_up, now->x, now->y, 0);
            else if (previous_direction == 2)
                al_draw_bitmap(snake_tail_right, now->x, now->y, 0);
            else if (previous_direction == 3)
                al_draw_bitmap(snake_tail_down, now->x, now->y, 0);
            else
                al_draw_bitmap(snake_tail_left, now->x, now->y, 0);
        }
        else
        {
            al_draw_filled_rectangle(now->x, now->y, now->x+SNAKE_SIZE, now->y+SNAKE_SIZE, al_map_rgb(42, 212, 48));
        }

        i++;
        previous_direction = now->direction;
        now = now->next;
    }
}

struct struct_snake *push(int snakeX, int snakeY, int direction, struct struct_snake *snake)
{
    struct struct_snake *new_node = (struct struct_snake *)malloc(sizeof(struct struct_snake));

    if (new_node != NULL)
    {
        new_node->x = snakeX;
        new_node->y = snakeY;
        new_node->direction = direction;
        new_node->next = snake;
        snake = new_node;
    }

    return snake;
}

void pop_back(struct struct_snake **snake)
{
    if ((*snake)->next == NULL)
    {
        *snake = NULL;
    }
    else
    {
        struct struct_snake *now = *snake;

        while (now->next->next != NULL)
        {
            now = now->next;
        }

        free(now->next);
        now->next = NULL;
    }
}

void move(int direction, int *snakeX, int *snakeY, bool are_portals_enabled, struct struct_portals portals[], ALLEGRO_SAMPLE *portal_sound)
{
    if (are_portals_enabled)
    {
        if (portals[0].x == *snakeX && portals[0].y == *snakeY)
        {
            al_play_sample(portal_sound, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

            int opposite_portal_x = portals[1].x;
            int opposite_portal_y = portals[1].y;

            switch(direction)
            {
                case 1:
                    *snakeX = opposite_portal_x;
                    *snakeY = opposite_portal_y-SNAKE_SIZE;
                    break;
                case 2:
                    *snakeX = opposite_portal_x+SNAKE_SIZE;
                    *snakeY = opposite_portal_y;
                    break;
                case 3:
                    *snakeX = opposite_portal_x;
                    *snakeY = opposite_portal_y+SNAKE_SIZE;
                    break;
                case 4:
                    *snakeX = opposite_portal_x-SNAKE_SIZE;
                    *snakeY = opposite_portal_y;
                    break;
            }
        }
        else if (portals[1].x == *snakeX && portals[1].y == *snakeY)
        {
            al_play_sample(portal_sound, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

            int opposite_portal_x = portals[0].x;
            int opposite_portal_y = portals[0].y;

            switch(direction)
            {
                case 1:
                    *snakeX = opposite_portal_x;
                    *snakeY = opposite_portal_y-SNAKE_SIZE;
                    break;
                case 2:
                    *snakeX = opposite_portal_x+SNAKE_SIZE;
                    *snakeY = opposite_portal_y;
                    break;
                case 3:
                    *snakeX = opposite_portal_x;
                    *snakeY = opposite_portal_y+SNAKE_SIZE;
                    break;
                case 4:
                    *snakeX = opposite_portal_x-SNAKE_SIZE;
                    *snakeY = opposite_portal_y;
                    break;
            }
        }
        else
        {
            switch(direction)
            {
                case 1:
                    *snakeY -= SNAKE_SIZE;
                    break;
                case 2:
                    *snakeX += SNAKE_SIZE;
                    break;
                case 3:
                    *snakeY += SNAKE_SIZE;
                    break;
                case 4:
                    *snakeX -= SNAKE_SIZE;
                    break;
            }
        }
    }
    else
    {
        switch(direction)
        {
            case 1:
                *snakeY -= SNAKE_SIZE;
                break;
            case 2:
                *snakeX += SNAKE_SIZE;
                break;
            case 3:
                *snakeY += SNAKE_SIZE;
                break;
            case 4:
                *snakeX -= SNAKE_SIZE;
                break;
        }
    }
}

bool check_for_collision_with_food(int snakeX, int snakeY, struct struct_food food)
{
    if (snakeX == food.x && snakeY == food.y)
        return true;

    return false;
}

bool check_for_collision_with_border(int snakeX, int snakeY, int *status)
{
    if (snakeX > WIDTH-BORDER-SNAKE_SIZE || snakeX < BORDER || snakeY > HEIGHT-BORDER-SNAKE_SIZE || snakeY < BORDER)
    {
        *status = 2;

        return true;
    }

    return false;
}

bool check_for_collision_with_body(struct struct_snake *snake, int snakeX, int snakeY, int *status, int points)
{
    struct struct_snake *now = snake;

    while (now != NULL)
    {
        if (now->x == snakeX && now->y == snakeY && points != 0)
        {
            *status = 2;

            return true;
        }

        now = now->next;
    }

    return false;
}

bool check_for_collision_with_obstacles(int snakeX, int snakeY, struct struct_obstacles obstacles[], int *status)
{
    for (int i=0; i<NUMBER_OF_OBSTACLES; i++)
    {
        if (obstacles[i].x == snakeX && obstacles[i].y == snakeY)
        {
            *status = 2;

            return true;
        }
    }

    return false;
}
