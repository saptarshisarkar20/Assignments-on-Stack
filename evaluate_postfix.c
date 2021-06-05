#include <stdio.h>
#include <math.h>
#define SIZE 50

char stack[SIZE];
int stack_top = -1;

int is_full()
{
    if ((stack_top + 1) == SIZE)
    {
        return 1;
    }
    return 0;
}

int is_empty()
{
    if (stack_top == (-1))
    {
        return 1;
    }
    return 0;
}

char top_val()
{
    return stack[stack_top];
}

char push(char x)
{
    if (is_full())
    {
        // printf("!X! Stack Overflow !X!\n");
        return '#';
    }
    stack_top++;
    stack[stack_top] = x;
    // printf("%c Pushed successfully :)\n", x);
    return x;
}

char pop()
{
    if (is_empty())
    {
        // printf("!X! Stack Underflow !X!\n");
        return '#';
    }
    char x = stack[stack_top];
    stack_top--;
    // printf("%c Popped successfully :)\n", x);
    return x;
}

void display_stack()
{
    if (is_empty())
    {
        // printf("Nothing is here :(\n");
    }
    int x = stack_top;
    while (x != (-1))
    {
        printf("| %c |\n", stack[x]);
        printf("------\n");
        x--;
    }
    printf("|||||\n");
}
int is_operator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
    {
        return 1;
    }
    return 0;
}

int evaluate_postfix(char *postfix)
{
    int a, b, c, ans = 0, i = 0;
    while (postfix[i] != '\0')
    {
        if (!is_operator(postfix[i]))
        {
            push(postfix[i]);
            i++;
        }
        else
        {
            a = pop() - '0';
            b = pop() - '0';
            if (postfix[i] == '+')
            {
                c = a + b;
                push(c + '0');
                i++;
            }
            else if (postfix[i] == '-')
            {
                c = a - b;
                push(c + '0');
                i++;
            }
            else if (postfix[i] == '*')
            {
                c = a * b;
                push(c + '0');
                i++;
            }
            else if (postfix[i] == '/')
            {
                c = b / a;
                push(c + '0');
                i++;
            }
            else if (postfix[i] == '^')
            {
                c = pow(b, a);
                push(c + '0');
                i++;
            }
        }
    }
    ans = pop()-'0';
    return ans;
}

int main(void)
{
    char postfix[50];
    char *pf = postfix;
    printf("Enter a postfix expression : ");
    scanf("%s", postfix);
    printf("Evaluated value of the expression is = %d", evaluate_postfix(pf));
    return 0;
}