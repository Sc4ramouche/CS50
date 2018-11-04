#include <stdio.h>
#include <cs50.h>

int fibonacci(int n);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./fibonacci n\n");
        return 1;
    }

    int n = atoi(argv[1]);
    printf("%i\n", fibonacci(n));

    return 0;
}

int fibonacci(int n)
{
    if (n == 1)
        return 1;
    if (n == 0)
        return 0;

    return fibonacci(n - 1) + fibonacci(n - 2);
}