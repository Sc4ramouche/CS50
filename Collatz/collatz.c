#import <cs50.h>
#import <stdio.h>

int collatz(int n);
void print_sequence(int n);

int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: collatz n");
        return 1;
    }

    int n = atoi(argv[1]);
    printf("number of steps: %i\n", collatz(n));

    return 0;
}

int collatz(int n)
{
    print_sequence(n);

    if (n == 1)
        return 0;

    if (n % 2 == 0)
        return 1 + collatz(n / 2);
    else
        return 1 + collatz(3 * n + 1);
}

void print_sequence(int n)
{
    if (n == 1)
        printf("%i\n", n);
    else
        printf("%i -> ", n);
}