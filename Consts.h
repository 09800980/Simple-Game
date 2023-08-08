#ifndef _CONSTS_H_
#define _CONSTS_H_

#include <chrono>

//Rozmiary Okna
#define ScreenWidth 1280
#define ScreenHeight 720
#define WallSize 96

//Typy dla Kierunku i Statusu
enum Direction { Left, Top, Right, Bottom};
enum Status { Walk, Hurt, Death, DeathEnd};

typedef std::chrono::high_resolution_clock::time_point TimePoint;
typedef std::chrono::high_resolution_clock TimeClock;
typedef std::chrono::duration<float> TimeFloat;

#endif // !_CONSTS_H_