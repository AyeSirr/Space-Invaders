#ifndef attributes_hpp
#define attributes_hpp
/**
 * @brief Klasa przechowujaca statystyki statku kosmicznego.
 *
 * @param Statek::x wspó³rzedna szerokosci statku.
 * @param Statek::y wspó³rzedna wysokosci statku.
 * @param Statek::lives zdrowie gracza.
 * @param Statek::speed predkosc poruszania sie statku gracza.
 * @param Statek::score wynik gracza.
 */
class Statek
{
    public:
	int x;
	int y;
	int lives;
	int speed;
	int score;
};
/**
 * @brief Klasa przechowujaca statystyki przeciwnikow rozgrywki.
 *
 * @param Statek::x wspó³rzedna x pojawienia sie wroga.
 * @param Statek::y wspó³rzedna y pojawienia sie wroga.
 * @param Statek::HP zdrowie wroga.
 * @param Statek::life okresla czy wrog jest martwy czy zywy.
 * @param Statek::speed predkosc poruszania sie wroga.
 */
class Invader {
    public:
	int x;
	int y;
	int HP;
	bool life;
	int speed;
};
/**
 * @brief Klasa przechowujaca statystyki pociskow gracza jak i wroga.
 *
 * @param Statek::x wspó³rzedna x pojawienia sie pocisku.
 * @param Statek::y wspó³rzedna y pojawienia sie pocisku.
 * @param Statek::life okresla czy pocisk zostal wykorzystany.
 * @param Statek::speed predkosc poruszania sie pocisku.
 */
class Bullets {
    public:
	int x;
	int y;
	bool life;
	int speed;

};

#endif

