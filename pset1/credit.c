#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long card_number = get_long_long("Please, provide card number to check: ");

    // values to store odd and even digits
    // note that we are moving backwards
    int odd_sum = 0;
    int even_sum = 0;

    // first digits of the card number
    int first_digits;

    // card validity
    int card_valid = 0;

    // initialize counter
    int i = 0;

    while (card_number > 0)
    {
        if (i % 2)
        {
            int doubled_remainder = (card_number % 10) * 2;

            // check if we have to split the number
            if (doubled_remainder > 9)
            {
                odd_sum += doubled_remainder % 10 + doubled_remainder / 10;
            }
            else
            {
                odd_sum += doubled_remainder;
            }
        }
        else
        {
            even_sum += card_number % 10;
        }

        // prepare for next iteration
        i++;

        // store first digits
        if (card_number / 10 != 0)
        {
            first_digits = card_number % 100;
        }

        // first_digits[1] == card
        card_number /= 10;
    }

    // check validity
    if ((odd_sum + even_sum) % 10 == 0)
    {
        card_valid = 1;
    }

    // define credit card type
    if (card_valid)
    {
        switch (i)
        {
            case 13:
                if (first_digits / 10 == 4)
                {
                    printf("VISA\n");
                    break;
                }
                else
                {
                    printf("INVALID\n");
                }
            case 15:
                if (first_digits == 34 || first_digits == 37)
                {
                    printf("AMEX\n");
                    break;
                }
                else
                {
                    printf("INVALID\n");
                }
            case 16:
                if (first_digits == 51 || first_digits == 52 || first_digits == 53 || first_digits == 54 || first_digits == 55)
                {
                    printf("MASTERCARD\n");
                    break;
                }
                else if (first_digits / 10 == 4)
                {
                    printf("VISA\n");
                    break;
                }
            default:
                printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}