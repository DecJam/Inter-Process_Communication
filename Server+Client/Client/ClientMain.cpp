#include <iostream>
#include <Windows.h>


struct Data
{
	int number;
	bool boolean;
	float floatingpoint;
	char* name[24];
};

int main()
{
	// Open access to the shared block of ram
	HANDLE handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"MyMemory");

	if (handle == nullptr)
	{
		// Failed to access ram
		std::cout << "Allocation Failed" << std::endl;
		std::cout << GetLastError() << std::endl;
		return 1;
	}

	Data* data = (Data*)MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Data));

	if (data == nullptr)
	{
		std::cout << "Could not map view of file: " << GetLastError() << std::endl;
	}

	else
	{
		std::cout << "Data = { ";
		std::cout << data->number << ", ";
		std::cout << data->boolean << ", ";
		std::cout << data->floatingpoint << ", ";
		std::cout << " }; " << std::endl;

		system("PAUSE");

	}

	UnmapViewOfFile(data);

	CloseHandle(handle);

	return 0;
}