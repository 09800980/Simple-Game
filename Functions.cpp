#include "Functions.h"

/**
 * @brief Oblicza kierunek między dwoma punktami.
 *
 * @param To Punkt docelowy.
 * @param From Punkt początkowy.
 * @return Wektor reprezentujący kierunek.
 */
Vector2f CalculateDirection(Vector2f To, Vector2f From)
{
	Vector2f Direction = Vector2f(To - From);
	float Distance = static_cast<float>(sqrt(pow(To.x - From.x, 2) + pow(To.y - From.y, 2)));
	Direction /= Distance;
	return Direction;
}

/**
 * @brief Znajduje pokój o określonym indeksie w liście pokoi.
 *
 * @param Rooms Wskaźnik na listę pokoi.
 * @param Index Indeks poszukiwanego pokoju.
 * @return Wskaźnik na znaleziony pokój lub NULL, jeśli nie znaleziono.
 */
Room* FindRoom(std::list<Room>* Rooms, Vector2f Index)
{
	for (std::list<Room>::iterator RoomsIt = Rooms->begin(); RoomsIt != Rooms->end(); ++RoomsIt)
	{
		if (RoomsIt->Index == Index)
			return &(*RoomsIt);
	}
	return NULL;
}

/**
 * @brief Generuje mapę pokoi.
 *
 * @param Seed Ziarno losowości.
 * @return Lista wygenerowanych pokoi.
 */
std::list<Room>  GenerateMap(int Seed)
{
	srand(Seed);
	puts("");

	//Rozmiar mapy
	const int x = 5, y = 5;
	int Map[x][y];
	//Ilcość pokoi
	const int NumOfRooms = 7;

	//Lista chroniąca mape
	std::list<Room> Rooms;

	//Wyzerowanie Mapy
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			Map[i][j] = 0;
		}
	}

	//W środku mapy zawsze jest pokój
	Map[x / 2][y / 2] = 1;
	Rooms.emplace_back(Vector2f(0, 0), Vector2f(x / 2, y / 2));
	Rooms.begin()->Cleared = true;
	Rooms.begin()->Block = false;

	//Generacja
	for (int Num = 0; Num < NumOfRooms;)
	{
		int forx = x / 2, fory = y / 2, state = 0;
		int stepx = 1, stepy = 1;
		static int step0 = 0;
		static int step1 = 0;
		static int step2 = 0;
		static int step3 = 0;
		//Pętla będzie przechodziła przez Mape po spirali od środka
		for (int i = 0; i < x * y; i++)
		{
			if (Map[forx][fory] && rand() % 2 == 1)
			{
				Direction Dir = (Direction)(rand() % 4);
				//Tworzenie pookoju w jednym z czterech kierunków
				switch (Dir)
				{
				case Bottom:
					if (forx + 1 < x)
					{
						if (Map[forx + 1][fory] == 0)
						{
							if (Num == 0)
							{
								Map[forx + 1][fory] = 2;
								Rooms.emplace_back(Vector2f(1280 * (fory - 2), 720 * (forx + 1 - 2)), Vector2f(forx + 1, fory), 1);

								FindRoom(&Rooms, Vector2f(forx, fory))->AddDoor(Bottom);
								FindRoom(&Rooms, Vector2f(forx, fory))->DeleteWall(Bottom);

								FindRoom(&Rooms, Vector2f(forx + 1, fory))->AddDoor(Top);
								FindRoom(&Rooms, Vector2f(forx + 1, fory))->DeleteWall(Top);
								Num++;
							}
							else if (Num < NumOfRooms)
							{
								Map[forx + 1][fory] = 1;
								Rooms.emplace_back(Vector2f(1280 * (fory - 2), 720 * (forx + 1 - 2)), Vector2f(forx + 1, fory));
								FindRoom(&Rooms, Vector2f(forx, fory))->AddDoor(Bottom);
								FindRoom(&Rooms, Vector2f(forx, fory))->DeleteWall(Bottom);

								FindRoom(&Rooms, Vector2f(forx + 1, fory))->AddDoor(Top);
								FindRoom(&Rooms, Vector2f(forx + 1, fory))->DeleteWall(Top);
								Num++;
							}

						}
					}
					break;
				case Right:
					if (fory + 1 < y)
					{
						if (Map[forx][fory + 1] == 0)
						{
							if (Num == 0)
							{
								Map[forx][fory + 1] = 2;
								Rooms.emplace_back(Vector2f(1280 * (fory + 1 - 2), 720 * (forx - 2)), Vector2f(forx, fory + 1), 1);

								FindRoom(&Rooms, Vector2f(forx, fory))->AddDoor(Right);
								FindRoom(&Rooms, Vector2f(forx, fory))->DeleteWall(Right);

								FindRoom(&Rooms, Vector2f(forx, fory + 1))->AddDoor(Left);
								FindRoom(&Rooms, Vector2f(forx, fory + 1))->DeleteWall(Left);
								Num++;
							}
							else if (Num < NumOfRooms)
							{
								Map[forx][fory + 1] = 1;
								Rooms.emplace_back(Vector2f(1280 * (fory + 1 - 2), 720 * (forx - 2)), Vector2f(forx, fory + 1));
								FindRoom(&Rooms, Vector2f(forx, fory))->AddDoor(Right);
								FindRoom(&Rooms, Vector2f(forx, fory))->DeleteWall(Right);

								FindRoom(&Rooms, Vector2f(forx, fory + 1))->AddDoor(Left);
								FindRoom(&Rooms, Vector2f(forx, fory + 1))->DeleteWall(Left);
								Num++;
							}
						}
					}
					break;
				case Top:
					if (forx - 1 >= 0)
					{
						if (Map[forx - 1][fory] == 0)
						{
							if (Num == 0)
							{
								Map[forx - 1][fory] = 2;
								Rooms.emplace_back(Vector2f(1280 * (fory - 2), 720 * (forx - 1 - 2)), Vector2f(forx - 1, fory), 1);

								FindRoom(&Rooms, Vector2f(forx, fory))->AddDoor(Top);
								FindRoom(&Rooms, Vector2f(forx, fory))->DeleteWall(Top);

								FindRoom(&Rooms, Vector2f(forx - 1, fory))->AddDoor(Bottom);
								FindRoom(&Rooms, Vector2f(forx - 1, fory))->DeleteWall(Bottom);
								Num++;
							}
							else if (Num < NumOfRooms)
							{
								Map[forx - 1][fory] = 1;
								Rooms.emplace_back(Vector2f(1280 * (fory - 2), 720 * (forx - 1 - 2)), Vector2f(forx - 1, fory));
								FindRoom(&Rooms, Vector2f(forx, fory))->AddDoor(Top);
								FindRoom(&Rooms, Vector2f(forx, fory))->DeleteWall(Top);

								FindRoom(&Rooms, Vector2f(forx - 1, fory))->AddDoor(Bottom);
								FindRoom(&Rooms, Vector2f(forx - 1, fory))->DeleteWall(Bottom);
								Num++;
							}
						}
					}
					break;
				case Left:
					if (fory - 1 >= 0)
					{
						if (Map[forx][fory - 1] == 0)
						{
							if (Num == 0)
							{
								Map[forx][fory - 1] = 2;
								Rooms.emplace_back(Vector2f(1280 * (fory - 1 - 2), 720 * (forx - 2)), Vector2f(forx, fory - 1), 1);

								FindRoom(&Rooms, Vector2f(forx, fory))->AddDoor(Left);
								FindRoom(&Rooms, Vector2f(forx, fory))->DeleteWall(Left);

								FindRoom(&Rooms, Vector2f(forx, fory - 1))->AddDoor(Right);
								FindRoom(&Rooms, Vector2f(forx, fory - 1))->DeleteWall(Right);
								Num++;
							}
							else if (Num < NumOfRooms)
							{
								Map[forx][fory - 1] = 1;
								Rooms.emplace_back(Vector2f(1280 * (fory - 1 - 2), 720 * (forx - 2)), Vector2f(forx, fory - 1));
								FindRoom(&Rooms, Vector2f(forx, fory))->AddDoor(Left);
								FindRoom(&Rooms, Vector2f(forx, fory))->DeleteWall(Left);

								FindRoom(&Rooms, Vector2f(forx, fory - 1))->AddDoor(Right);
								FindRoom(&Rooms, Vector2f(forx, fory - 1))->DeleteWall(Right);
								Num++;
							}
						}
					}
					break;
				default:
					break;
				}
			}

			//Logika przechodzenia Mapy po spirali
			switch (state % 4)
			{
			case 0:
				fory++;
				step0++;
				if (step0 == stepy)
				{
					step0 = 0;
					stepy++;
					state++;
				}
				break;
			case 1:
				forx++;
				step1++;
				if (step1 == stepx)
				{
					step1 = 0;
					stepx++;
					state++;
				}
				break;
			case 2:
				fory--;
				step2++;
				if (step2 == stepy)
				{
					step2 = 0;
					stepy++;
					state++;
				}
				break;
			case 3:
				forx--;
				step3++;
				if (step3 == stepx)
				{
					step3 = 0;
					stepx++;
					state++;
				}
				break;
			default:
				break;
			}
		}
	}

	//Wyświetlanie Mapy w konsoli
	for (int i = 0; i < x; i++)
	{
		printf("\n");
		for (int j = 0; j < y; j++)
		{
			printf("%d", Map[i][j]);
		}
	}

	return Rooms;
}