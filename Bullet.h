#ifndef _Bullet_H_
#define _Bulet_H_

#include "GameSprite.h"

//Klasa Strału
class Bullet : public GameSprite
{
private:
    float Damage = 10;
    const float BulletSpeed = 1000.0;
    Vector2f Direction;
public:
    Bullet(String _LoadFromFile, Vector2f _Position, Vector2f _Direction);

    //Klasa odświeżająca przemieszcznie Strzału i odrysowuje ich
    void Update(RenderWindow& window, float LocalTime);
};

#endif // !_Bullet_H_