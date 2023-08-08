#include "Bullet.h"
/**
 * @file Bullet.h
 * @brief Plik nagłówkowy zawierający deklarację klasy Bullet.
 */

 /**
  * @class Bullet
  * @brief Klasa reprezentująca strały.
  */

/**
 * @brief Konstruktor klasy Bullet.
 *
 * @param _LoadFromFile Ścieżka do pliku z teksturą pocisku.
 * @param _Position Pozycja pocisku.
 * @param _Direction Kierunek ruchu pocisku.
 */
Bullet::Bullet(String _LoadFromFile, Vector2f _Position, Vector2f _Direction) :GameSprite(_LoadFromFile, _Position)
{
    Direction = _Direction;
    SetScale(Vector2f(0.8f, 0.8f));
}

/**
 * @brief Metoda do aktualizacji pozycji pocisku i rysowania go na ekranie.
 *
 * @param window Referencja do obiektu RenderWindow, na którym rysowany jest pocisk.
 * @param LocalTime Czas lokalny.
 */
void Bullet::Update(RenderWindow& window, float LocalTime)
{
    _Sprite.move(Direction * BulletSpeed * LocalTime);
    window.draw(_Sprite);
}
