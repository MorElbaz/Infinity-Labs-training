#include <stdio.h>/*fopen*/
#include <stdlib.h>/*exit*/
#include <string.h>/*strcmp*/

#define MAX_LEN 100
#define MAX_NAME 30
#define NUM_OF_FUNCS 4
#define UNUSED(X) (void)(X);
#define RETURN_IF_FAIL(IS_FAIL, PRINT_STR, RETURN_VALUE); \
if(IS_FAIL) { puts(PRINT_STR); return RETURN_VALUE; }

/*need to make a macro for fail*/

typedef enum status_ret
{
	SUCCSESS = 0,
	FAIL_OPEN = 1,
	FAIL_FGETS = 2,
	FAIL_REMOVE = 3,
	FAIL_RENAME = 4,
	FAIL_CLOSE = 5,
	FAIL_EXIT = 6
	
}exit_status;

exit_status SaveToFile(const char *usr_str, const char *filename);
exit_status Exit(const char *usr_str, const char *filename);
exit_status Remove(const char *usr_str, const char *filename);
exit_status Count(const char *usr_str, const char *filename);
int IsMatchToPrepend(const char *usr_str, const char *func_str);
int IsMatch(const char *usr_str, const char *func_str);
exit_status AddToBeg(const char *usr_str, const char *filename);




int main(int argc, char **argv) /*jonatan kid*/
{
	char usr_str[MAX_LEN];
	int i;
	int err_num;

	struct func_struct
	{
		char func_str[MAX_NAME];
		int (*is_match_ptr)(const char *usr_str, const char *func_str);
		exit_status (*operation_ptr)(const char *usr_str, const char *filename);
	};
	
	typedef struct func_struct func_t;
	func_t funcs[NUM_OF_FUNCS] = {{"-remove", IsMatch, Remove},
									{"-exit", IsMatch, Exit},
									{"-count", IsMatch, Count},
									{"AddToBeg", IsMatchToPrepend, AddToBeg}};
	
	if(argc < 2)
	{
		puts("missing main arguments");
		return 1;
	}

	/*loops utill the user writes the "-exit" string*/
	while (1)
	{
		/*getting a string from the user*/
		puts("please enter a string:");
	
		RETURN_IF_FAIL((scanf(" %[^\n]%*c", usr_str) <= 0), "scanf failed", 1);
	
		for(i = 0; i < NUM_OF_FUNCS; ++i)
		{
			if (funcs[i].is_match_ptr(usr_str, funcs[i].func_str))
			{	
				if(!(err_num =(funcs[i].operation_ptr(usr_str, argv[1]))))
				{
					break;
				}
				printf("the operation \"%s\" failed\n", funcs[i].func_str);
				return 1;
			}
		}

		/*saving the user-string to the file*/
		if(i == NUM_OF_FUNCS)
		{
			SaveToFile(usr_str, argv[1]);
		}	
	}	
	return 0;
}

exit_status SaveToFile(const char *usr_str, const char *filename)
{
	FILE *fl_ptr = NULL;
	
	RETURN_IF_FAIL((fl_ptr = fopen(filename, "a+")) == NULL, "fail to open file", FAIL_OPEN);
	
	fputs(usr_str, fl_ptr);
	fputc('\n', fl_ptr);	
	
	RETURN_IF_FAIL(fclose(fl_ptr), "fail to close", FAIL_CLOSE);
		
	return SUCCSESS ;
}

exit_status Remove(const char *usr_str, const char *filename)
{
	UNUSED(usr_str)

	RETURN_IF_FAIL(remove(filename), "failed to remove file", FAIL_REMOVE);

	return SUCCSESS; 
}

exit_status Count(const char *usr_str, const char *filename)
{
	char str_to_count[MAX_LEN];
	int lines = 0;
	FILE *fl_ptr = NULL;
	UNUSED(usr_str)

	RETURN_IF_FAIL((fl_ptr = fopen(filename, "r")) == NULL, "failed to open file", FAIL_OPEN); 
	
	while(fgets(str_to_count, MAX_LEN, fl_ptr))
	{
		++lines;
	}

	RETURN_IF_FAIL(fclose(fl_ptr), "failed to close file", FAIL_CLOSE);
	
	printf("the number of lines in file %s is: %d\n", filename, lines);

	return SUCCSESS;
}

exit_status Exit(const char *usr_str, const char *filename)
{
	UNUSED(filename)
	UNUSED(usr_str)
	exit(0);
	
	return FAIL_EXIT;
}

int IsMatch(const char *usr_str, const char *func_str)
{
	return (strcmp(usr_str, func_str) == 0);
}

int IsMatchToPrepend(const char *usr_str, const char *func_str)
{
	UNUSED(func_str)
	return (*usr_str == '<');
}

exit_status AddToBeg(const char *usr_str, const char *filename)
{
	FILE *tmp_file_ptr = NULL;
	FILE *file_ptr = NULL;
	char str_to_cpy[MAX_LEN];

	if(((tmp_file_ptr = fopen("temp.txt", "w")) == NULL) || ((file_ptr = fopen(filename, "r")) == NULL))
	{
		puts("failed to open file");
		return FAIL_OPEN;
	}
	
	fputs((usr_str + 1), tmp_file_ptr);
	fputc('\n', tmp_file_ptr);

	while(fgets(str_to_cpy, MAX_LEN, file_ptr) != NULL)
	{
		fputs(str_to_cpy, tmp_file_ptr);
	}

	RETURN_IF_FAIL((fclose(file_ptr) != 0) || (fclose(tmp_file_ptr) != 0), "failed to close file", FAIL_CLOSE);

	RETURN_IF_FAIL(remove(filename), "failed to remove file", FAIL_REMOVE);
	
	RETURN_IF_FAIL(rename("temp.txt", filename), "failed to rename file", FAIL_RENAME);

	return SUCCSESS;	
}

	


		
		











