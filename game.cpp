#include "menu.hpp"
#include "attributes.hpp"
#include "bitmaps.hpp"
#include "game.hpp"
#include "attributes.hpp"
#include <stdio.h>
#include <iostream>
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
/**
 * Typ wyliczeniowy pozwalajacy uzycie klawiszu strzalki w lewo, w prawo i spacji.
 */
enum KEYUSER {LEFT, RIGHT, SPACE};
/**
 * Szerokosc ekranu okna allegro.
 */
#define ScreenW 800
/**
 * Wysokosc ekranu okna allegro.
 */
#define ScreenH 600
/**
 * Funkcja okreslajaca statystyki statku gracza.
 *
 * @param &ship wskaźnik na obiekt klasy Statek.
 */
void ShipStats(Statek &ship)
{
    ship.x = ScreenW/2;
	ship.y = 500;
    ship.lives = 3;
    ship.score = 0;
	ship.speed = 4;
}
/**
 * Funkcja pozwalajaca poruszanie sie statkiem w lewo.
 */
void MoveLeft(Statek &ship)
{
	ship.x -= ship.speed;
	if(ship.x < 0)
		ship.x = 0;
}
/**
 * Funkcja pozwalajaca poruszanie sie statkiem w prawo.
 */
void MoveRight(Statek &ship)
{
    ship.x += ship.speed;
	if(ship.x > 750)
		ship.x = 750;
}
/**
 * Inicjacja statystyk pociskow statku.
 * @param shipbullets[] tablica obiektow klasy Bullets.
 * @param size maksymalna ilosc pociskow.
 */
void ShipBulletsStats(Bullets shipbullets[], int size)
{
     for(int i = 0;i<size;i++)
    {
        shipbullets[i].life = false;
        shipbullets[i].speed = 3;
    }
}
/**
 * Funkcja rysuje pociski gracza, gdy ich stan jest rowny true.
 */
void MakeShipBullet(Bullets shipbullets[], int size)
{
    for(int i = 0;i<size;i++)
    {
        if(shipbullets[i].life)
			al_draw_filled_circle(shipbullets[i].x, shipbullets[i].y, 3, al_map_rgb(255, 255, 255));
    }
}
/**
 * Funkcja okreslajaca miejsce rozpoczecia wedrowki pocisku gracza, sprawia, że pociski mogą zostać stworzone i można nimi manipulowac.
 */
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
/**
 * Funkcja okreslajaca predkosc i kierunek poruszania sie pociskow gracza.
 */
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
/**
 * Inicjacja statystyk pociskow wroga.
 */
void InvadersBulletsStats(Bullets invaders[], int size)
{
     for(int i = 0;i<size;i++)
    {
        invaders[i].life = false;
        invaders[i].speed = 3;
    }
}
/**
 * Funkcja tworzaca obraz graficzny wroga.
 */
void MakeInvadersBullet(Bullets invaders[], int size)
{
    for(int i = 0;i<size;i++)
    {
        if(invaders[i].life)
			al_draw_filled_circle(invaders[i].x, invaders[i].y, 3, al_map_rgb(255, 150, 255));
    }
}
/**
 * Funkcja okreslajaca miejsce rozpoczecia wedrowki pocisku wroga czyli invander3. Sprawia, że pociski mogą zostać stworzone i poddane modyfikacji.
 */
void StartInvadersBullet(Bullets invaders[], int size, Invader &invader3)
{
    int i;
    i = -1 + rand()%8;
		if(!invaders[i].life)
		{
			invaders[i].x = invader3.x + 25;
			invaders[i].y = invader3.y;
			invaders[i].life = true;
            // Bez break, wszystkie pociski lec¹ rownoczesnie(nakladaja sie)
		}
}
/**
 * Funkcja okreslajaca predkosc i kierunek poruszania sie pociskow wroga oraz koniec ich zywotnosci(po opuszczeniu granic ekranu lub gdy obiekt straci cala ilosc zdrowia.
 */
void MoveInvadersBullet(Bullets invaders[], int size, Invader &invader3)
{
    for( int i = 0; i < size; i++)
	{
		if(invaders[i].life)
		{
			invaders[i].y += invaders[i].speed;
			if(invaders[i].y > 600)
                invaders[i].life = false;
            if(invader3.HP==0){
                invaders[i].life = false;
                invaders[i].y = NULL;
            }

		}
	}
}
/**
 * Inicjacja statystyk wroga. Jako parametry sa przyjmowane tablice obiektow klasy okreslajacej charakterystyke wroga.
 */
void InitInvaders(Invader invader1[], Invader invader2[], Invader &invader3, Invader invader4[], int size)
{
     for(int i = 0;i<size;i++)
    {
        invader1[i].HP = 25;
        invader1[i].speed = 2;
        invader1[i].x = i*75 + 100;
        invader1[i].y = 200;
        invader1[i].life = true;
        invader2[i].HP = 50;
        invader2[i].speed = 2;
        invader2[i].x = i*75 + 100;
        invader2[i].y = 150;
        invader2[i].life = true;
        invader4[i].HP = 75;
        invader4[i].speed = 2;
        invader4[i].x = i*75 + 100;
        invader4[i].y = 100;
        invader4[i].life = true;
    }
        invader3.x = 375;
        invader3.y = 0;
        invader3.HP = 100;
        invader3.speed = 4;
        invader3.life = true;
}
/**
 * Funkcja tworzaca wrogow w sposob graficznym tylko wtedy, gdy im zostanie nadana "zywotnosc".
 */
void CreateInvaders(Invader invader1[], Invader invader2[], Invader &invader3, Invader invader4[], int size, Bitmaps bitmap)
{
    for(int i = 0;i<size;i++)
    {
        if(invader1[i].life)
           al_draw_bitmap(bitmap.invader1, invader1[i].x, invader1[i].y,0);
           if(invader2[i].life)
           al_draw_bitmap(bitmap.invader2, invader2[i].x, invader2[i].y,0);
           if(invader4[i].life)
           al_draw_bitmap(bitmap.invader4, invader4[i].x, invader4[i].y,0);
    }
        if(invader3.life)
           al_draw_bitmap(bitmap.invader3, invader3.x, invader3.y,0);
}
/**
 * Funkcja okreslajaca sposob poruszania sie przeciwnikow np. odbijanie sie od granic okna.
 */
void MoveInvaders(Invader invader1[], Invader invader2[], Invader &invader3, Invader invader4[], int size)
{
      for( int i = 0; i < size; i++)
	{
            if(invader1[i].life){
			invader1[i].x += invader1[i].speed;
			 if (invader1[i].x > 210 + i*75|| invader1[i].x < 0 + i*75) {  invader1[i].speed *= -1;  invader1[i].x += invader1[i].speed; invader1[i].y = invader1[i].y + 2; } }
			 if(invader2[i].life){
			 invader2[i].x += invader2[i].speed;
			 if (invader2[i].x > 210+ i*75 || invader2[i].x < 0 + i*75) {  invader2[i].speed *= -1;  invader2[i].x += invader2[i].speed; invader2[i].y = invader2[i].y + 2;} }
			 if(invader4[i].life){
			 invader4[i].x += invader4[i].speed;
			 if (invader4[i].x > 210+ i*75 || invader4[i].x < 0 + i*75) {  invader4[i].speed *= -1;  invader4[i].x += invader4[i].speed; invader4[i].y = invader4[i].y + 2;} }
	}
            if(invader3.life){
            invader3.x += invader3.speed;
			 if (invader3.x > 750 || invader3.x < 0) {  invader3.speed *= -1;  invader3.x += invader3.speed; } }
    }
/**
 * Funkcja okreslajaca kolizje kazdej tablicy obiektow przeciwnika z pociskami gracza oraz pociskow przeciwnika z statkiem gracza.
 */
void InvadersCollision(Invader invader1[], Invader invader2[], Invader &invader3, Invader invader4[],Bullets shipbullets[], Statek &ship, int Max_Bul, int Max_Inv, Bitmaps bitmap, Bullets invaders[])
{
    int Width1 = al_get_bitmap_width(bitmap.invader1);
    int Height1 = al_get_bitmap_height(bitmap.invader1);
	for(int i = 0; i < Max_Bul; i++)
	{
    if(shipbullets[i].life)
    {
    for(int k =0; k < Max_Inv; k++)
    {
            if(invader1[i].life)
                {
					if(shipbullets[i].x > (invader1[k].x - 20) &&
						shipbullets[i].x < (invader1[k].x + 30) &&
						shipbullets[i].y < (invader1[k].y + 35) &&
						shipbullets[i].y > (invader1[k].y - 35))
					{
					    shipbullets[i].life = false;
					    invader1[k].life = false;
					    invader1[k].x = NULL;
					    ship.score++;

					}
				}
                if(invader2[i].life)
                {
					if(shipbullets[i].x > (invader2[k].x - 20) &&
						shipbullets[i].x < (invader2[k].x + 30) &&
						shipbullets[i].y < (invader2[k].y + 35) &&
						shipbullets[i].y > (invader2[k].y - 35))
					{
					    shipbullets[i].life = false;
					    invader2[k].life = false;
					    invader2[k].x = NULL;
                        ship.score++;
					}
				}
				 if(invader4[i].life)
                {
					if(shipbullets[i].x > (invader4[k].x - 20) &&
						shipbullets[i].x < (invader4[k].x + 30) &&
						shipbullets[i].y < (invader4[k].y + 35) &&
						shipbullets[i].y > (invader4[k].y - 35))
					{
					    shipbullets[i].life = false;
					    invader4[k].life = false;
					    invader4[k].x = NULL;
                        ship.score++;
					}
				}
				 if(invader3.life)
                {
					if(shipbullets[i].x > (invader3.x - 20) &&
						shipbullets[i].x < (invader3.x + 30) &&
						shipbullets[i].y < (invader3.y + 35) &&
						shipbullets[i].y > (invader3.y - 35))
					{
					    shipbullets[i].life = false;
					    invader3.HP = invader3.HP - 50;
					    if(invader3.HP==0){
					    invader3.life = false;
					    invader3.x = NULL;
					    ship.score++;
					    }
					}
				}

    }
    }
    if(invaders[i].life)
    {
					if(invaders[i].x > (ship.x - 15) &&
						invaders[i].x < (ship.x + 30) &&
						invaders[i].y < (ship.y + 25) &&
						invaders[i].y > (ship.y - 25))
					{
					    invaders[i].life = false;
					    ship.lives--;

					}
	}
}
}
/**
 * @brief Funkcja odpowiedzialna za glowne uruchomienie gry.
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
    Bullets invaders[Max_Bullets];
    Invader invader1[Max_Invaders];
    Invader invader2[Max_Invaders];
    Invader invader3;
    Invader invader4[Max_Invaders];
    int pos_x, pos_y;
    srand(time(NULL));
    InitInvaders(invader1, invader2, invader3, invader4, Max_Invaders);
    ShipStats(ship);
    ShipBulletsStats(shipbullets, Max_Bullets);
    InvadersBulletsStats(invaders, Max_Bullets);
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
                StartInvadersBullet(invaders, Max_Bullets, invader3);
                MoveInvadersBullet(invaders, Max_Bullets, invader3);
				MoveShipBullet(shipbullets, Max_Bullets);
                MoveInvaders(invader1, invader2, invader3, invader4,Max_Invaders);

                InvadersCollision(invader1, invader2, invader3,invader4, shipbullets, ship, Max_Bullets, Max_Invaders, bitmap, invaders);
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
			MakeInvadersBullet(invaders, Max_Bullets);
			CreateInvaders(invader1, invader2, invader3, invader4, Max_Invaders, bitmap);
			al_draw_textf(bitmap.font24b, al_map_rgb(250,200,0), 500, 570, ALLEGRO_ALIGN_CENTER, "SCORE:  %d", ship.score);
            al_draw_textf(bitmap.font24b, al_map_rgb(250,200,0), 300, 570, ALLEGRO_ALIGN_CENTER, "HEALTH:  %d", ship.lives);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));

		}
		if(ship.score == 25)
                {
                 done = true;
                 al_draw_bitmap(bitmap.gameover, 0, 0,0);
                 al_flip_display();
                 al_rest(5);
                 StartMenu(bitmap, eventQueue, display, timer);
                }
		if(ship.lives < 1)
                {
                 done = true;
                 al_draw_bitmap(bitmap.gameover, 0, 0,0);
                 al_flip_display();
                 al_rest(5);
                 StartMenu(bitmap, eventQueue, display, timer);
                }
	}
}
