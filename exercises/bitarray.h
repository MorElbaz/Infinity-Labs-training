#include <stddef.h>/*size_t*/

#ifndef BITARRAY_H_
#define BITARRAY_H_

unsigned long AllOn();
unsigned long AllOff();

/* print from the least significant bit to most significant bit */
void PrintLTM(unsigned long bit_arr, char *buffer);

/* print from the most significant bit to least significant bit */
void PrintMTL(unsigned long bit_arr, char *buffer);

/* set a specific bit according to the input in bit_stat (0 or 1) */
unsigned long SetBit(unsigned long bit_arr, unsigned int bit_num, int bit_stat);

/* set a specific bit off */
unsigned long SetOff(unsigned long bit_arr, unsigned int bit_num);

/* set a specific bit on */
unsigned long SetOn(unsigned long bit_arr, unsigned int bit_num);

/* return 1 if true 0 if false*/
int IsOn(unsigned long bit_arr, unsigned int bit_num);

/* return 1 if true 0 if false*/
int IsOff(unsigned long bit_arr, unsigned int bit_num);

unsigned long FlipBit(unsigned long bit_arr, unsigned int bit_num);
unsigned long RoatetLeft(unsigned long bit_arr, int bit_shift);
unsigned long RoatetRight(unsigned long bit_arr, int bit_shift);
unsigned long Mirror(unsigned long bit_arr);
/* return the bit number which on*/
int CountOn(unsigned long bit_arr);
/* return the bit number which off*/
int  CountOff(unsigned long bit_arr);

#endif /*BITARRAY_H_*/

