#ifndef _Animated_H_
#define _Animated_H_

#include "Consts.h"
#include "GameSprite.h"

//Klasa Animacja (Nie pracuje tak jak powinna)
class Animated : public GameSprite
{
private:
    const Time _FrameTime = seconds(0.1);
protected:
    int top, left;
public:
    //Konstruktor dla inicjalizacji zegara
    Animated(String _LoadFromFile, Vector2f _Position, int _PixelWidth = 0, int _PixelHeight = 0);

    //Metoda zmiany kadrów
    virtual Status Animate(int top, Status St);
};

#endif // !_Animated_H_