#include "Player.h"
/**
 * @file Player.h
 * @brief Plik nagłówkowy zawierający deklarację klasy Player.
 */

 /**
  * @class Player
  * @brief Klasa reprezentująca bohatera.
  */

/**
 * @brief Konstruktor klasy Player.
 *
 * @param _LoadFromFile Ścieżka do pliku z teksturą gracza.
 * @param _Position Pozycja początkowa gracza.
 */
Player::Player(String _LoadFromFile, Vector2f _Position) :Animated(_LoadFromFile, _Position, 16, 16)
{
    Shadow = new GameSprite("Textures/Shadow.png", _Sprite.getPosition() + Vector2f(0, _PixelHeight * 2));
    Shadow->SetScale(Vector2f(5.f, 5.f));
    Direction = Vector2f(0, 0);
    IsMove = false;
    SetScale(Vector2f(5.f, 5.f));
}

/**
 * @brief Ustawia pozycję gracza.
 *
 * @param _Position Nowa pozycja gracza.
 */
void Player::SetPlayerPosition(Vector2f _Position)
{
    _Sprite.setPosition(_Position);
    Shadow->SetSpritePosition(Vector2f(_Position.x, _Position.y + _PixelHeight * 2));
}

/**
 * @brief Aktualizuje logikę gracza, poruszanie się, animację itp.
 *
 * @param window Referencja do obiektu RenderWindow, na którym rysowany jest gracz.
 * @param LocalTime Czas lokalny.
 * @param _SelectedRoom Wybrany pokój.
 */
void Player::Update(RenderWindow& window, float LocalTime, Room _SelectedRoom)
{
    if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::D))
    {
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            top = 1;
            Direction += Vector2f(-1, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            top = 2;
            Direction += Vector2f(1, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            top = 0;
            Direction += Vector2f(0, 1);
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            top = 3;
            Direction += Vector2f(0, -1);
        }

        for (auto& WallsIt : _SelectedRoom.Walls)
        {
            if (WallsIt.GetGameSprite().getGlobalBounds().contains(Shadow->GetGameSprite().getPosition() + Vector2f(Direction.x * Shadow->GetGameSprite().getGlobalBounds().width / 2, Direction.y * Shadow->GetGameSprite().getGlobalBounds().height / 2)))
            {
                IsMove = false;
                break;
            }
            else
                IsMove = true;
        }

    }
    else
        IsMove = false;
    if (IsMove)
    {
        _Sprite.move(Direction * MoveSpeed * LocalTime);
        Shadow->MoveGameSprite(Direction * MoveSpeed * LocalTime);
    }
    Direction = Vector2f(0, 0);

    if (!IsMove)
        _Sprite.setTextureRect(IntRect(0, top * _PixelHeight, 16, 16));
    else
        (void)Animate(top, Walk);
}

/**
 * @brief Porusza gracza w zadanym kierunku i aktualizuje animację.
 *
 * @param _Direction Kierunek ruchu.
 * @param Speed Prędkość ruchu.
 */
void Player::DirMove(Vector2f _Direction, float Speed)
{
    if (_Direction.y < 0 && abs(_Direction.y) > abs(_Direction.x))
    {
        top = 3;
    }
    if (_Direction.x < 0 && abs(_Direction.x) > abs(_Direction.y))
    {
        top = 1;
    }
    if (_Direction.y > 0 && abs(_Direction.y) > abs(_Direction.x))
    {
        top = 0;
    }
    if (_Direction.x > 0 && abs(_Direction.x) > abs(_Direction.y))
    {
        top = 2;
    }
    _Sprite.move(_Direction * Speed);
    Shadow->MoveGameSprite(_Direction * Speed);

    (void)Animate(top, Walk);
}

/**
 * @brief Tworzy pocisk i strzela w zadanym kierunku.
 *
 * @param _Direction Kierunek strzału.
 */
void Player::Shot(Vector2f _Direction)
{
    Bullets.emplace_back("Textures/Hero/Bullet.png", _Sprite.getPosition(), _Direction);
}

/**
 * @brief Rysuje gracza i jego cień na ekranie.
 *
 * @param window Referencja do obiektu RenderWindow, na którym rysowany jest gracz.
 */
void Player::DrawSprite(RenderWindow& window)
{
    window.draw(_Sprite);
    window.draw(Shadow->GetGameSprite());
}

/**
 * @brief Zwraca obiekt Sprite reprezentujący cień gracza.
 *
 * @return Obiekt Sprite reprezentujący cień gracza.
 */
Sprite Player::GetShadow()
{
    return Shadow->GetGameSprite();
}
