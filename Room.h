#pragma once
#ifndef _Room_H_
#define _Room_H_

//Przed deklaracja klas
class Player;
class Item;
class DamageUp;

#include "Player.h"
#include "GameSprite.h"
#include <list>
#include "Enemy.h"
#include "Functions.h"
#include "Game.h"
#include "Consts.h"
#include "Start.h"

//Klasa Pokoju
class Room
{
protected:
	Vector2f RoomPosition;
public:
	//Index pokoju odpowiadający Mapie w konsoli
	Vector2f Index;
	bool Selected;
	bool Cleared;
	bool Block;
	//Objekty do odrysowania
	GameSprite* Floor;
	GameSprite* Item;
	std::list<GameSprite> Walls;
	std::list<GameSprite> Doors;
	std::list<GameSprite> FreeDoor;
	std::list<Enemy> Enemies;
	//Koordynaty środka pokoju
	Vector2f CameraPosition;

	Room(Vector2f _RoomPosition, Vector2f _RoomIndex, int PowerUp = 0);

	//Metoda dodania ściany
	void AddWall(Direction _WallPosition);
	//Metoda Usunięncia ściany
	void DeleteWall(Direction _WallPosition);
	//Metoda dodania dźwi
	void AddDoor(Direction _WallPosition);
	//Metoda Blokująca Pokój
	void BlockRoom();
	//Metoda odblokująca Pokój
	void UnBlockRoom();
	//Metoda wybierania Pokoju do odrysowania
	void SelectRoom();
	//Metoda odświeżająca wszystkie zdażenia w pokoju
	bool Update(RenderWindow& window, float LocalTime, Player& Hero);
	//Metoda odrysowania pokoju
	void DrawRoom(RenderWindow& window, Player Hero);
};

#endif // !_Room_H_