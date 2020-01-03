#include <string.h>/*str6*/
#include <stdio.h>/*sprintf*/
#include <stdlib.h>/*calloc*/

#include "bitarray.h"

typedef struct
{
    int x;
    int y;
    int options_count;
}option_t;

static size_t CalcIdx(int x, int y)
{
    return (x * 8 + y + 1);
}

int IsValidOption(int x, int y, unsigned long board)
{
    return (!((x < 0) || (x > 7) || (y < 0) || (y > 7) || 
             (IsOn(board, CalcIdx(x, y)))));
}

int KnightTourImpl(int x, int y, int *buf, unsigned long board)
{
    if (! IsValidOption(x, y, board))
    {
        return (1);
    }
    
    board = SetOn(board, CalcIdx(x, y));
    *buf = x;
    *(buf + 1) = y;
    
    if (AllOn() == board)
    {
        return (0);
    }
    
    if (KnightTourImpl(x - 2, y + 1, buf + 2, board) == 0)
    {
        return (0);
    }
    
    if (KnightTourImpl(x - 1, y + 2, buf + 2, board) == 0)
    {
        return (0);
    }
    
    if (KnightTourImpl(x + 1, y + 2, buf + 2, board) == 0)
    {
        return (0);
    }
    
    if (KnightTourImpl(x + 2, y + 1, buf + 2, board) == 0)
    {
        return (0);
    }
    
    if (KnightTourImpl(x + 2, y - 1, buf + 2, board) == 0)
    {
        return (0);
    }
    
    if (KnightTourImpl(x + 1, y - 2, buf + 2, board) == 0)
    {
        return (0);
    }
    
    if (KnightTourImpl(x - 1, y - 2, buf + 2, board) == 0)
    {
        return (0);
    }
    
    if (KnightTourImpl(x - 2, y - 1, buf + 2, board) == 0)
    {
        return (0);
    }
    
    return (1);
    
}

static int CountOptions(option_t option, unsigned long board)
{
    int x = option.x;
    int y = option.y;
    
    if (! IsValidOption(x, y, board))
    {
        return (-1);
    }
    
    return (IsValidOption(x - 2, y + 1, board) + 
            IsValidOption(x - 1, y + 2, board) +
            IsValidOption(x + 1, y + 2, board) +
            IsValidOption(x + 2, y + 1, board) +
            IsValidOption(x + 2, y - 1, board) +
            IsValidOption(x + 1, y - 2, board) +
            IsValidOption(x - 1, y - 2, board) +
            IsValidOption(x - 2, y - 1, board));
}

int CmpOptions(const void *data1, const void *data2)
{
    return (((option_t*)data1)->options_count - ((option_t*)data2)->options_count);
}

int KnightTourImplOpt(int x, int y, int *buf, unsigned long board)
{
    option_t options_arr[8];
    char buffer[64];
    int i;
    
    if (! IsValidOption(x, y, board))
    {
        return (1);
    }
    
    board = SetOn(board, CalcIdx(x, y));
    *buf = x;
    *(buf + 1) = y;
    
    if (AllOn() == board)
    {
        return (0);
    }
 
    options_arr[0].x = x - 2;
    options_arr[0].y = y + 1;
    options_arr[1].x = x - 1;
    options_arr[1].y = y + 2;
    options_arr[2].x = x + 1;
    options_arr[2].y = y + 2;
    options_arr[3].x = x + 2;
    options_arr[3].y = y + 1;
    options_arr[4].x = x + 2;
    options_arr[4].y = y - 1;
    options_arr[5].x = x + 1;
    options_arr[5].y = y - 2;
    options_arr[6].x = x - 1;
    options_arr[6].y = y - 2;
    options_arr[7].x = x - 2;
    options_arr[7].y = y - 1;
    
    for (i = 0; i < 8; ++i)
    {
        options_arr[i].options_count = CountOptions(options_arr[i], board);
    }

    qsort(options_arr, 8, sizeof(option_t), CmpOptions);
    
    for (i = 0; i < 8; ++i)
    {
        if (options_arr[i].options_count > -1)
        {
            if (! KnightTourImplOpt(options_arr[i].x, options_arr[i].y, buf + 2, board))
            {
                return (0);
            }
        }
    }
    
    return (1);
}

void KnightTour(int x, int y, int *buf)
{
    /*KnightTourImpl(x, y, buf, 0U);*/
    KnightTourImplOpt(x, y, buf, 0U);
}

int main ()
{
    int i = 0;
    int j = 0;
    int k;
    int arr[8][8] = {0};
    int *p = (int *)calloc(64 * 2, sizeof(int));
    if(p == NULL)
    {
        printf("YEAH MUDDER FUKER\n");
    }

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            printf("%d ", arr[i][j]);
        }

        printf("\n");
        
    }
    sleep(1);
    system("clear");
        
    KnightTour(0,0, p);

    for (k = 0; k < 128; k += 2)
    {
        arr[p[k]][p[k + 1]] = 1;

        for (i = 0; i < 8; ++i)
        {
            for (j = 0; j < 8; ++j)
            {
                printf("%d ", arr[i][j]);
            }

            printf("\n");
        }

        sleep(1);
        system("clear");
    }

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            printf("%d ", arr[i][j]);
        }

        printf("\n");
    }
    
    return (0);
}
