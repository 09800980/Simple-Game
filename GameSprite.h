#pragma once
#ifndef _GameSprite_H_
#define _GameSprite_H_

#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace sf;

//Bazowa klasa Obiektów Gry
class GameSprite
{
private:
    Texture _Texture;
protected:
    int _PixelWidth, _PixelHeight;
    IntRect _FrameSprite;
public:
    Sprite _Sprite;
    GameSprite();
    GameSprite(String LoadFromFile, Vector2f Position, bool SetOrigin = true, int PixelWidth = 0, int PixelHeight = 0);

    //Metoda ustawiająca Skale Objektu
    void SetScale(Vector2f Scale);
    //Metoda ustawiająca pozycje Objektu
    void SetSpritePosition(Vector2f Position);
    //Metoda przesuwająca Objekt
    void MoveGameSprite(Vector2f Direction);
    //Metoda odrysowująca Objekt
    void virtual DrawSprite(RenderWindow& window);
    //Metoda zwracająca Sprite Objektu
    Sprite GetGameSprite();
};

#endif // !_GameObject_H_