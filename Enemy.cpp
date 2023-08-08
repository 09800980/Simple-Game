#include "Enemy.h"
/**
 * @file Enemy.h
 * @brief Plik nagłówkowy zawierający deklarację klasy Enemy.
 */

 /**
  * @class Enemy
  * @brief Klasa reprezentująca wroga.
  */

/**
 * @brief Konstruktor klasy Enemy.
 *
 * @param _LoadFromFile Ścieżka do pliku z teksturą wroga.
 * @param _Position Pozycja wroga.
 */
Enemy::Enemy(String _LoadFromFile, Vector2f _Position) :Animated(_LoadFromFile, _Position, 16, 16)
{
    top = 0;
    left = 0;
    IsDead = false;
    IsDeadEnd = false;
    Shadow = new GameSprite("Textures/Shadow.png", _Sprite.getPosition() + Vector2f(0, _PixelHeight * 2));
    EnemyStatus = Walk;
    Shadow->SetScale(Vector2f(5.f, 5.f));
    SetScale(Vector2f(5.f, 5.f));
}

/**
 * @brief Metoda do animacji wroga.
 *
 * @param _top Indeks wiersza animacji.
 * @param St Aktualny status wroga.
 * @return Nowy status wroga po animacji.
 */
Status Enemy::Animate(int _top, Status St)
{
    TimePoint CurrentFrameTime = TimeClock::now();
    static TimePoint PreviousFrameTime = TimeClock::now();
    TimeFloat TimeSinceLastFrame = CurrentFrameTime - PreviousFrameTime;
    top = _top;
    if (TimeSinceLastFrame.count() >= _FrameTime.asSeconds())
    {
        switch (St)
        {
        case Walk:
            MoveSpeed = 90.0;
            _FrameTime = seconds(0.2);
            left = (left + 1) % 4;
            PreviousFrameTime = CurrentFrameTime;
            break;
        case Hurt:
            MoveSpeed = 40.0;
            _FrameTime = seconds(0.1);
            if (left < 3)
                left = 3;
            left = ((left + 1) % 2) + 4;
            PreviousFrameTime = CurrentFrameTime;
            if (left == 5)
                St = Walk;
            break;
        case Status::Death:
            _FrameTime = seconds(0.2);
            MoveSpeed = 0.0;
            if (left < 5)
                left = 5;
            left = ((left + 1) % 6) + 6;
            PreviousFrameTime = CurrentFrameTime;
            if (left == 9)
                St = DeathEnd;
            break;
        default:
            break;
        }
    }
    _FrameSprite.left = left * _PixelWidth;
    _FrameSprite.top = top * _PixelHeight;

    _Sprite.setTextureRect(_FrameSprite);
    return St;
}

/**
 * @brief Metoda do zadawania obrażeń wrogowi.
 *
 * @param Damage Wartość obrażeń.
 * @return True, jeśli wróg zginął; false w przeciwnym razie.
 */
bool Enemy::TakeDamage(int Damage)
{
    Health -= Damage;
    if (Health <= 0)
        return true;
    EnemyStatus = Hurt;
    return false;
}

/**
 * @brief Metoda do poruszania wroga.
 *
 * @param _Direction Kierunek ruchu wroga.
 * @param LocalTime Czas lokalny.
 */
void Enemy::Move(Vector2f _Direction, float LocalTime)
{
    if (IsDead)
    {
        if (Animate(top, Status::Death) == DeathEnd && IsDeadEnd == false)
            IsDeadEnd = true;
        return;
    }
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
    if (EnemyStatus == Hurt)
    {
        _Direction = -_Direction;
    }
    _Sprite.move(_Direction * LocalTime * MoveSpeed);
    Shadow->MoveGameSprite(_Direction * LocalTime * MoveSpeed);

    EnemyStatus = Animate(top, EnemyStatus);
}

/**
 * @brief Metoda do poruszania wroga w określonym kierunku.
 *
 * @param _Direction Kierunek ruchu wroga.
 * @param Speed Prędkość poruszania.
 */
void Enemy::DirMove(Vector2f _Direction, float Speed)
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
 * @brief Metoda do rysowania wroga na ekranie.
 *
 * @param window Referencja do obiektu RenderWindow, na którym rysowany jest wróg.
 */
void Enemy::DrawSprite(RenderWindow& window)
{
    window.draw(_Sprite);
    window.draw(Shadow->GetGameSprite());
}

/**
 * @brief Metoda do pobierania cienia wroga.
 *
 * @return Obiekt klasy Sprite reprezentujący cień wroga.
 */
Sprite Enemy::GetShadow()
{
    return Shadow->GetGameSprite();
}
