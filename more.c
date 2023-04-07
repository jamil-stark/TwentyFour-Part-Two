#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int *values;
    char *operators;
    int value_top;
    int operator_top;
} Stack;

void push_value(Stack *s, int value)
{
    s->values[++s->value_top] = value;
}

int pop_value(Stack *s)
{
    return s->values[s->value_top--];
}

void push_operator(Stack *s, char op)
{
    s->operators[++s->operator_top] = op;
}

char pop_operator(Stack *s)
{
    return s->operators[s->operator_top--];
}

int is_operator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

void evaluate_operation(Stack *s)
{
    int b = pop_value(s);
    int a = pop_value(s);
    char op = pop_operator(s);
    int result;
    switch (op)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        result = a / b;
        break;
    }
    push_value(s, result);
    printf("%d %c %d = %d.\n", a, op, b, result);
}

int evaluate_expression(char *input)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->values = malloc(strlen(input) * sizeof(int));
    stack->operators = malloc(strlen(input) * sizeof(char));
    stack->value_top = -1;
    stack->operator_top = -1;

    int i = 0;
    while (input[i] != '\0')
    {
        if (isdigit(input[i]))
        {
            int value = 0;
            while (isdigit(input[i]))
            {
                value = value * 10 + (input[i] - '0');
                i++;
            }
            push_value(stack, value);
        }
        else if (is_operator(input[i]))
        {
            while (stack->operator_top >= 0 &&
                   stack->operators[stack->operator_top] != '(' &&
                   precedence(input[i]) <= precedence(stack->operators[stack->operator_top]))
            {
                evaluate_operation(stack);
            }
            push_operator(stack, input[i]);
            i++;
        }
        else if (input[i] == '(')
        {
            push_operator(stack, '(');
            i++;
        }
        else if (input[i] == ')')
        {
            while (stack->operator_top >= 0 && stack->operators[stack->operator_top] != '(')
            {
                evaluate_operation(stack);
            }
            pop_operator(stack); // discard the left parenthesis
            i++;
        }
        else
        {
            // skip over any whitespace or unrecognized characters
            i++;
        }
    }

    // evaluate any remaining operators on the stack
    while (stack->operator_top >= 0)
    {
        evaluate_operation(stack);
    }

    int final_result = pop_value(stack);
    printf("Final result: %d.\n", final_result);
    free(stack->values);
    free(stack->operators);
    free(stack);
    return final_result;
}

int sizeofInput = 0;

int main()
{
    char input[100];
    printf("Enter an arithmetic expression: ");
    fgets(input, sizeof(input), stdin);
    sizeofInput = strlen(input);
    int fineCharacters = 1;
    int finedigits = 1;
    char digitChar = '0';
    for (int c = 0; c < sizeofInput; c++)
    {
        fineCharacters = 0;
        if (((input[c] == '(')) || isdigit(input[c]) || ((input[c] == ')')) || isspace(input[c]) || ((input[c] == '*')) || ((input[c] == '/')) || ((input[c] == '+')) || ((input[c] == '-')))
        {
            fineCharacters = 1;
        }
        else
        {
            fineCharacters = 0;
            printf("Invalid Characters.\n");
            break;
        }



    }

    if (fineCharacters){
        for (int l = 0; l < sizeofInput; l++)
        {
                       if (isdigit(input[l]))
            {
                digitChar = input[l];
                if ((digitChar - '0' != 2) && (digitChar - '0' != 3) && (digitChar - '0' != 4) && (digitChar - '0' != 5))
                {
                    finedigits = 0;
                    printf("\nUse specific numbers\n");
                    break;
                }
                else
                {
                    finedigits = 1;
                }
            }
        }
        
    }

    if (fineCharacters && finedigits)
    {
        input[strcspn(input, "\n")] = '\0'; // remove the newline character at the end of the input
        int result = evaluate_expression(input);
        printf("The result is: %d\n", result);
    }
    else
    {
        printf("Kibulamu ku bwerufu");
    }

    return 0;
}

