#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void Help()
{
	printf("\nSyntax:\n");
	printf("\nMaskedInput \"[input text]\"\n");
	printf("\nExample:\n");
	printf("\nMaskedInput \"Password: \"");
	printf("\nWill make a masked input with \'Password: \' prompt and it will print result into STDOUT");
	printf("\n\n\nCopyright (c) 2020 anic17 Software\n");
}

void BS()
{
	putchar('\b');
	putchar(' ');
	putchar('\b');
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		Help();
		return 0;
	}

	if(!_stricmp(argv[1], "/?") || !_stricmp(argv[1], "--help"))
	{
		Help();
	return 0;
	}
	fprintf(stderr, "%s", argv[1]);
	char str[8192];
	int index = 0;
	int ch;
	while(ch != 13)
	{
		int ch = getch();
		str[index++] = ch;


		if(ch == 8)
		{
			index--;
			if(!index <= 0){
				BS();
				str[--index] = '\0';
			}
		} else if(ch == 3)
		{
						
			exit(3);
		}


		if(ch == 13){
		
			break;
		
		} else {
			if(ch != 8){
				fprintf(stderr, "*");
				}

			}
		}
	printf("%s", str);
}
