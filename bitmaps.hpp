#ifndef bitmaps_hpp
#define bitmaps_hpp
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>

/**
 * \brief Struktura przechowujaca pliki audio, bitmapy i czcionki gry.
 *
 */
struct Bitmaps
{
    ALLEGRO_BITMAP *tlo;
    ALLEGRO_BITMAP *crosshair;
    ALLEGRO_FONT *font72b;
    ALLEGRO_FONT *font48b;
    ALLEGRO_FONT *font24b;
};
struct Bitmaps CreateBitmaps(ALLEGRO_DISPLAY *display);
#endif // BITMAPS_HPP_INCLUDED
