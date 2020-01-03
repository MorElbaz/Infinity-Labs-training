#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*strlen*/
#include <ctype.h>/*tolower*/
#define NULL_TER 1

void PrintFun(char **env);



int main(int argc, char **argv, char **envp) // checked by motty
{
	char **buffer = NULL;
	char **envp_ptr = envp;
	int row= 0;
	int col = 0;
	size_t rows_total= 0;
	int i = 0;

	while(*envp_ptr)
	{
		++envp_ptr;	
	}
	
	rows_total = envp_ptr - envp;

	buffer = (char **)malloc((rows_total+ NULL_TER) * sizeof(char *));
	if(buffer == NULL)
	{
		return 1;
	}
	
		while(row < rows_total)
		{
			buffer[row] = (char *)malloc(sizeof(char) * (strlen(envp[row])+NULL_TER));
			if(buffer[row] == NULL)
			{
				return 1;
			}
			
				for(col = 0; envp[row][col]; ++col)
				{
					buffer[row][col]= tolower(envp[row][col]);
				}

				buffer[row][col] = 0;
				++row;
			
		}
		buffer[row] = 0;
	
		PrintFun(buffer);

		while(buffer[i])
		{
				free(buffer[i]);
				++i;
		}
		free(buffer);
	
	
	return 0;
}


void PrintFun(char **arr)
{
	while(*arr)
	{
		puts(*arr);
		++arr;		
	}
}





