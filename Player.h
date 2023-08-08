#pragma once
#ifndef _Player_H_
#define _Player_H_

class Room;

#include "Animated.h"
#include "Bullet.h"
#include "Room.h"
#include <list>

//Klasa Gracza
class Player : public Animated
{
private:
    Vector2f Move;
    Vector2f Direction;
    const float MoveSpeed = 150.0;
    bool IsMove;
    GameSprite *Shadow;
public:
    std::list<Bullet> Bullets;
    int Damage = 2;

    Player(String _LoadFromFile, Vector2f _Position);

    //Metoda ustawienia pozycji Bohatera
    void SetPlayerPosition(Vector2f _Posiyion);
    //Metoda Kierowania Bohaterem
    void Update(RenderWindow& window, float LocalTime, Room _SelectedRoom);
    //Metoda Przemieszczenia Bohatera (Potrzebna jest tylko dla Menu)
    void DirMove(Vector2f _Direction, float Speed);
    //Metoda Strzału
    void Shot(Vector2f _Direction);
    //Metoda Odrysowania Bohatera
    void DrawSprite(RenderWindow& window) override;
    Sprite GetShadow();
};

#endif // !_Player_H_