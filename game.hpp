#ifndef game_hpp
#define game_hpp
#include "attributes.hpp"
#include "bitmaps.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
void GotoGame(struct Bitmaps bitmap, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, ALLEGRO_DISPLAY *display);


#endif




