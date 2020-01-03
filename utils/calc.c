#include <stdlib.h>/*malloc*/
#include <math.h>/*pow*/
#include <string.h>/*strlen*/
#include <assert.h>/*assert*/

#include "calc.h"
#include "stack.h"

#define NUM_OF_STATES 2

typedef unsigned char uchar;

typedef enum
{
    POW_PR, 
    MUL_PR,
    DIV_PR = MUL_PR,
    ADD_PR,
    SUB_PR = ADD_PR,
    PARENTHESIS_PR
}precedence_t;

typedef enum

{
    EXP_OPERAND = 0,
    EXP_OPERATOR = 1
}state_t;

typedef struct
{
    double (*operator_func)(double operand1, double operand2);
    precedence_t precedence;
}operator_data_t;

typedef calc_status_t (*handler_func_t)(calc_t *calc, const char **event);

struct calc
{
    operator_data_t lut_operators[256];
    handler_func_t  events_per_state[NUM_OF_STATES][256];
    state_t         state;
    stack_t        *operands;
    stack_t        *operators;
};
    

static double Add(double operand1, double operand2)
{
    return (operand1 + operand2);
}

static double Substract(double operand1, double operand2)
{
    return (operand1 - operand2);
}

static double Multiply(double operand1, double operand2)
{
    return (operand1 * operand2);
}

static double Divide(double operand1, double operand2)
{
    return (operand1 / operand2);
}

static precedence_t GetPrecedence(calc_t *calc, const char *operator)
{
    return (calc->lut_operators[(uchar)*operator].precedence);
}

static void *PeekAndPop(stack_t *stack)
{
    void *data = StackPeek(stack);
    
    StackPop(stack);
    
    return (data);
}

static calc_status_t HandleOpenBrackets(calc_t *calc, const char **event)
{
    StackPush(calc->operators, *event);
    ++(*event);
    
    return (CALC_SUCCESS);
}

static calc_status_t HandleOperand(calc_t *calc, const char **event)
{
    char *ptr = NULL;
    double operand = strtod(*event, &ptr);
    
    if (ptr == *event)
    {
        return (CALC_SYNTAX_ERROR);
    }
    
    *event = ptr;
    StackPush(calc->operands, &operand);
    calc->state = EXP_OPERATOR;
    
    return (CALC_SUCCESS);
}

static calc_status_t Calculate(calc_t *calc)
{
    double *first_operand = (double *)PeekAndPop(calc->operands);
    double *second_operand = (double *)PeekAndPop(calc->operands);
    char curr_operator = *(char*)PeekAndPop(calc->operators);
    
    if ((curr_operator == '/') && (*first_operand == 0))
    {        
        return (CALC_MATH_ERROR);
    }
    
    *first_operand = 
    (calc->lut_operators[(uchar)curr_operator].operator_func)
                                              (*second_operand, *first_operand);
                                                            
    StackPush(calc->operands, first_operand);
    
    return (CALC_SUCCESS);
}    

static calc_status_t HandleOperator(calc_t *calc, const char **event)
{
    char curr = **event;
    
    if (curr != '^')
    {
        while ((StackSize(calc->operators) > 0) &&  
              ((GetPrecedence(calc, &curr)) >= 
              (GetPrecedence(calc, StackPeek(calc->operators)))))
        {
            if (Calculate(calc) != CALC_SUCCESS)
            {
                return (CALC_MATH_ERROR);
            }
        }
    }
    
    StackPush(calc->operators, *event);
    ++(*event);
    calc->state = EXP_OPERAND;
    
    return (CALC_SUCCESS);
}

static calc_status_t HandleCloseBrackets(calc_t *calc, const char **event)
{
    calc_status_t ret_status = CALC_SUCCESS;
    (void)event;
    
    while ((StackSize(calc->operators) > 0) && 
           (*(char*)StackPeek(calc->operators) != '('))
    {
        ret_status = Calculate(calc);
    }
    
    if (StackSize(calc->operators) == 0)
    {
        return (CALC_SYNTAX_ERROR);
    }
    
    StackPop(calc->operators);
    ++(*event);
    
    return (ret_status);
}

static calc_status_t HandleFatalError(calc_t *calc, const char **event)
{
    (void)calc;
    (void)event;
    
    return (CALC_SYNTAX_ERROR);
}


static calc_status_t HandleSpace(calc_t *calc, const char **event)
{
    (void)calc;
    ++(*event);
    
    return (CALC_SUCCESS);
}

static calc_status_t HandleNull(calc_t *calc, const char **event)
{
    (void)event;
    
    while (StackSize(calc->operands) > 1)
    {
        if (Calculate(calc) != CALC_SUCCESS)
        {
            return (CALC_MATH_ERROR);
        }
    }
    
    if (StackSize(calc->operators) != 0)
    {
        return (CALC_SYNTAX_ERROR);
    }
    
    return (CALC_SUCCESS);
}

static void InitLutOperators(calc_t *calc)
{    
    calc->lut_operators['+'].operator_func = Add;
    calc->lut_operators['+'].precedence    = ADD_PR;
    
    calc->lut_operators['-'].operator_func = Substract;
    calc->lut_operators['-'].precedence    = SUB_PR;
    
    calc->lut_operators['*'].operator_func = Multiply;
    calc->lut_operators['*'].precedence    = MUL_PR;
    
    calc->lut_operators['/'].operator_func = Divide;
    calc->lut_operators['/'].precedence    = DIV_PR;
    
    calc->lut_operators['^'].operator_func = pow;
    calc->lut_operators['^'].precedence    = POW_PR;
    
    calc->lut_operators['('].precedence    = PARENTHESIS_PR;
}
static void InitEventsPerState(calc_t *calc)
{
    int state;
    int event;
    
    for (state = 0; state < NUM_OF_STATES; ++state)
    {
        for(event = 0; event < 256; ++event)
        {
            calc->events_per_state[state][event] = HandleFatalError;
        }
    }
    
    for(event = '0'; event <= '9'; ++event)
    {
        calc->events_per_state[EXP_OPERAND][event] = HandleOperand;
    }
    
    calc->events_per_state[EXP_OPERATOR]['+']  = HandleOperator;
    calc->events_per_state[EXP_OPERATOR]['-']  = HandleOperator;
    calc->events_per_state[EXP_OPERATOR]['*']  = HandleOperator;
    calc->events_per_state[EXP_OPERATOR]['/']  = HandleOperator;
    calc->events_per_state[EXP_OPERATOR]['^']  = HandleOperator;
    calc->events_per_state[EXP_OPERATOR]['\0'] = HandleNull;
    calc->events_per_state[EXP_OPERATOR][' ']  = HandleSpace;
    calc->events_per_state[EXP_OPERATOR][')']  = HandleCloseBrackets;
    
    calc->events_per_state[EXP_OPERAND]['+'] = HandleOperand;
    calc->events_per_state[EXP_OPERAND]['-'] = HandleOperand;
    calc->events_per_state[EXP_OPERAND]['.'] = HandleOperand;
    calc->events_per_state[EXP_OPERAND][' '] = HandleSpace;
    calc->events_per_state[EXP_OPERAND]['('] = HandleOpenBrackets;
}
    
calc_t *CalcCreate()
{
    calc_t *calc = (calc_t *) calloc(1, sizeof(calc_t));
    if (calc == NULL)
    {
        return (NULL);
    }
    
    InitLutOperators(calc);
    InitEventsPerState(calc);
    
    return (calc);
}

/*accept integers, floating points, spaces and parenthesis*/
calc_status_t Calc(calc_t *calc, const char *str, double *ret)
{
    size_t len = 0;
    size_t i = 0;
    calc_status_t ret_status = CALC_SUCCESS;
    calc->state = EXP_OPERAND;
    
    assert(calc != NULL);
    assert(ret != NULL);
    
    len = strlen(str);
    
    calc->operands = StackCreate(sizeof(double), len);
    if (calc->operands == NULL)
    {
        return (CALC_ALLOC);
    }
    
    calc->operators = StackCreate(sizeof(char), len);
    if (calc->operators == NULL)
    {
        StackDestroy(calc->operands);
        
        return (CALC_ALLOC);
    }
    
    while ((i <= len) && (ret_status == CALC_SUCCESS))
    {
        ret_status = (calc->events_per_state[calc->state][(uchar)*str])(calc, &str);
        ++i;
    }
    
    if (StackSize(calc->operands) == 1)
    {
        *ret = *(double*)(StackPeek(calc->operands));
    }
    
    StackDestroy(calc->operands);
    StackDestroy(calc->operators);
    
    return (ret_status);
}

void CalcDestroy(calc_t *calc)
{
    free(calc);
}

