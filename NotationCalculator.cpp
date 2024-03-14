#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_EXPRESSION_LEN 50

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
} Stack;

void init(Stack *s)
{
    s->top = NULL;
}

int isEmpty(Stack *s)
{
    return s->top == NULL;
}

void push(Stack *s, char value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

char getTop(Stack *s)
{
    return s->top->data;
}

int pop(Stack *s)
{
    if (isEmpty(s))
    {
        puts("Stack is empty");
        return -1;
    }

    Node *del = s->top;
    int temp = del->data;
    s->top = s->top->next;
    free(del);
    return temp;
}

int isOp(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int getPrecedence(char c)
{
    switch (c)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return -1;
    }
}

void infixToPrefix(char infix[], char prefix[])
{
    Stack stack;
    init(&stack);
    int len = strlen(infix);
    char infixCopy[MAX_EXPRESSION_LEN];
    strcpy(infixCopy, infix);

    int index = 0;

    for (int i = 0; i < len; i++)
    {
        char c = infixCopy[len - i - 1];
        if (isdigit(c))
        {
            // add to prefix
            prefix[index++] = c;
        }
        else if (isOp(c))
        {
            // push operator to stack given operator has higher precedence
            if (isEmpty(&stack) || (getPrecedence(c) > getPrecedence(getTop(&stack))))
            {
                push(&stack, c);
            }
            else
            {
                // empty stack if current precedence less or equal to operators in stack
                char top = getTop(&stack);
                while (isOp(top) && getPrecedence(c) <= getPrecedence(top))
                {
                    prefix[index++] = pop(&stack);
                    if (isEmpty(&stack))
                    {
                        break;
                    }
                    else
                    {
                        top = getTop(&stack);
                    }
                }
                push(&stack, c);
            }
        }
        else if (c == ')')
        {
            push(&stack, c);
        }
        else if (c == '(')
        {
            char top = getTop(&stack);
            while (isOp(top) && c != ')')
            {
                prefix[index++] = pop(&stack);
                top = getTop(&stack);
            }
            pop(&stack);
        }
        else
        {
            puts("invalid character!");
        }
    }

    // empty remaining operators in stack
    while (!isEmpty(&stack))
    {
        prefix[index++] = pop(&stack);
    }

    prefix[index] = '\0';
    strrev(prefix);
}

void infixToPostfix(char infix[], char postfix[])
{
    Stack stack;
    init(&stack);
    int len = strlen(infix);
    char infixCopy[50];
    strcpy(infixCopy, infix);

    int index = 0;

    for (int i = 0; i < len; i++)
    {
        char c = infixCopy[i];
        if (isdigit(c))
        {
            // add to prefix
            postfix[index++] = c;
        }
        else if (isOp(c))
        {
            // push operator to stack given operator has higher precedence
            if (isEmpty(&stack) || (getPrecedence(c) > getPrecedence(getTop(&stack))))
            {
                push(&stack, c);
            }
            else
            {
                // empty stack if current precedence less or equal to operators in stack
                char top = getTop(&stack);
                while (isOp(top) && getPrecedence(c) <= getPrecedence(top))
                {
                    postfix[index++] = pop(&stack);
                    if (isEmpty(&stack))
                    {
                        break;
                    }
                    else
                    {
                        top = getTop(&stack);
                    }
                }
                push(&stack, c);
            }
        }
        else if (c == '(')
        {
            push(&stack, c);
        }
        else if (c == ')')
        {
            char top = getTop(&stack);
            while (isOp(top) && c != '(')
            {
                postfix[index++] = pop(&stack);
                top = getTop(&stack);
            }
            pop(&stack);
        }
        else
        {
            puts("invalid character!");
        }
    }

    // empty remaining operators in stack
    while (!isEmpty(&stack))
    {
        postfix[index++] = pop(&stack);
    }

    postfix[index] = '\0';
}

// Calculate functions
int operate(char op, int num1, int num2)
{
    switch (op)
    {
    case '-':
        return num2 - num1;
        break;
    case '+':
        return num2 + num1;
        break;
    case '/':
        return num2 / num1;
        break;
    case '*':
        return num2 * num1;
        break;
    default:
        return -1;
        break;
    }
}

int calculatePrefix(char prefix[])
{
    Stack stack;
    init(&stack);
    char prefixCopy[50];
    strcpy(prefixCopy, prefix);
    strrev(prefixCopy);

    int len = strlen(prefixCopy);
    for (int i = 0; i < len; i++)
    {
        char c = prefixCopy[i];
        if (isOp(c))
        {
            int num1, num2;
            num1 = pop(&stack);
            num2 = pop(&stack);
            push(&stack, operate(c, num1, num2));
        }
        else
        {
            push(&stack, c - '0');
        }
    }
    int result = pop(&stack);
    return result;
}

int calculatePostfix(char postfix[])
{
    Stack stack;
    init(&stack);

    int len = strlen(postfix);
    for (int i = 0; i < len; i++)
    {
        char c = postfix[i];
        if (isOp(c))
        {
            int num1, num2;
            num1 = pop(&stack);
            num2 = pop(&stack);
            push(&stack, operate(c, num1, num2));
        }
        else
        {
            push(&stack, c - '0');
        }
    }
    int result = pop(&stack);
    return result;
}

// Menu related functions
void viewMenu()
{
    printf("=== Welcome to NotationCalculator! ===\n");
    printf("--------------------------------------\n");
    puts("");
    printf("Operations:\n");
    printf("1. Convert infix to prefix\n");
    printf("2. Convert infix to postfix\n");
    printf("3. Calculate prefix\n");
    printf("4. Calculate postfix\n");
    printf("5. Exit\n");
    puts("");
    printf(">>");
}

void viewToPrefixMenu()
{
    printf("=== Convert Infix to Prefix ===\n\n");
    printf("e.g. 5*3(3-2)\n");
    printf("*enter number between 0-9*\n");
    printf("-------------------------------\n\n");
    printf("Please input an expression with infix notation:\n");
    printf(">>");
}

void viewToPostfixMenu()
{
    printf("=== Convert Infix to Postfix ===\n\n");
    printf("e.g. 5*3(3-2)\n");
    printf("*enter number between 0-9*\n");
    printf("-------------------------------\n\n");
    printf("Please input an expression with infix notation:\n");
    printf(">>");
}

void viewCalcPrefixMenu()
{
    printf("=== Calculate Prefix Expression ===\n\n");
    printf("e.g. *32 -> * 3 2\n");
    printf("*enter number between 0-9*\n");
    printf("-------------------------------\n\n");
    printf("Please input an expression with prefix notation:\n");
    printf(">>");
}

void viewCalcPostfixMenu()
{
    printf("=== Calculate Postfix Expression ===\n\n");
    printf("e.g. 32* -> 3 2 *\n");
    printf("*enter number between 0-9*\n");
    printf("-------------------------------\n\n");
    printf("Please input an expression with postfix notation:\n");
    printf(">>");
}

int main(int argc, char const *argv[])
{
    // Menu
    int option;
    do
    {
        viewMenu();
        scanf("%d", &option);
        getchar();
        system("cls");
        char input[MAX_EXPRESSION_LEN];
        int result;
        switch (option)
        {
        case 1:
            // infix to prefix
            viewToPrefixMenu();
            scanf("%s", input);
            getchar();
            char prefix[MAX_EXPRESSION_LEN];
            infixToPrefix(input, prefix);
            printf("\nPrefix: ");
            printf("%s\n", prefix);
            break;
        case 2:
            // infix to postfix
            viewToPostfixMenu();
            scanf("%s", input);
            getchar();

            char postfix[MAX_EXPRESSION_LEN];
            infixToPostfix(input, postfix);
            printf("\nPostfix: ");
            printf("%s\n", postfix);
            break;
        case 3:
            // calculate prefix
            viewCalcPrefixMenu();
            scanf("%s", input);
            getchar();

            result = calculatePrefix(input);
            printf("= %d\n", result);
            break;
        case 4:
            // calculate postfix
            viewCalcPostfixMenu();
            scanf("%s", input);
            getchar();

            result = calculatePostfix(input);
            printf("= %d\n", result);
            break;
        case 5:
            puts("Thankyou for using NotationCalculator!");
            break;
        default:
            puts("please input a number between 1-5");
            break;
        }
        system("pause");
        system("cls");
    } while (option != 5);

    return 0;
}
