#include <iostream>
#include <Windows.h>
#include <conio.h>

class Player
{
public:
	struct Vector2
	{
		void PrintPosition()
		{
			std::cout << "Position X: " << posX << std::endl;
			std::cout << "Position Y: " << posY << std::endl;
		}

		float posX;
		float posY;
	};

	char* GetName()
	{
		return m_Name;
	}

	void SetName(char* name)
	{
		strcpy_s(m_Name, sizeof(m_Name), name);
	}

	float GetAttackSpeed()
	{
		return m_AttackSpeed;
	}

	void SetAttackSpeed(float attackSpeed)
	{
		m_AttackSpeed = attackSpeed;
	}

	int GetXPLevel()
	{
		return m_XPLevel;
	}

	void SetXPLevel(int level)
	{
		m_XPLevel = level;
	}

	float GetXPosition()
	{
		return m_Position.posX;
	}

	void SetXPosition(float X)
	{
		m_Position.posX = X;
	}

	float GetYPosition()
	{
		return m_Position.posY;
	}

	void SetYPosition(float Y)
	{
		m_Position.posY = Y;
	}

	Vector2* GetPosition(float X, float Y)
	{
		m_Position.posX = X;
		m_Position.posY = Y;
	}

	void SetPosition(float X, float Y)
	{
		m_Position.posX = X;
		m_Position.posY = Y;
	}

	void Print()
	{
		std::cout << "Name: " << m_Name << std::endl;
		std::cout << "AttackSpeed: " << m_AttackSpeed << std::endl;
		std::cout << "XPLevel: " << m_XPLevel << std::endl;
		m_Position.PrintPosition();
		std::cout << std::endl;
	}

private:

	char m_Name[24];
	float m_AttackSpeed;
	int m_XPLevel;
	Vector2 m_Position;
};

void Update(Player* player, HANDLE handle);

int main()
{
	// Allocating a block of ram that can be shared between programs
	HANDLE handle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(Player), L"MyMemory");
	if (handle == nullptr)
	{
		// Failed to allocate ram
		std::cout << "Allocation Failed" << std::endl;
		std::cout << GetLastError() << std::endl;
		return 1;
	}

	Player* player = (Player*)MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Player));

	if (player == nullptr)
	{
		std::cout << "Could not map view of file: " << GetLastError() << std::endl; 
		CloseHandle(handle); 
		return 2;
	}

	else
	{
		char name[24];
		std::cout << "Please insert a name" << std::endl;
		std::cin >> name;

		player->SetName(name);
		player->SetAttackSpeed(1);
		player->SetXPLevel(0);
		player->SetPosition(1.0f, 2.0f);

		bool run = true;
		char command[24];
		bool update = false;
		player->Print();
		std::cout << "Please type what you would like to change? NAME, ATTACKSPEED, XPLEVEL or POSITION" << std::endl;

		while (run)
		{
			if (_kbhit())
			{
				std::cin >> command;

				// Converts all Uppercase letters to lowercase X -> x
				for (int i = 0; i < strlen(command - 1); i++)
				{
					if (command[i] >= 65 && command[i] <= 90)
					{
						command[i] = command[i] + 32;
					}
				}

				// Runs appropriate function depending on the command given
				if (strcmp(command, "name") == 0)
				{
					char name[24];
					std::cout << "What would you like your name to be?" << std::endl;
					std::cin >> name;

					player->SetName(name);
				}

				if (strcmp(command, "attackspeed") == 0)
				{
					float attack;
					std::cout << "What would you like your attackspeed to be?" << std::endl;
					std::cin >> attack;

					player->SetAttackSpeed(attack);
				}

				if (strcmp(command, "xplevel") == 0)
				{
					int xp;
					std::cout << "What would you like your xp level to be?" << std::endl;
					std::cin >> xp;

					player->SetXPLevel(xp);
				}

				if (strcmp(command, "position") == 0)
				{
					float posX, posY;

					std::cout << "What would you like your X position to be?" << std::endl;
					std::cin >> posX;

					std::cout << "What would you like your Y position to be?" << std::endl;
					std::cin >> posY;

					player->SetPosition(posX, posY);
				}

				if (strcmp(command, "end") == 0)
				{
					run = false;
				}

				else
				{
					std::cout << "command does not exist" << std::endl;
				}

				std::cout << "Please type what you would like to change? NAME, ATTACKSPEED, XPLEVEL or POSITION" << std::endl;
			}

			Update(player, handle);
			std::cout << "SERVER" << std::endl;

			std::cout << "Please type what you would like to change? NAME, ATTACKSPEED, XPLEVEL or POSITION" << std::endl;
		}
	}

	system("PAUSE");

	UnmapViewOfFile(player);

	CloseHandle(handle);
	return 0;
}

void Update(Player* player, HANDLE handle)
{
	player = (Player*)MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Player));
	system("CLS");
	player->Print();
}