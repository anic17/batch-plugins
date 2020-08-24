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
	if(argv[1] == NULL){return 0;}
	/* 
		K argument: Key
		Use function getch() in "conio.h"
	*/
	if(*argv[1] == 'k' || *argv[1] == 'K')
	{
		int key = _getch();
		return(key);
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

	if(*argv[1] == 'g' || *argv[1] == 'G')
    {
    	// If the string is empty (NULL), return 1 and quit the program
    	if(argv[3] == NULL)
    	{
    		return 1;
    	}

		// Create console handle
	    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

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

	    // Create handle
		HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;

	    if(atoi(argv[2]) == 1)
	    {
	    	info.bVisible = FALSE;
	    	SetConsoleCursorInfo(ConsoleHandle, &info);
	    } else {
			info.bVisible = TRUE;
	    	SetConsoleCursorInfo(ConsoleHandle, &info);
	    }
	    CloseHandle(ConsoleHandle);
    	return 0;
    }
    /*
		Q argument: QuickEdit
		Enable or disable QuickEdit mode
    */
    if(*argv[1] == 'q' || *argv[1] == 'Q')
    {
    	// Create console handle and DWORD
		HANDLE hConsoleHandle = GetStdHandle(STD_INPUT_HANDLE);
		DWORD dwMode;
		// Get current console mode
		GetConsoleMode(hConsoleHandle, &dwMode);

		// Disable QuickEdit mode
		if(atoi(argv[2]) == 0)
		{
			// Disable QuickEdit mode
			SetConsoleMode(hConsoleHandle, 0x0080 | (dwMode & ~0x0040));

		} else {
			// Enable QuickEdit mode
			SetConsoleMode(hConsoleHandle, dwMode);
		
	    }
	    // Close the open handle
	    CloseHandle(hConsoleHandle);
	    return 0;

	}
	if(*argv[1] == 's' || *argv[1] == 'S')
	    {

	    	int cursize = atoi(argv[2]);

	    	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_CURSOR_INFO info;
			info.dwSize = cursize;
			SetConsoleCursorInfo(ConsoleHandle, &info);
			CloseHandle(ConsoleHandle);
	    }


	/*
		W argument: Wait
		Wait specified milliseconds
    */
    if(*argv[1] == 'w' || *argv[1] == 'W')
    {
    	// Get milliseconds in argument and transform it to int using atoi()
    	int ms_sleep = atoi(argv[2]);
    	// Wait 
    	Sleep(ms_sleep);

    	// Quit the program after function has completed
    	return 0;
    }
}


