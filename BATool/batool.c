/*
	BATool: The 9 in 1 tool for batch scripts

	Copyright (C) 2020 anic17

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>

*/

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
	if(argv[1] == NULL){
		return 0;
	}

	/* 
		K argument: Key
		Use function getch() in "conio.h"
	*/
	if(*argv[1] == 'k' || *argv[1] == 'K')
	{
		int key = _getch();
		return(key);
	}



	
	if(*argv[1] == 'i' || *argv[1] == 'I')
	{

		HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		INPUT_RECORD buf;
		PINPUT_RECORD lpBuffer = &buf;
		DWORD nLength = 1;
		DWORD nNumberOfEventsRead;
		int key, x, y, button;

		while (1)
		{
			if (ReadConsoleInput(hConsoleInput, lpBuffer, nLength, &nNumberOfEventsRead) == 0)
			{
				return EXIT_FAILURE;
			}
			if (buf.EventType == MOUSE_EVENT) // Mouse event
			{
					if (buf.Event.MouseEvent.dwButtonState)
					{
						x = buf.Event.MouseEvent.dwMousePosition.X;
						y = buf.Event.MouseEvent.dwMousePosition.Y;
						button = buf.Event.MouseEvent.dwButtonState;
						printf("%d:%d:%d", x, y, button);
						break;
					}
				


			} else {
			    ReadConsoleInput(hConsoleInput, lpBuffer, nLength, &nNumberOfEventsRead);
			    key = buf.Event.KeyEvent.uChar.UnicodeChar;
		    	printf("%c", buf.Event.KeyEvent.uChar.UnicodeChar);
		    	return buf.Event.KeyEvent.wVirtualKeyCode;
		    }
		}
		CloseHandle(hConsoleInput);
	}
	

	if(*argv[1] == 'm' || *argv[1] == 'M')
	{
		HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		INPUT_RECORD buf;
		PINPUT_RECORD lpBuffer = &buf;
		DWORD nLength = 1;
		DWORD nNumberOfEventsRead;

		int x, y, button;


		while (1)
		{
			if (ReadConsoleInput(hConsoleInput, lpBuffer, nLength, &nNumberOfEventsRead) == 0)
			{
				return EXIT_FAILURE;
			}
			if (buf.EventType == MOUSE_EVENT) // Mouse event
			{
				if (buf.Event.MouseEvent.dwButtonState)
				{
				
					x = buf.Event.MouseEvent.dwMousePosition.X;
					y = buf.Event.MouseEvent.dwMousePosition.Y;
					button = buf.Event.MouseEvent.dwButtonState;
					printf("%d:%d:%d", x, y, button);
					break;

				}

			}

		}
		CloseHandle(hConsoleInput);
	}

	// Main function: If the string is empty (NULL), return 1 and quit the program
	if(argc < 3)
	{
		return 1;
	}


	/*
		A argument: ASCII
		Prints the ASCII code of every character in a string
	*/
	if(*argv[1] == 'a' || *argv[1] == 'A')
	{

		// Get length of the string using strlen
		int length = strlen(argv[2]);

		// Set size of i = 0
		int i = 0; 
		// Loop for every character on string and then print his ASCII code
		for (; i < length; i++) {
				printf("%d ", argv[2][i]);
		}
		// Quit the program after function has completed
		return 0;
	}



	/*
		G argument: Goto
		Go to a position at the screen
	*/
	// Create console handle
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if(*argv[1] == 'g' || *argv[1] == 'G')
	{
		// If the string is empty (NULL), return 1 and quit the program
		if(argv[3] == NULL)
		{
			return 1;
		}

		// Get console cursor coordinates
		COORD dwPos;
		dwPos.X = atoi(argv[2]);
		dwPos.Y = atoi(argv[3]);

		// Change cursor position
		SetConsoleCursorPosition(hConsoleHandle, dwPos);

		CloseHandle(hConsoleHandle);
		return 0;
	}


	/*
		H argument: HideCursor
		Hide or unhide the cursor
	*/
	if(*argv[1] == 'h' || *argv[1] == 'H')
	{

		CONSOLE_CURSOR_INFO info;

		if(atoi(argv[2]) == 1)
		{
			info.bVisible = FALSE;
			SetConsoleCursorInfo(hConsoleHandle, &info);
		} else {
			info.bVisible = TRUE;
			SetConsoleCursorInfo(hConsoleHandle, &info);
		}
		CloseHandle(hConsoleHandle);
		return 0;
	}

	/*

	/*
		Q argument: QuickEdit
		Enable or disable QuickEdit mode
	*/
	if(*argv[1] == 'q' || *argv[1] == 'Q')
	{
		// Create console handle and DWORD
		HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		DWORD dwMode;
		// Get current console mode
		GetConsoleMode(hConsoleInput, &dwMode);

		// Disable QuickEdit mode
		if(atoi(argv[2]) == 1)
		{
			// Disable QuickEdit mode
			SetConsoleMode(hConsoleInput, 0x0080 | (dwMode & ~0x0040));

		} else {
			// Enable QuickEdit mode
			SetConsoleMode(hConsoleInput, dwMode | 0x0040 | 0x0080);
		
		}
		// Close the open handle

		CloseHandle(hConsoleInput);
		return 0;
	}

	if(*argv[1] == 's' || *argv[1] == 'S')
		{

			// int cursize = ;

			CONSOLE_CURSOR_INFO info;
			info.dwSize = atoi(argv[2]);
			SetConsoleCursorInfo(hConsoleHandle, &info);
			CloseHandle(hConsoleHandle);
		}

	/*
		W argument: Wait
		Wait specified milliseconds
	*/
	if(*argv[1] == 'w' || *argv[1] == 'W')
	{
		// Get milliseconds in argument and transform it to int using atoi() and wait
		Sleep(atoi(argv[2]));

	}
	// Quit the program after function has completed
	return 0;
}


