#include <iostream>
#include <Windows.h>


struct Data
{
	int number;
	bool boolean;
	float floatingpoint;
};

int main()
{

	char* Name[24];
	// Allocating a block of ram that can be shared between programs
	HANDLE handle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(Data), L"MyMemory");
	if (handle == nullptr)
	{
		// Failed to allocate ram
		std::cout << "Allocation Failed" << std::endl;
		std::cout << GetLastError() << std::endl;
		return 1;
	}

	Data* data = (Data*)MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Data));

	if (data == nullptr)
	{
		std::cout << "Could not map view of file: " << GetLastError() << std::endl; 
		CloseHandle(handle); 
		return 2;
	}

	else
	{
		std::cout << "allocating ram.." << std::endl;
		data->number = 10;
		data->boolean = true;
		data->floatingpoint = 1.2f;
	}

	system("PAUSE");

	UnmapViewOfFile(data);

	CloseHandle(handle);
	return 0;
}