#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack
{
    int size;
    int top;
    char *arr;
};

int stack_top(struct stack *sp)
{
    return sp->arr[sp->top];
}

int is_empty(struct stack *sp)
{
    if (sp->top == -1)
    {
        return 1;
    }
    return 0;
}

int is_full(struct stack *sp)
{
    if (sp->top == sp->size - 1)
    {
        return 1;
    }

    return 0;
}

void push(struct stack *sp, char val)
{
    if (is_full(sp))
    {
        printf("Stack Overflow!\n");
    }
    else
    {
        sp->top++;
        sp->arr[sp->top] = val;
    }
}

char pop(struct stack *sp)
{
    if (is_empty(sp))
    {
        printf("Stack Underflow!\n");
        return -1;
    }
    else
    {
        char val = sp->arr[sp->top];
        sp->top--;
        return val;
    }
}

int prece_dance(char ch)
{
    if (ch == '^')
    {
        return 3;
    }
    else if (ch == '*' || ch == '/')
    {
        return 2;
    }
    else if (ch == '+' || ch == '-')
    {
        return 1;
    }

    return 0;
}

int is_operator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
    {
        return 1;
    }
    return 0;
}

char *infix_to_postfix(char *infix)
{
    struct stack *sp = (struct stack *)malloc(sizeof(struct stack));
    sp->size = 10;
    sp->top = -1;
    sp->arr = (char *)malloc(sp->size * sizeof(char));
    char *postfix = (char *)malloc((strlen(infix) + 1) * sizeof(char));
    int i = 0;
    int j = 0;
    // char z;
    while (infix[i] != '\0')
    {
        if (!is_operator(infix[i]))
        {
            postfix[j] = infix[i];
            j++;
            i++;
        }
        else
        {
            if (prece_dance(infix[i]) > prece_dance(stack_top(sp)))
            {
                push(sp, infix[i]);
                i++;
            }
            else
            {
                postfix[j] = pop(sp);
                j++;
            }
        }
    }
    while (!is_empty(sp))
    {
        postfix[j] = pop(sp);
        j++;
    }
    postfix[j] = '\0';
    return postfix;
}

char *reverse_arr(char *arr, char *re)
{
    int n = 0, i = 0, z;
    while (arr[n] != '\0')
    {
        n++;
    }
    z = n;
    n--;
    while (i < z)
    {
        re[i] = arr[n];
        i++;
        n--;
    }
    re[i] = '\0';
    // printf("%s\n",re);
    return re;
}

char *infix_to_prefix(char *infix)
{
    struct stack *sp2 = (struct stack *)malloc(sizeof(struct stack));
    sp2->size = 10;
    sp2->top = -1;
    sp2->arr = (char *)malloc(sp2->size * sizeof(char));
    char *reverse = (char *)malloc((strlen(infix) + 1) * sizeof(char));
    char *prefix = (char *)malloc((strlen(infix) + 1) * sizeof(char));
    reverse = reverse_arr(infix, reverse);
    // printf("#### %s\n",reverse);
    reverse = infix_to_postfix(reverse);
    // printf("#### %s\n",reverse);
    prefix = reverse_arr(reverse, prefix);
    // printf("#### %s\n",prefix);
    return prefix;
}

int main()
{
    char infix[50];
    char rev[50];
    char *in;
    char *re;
    in = infix;
    printf("Enter the infix expression : ");
    scanf("%s", in);
    printf("Postfix expression is --> %s \n", infix_to_postfix(in));
    printf("Prefix expression is --> %s \n", infix_to_prefix(in));
    return 0;
}