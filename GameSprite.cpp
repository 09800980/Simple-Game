#include "GameSprite.h"

/**
 * @file GameSprite.h
 * @brief Plik nagłówkowy zawierający deklarację klasy GameSprite.
 */

 /**
  * @class GameSprite
  * @brief Klasa reprezentująca sprajt gry.
  */

  /**
	   * @brief Konstruktor obiektu GameSprite, tworzący sprajt na podstawie wczytanego pliku graficznego.
	   *
	   * @param LoadFromFile Ścieżka do pliku graficznego.
	   * @param Position Pozycja sprajtu.
	   * @param SetOrigin Określa, czy ustawić punkt odniesienia w środku sprajtu.
	   * @param PixelWidth Szerokość pojedynczego kafelka sprajtu (opcjonalne).
	   * @param PixelHeight Wysokość pojedynczego kafelka sprajtu (opcjonalne).
	   */
//Konstruktor obiektu który tworzy sprajty dla późniejszego odrysowania
GameSprite::GameSprite(String LoadFromFile, Vector2f Position, bool SetOrigin, int PixelWidth, int PixelHeight)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!_Texture.loadFromFile(LoadFromFile))
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		printf("\n%s Don`t Open", LoadFromFile.toAnsiString().c_str());
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
	_Sprite.setTexture(_Texture);
	if (PixelWidth != 0 && PixelHeight != 0)
	{
		_PixelHeight = PixelHeight;
		_PixelWidth = PixelWidth;
		_FrameSprite = IntRect(0, 0, _PixelWidth, _PixelHeight);
		_Sprite.setTextureRect(_FrameSprite);
	}
	else {
		_PixelWidth = static_cast<int>(_Sprite.getLocalBounds().width);
		_PixelHeight = static_cast<int>(_Sprite.getLocalBounds().height);
		_FrameSprite = IntRect(0, 0, 0, 0);
	}
	if (SetOrigin)
		_Sprite.setOrigin(_Sprite.getLocalBounds().width / 2, _Sprite.getLocalBounds().height / 2);
	_Sprite.setPosition(Position);
}

/**
	 * @brief Domyślny konstruktor obiektu GameSprite.
	 */
GameSprite::GameSprite()
{

}

/**
	 * @brief Ustawia skalę sprajtu.
	 *
	 * @param Scale Wektor skalujący.
	 */
void GameSprite::SetScale(Vector2f Scale)
{
	_Sprite.setScale(Scale);
}

/**
	 * @brief Zwraca sprajt gry.
	 *
	 * @return Obiekt Sprite reprezentujący sprajt gry.
	 */
Sprite GameSprite::GetGameSprite()
{
	return _Sprite;
}

/**
	 * @brief Ustawia pozycję sprajtu.
	 *
	 * @param _Position Nowa pozycja sprajtu.
	 */
void GameSprite::SetSpritePosition(Vector2f _Position)
{
	_Sprite.setPosition(_Position);
}

/**
	* @brief Rysuje sprajt na oknie renderowania.
	*
	* @param window Okno renderowania.
	*/
void GameSprite::DrawSprite(RenderWindow& window)
{
	window.draw(_Sprite);
}

/**
	 * @brief Przesuwa sprajt o określony wektor.
	 *
	 * @param _Direction Wektor przesunięcia.
	 */
void GameSprite::MoveGameSprite(Vector2f _Direction)
{
	_Sprite.move(_Direction);
}