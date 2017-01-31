#include "menu.hpp"
#include "attributes.hpp"
#include "bitmaps.hpp"
#include "game.hpp"
#include "attributes.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

enum KEYUSER {LEFT, RIGHT, SPACE};
/**
 * Szerokosc ekranu okna allegro.
 */
#define ScreenW 800
/**
 * Wysokosc ekranu okna allegro.
 */
#define ScreenH 600


void ShipStats(Statek &ship)
{
    ship.x = ScreenW/2;
	ship.y = 500;
    ship.lives = 5;
    ship.score = 0;
	ship.speed = 4;
}
void MoveLeft(Statek &ship)
{
	ship.x -= ship.speed;
	if(ship.x < 0)
		ship.x = 0;
}
void MoveRight(Statek &ship)
{
    ship.x += ship.speed;
	if(ship.x > 750)
		ship.x = 750;
}
/**
 * \brief Funkcja odpowiedzialna za glowne uruchomienie gry.
 *
 */
void GotoGame(struct Bitmaps bitmap, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, ALLEGRO_DISPLAY *display) {

    bool klawisze[3] = {false, false ,false};
    bool done = false;
    Statek ship;
    int pos_x, pos_y;
    srand(time(NULL));
    ShipStats(ship);
   while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);
        bool redraw = true;
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			if(klawisze[LEFT])
				MoveLeft(ship);
			else if(klawisze[RIGHT])
				MoveRight(ship);
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				klawisze[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				klawisze[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				klawisze[SPACE] = true;
				break;
				}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				klawisze[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				klawisze[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				klawisze[SPACE] = false;
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(eventQueue))
		{
			redraw = false;
            al_draw_bitmap(bitmap.tlo1, 0, 0,0);
			al_draw_bitmap(bitmap.ship, ship.x, ship.y,0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
}
