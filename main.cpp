/**
 * @file main.cpp
 *
 * @brief Plik główny programu.
 */

#define _CRT_SECURE_NO_WARNINGS

#define ScreenWidth 1280
#define ScreenHeught 720
#define WallSize 96

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Start.h"
#include "Game.h"

using namespace sf;

/**
 * @brief Główna funkcja programu.
 *
 * @return Kod zakończenia programu.
 */
int main()
{
    // Konsola dla komunikatów błędów
    AllocConsole();
    (void)freopen("CONOUT$", "w", stdout);
    printf("Console has open");

    // Właściwości Okna
    StartMenu();
    return 0;
}
