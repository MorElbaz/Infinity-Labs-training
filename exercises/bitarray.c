#include <stdio.h>/*sprintf*/

#include "bitarray.h"

#define LONG_BITS (sizeof(long unsigned) * 8)
#define LONG_BYTES (sizeof(long unsigned))
#define BITS_IN_BYTE 8


unsigned long AllOn()/*Chen*/
{
    
    return (~(0UL));
}

unsigned long AllOff()
{
    return (0UL);
}

void PrintLTM(unsigned long bit_arr, char *buffer)
{
    unsigned int i;
    
    for(i = 0; i < LONG_BITS; ++i)
    {
        sprintf(buffer, "%lu", ((bit_arr >> i) & 1));
        ++buffer;
    }
    *buffer = 0;
}

void PrintMTL(unsigned long bit_arr, char *buffer)
{
    int i;

    for(i = LONG_BITS - 1; i >= 0; --i)
    {
        sprintf(buffer, "%lu", ((bit_arr >> i) & 1));
        ++buffer;
    }
    *buffer = 0;
}


int IsOn(unsigned long bit_arr, unsigned int bit_num)
{
    return ((bit_arr >> (bit_num-1)) & 1);
}

int IsOff(unsigned long bit_arr, unsigned int bit_num)
{
    return !((bit_arr >> (bit_num-1)) & 1);
}


unsigned long FlipBit(unsigned long bit_arr, unsigned int bit_num)
{
    return (bit_arr ^ (1UL << (bit_num-1)));
}


unsigned long SetOn(unsigned long bit_arr, unsigned int bit_num)
{
    
    return (bit_arr | (1UL << (bit_num-1)));
}

unsigned long SetOff(unsigned long bit_arr, unsigned int bit_num)
{
    return (bit_arr & (~(1UL << (bit_num-1))));
}   


unsigned long SetBit(unsigned long bit_arr, unsigned int bit_num, int bit_stat)
{
    if (bit_stat)
    {
        return (bit_arr | (1UL << (bit_num-1)));
    }
    
    return (bit_arr & (~(1UL << (bit_num-1))));
}

static int CountInternal(unsigned long bit_arr)
{
    int count = 0;
    
    while (bit_arr)
    {
        ++count;
        bit_arr &= bit_arr-1;
    }
    
    return count;
}


int CountOff(unsigned long bit_arr)
{
    int count = 0;
    
    while (bit_arr)
    {
        ++count;
        bit_arr &= bit_arr-1;
    }   
    
    return (LONG_BITS - count);
}

unsigned long RoatetLeft(unsigned long bit_arr, int bit_shift)
{
    bit_shift %= LONG_BITS;
    
    return ((bit_arr << bit_shift) | (bit_arr >> (LONG_BITS - bit_shift)));
}


unsigned long RoatetRight(unsigned long bit_arr, int bit_shift)
{
    bit_shift %= LONG_BITS;
    
    return ((bit_arr >> bit_shift) | (bit_arr << (LONG_BITS-bit_shift)));
}

    
    
int CountOn(unsigned long bit_arr)
{
    static int lut_count[256];
    static int is_init_count = 0;
    int total_set_bits = 0;
    int i;

    if (is_init_count == 0)
    {   
        is_init_count = 1;
        
        for (i = 0; i < 256; ++i)
        {
            lut_count[i] = CountInternal(i);
        }
    }
    
    while (bit_arr)
    {
        total_set_bits += lut_count[bit_arr & 0xff];
        bit_arr >>= BITS_IN_BYTE;
    }

    return (total_set_bits);
}
    
    
    
unsigned long Mirror(unsigned long bit_arr)
{
    static unsigned char lut_mirror[256];
    static int is_init_mirror = 0;
    unsigned int i;
    unsigned char mirror_i;
    unsigned long mirror_bit_arr = 0;

    if (is_init_mirror == 0)
    {   
        is_init_mirror = 1;
        
        for (i = 0; i < 256; ++i)
        {
            mirror_i = i;
            
            mirror_i = ((mirror_i & 0x0f) << 4) | ((mirror_i & 0xf0) >> 4);
            mirror_i = ((mirror_i & 0x33) << 2) | ((mirror_i & 0xcc) >> 2);
            mirror_i = ((mirror_i & 0x55) << 1) | ((mirror_i & 0xaa) >> 1);
            
            lut_mirror[i] = mirror_i;
        }
    }
    
    
    for (i = 0; i < LONG_BYTES; ++i)
    {   
        mirror_bit_arr = (mirror_bit_arr << 8) | lut_mirror[bit_arr & 0xff];
        bit_arr >>= BITS_IN_BYTE;
    }
    
    return (mirror_bit_arr);
    
}   
    
    
    
    


