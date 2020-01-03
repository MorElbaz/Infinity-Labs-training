#ifndef CALC_H_
#define CALC_H_

typedef struct calc calc_t;

typedef enum
{
    CALC_SUCCESS = 0,
    CALC_ALLOC = 1,
    CALC_SYNTAX_ERROR = 2,
    CALC_MATH_ERROR = 3
}calc_status_t;

calc_t *CalcCreate();

/*accept integers, floating points, spaces and parenthesis*/
calc_status_t Calc(calc_t *calc, const char *str, double *ret);

void CalcDestroy(calc_t *calc);

#endif /*CALC_H_*/
