#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
FILE *fp;
int count = 1;
char c;
int easyArray[100][4];
int i, j;
int lines;
int valueToUseInFileName = 0;
int randomNumber, num1, num2, num3, num4, result;
int option = 0;

int main()
{
    srand(1);
    int size;

    char letterChose[2];
    printf("Welcome to the game of TwentyFour Part Two!\nUse each of the four numbers shown exactly once,\ncombining them somehow with the basic mathematical operators (+,-,*,/)\nto yield the value twenty-four.");
    chooseText(letterChose);                                // Prompt User to enter letter for difficulty.
    lines = changeLevelAndReturnNumberOfLines(letterChose); // call the function which returns number of lines corresponding with the selected difficulty.
    initArray(lines);                                       // Set the array values.

    printNumbersToUse();
    // printf("The result is: %d\n", result);
    while (option != 3)
    {
        option = prompt();
        if (option == 1)
        {
            printNumbersToUse();
        }
        else if (option == 2)
        {
            chooseText(letterChose);                                // Prompt User to enter letter for difficulty.
            lines = changeLevelAndReturnNumberOfLines(letterChose); // call the function which returns number of lines corresponding with the selected difficulty.
            initArray(lines);                                       // Set the array values.

            printNumbersToUse();
        }
        else{
            break;
        }
    }

    printf("Thanks for playing!\nExiting...");

    return 0;
}

int sizeofInput = 0;
void printNumbersToUse()
{

    int fineCharacters = 1;
    int finedigits = 1;
    char digitChar = '0';
    int outOfLoop = 0;
    int err = 0;

    while (!outOfLoop)
    {
        selectRandomNumbers();
        printf("The numbers to use are: %d, %d, %d, %d.\n", num1, num2, num3, num4);
        char input[100];
        printf("Enter your solution: ");
        fgets(input, sizeof(input), stdin);
        sizeofInput = strlen(input);
        if (sizeofInput < 2)
        {
            continue;
        }

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
                printf("\nError! Invalid symbol entered. Please try again.\n\n");
                break;
            }
        }

        if (fineCharacters)
        {
            for (int l = 0; l < sizeofInput; l++)
            {
                if (isdigit(input[l]))
                {
                    digitChar = input[l];
                    if ((digitChar - '0' != num1) && (digitChar - '0' != num2) && (digitChar - '0' != num3) && (digitChar - '0' != num4))
                    {

                        finedigits = 0;
                        printf("\nError! You must use all four numbers, and use each only once. Please try again.\n\n");
                        err = 1;
                        break;
                    }
                    else
                    {
                        if ((digitChar - '0' == num1))
                        {
                            num1 = 100;
                        }
                        else if ((digitChar - '0' == num2))
                        {
                            num2 = 100;
                        }
                        else if ((digitChar - '0' == num3))
                        {
                            num3 = 100;
                        }
                        else if ((digitChar - '0' == num4))
                        {
                            num4 = 100;
                        }
                    }
                }
            }

            if (num1 == 100 && num2 == 100 && num3 == 100 && num4 == 100)
            {
                finedigits = 1;
            }
            else
            {
                if (!err)
                {
                    // printf("nummbers : %d %d %d %d", num1, num2, num3, num4);
                    finedigits = 0;
                    printf("\nError! You must use all four numbers, and use each only once. Please try again.\n\n");
                    err = 1;
                }
            }
        }

        if (fineCharacters && finedigits)
        {
            input[strcspn(input, "\n")] = '\0'; // remove the newline character at the end of the input
            result = evaluate_expression(input);
            if (result == 24)
            {
                printf("Well done! You are a math genius.\n\n");
            }
            else
            {
                printf("Sorry. Your soulution did not evaluate to 24.\n\n");
            }

            outOfLoop = 1;
        }
        // else
        // {
        //     printf("Kibulamu ku bwerufu");
        // }
    }
}

int prompt()
{
    option = 1;
    printf("Enter: \t1 to play again,\n\t2 to change the difficulty level and then play again, or\n\t3 to exit the program.\n\tYour choice --> ");
    scanf("%d", &option);
    while (getchar() != '\n');

    return option;
}

void chooseText(char *letterChose)
{
    printf("\nChoose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\nYour choice --> ");
    scanf("%s", letterChose);
    while (getchar() != '\n');
}

int changeLevelAndReturnNumberOfLines(char letterToCompare[2])
{
    int linecount = 0;
    if (strcmp(letterToCompare, "M") == 0)
    {
        valueToUseInFileName = 1; // changed such that we keep track of level chose.
        linecount = countNumberOfLines("medium (1).txt");
    }
    else if (strcmp(letterToCompare, "H") == 0)
    {
        valueToUseInFileName = 2;
        linecount = countNumberOfLines("hard.txt");
    }
    else
    {
        valueToUseInFileName = 0;
        linecount = countNumberOfLines("easy.txt");
    }

    return linecount;
}

int countNumberOfLines(char filename[20])
{

    count = 1;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n')
        {
            count++;
        }
    }
    fclose(fp);

    return count;
}

void initArray(int size)
{
    if (valueToUseInFileName == 1)
    {
        fp = fopen("medium (1).txt", "r");
    }
    else if (valueToUseInFileName == 2)
    {
        fp = fopen("hard.txt", "r");
    }
    else
    {
        fp = fopen("easy.txt", "r");
    }

    if (fp == NULL)
    {
        printf("Error opening file.");
        return 1;
    }

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < 4; j++)
        {
            fscanf(fp, "%d", &easyArray[i][j]);
        }
    }
}

void selectRandomNumbers()
{
    randomNumber = rand() % lines; // generate a radndom number between 0 and size of identified file.
    // printf("Random number: %d \n", randomNumber);
    num1 = easyArray[randomNumber][0];
    num2 = easyArray[randomNumber][1];
    num3 = easyArray[randomNumber][2];
    num4 = easyArray[randomNumber][3];
}

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
