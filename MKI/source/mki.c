#include <Windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
   HANDLE hConsoleInput;

   hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

   DWORD mode;
   LPDWORD lpMode = &mode;
   INPUT_RECORD buf;
   PINPUT_RECORD lpBuffer = &buf;
   DWORD nLength = 1;
   DWORD nNumberOfEventsRead;

   int key, x, y, button;

   	if(hConsoleInput == INVALID_HANDLE_VALUE)
	{
		printf("Failed to get console handle.\n");
		return 1;
	}

   if(GetConsoleMode(hConsoleInput, lpMode) == 0)
	{
		printf("Failed to read console mode.\n");
		return 1;
	}

	if(SetConsoleMode(hConsoleInput, ENABLE_MOUSE_INPUT) == 0)
	{
		printf("Failed to set console mode.\n");
		return 1;
	}

   while (1)

   {
      if (ReadConsoleInput(hConsoleInput, lpBuffer, nLength, &nNumberOfEventsRead) == 0)

      {
         printf("Failed to read console events.");
         return 1;
      }

      if (buf.EventType == MOUSE_EVENT)   //MOUSE event, no hover info
      {
         if (buf.Event.MouseEvent.dwButtonState)
         {
            x = buf.Event.MouseEvent.dwMousePosition.X;
            y = buf.Event.MouseEvent.dwMousePosition.Y;
            button = buf.Event.MouseEvent.dwButtonState;
            printf("m:%d:%d:%d", button, x, y);
            break;
         }
		if (argv[1])   //MOUSE event, hover info
		{
			if ((int)*argv[1]==102||(int)*argv[1]==70) {
				x = buf.Event.MouseEvent.dwMousePosition.X;
				y = buf.Event.MouseEvent.dwMousePosition.Y;
				button = buf.Event.MouseEvent.dwButtonState;
				printf("m:%d:%d:%d", button, x, y);
				break;
			}
		}
      }
      if (buf.EventType == KEY_EVENT)   // KEY event
      {
         ReadConsoleInput(hConsoleInput, lpBuffer, nLength, &nNumberOfEventsRead);
         key = buf.Event.KeyEvent.uChar.UnicodeChar;
         printf("k:%d:%c", buf.Event.KeyEvent.wVirtualKeyCode, buf.Event.KeyEvent.uChar.UnicodeChar);
         break;
      }
   }
   return 0;
}
