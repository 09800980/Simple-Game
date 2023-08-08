#include "Game.h"

/**
 * @brief Main game function.
 *
 * This function represents the main game loop. It handles user input, updates game objects, and renders the game window.
 *
 * @param window The render window in which the game is displayed.
 * @return The exit code of the game.
 */
int Game(RenderWindow& window)
{
	// Camera
	View Camera(FloatRect(0, 0, 1280, 720));

Start:
	// List that stores all the rooms
	std::list<Room> Map = GenerateMap(time(NULL));

	// Pointer to the current room
	Room* ActualRoom = &(*Map.begin());

	// Player
	Player Hero("Textures/Hero/Hero.png", Vector2f(ScreenWidth / 2, ScreenHeight / 2));

	// Mouse class (currently only needed for shooting)
	Mouse _Mouse;

	// Timer for shooting
	TimePoint CurrentFrameTime_Shot = TimeClock::now();
	static TimePoint PreviousFrameTime_Shot = TimeClock::now();
	TimeFloat TimeSinceLastFrame_Shot = CurrentFrameTime_Shot - PreviousFrameTime_Shot;
	Time TimeToReload = seconds(0.5);

	bool IsShot = false;
	bool Reset = false;

	// Clock to help with smooth object movement
	Clock GlobalClock;
	float GlobalTime = 0.0;

	// Game window loop
	while (window.isOpen())
	{
		Event event;

		GlobalTime = GlobalClock.getElapsedTime().asSeconds();
		GlobalClock.restart();

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			// Left mouse button condition
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
				IsShot = true;

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
				IsShot = false;

			// Condition for the R key
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::R)
					Reset = true;
			}
		}

		CurrentFrameTime_Shot = TimeClock::now();
		TimeSinceLastFrame_Shot = CurrentFrameTime_Shot - PreviousFrameTime_Shot;

		// Shoot if enough time has passed since the last shot
		if (IsShot && TimeSinceLastFrame_Shot.count() > TimeToReload.asSeconds())
		{
			Hero.Shot(CalculateDirection(window.mapPixelToCoords(_Mouse.getPosition(window)), Hero.GetGameSprite().getPosition()));
			PreviousFrameTime_Shot = CurrentFrameTime_Shot;
		}

		if (Reset)
		{
			Reset = false;
			goto Start;
		}

		// Update player movement
		Hero.Update(window, GlobalTime, *ActualRoom);

		// Conditions for transitioning between rooms
		// Right
		if (Hero.GetGameSprite().getPosition().x > (ActualRoom->Index.y - 1) * 1280 - (WallSize - 10))
		{
			ActualRoom->Selected = false;
			ActualRoom = FindRoom(&Map, Vector2f(ActualRoom->Index.x, ActualRoom->Index.y + 1));
			Hero.SetPlayerPosition(Vector2f(ActualRoom->CameraPosition.x + WallSize + 2 - ScreenWidth / 2, ActualRoom->CameraPosition.y));
		}

		// Bottom
		if (Hero.GetGameSprite().getPosition().y > (ActualRoom->Index.x - 1) * 720 - (WallSize - 10))
		{
			ActualRoom->Selected = false;
			ActualRoom = FindRoom(&Map, Vector2f(ActualRoom->Index.x + 1, ActualRoom->Index.y));
			Hero.SetPlayerPosition(Vector2f(ActualRoom->CameraPosition.x, ActualRoom->CameraPosition.y + WallSize + 2 - ScreenHeight / 2));
		}

		// Left
		if (Hero.GetGameSprite().getPosition().x < (ActualRoom->Index.y - 2) * 1280 + (WallSize - 10))
		{
			ActualRoom->Selected = false;
			ActualRoom = FindRoom(&Map, Vector2f(ActualRoom->Index.x, ActualRoom->Index.y - 1));
			Hero.SetPlayerPosition(Vector2f(ActualRoom->CameraPosition.x - WallSize - 2 + ScreenWidth / 2, ActualRoom->CameraPosition.y));
		}

		// Top
		if (Hero.GetGameSprite().getPosition().y < (ActualRoom->Index.x - 2) * 720 + (WallSize - 50))
		{
			ActualRoom->Selected = false;
			ActualRoom = FindRoom(&Map, Vector2f(ActualRoom->Index.x - 1, ActualRoom->Index.y));
			Hero.SetPlayerPosition(Vector2f(ActualRoom->CameraPosition.x, ActualRoom->CameraPosition.y - WallSize - Hero.GetGameSprite().getLocalBounds().height * 5 / 2 - 2 + ScreenHeight / 2));
		}

		// Select the current room
		if (!ActualRoom->Selected)
		{
			ActualRoom->SelectRoom();
			Camera.setCenter(ActualRoom->CameraPosition);
			window.setView(Camera);
		}

		// Render all objects in the game window
		window.clear();
		ActualRoom->DrawRoom(window, Hero);
		if (ActualRoom->Update(window, GlobalTime, Hero))
			return 0;
		window.display();
	}

	return 0;
}
