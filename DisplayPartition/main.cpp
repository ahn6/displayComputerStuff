#include <Windows.h>
#include <stdio.h>
#include <iostream>

#define MBR_SIZE 512
int main()
{
	unsigned char buff[MBR_SIZE];

	DWORD read = 0;
	HANDLE hDisk = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL); //Open the handle for the MBR

	if (!ReadFile(hDisk, buff, MBR_SIZE, &read, 0)) //Store the data into a buffer
	{
		std::cout << "Read failed" << std::endl;
	}
	CloseHandle(hDisk);

	// The presence of an IBM PC compatible boot loader for x86-CPUs in the boot sector is by convention indicated by a two-byte hexadecimal sequence 0x55 0xAA
	// https://en.wikipedia.org/wiki/Boot_sector
	// So does that mean it is conventional for all boot sectors to be represented by 0x55 (85) and 0xaa (170)?
	if ((unsigned char)buff[510] == 0x55 && (unsigned char)buff[511] == 0xaa) std::cout << "Disk is bootable!" << std::endl; 

	// Not sure what to do after we read the file.
	// 0.....0 idkkkkkkkkk I give up.... 
	int buffint[MBR_SIZE];
	for (int i = 0; i < MBR_SIZE; i++)
	{
		buffint[i] = buff[i];
	}
}