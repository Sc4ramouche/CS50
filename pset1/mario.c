#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int pyramid_height;

    do
    {
        pyramid_height = get_int("Please, enter the height of the pyramid: ");
    }
    while (pyramid_height < 0 || pyramid_height > 23);

    // looping from the top
    for (int i = pyramid_height; i > 0; i--)
    {
        // printing pyramid indentation
        for (int j = i - 1; j > 0; j--)
        {
            printf(" ");
        }

        // printing upward pyramid steps
        for (int k = 0; k < pyramid_height + 1 - i; k++)
        {
            printf("#");
        }

        // gap between half-pyramides
        printf("  ");

        // printing downward pyramid steps
        for (int r = 0; r < pyramid_height + 1 - i; r++)
        {
            printf("#");
        }

        // go to the next floor
        printf("\n");
    }
}