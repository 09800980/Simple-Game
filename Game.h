#pragma once
#ifndef _Game_H_
#define _Game_H_

#include <SFML/Graphics.hpp>
#include "Consts.h"
#include "Player.h"
#include "Enemy.h"
#include "Room.h"
#include "Functions.h"
#include <list>

//Klasa Gry
int Game(sf::RenderWindow& window);

#endif // !_Game_H_