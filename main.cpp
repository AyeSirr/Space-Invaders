#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <time.h>
#include "menu.hpp"
#include "bitmaps.hpp"
#include "attributes.hpp"
#include "game.hpp"
#define ScreenW 800
#define ScreenH 600
/**
 * @brief Funkcja uruchamiajaca program.
 * @brief Funkcja zawiera inicjacje biblioteki allegro - czcionki, audio, bitmapy, timer, itp.
 * @brief Funkcja przechodzi do funkcji uruchamiajaca menu gry.
 */
int main()
{
    srand(time(NULL));
    float FPS = 60;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;

    if(!al_init())                     // inicjacja allegro
    {
        return -1;
    }
    display = al_create_display(ScreenW,ScreenH); // tworzenie okna
    timer = al_create_timer(1.0/FPS);
    if(!display)                          //sprawdzanie okna
    {
        return -1;
    }
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    al_hide_mouse_cursor(display);
    al_install_keyboard();
    al_install_mouse();
    struct Bitmaps bitmap = CreateBitmaps(display);
    eventQueue = al_create_event_queue();

    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_start_timer(timer);
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));

    StartMenu(bitmap, eventQueue, display, timer);
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);          // usuwanie okna

    return 0;
}

