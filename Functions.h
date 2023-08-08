#pragma once
#ifndef _Functions_H_
#define _Functions_H_

#define ScreenWidth 1280
#define ScreenHeight 720
#define WallSize 96

class Room;

#include <list>
#include "Enemy.h"
#include "Player.h"
#include "Room.h"

using namespace sf;

//Funkcja wyliczająca kierunek poruszania przez wektor bazowy
Vector2f CalculateDirection(Vector2f To, Vector2f From);

//Funkcja która zwraca wskaźnik na pokój o właściwym indeksie
Room* FindRoom(std::list<Room>* Rooms, Vector2f Index);

//Funkcja tworząca mape pokoi
std::list<Room> GenerateMap(int Seed);

#endif // !_Functions_H_