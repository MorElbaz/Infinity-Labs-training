#include <stdio.h> /* printf */
#include <string.h> /* strncmp */

#include "circ_buf.h" 

void TestCreateAndDestroy(circ_buf_t *ptr);
void TestEmptyIsEmpty(circ_buf_t *ptr);
void TestCapacity(circ_buf_t *ptr);
void TestWriteAndFreeSpace(circ_buf_t *ptr, char *in);
void TestWriteReadSimple(circ_buf_t *ptr, char *in, char *out);
void TestWriteReadMedium(circ_buf_t *ptr, char *in, char *out);
void TestWriteReadHard(circ_buf_t *ptr, char *in, char *out);
void TestWriteReadFinal(circ_buf_t *ptr, char *in, char *out);
void TestWriteReadDoom(circ_buf_t *ptr, char *in, char *out);

int main()
{
	char in[]="12345";
	char in2[]="1234567890987654321";
	char out[10];

	circ_buf_t *ptr = NULL;

	TestCreateAndDestroy(ptr);
	TestEmptyIsEmpty(ptr);
	TestCapacity(ptr);
	TestWriteReadSimple(ptr,in,out);
	TestWriteAndFreeSpace(ptr,in);
	TestWriteReadMedium(ptr,in,out);
	TestWriteReadHard(ptr,in,out);
	TestWriteReadFinal(ptr,in2,out);
	TestWriteReadDoom(ptr,in2,out);

	if (circ_buff_errno != 0)
	{
		printf("There is an error in your code - go find it!\n");
	}

	return 0;
}

void TestCreateAndDestroy(circ_buf_t *ptr)
{
	ptr = CircBufCreate(10);
	CircBufDestroy(ptr);

	printf("You are creator and destroyer of worlds - Now go do valgrind!!!\n");
}

void TestEmptyIsEmpty(circ_buf_t *ptr)
{
	ptr = CircBufCreate(10);

	if (CircBufIsEmpty(ptr) != 1)
	{
		printf("IsEmpty doesn't work - go fix it!\n");
	}

	CircBufDestroy(ptr);
}

void TestCapacity(circ_buf_t *ptr)
{
	size_t n = 7;

	ptr = CircBufCreate(n);

	if (CircBufCapacity(ptr) != n)
	{
		printf("Capacity doesn't work - go fix it!\n");
	}

	CircBufDestroy(ptr);
}


void TestWriteReadSimple(circ_buf_t *ptr, char *in, char *out)
{
	ptr = CircBufCreate(10);

	CircBufWrite(ptr,in,5);

	if (CircBufIsEmpty(ptr) != 0)
	{
		printf("Write doesn't work - go fix it!\n");
	}

	CircBufRead(ptr,out,5);

	if (CircBufIsEmpty(ptr) != 1)
	{
		printf("Read doesn't work - go fix it!\n");
	}

	CircBufDestroy(ptr);
}

void TestWriteAndFreeSpace(circ_buf_t *ptr, char *in)
{
	ptr = CircBufCreate(10);

	CircBufWrite(ptr,in,4);

	if (CircBufFreeSpace(ptr) != 6)
	{
		printf("Free Space doesn't work - go fix it!\n");
	}

	CircBufDestroy(ptr);
}

void TestWriteReadMedium(circ_buf_t *ptr, char *in, char *out)
{
	ptr = CircBufCreate(10);

	CircBufWrite(ptr,in,3);
	CircBufRead(ptr,out,3);

	if (strncmp(out,"12345",3) != 0)
	{
		printf("Read/write medium test 1 doesn't work - go fix it!\n");
	}

	CircBufWrite(ptr,in,5);
	CircBufWrite(ptr,in,5);
	CircBufRead(ptr,out,10);

	if (strncmp(out,"1234512345",10) != 0)
	{
		printf("Read/write medium test 2 doesn't work - go fix it!\n");
	}

	CircBufDestroy(ptr);
}

void TestWriteReadHard(circ_buf_t *ptr, char *in, char *out)
{
	ptr = CircBufCreate(10);

	CircBufWrite(ptr,in,3);
	CircBufWrite(ptr,in,5);
	CircBufRead(ptr,out,8);

	if (strncmp(out,"12312345",8) != 0)
	{
		printf("Read/write hard test 1 doesn't work - go fix it!\n");
	}

	CircBufWrite(ptr,in,5);
	CircBufWrite(ptr,in,5);
	CircBufRead(ptr,out,10);

	if (strncmp(out,"1234512345",10) != 0)
	{
		printf("Read/write hard test 2 doesn't work - go fix it!\n");
	}

	CircBufDestroy(ptr);
}

void TestWriteReadFinal(circ_buf_t *ptr, char *in, char *out)
{
	ptr = CircBufCreate(10);

	CircBufWrite(ptr,in+5,10);
	CircBufRead(ptr,out,10);

	CircBufWrite(ptr,in,5);
	CircBufRead(ptr,out,5);

	if (strncmp(out,"12345",5) != 0)
	{
		printf("Read/write final test 1 doesn't work - go fix it!\n");
	}

	CircBufDestroy(ptr);
}

void TestWriteReadDoom(circ_buf_t *ptr, char *in, char *out)
{
	ptr = CircBufCreate(10);

	CircBufWrite(ptr,in,10);
	CircBufRead(ptr,out,5);
	CircBufRead(ptr,out,5);

	if (strncmp(out,"67890",5) != 0)
	{
		printf("Read/write doom test 1 doesn't work - go fix it!\n");
	}

	CircBufDestroy(ptr);
}




/*#include <stdio.h>*/

/*#include "circ_buf.h"*/

/*void TestWrite();*/
/*void TestRead();*/

/*int main()*/
/*{*/
/*	circ_buf_t *circ_buf = CircBufCreate(10);*/
/*	TestWrite();*/
/*	TestRead();*/
/*	*/
/*	*/
/*	return 0;*/
/*}*/


/*void TestWrite()*/
/*{*/
/*	char buf[20]= "cheking write func";*/
/*	circ_buf_t *circ_buf = CircBufCreate(10);*/
/*	*/
/*	if(CircBufWrite(circ_buf, buf, 5) != 5)*/
/*	{*/
/*		fprintf(stderr,"first write failed");*/
/*	}*/
/*	if(circ_buff_errno != 0)*/
/*	{*/
/*		fprintf(stderr,"wrong errno value after first write");*/
/*	}*/
/*	*/
/*	if(CircBufWrite(circ_buf, buf + 5, 3) != 3)*/
/*	{*/
/*		fprintf(stderr,"second write failed");*/
/*	}*/
/*	if(circ_buff_errno != 0)*/
/*	{*/
/*		fprintf(stderr,"wrong errno value after second write");*/
/*	}*/
/*		*/
/*	if(CircBufWrite(circ_buf, buf + 8, 5) != 2)*/
/*	{*/
/*		fprintf(stderr,"third write failed");*/
/*	}*/
/*	if(circ_buff_errno != 1)*/
/*	{*/
/*		fprintf(stderr,"wrong errno value after third write");*/
/*	}*/
/*	*/
/*	CircBufDestroy(circ_buf);*/
/*		*/
/*}*/
/*	*/
/*	*/
/*void TestRead()*/
/*{*/
/*	char buf[20];*/
/*	char buf2[20] = "this is buf2";*/
/*	circ_buf_t *circ_buf = CircBufCreate(10);*/
/*	*/
/*	if(CircBufWrite(circ_buf, buf2, 5) != 5)*/
/*	{*/
/*		fprintf(stderr,"first write failed\n");*/
/*	}*/
/*	if(circ_buff_errno != 0)*/
/*	{*/
/*		fprintf(stderr,"wrong errno value after first write\n");*/
/*	}*/
/*	*/
/*	if(CircBufWrite(circ_buf, buf2 + 5, 3) != 3)*/
/*	{*/
/*		fprintf(stderr,"second write failed\n");*/
/*	}*/
/*	if(circ_buff_errno != 0)*/
/*	{*/
/*		fprintf(stderr,"wrong errno value after second write\n");*/
/*	}*/
/*	*/
/*	*/
/*	if(CircBufRead(circ_buf, buf, 5) != 5)*/
/*	{*/
/*		fprintf(stderr,"first ead failed\n");*/
/*	}*/
/*	if(circ_buff_errno != 0)*/
/*	{*/
/*		fprintf(stderr,"wrong errno value after first read\n");*/
/*	}*/
/*	*/
/*	if(CircBufRead(circ_buf, buf + 5, 2) != 2)*/
/*	{*/
/*		fprintf(stderr,"second read failed\n");*/
/*	}*/
/*	if(circ_buff_errno != 0)*/
/*	{*/
/*		fprintf(stderr,"wrong errno value after second read\n");*/
/*	}*/
/*	*/
/*	if(CircBufRead(circ_buf, buf + 7, 3) != 1)*/
/*	{*/
/*		fprintf(stderr,"third read failed\n");*/
/*	}*/
/*	if(circ_buff_errno != 2)*/
/*	{*/
/*		fprintf(stderr,"wrong errno value after third read\n");*/
/*	}*/

/*	CircBufDestroy(circ_buf);*/
/*}*/
/*	*/
	
/*TestIsEmpty()*/
/*{*/
/*	circ_buf_t *circ_buf = CircBufCreate(10);*/
/*	*/
