#ifndef attributes_hpp
#define attributes_hpp

struct Statek
{
	int x;
	int y;
	int lives;
	int speed;
	int score;
};

struct Invader {
	int x;
	int y;
	int HP;
	int speed;
};
struct Bullets {
	int x;
	int y;
	bool live;
	int speed;

};

#endif

