#include <stdio.h>/*puts*/
#include <stdlib.h> /*exit*/

#define ESC_ASCII 27
#define ASCII_KEYBOARD 256

void InitialLut(void (**lut_func)(void));
void PrintAPressed(void);
void PrintTPressed(void);
void Exit(void);
void EmptyFunc(void);

int main()
{
	
	static void(*lut_func[ASCII_KEYBOARD])(void);
	unsigned int input_char;

	InitialLut(lut_func);
	
	while(1)
	{
		if(system("stty -icanon -echo") == -1)
		{
			puts("system() failed");
		}
		
		puts("please enter a character:");
		input_char = getchar();
		
		if(system("stty icanon echo") == -1)
		{
			puts("system() failed");
			return 1;
		}
	
		(*lut_func[input_char])();
	}

	return 0;
}


void InitialLut(void (**lut_func)(void))
{
	int i;

	for(i = 0; i < ASCII_KEYBOARD; ++i)
	{
		lut_func[i] = EmptyFunc;
	}

	lut_func['A'] = PrintAPressed;
	lut_func['T'] = PrintTPressed;
	lut_func[ESC_ASCII] = Exit;
}

void PrintAPressed(void)
{
	puts("A pressed");
}


void PrintTPressed(void)
{
	puts("T pressed");
}

void Exit(void)
{
	exit(0);
}

void EmptyFunc(void)
{
	puts("");
}



