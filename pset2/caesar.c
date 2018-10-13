#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cypher(string p, int k);

int main(int argc, string argv[])
{
    if (argc == 1)
    {
        printf("Usage: ./caesar k");
        return 1;
    }

    // converts command line argument to integer
    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext:");

    cypher(plaintext, key);

    printf("ciphertext:%s\n", plaintext);

    return 0;
}

void cypher(string p, int k)
{
    int alphabet_count = 26;
    // store ASCII boundaries for upper and lowercase letters
    int uppercase[2] = { 65, 90 };
    int lowercase[2] = { 97, 122 };

    // get rid of overload
    k %= alphabet_count;

    // iterate through given string
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        // check if the character is actually a letter
        if (isalpha(p[i]))
        {
            // handle uppercase letters
            if (p[i] >= uppercase[0] && p[i] <= uppercase[1])
            {
                if (p[i] + k > uppercase[1])
                {
                    p[i] = uppercase[0] + (k - (uppercase[1] - p[i]) - 1);
                }
                else
                {
                    p[i] += k;
                }
            }

            // handle lowercase letters
            if (p[i] >= lowercase[0] && p[i] <= lowercase[1])
            {
                if (p[i] + k > lowercase[1])
                {
                    p[i] = lowercase[0] + (k - (lowercase[1] - p[i]) - 1);
                }
                else
                {
                    p[i] += k;
                }
            }
        }
    }
}