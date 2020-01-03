#include <stdio.h>/*fwrite*/

#define NUM_OF_CONTACTS 10
#define SIZEOF(x) ((size_t)(&x + 1) - (size_t)(&x))
#define SIZE_OF_TYPE(x) ((x*)0 + 1)
 
typedef struct 
{
	size_t day;
	size_t month;
	size_t year;
}DateOfBirth_t;

typedef struct
{
	char f_name[50];
	char l_name[50];
	DateOfBirth_t dob;
	size_t ID;
}Contact_t;
	
int main()
{
	FILE *file_ptr = NULL;
	
	Contact_t arr_contact[NUM_OF_CONTACTS] = 
	{
	{"mor", "elbaz", {26, 9, 1989}, 201432}, 
	{"yasmin", "shay", {12, 8, 1993}, 398746},
	{"chen", "markovitch", {1, 2, 8372}, 39872},
	{"danny", "ufjds", {3, 4, 5}, 39872},
	{"yinon", "yishay", {4, 5, 6}, 8574},
	{"tar" , "bareket", {5, 6, 7}, 9847},
	{"asaf", "einsl", {7, 6, 5}, 49873},
	{"yonatan", "kidron", {3, 5, 3}, 389723},
	{"yonatan", "edkjhas", {4, 4, 3}, 8376},
	{"motty", "dkjhd", {4, 5, 3}, 3937}
	};

	Contact_t copy_arr[NUM_OF_CONTACTS] = {0};
	
	
	if((file_ptr = fopen("arr_copy.txt", "w+")) == NULL)
	{
		puts("failed to open file");
		return 1;
	}
	
	if(fwrite(arr_contact, sizeof(Contact_t), NUM_OF_CONTACTS, file_ptr)!= NUM_OF_CONTACTS)
	{
		puts("failed to write to file");
		return 1;
	}
	
	rewind(file_ptr); 

	if(fread(copy_arr, sizeof(Contact_t), NUM_OF_CONTACTS, file_ptr)!= NUM_OF_CONTACTS)
	{
		puts("failed to read from file");
		return 1;
	}
	
	if(fclose(file_ptr))
	{
		puts("failed to read from file");
		return 1;
	}

	printf("the name is %s\n", copy_arr[1].f_name);
	printf("the size of copy_arr struct is: %lu\n", SIZEOF(copy_arr));
	printf("the size of copy_arr struct is: %lu\n", sizeof(copy_arr));
	printf("the size of type contact_t is: %lu\n", SIZE_OF_TYPE(Contact_t));
	printf("the size of type contact_t is: %lu\n", sizeof(Contact_t));
	printf("the size of yasmin name is %lu\n", SIZEOF(copy_arr[1].f_name));
	return 0;
}
