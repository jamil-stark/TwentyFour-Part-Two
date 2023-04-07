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
                int b = pop_value(stack);
                int a = pop_value(stack);
                char op = pop_operator(stack);
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
                push_value(stack, result);
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
                int b = pop_value(stack);
                int a = pop_value(stack);
                char op = pop_operator(stack);
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
                push_value(stack, result);
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
        int b = pop_value(stack);
        int a = pop_value(stack);
        char op = pop_operator(stack);
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
        push_value(stack, result);
    }
    int final_result = pop_value(stack);
    free(stack->values);
    free(stack->operators);
    free(stack);
    return final_result;
}

int main()
{
    char input[100];
    printf("Enter an expression: ");
    fgets(input, 100, stdin);
    // remove newline character from input
    input[strcspn(input, "\n")] = '\0';
    int result = evaluate_expression(input);
    printf("Result: %d\n", result);

    return 0;
}