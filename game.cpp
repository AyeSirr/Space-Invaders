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
enum Bound {LEFTT, RIGHTT};
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
void ShipBulletsStats(Bullets shipbullets[], int size)
{
     for(int i = 0;i<size;i++)
    {
        shipbullets[i].life = false;
        shipbullets[i].speed = 3;
    }
}
void MakeShipBullet(Bullets shipbullets[], int size)
{
    for(int i = 0;i<size;i++)
    {
        if(shipbullets[i].life)
			al_draw_filled_rectangle(shipbullets[i].x-2, shipbullets[i].y-4, shipbullets[i].x+2,shipbullets[i].y+4 , al_map_rgb(255, 255, 255));
    }
}
void StartShipBullet(Bullets shipbullets[], int size, Statek &ship)
{
    for( int i = 0; i < size; i++)
	{
		if(!shipbullets[i].life)
		{
			shipbullets[i].x = ship.x + 25;
			shipbullets[i].y = ship.y;
			shipbullets[i].life = true;
			break; // Bez break, wszystkie pociski lec¹ rownoczesnie(nakladaja sie)
		}
	}
}
void MoveShipBullet(Bullets shipbullets[], int size)
{
    for( int i = 0; i < size; i++)
	{
		if(shipbullets[i].life)
		{
			shipbullets[i].y -= shipbullets[i].speed;
			if(shipbullets[i].y < 0)
                shipbullets[i].life = false;
		}
	}
}
void InitInvaders(Invader invader1[], Invader invader2[], Invader &invader3, Invader invader4[], int size)
{
     for(int i = 0;i<size;i++)
    {
        invader1[i].HP = 25;
        invader1[i].speed = 2;
        invader1[i].x = 100;
        invader1[i].y = 250;
        invader1[i].life = false;
        invader2[i].HP = 50;
        invader2[i].speed = 2;
        invader2[i].x = 100;
        invader2[i].y = 150;
        invader2[i].life = false;
        invader4[i].HP = 75;
        invader4[i].speed = 2;
        invader4[i].x = 100;
        invader4[i].y = 100;
        invader4[i].life = false;
    }
        invader3.x = 375;
        invader3.y = 0;
        invader3.HP = 100;
        invader3.speed = 4;
        invader3.life = false;
}
void CreateInvaders(Invader invader1[], Invader invader2[], Invader &invader3, Invader invader4[], int size, Bitmaps bitmap)
{
    int spaceX;
    for(int i = 0;i<size;i++)
    {
        if(invader1[i].HP>0)
           al_draw_bitmap(bitmap.invader1, invader1[i].x+spaceX, invader1[i].y,0);
           al_draw_bitmap(bitmap.invader1, invader1[i].x+spaceX, invader1[i].y-50,0);
           al_draw_bitmap(bitmap.invader2, invader2[i].x+spaceX, invader2[i].y,0);
           al_draw_bitmap(bitmap.invader4, invader4[i].x+spaceX, invader4[i].y,0);
        spaceX +=75;
    }
           al_draw_bitmap(bitmap.invader3, invader3.x, invader3.y,0);
}
long long GiveTimeInMiliseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long Miliseconds = tv.tv_sec*1000LL + tv.tv_usec/1000;
    return Miliseconds;
}
void MoveInvaders(Invader invader1[], Invader invader2[], Invader &invader3, Invader invader4[], int size)
{
      for( int i = 0; i < size; i++)
	{
			invader1[i].x += invader1[i].speed;
			 if (invader1[i].x > 210 || invader1[i].x < 0) {  invader1[i].speed *= -1;  invader1[i].x += invader1[i].speed; }
			 invader2[i].x += invader2[i].speed;
			 if (invader2[i].x > 210 || invader2[i].x < 0) {  invader2[i].speed *= -1;  invader2[i].x += invader2[i].speed; }
			 invader4[i].x += invader4[i].speed;
			 if (invader4[i].x > 210 || invader4[i].x < 0) {  invader4[i].speed *= -1;  invader4[i].x += invader4[i].speed; }
	}
            invader3.x += invader3.speed;
			 if (invader3.x > 750 || invader3.x < 0) {  invader3.speed *= -1;  invader3.x += invader3.speed; }
    }
void InvadersCollision(Invader invader1[], Invader invader2[], Invader &invader3, Invader invader4[],Bullets shipbullets[], Statek &ship, int Max_Bul, int Max_Inv, Bitmaps bitmap)
{
	for(int i = 0; i < Max_Bul; i++)
	{
		if(shipbullets[i].life)
		{
			for(int k =0; k < Max_Inv; k++)
			{
                {
					if(shipbullets[i].x > (invader1[k].x - 50) &&
						shipbullets[i].x < (invader1[k].x + 50) &&
						shipbullets[i].y <(invader1[k].y + 50) &&
						shipbullets[i].y > (invader1[k].y - 50))
					{
					    printf("Collision");
						shipbullets[i].life = false;
					}
				}
			}
		}
	}
}
/**
 * \brief Funkcja odpowiedzialna za glowne uruchomienie gry.
 *
 */
void GotoGame(struct Bitmaps bitmap, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, ALLEGRO_DISPLAY *display)
{
    const int Max_Bullets = 7;
    const int Max_Invaders = 8;
    bool klawisze[3] = {false, false ,false};
    bool done = false;
    Statek ship;
    Bullets shipbullets[Max_Bullets];
    Invader invader1[Max_Invaders];
    Invader invader2[Max_Invaders];
    Invader invader3;
    Invader invader4[Max_Invaders];
    int pos_x, pos_y;
    srand(time(NULL));
    InitInvaders(invader1, invader2, invader3, invader4, Max_Invaders);
    ShipStats(ship);
    ShipBulletsStats(shipbullets, Max_Bullets);
    long long time=0;
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
                {
				MoveRight(ship);
                }
				MoveShipBullet(shipbullets, Max_Bullets);
                MoveInvaders(invader1, invader2, invader3, invader4,Max_Invaders);
                InvadersCollision(invader1, invader2, invader3,invader4, shipbullets, ship, Max_Bullets, Max_Invaders, bitmap);
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
				StartShipBullet(shipbullets, Max_Bullets, ship);
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
			MakeShipBullet(shipbullets, Max_Bullets);
			CreateInvaders(invader1, invader2, invader3, invader4, Max_Invaders, bitmap);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
}
