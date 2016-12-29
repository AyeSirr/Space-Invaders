#include "bitmaps.hpp"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
/**
 * \brief Funkcja tworzaca strukture "bitmap", w kt�rej sa zapisane wszystkie bitmapy, pliki audio i czcionki potrzebne do uruchomienia gry.
 *
 */
struct Bitmaps CreateBitmaps(ALLEGRO_DISPLAY *display)
{
    struct Bitmaps bitmap;
    bitmap.tlo = al_load_bitmap("tlo.png");
    bitmap.font48b = al_load_font("Amatic-Bold.ttf", 48, 0);
    bitmap.font72b = al_load_font("Amatic-Bold.ttf", 72, 0);
    bitmap.font24b = al_load_font("Amatic-Bold.ttf", 24, 0);
    return bitmap;
};
