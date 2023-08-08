#include "Start.h"

/**
 * @brief Funkcja reprezentująca menu startowe gry.
 *
 * @return Kod zakończenia funkcji.
 */
int StartMenu()
{
    RenderWindow window(VideoMode(ScreenWidth, ScreenHeight), "Prosta Gra Przygodowa");
    window.setFramerateLimit(60);

    // Obiekty menu
    GameSprite BackGround("Textures/room.png", Vector2f(0, 0), false);
    Player Hero("Textures/Hero/Hero.png", Vector2f(1280 / 2 - 250 + 230.f, 720 / 2));
    Enemy Skeleton("Textures/Enemy/Skeleton.png", Hero.GetGameSprite().getPosition());
    GameSprite Play("Textures/Buttons/Play.png", Vector2f(1280 / 2 + 300, 720 / 2 - 150), true, 37, 19);
    Play.SetScale(Vector2f(10, 8));
    GameSprite Quit("Textures/Buttons/Quit.png", Vector2f(1280 / 2 + 300, 720 / 2 + 50), true, 37, 19);
    Quit.SetScale(Vector2f(10, 8));

    // Zmienna dla poruszania się po okręgu
    float centerX = 1280 / 2 - 250;
    float centerY = 720 / 2 - 35;
    float radius = 210.f;
    float angle = 0.f;
    float spacing = -75.f;

    sf::Vector2f prevPosition;

    sf::Clock clock;

    bool IsStart = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Logika przycisków
            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i MousePosition = Mouse::getPosition(window);
                if (Play.GetGameSprite().getGlobalBounds().contains(Vector2f(MousePosition)))
                {
                    Play._Sprite.setTextureRect(IntRect(37, 0, 37, 19));
                }
                if (Quit.GetGameSprite().getGlobalBounds().contains(Vector2f(MousePosition)))
                {
                    Quit._Sprite.setTextureRect(IntRect(37, 0, 37, 19));
                }

            }
            if (event.type == Event::MouseButtonReleased)
            {
                Vector2i MousePosition = Mouse::getPosition(window);
                if (Play.GetGameSprite().getGlobalBounds().contains(Vector2f(MousePosition)))
                {
                    Play._Sprite.setTextureRect(IntRect(0, 0, 37, 19));
                    IsStart = true;
                }
                else
                    Play._Sprite.setTextureRect(IntRect(0, 0, 37, 19));
                if (Quit.GetGameSprite().getGlobalBounds().contains(Vector2f(MousePosition)))
                {
                    Quit._Sprite.setTextureRect(IntRect(0, 0, 37, 19));
                    event.type = Event::Closed;
                }
                else
                    Quit._Sprite.setTextureRect(IntRect(0, 0, 37, 19));
                if (event.type == sf::Event::Closed)
                    window.close();
            }

        }

        if (IsStart)
        {
            Game(window);
            IsStart = false;
        }

        float x1 = centerX + std::cos(angle) * radius;
        float y1 = centerY + std::sin(angle) * radius;

        // Logika poruszania się po okręgu
        sf::Vector2f newPosition1(x1, y1);
        Hero.DirMove(newPosition1 - Hero.GetGameSprite().getPosition(), 0.1);

        if (prevPosition != sf::Vector2f())
        {
            sf::Vector2f direction = Hero.GetGameSprite().getPosition() - prevPosition;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            sf::Vector2f offset(direction.x / length * spacing, direction.y / length * spacing);
            sf::Vector2f newPosition2 = prevPosition + offset;
            Skeleton.DirMove(newPosition2 - Skeleton.GetGameSprite().getPosition(), 0.1);
        }

        prevPosition = Hero.GetGameSprite().getPosition();

        // Odrysowanie
        window.clear();
        BackGround.DrawSprite(window);
        Hero.DrawSprite(window);
        Skeleton.DrawSprite(window);
        Play.DrawSprite(window);
        Quit.DrawSprite(window);
        window.display();

        float deltaTime = clock.restart().asSeconds();
        float angularSpeed = 0.5f;
        angle += angularSpeed * deltaTime;
    }

    return 0;
}
