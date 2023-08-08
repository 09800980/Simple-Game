#pragma once
#ifndef _Enemy_H_
#define _Enemy_H_

#include "Animated.h"
#include "Consts.h"
#include "GameSprite.h"

using namespace sf;

//Klasa wroga
class Enemy : public Animated
{
private:
    Time _FrameTime = seconds(0.1);
    float MoveSpeed = 90.0;
    //Cień która jest potrzebna dla kolizji przemieszczania
    GameSprite* Shadow;
    int Health = 10;
    int top, left;
    Status EnemyStatus;
public:
    bool IsDead;
    bool IsDeadEnd;

    //Konstruktor wroga
    Enemy(String _LoadFromFile, Vector2f _Position);

    //Metoda odpowiadająca za naniesienie szkody Wrogu
    bool TakeDamage(int Damage);
    //Metoda poruszania wroga
    void Move(Vector2f _Direction, float LocalTime);
    //Metoda porusznia służonca tylko dla Menu
    void DirMove(Vector2f _Direction, float Speed);
    //Metoda odrysowania Wroga
    void DrawSprite(RenderWindow& window) override;
    //Metoda Animacji Wroga
    Status Animate(int top, Status St) override;
    //Metoda pobierania Cieni
    Sprite GetShadow();
};

#endif // !_Enemy_H_