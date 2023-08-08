#include "Animated.h"

/**
 * @file Animated.h
 * @brief Plik nagłówkowy zawierający deklarację klasy Aniamted.
 */

 /**
  * @class Animated
  * @brief Klasa reprezentująca animacje bohatera.
  */

/**
 * @brief Konstruktor klasy Animated.
 *
 * @param LoadFromFile Ścieżka do pliku z teksturą animacji.
 * @param Position Pozycja animacji.
 * @param PixelWidth Szerokość pojedynczego klatki animacji w pikselach.
 * @param PixelHeight Wysokość pojedynczego klatki animacji w pikselach.
 */
Animated::Animated(String LoadFromFile, Vector2f Position, int PixelWidth, int PixelHeight) :GameSprite(LoadFromFile, Position, true, PixelWidth, PixelHeight)
{
    top = 0;
    left = 0;
    _PixelHeight = PixelHeight;
    _PixelWidth = PixelWidth;
}

/**
 * @brief Metoda do animowania zmiany klatek.
 *
 * @param _top Indeks wiersza klatki animacji do wyświetlenia.
 * @param St Aktualny stan animacji.
 * @return Aktualny stan animacji.
 */
Status Animated::Animate(int _top, Status St)
{
    TimePoint CurrentFrameTime = TimeClock::now();
    static TimePoint PreviousFrameTime = TimeClock::now();
    TimeFloat TimeSinceLastFrame = CurrentFrameTime - PreviousFrameTime;
    static int left = 0;
    static int top = 0;
    top = _top;
    if (TimeSinceLastFrame.count() >= _FrameTime.asSeconds())
    {
        switch (St)
        {
        case Walk:
            left = (left + 1) % 4;
            PreviousFrameTime = CurrentFrameTime;
            break;
        case Hurt:
            left = ((left + 1) % 2) + 4;
            PreviousFrameTime = CurrentFrameTime;
            if (left == 5)
                St = Walk;
            break;
        case Death:
            break;
        default:
            break;
        }
    }
    _FrameSprite.left = left * _PixelWidth;
    _FrameSprite.top = top * _PixelHeight;
    Animated::top = top;
    Animated::left = left;

    _Sprite.setTextureRect(_FrameSprite);
    return St;
}
