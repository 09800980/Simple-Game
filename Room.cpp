#include "Room.h"
/**
 * @file Room.h
 * @brief Plik nagłówkowy zawierający deklarację klasy Room.
 */

 /**
  * @class Room
  * @brief Klasa reprezentująca pokoje.
  */

  /**
   * @brief Konstruktor klasy Room.
   *
   * @param _RoomPosition Pozycja pokoju.
   * @param _RoomIndex Indeks pokoju.
   * @param PowerUp Określa rodzaj bonusu w pokoju.
   */
Room::Room(Vector2f _RoomPosition, Vector2f _RoomIndex, int PowerUp)
{
	Index = _RoomIndex;
	this->RoomPosition = _RoomPosition;
	CameraPosition = Vector2f(_RoomPosition.x + 1280 / 2, _RoomPosition.y + 720 / 2);
	Selected = false;
	if (Enemies.empty())
	{
		Cleared = false;
		Block = false;
	}
	else
	{
		Cleared = true;
		Block = true;
	}
	Floor = new GameSprite("Textures/Room/floor.png", RoomPosition, false);

	//Tworzenie pokoju
	Walls.emplace_back("Textures/Room/top-left_wall.png", RoomPosition, false);
	Walls.emplace_back("Textures/Room/top-right_wall.png", Vector2f(RoomPosition.x + 688, RoomPosition.y), false);
	Walls.emplace_back("Textures/Room/right-top_wall.png", Vector2f(RoomPosition.x + 1184, RoomPosition.y), false);
	Walls.emplace_back("Textures/Room/right-bottom_wall.png", Vector2f(RoomPosition.x + 1184, RoomPosition.y + 407), false);
	Walls.emplace_back("Textures/Room/bottom-right_wall.png", Vector2f(RoomPosition.x + 688, RoomPosition.y + 616), false);
	Walls.emplace_back("Textures/Room/bottom-left_wall.png", Vector2f(RoomPosition.x, RoomPosition.y + 616), false);
	Walls.emplace_back("Textures/Room/left-bottom_wall.png", Vector2f(RoomPosition.x, RoomPosition.y + 409), false);
	Walls.emplace_back("Textures/Room/left-top_wall.png", RoomPosition, false);
	AddWall(Top);
	AddWall(Right);
	AddWall(Bottom);
	AddWall(Left);

	Item = NULL;
	switch (PowerUp)
	{
	case 0:
		Enemies.emplace_back("Textures/Enemy/Skeleton.png", CameraPosition);
		break;
	case 1:
		Item = new GameSprite("Textures/Items/DamageUp.png", CameraPosition);
		Item->SetScale(Vector2f(2, 2));
		break;
	default:
		break;
	}
}
/**
 * @brief Dodaje ścianę do pokoju na podanej pozycji.
 *
 * @param _WallPosition Pozycja ściany.
 */
void Room::AddWall(Direction _WallPostion)
{
	switch (_WallPostion)
	{
	case Left:
		Walls.emplace_back("Textures/Room/left_door-wall.png", Vector2f(RoomPosition.x, RoomPosition.y + 311), false);
		break;
	case Top:
		Walls.emplace_back("Textures/Room/top_door-wall.png", Vector2f(RoomPosition.x + 592, RoomPosition.y), false);
		break;
	case Right:
		Walls.emplace_back("Textures/Room/right_door-wall.png", Vector2f(RoomPosition.x + 1184, RoomPosition.y + 311), false);
		break;
	case Bottom:
		Walls.emplace_back("Textures/Room/bottom_door-wall.png", Vector2f(RoomPosition.x + 592, RoomPosition.y + 616), false);
		break;
	default:
		break;
	}
}
/**
 * @brief Usuwa ścianę z pokoju na podanej pozycji.
 *
 * @param _WallPosition Pozycja ściany.
 */
void Room::DeleteWall(Direction _WallPosition)
{
	switch (_WallPosition)
	{
	case Left:
		for (std::list<GameSprite>::iterator WallsIt = Walls.begin(); WallsIt != Walls.end(); ++WallsIt)
			if (WallsIt->GetGameSprite().getPosition() == Vector2f(RoomPosition.x, RoomPosition.y + 311))
			{
				Walls.erase(WallsIt);
				break;
			}
		break;
	case Top:
		for (std::list<GameSprite>::iterator WallsIt = Walls.begin(); WallsIt != Walls.end(); ++WallsIt)
			if (WallsIt->GetGameSprite().getPosition() == Vector2f(RoomPosition.x + 592, RoomPosition.y))
			{
				Walls.erase(WallsIt);
				break;
			}
		break;
	case Right:
		for (std::list<GameSprite>::iterator WallsIt = Walls.begin(); WallsIt != Walls.end(); ++WallsIt)
			if (WallsIt->GetGameSprite().getPosition() == Vector2f(RoomPosition.x + 1184, RoomPosition.y + 311))
			{
				Walls.erase(WallsIt);
				break;
			}
		break;
	case Bottom:
		for (std::list<GameSprite>::iterator WallsIt = Walls.begin(); WallsIt != Walls.end(); ++WallsIt)
			if (WallsIt->GetGameSprite().getPosition() == Vector2f(RoomPosition.x + 592, RoomPosition.y + 616))
			{
				WallsIt = Walls.erase(WallsIt);
				break;
			}
		break;
	default:
		break;
	}
}
/**
 * @brief Dodaje drzwi do pokoju na podanej pozycji.
 *
 * @param _WallPosition Pozycja drzwi.
 */
void Room::AddDoor(Direction _WallPostion)
{
	switch (_WallPostion)
	{
	case Left:
		Doors.emplace_back("Textures/Room/left_door.png", Vector2f(RoomPosition.x, RoomPosition.y + 311), false);
		FreeDoor.emplace_back("Textures/Room/left_enter-door.png", Vector2f(RoomPosition.x, RoomPosition.y + 311), false);
		break;
	case Top:
		Doors.emplace_back("Textures/Room/top_door.png", Vector2f(RoomPosition.x + 592, RoomPosition.y), false);
		FreeDoor.emplace_back("Textures/Room/top_enter-door.png", Vector2f(RoomPosition.x + 592, RoomPosition.y), false);
		break;
	case Right:
		Doors.emplace_back("Textures/Room/right_door.png", Vector2f(RoomPosition.x + 1184, RoomPosition.y + 311), false);
		FreeDoor.emplace_back("Textures/Room/right_enter-door.png", Vector2f(RoomPosition.x + 1184, RoomPosition.y + 311), false);
		break;
	case Bottom:
		Doors.emplace_back("Textures/Room/bottom_door.png", Vector2f(RoomPosition.x + 592, RoomPosition.y + 616), false);
		FreeDoor.emplace_back("Textures/Room/bottom_enter-door.png", Vector2f(RoomPosition.x + 592, RoomPosition.y + 616), false);
		break;
	default:
		break;
	}
}
/**
 * @brief Blokuje pokój poprzez dodanie ścian na wszystkich stronach.
 */
void Room::BlockRoom()
{
	AddWall(Top);
	AddWall(Right);
	AddWall(Bottom);
	AddWall(Left);
	Block = true;
}
/**
 * @brief Odblokowuje pokój poprzez usunięcie ścian na wszystkich stronach.
 */
void Room::UnBlockRoom()
{
	Walls.pop_back();
	Walls.pop_back();
	Walls.pop_back();
	Walls.pop_back();
	Block = false;
}
/**
 * @brief Zaznacza pokój jako wybrany.
 *
 * Jeśli pokój jest już wyczyszczony, nic nie robi.
 */
void Room::SelectRoom()
{
	if (Cleared) return;
	Selected = true;
	BlockRoom();
}
/**
 * @brief Aktualizuje pokój.
 *
 * @param window Referencja do okna renderowania.
 * @param LocalTime Czas lokalny.
 * @param Hero Referencja do obiektu gracza.
 * @return true jeśli gra powinna zostać zrestartowana, false w przeciwnym razie.
 */
bool Room::Update(RenderWindow& window, float LocalTime, Player& Hero)
{
	if (Enemies.empty() && Block)
	{
		UnBlockRoom();
		Cleared = true;
	}
	//Pętla orydrysowująca wrogów, odświeżająca ich pozycje i usuwająca ich kiedy jest potrzeba
	for (auto EnemiesIt = Enemies.begin(); EnemiesIt != Enemies.end();)
	{
		bool _IsEnemyDelete = false;
		EnemiesIt->Move(CalculateDirection(Hero.GetGameSprite().getPosition(), EnemiesIt->GetGameSprite().getPosition()), LocalTime);
		EnemiesIt->DrawSprite(window);
		if (EnemiesIt->IsDeadEnd)
		{
			EnemiesIt = Enemies.erase(EnemiesIt);
			_IsEnemyDelete = true;
		}
		if (!_IsEnemyDelete)
			++EnemiesIt;
	}
	if (Item != NULL)
	{
		Item->DrawSprite(window);
		if (Item->GetGameSprite().getGlobalBounds().intersects(Hero.GetShadow().getGlobalBounds()))
		{
			Hero.Damage += 2;
			Item = NULL;
		}
	}
	Hero.DrawSprite(window);
	//Pętla odpowiadająca za strzały
	for (auto BulletsIt = Hero.Bullets.begin(); BulletsIt != Hero.Bullets.end();)
	{
		BulletsIt->Update(window, LocalTime);
		bool _IsBulletDelete = false;
		//Pętla odrysowująca Ściany
		for (auto& WallsIt : Walls)
		{
			if (WallsIt.GetGameSprite().getGlobalBounds().intersects(BulletsIt->GetGameSprite().getGlobalBounds()))
			{
				BulletsIt = Hero.Bullets.erase(BulletsIt);
				_IsBulletDelete = true;
				break;
			}
		}
		//Usunięncie Strzałów
		if (!_IsBulletDelete)
			for (auto& DoorsIt : Doors)
			{
				if (DoorsIt.GetGameSprite().getGlobalBounds().intersects(BulletsIt->GetGameSprite().getGlobalBounds()))
				{
					BulletsIt = Hero.Bullets.erase(BulletsIt);
					_IsBulletDelete = true;
					break;
				}
			}
		if (BulletsIt == Hero.Bullets.end()) break;
		//Pętla odpowiadjąca za zwycięztwo nad wrogiem
		for (auto EnemiesIt = Enemies.begin(); EnemiesIt != Enemies.end(); ++EnemiesIt)
		{
			if (EnemiesIt->GetGameSprite().getGlobalBounds().intersects(BulletsIt->GetGameSprite().getGlobalBounds()))
			{
				if (EnemiesIt->TakeDamage(Hero.Damage))
				{
					EnemiesIt->IsDead = true;
				}
				BulletsIt = Hero.Bullets.erase(BulletsIt);
				_IsBulletDelete = true;
				break;
			}
		}
		if (!_IsBulletDelete)
			++BulletsIt;
	}
	//Pętla odpowiadająca za kontakt Bohatera z Wrogiem
	for (auto& EnemiesIt : Enemies)
	{
		if (EnemiesIt.GetShadow().getGlobalBounds().intersects(Hero.GetShadow().getGlobalBounds()))
		{
			GameSprite GameOver("Textures/Menu/GameOver.jpg", CameraPosition);
			bool Restart = false;
			window.draw(GameOver.GetGameSprite());
			window.display();
			while (!Restart)
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::R)
						{
							window.close();
							StartMenu();
						}
					}
				}
			}
			return true;
		}
	}
	return false;
}
/**
 * @brief Odrysowuje pokój.
 *
 * @param window Referencja do okna renderowania.
 * @param Hero dla odrysowania.
 */
void Room::DrawRoom(RenderWindow& window, Player Hero)
{
	window.draw(Floor->GetGameSprite());

	for (auto& FreeDoorIt : FreeDoor)
	{
		window.draw(FreeDoorIt.GetGameSprite());
	}
	for (auto& WallsIt : Walls)
	{
		window.draw(WallsIt.GetGameSprite());
	}
	for (auto& DoorsIt : Doors)
	{
		window.draw(DoorsIt.GetGameSprite());
	}
}