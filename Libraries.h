#ifndef _Libraries_H_
#define _Libraries_H_

class GameSprite;
class Room;
class Enemy : public Animated {};
class Player : public Animated {};

#include <SFML/Graphics.hpp>

using namespace sf;

#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <list>
#include <cmath>
#include "Consts.h"
#include "Game.h"
#include "GameSprite.h"
#include "Room.h"
#include "Animated.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Functions.h"

#endif // !_Libraries_H_