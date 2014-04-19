#ifndef keycode_h
#define keycode_h

#include "Player.h"

struct KeyCode
{
	KeyCode(Player* _player) : player(_player) { }
	KeyCode(void) {}
	~KeyCode(void) {}

	void up()			{player->move(Player::UP);}
	void down()			{player->move(Player::DOWN);}
	void left()			{player->move(Player::LEFT);}
	void right()		{player->move(Player::RIGHT);}
private:
	Player*  player;
};

#endif