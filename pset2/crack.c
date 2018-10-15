#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

string crack(string hash);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }



    string hashed_password = argv[1];

    string cracked_password = crack(hashed_password);

    printf("\n%s\n", hashed_password);
    printf("%s\n", crypt("ROFL", "50"));
    return 0;
}

string crack(string hash)
{
    // form array of allowed characters
    char allowed_characters[64];
    int count = 0;

    for (int i = 46; i <= 122; i++)
    {
        char c = i;
        if (isalnum(c) || c == '.' || c == '/')
        {
            allowed_characters[count] = c;
            count++;
            // printf("%c", c);
        }
    }

    // each password is no longer than 5 character
    for (int i = 1; i <= 5; i++)
    {
        char password[i+1];
        password[i] = '\0';

        for (int z = 0; z < i; z++)
        {
            password[z] = 'a';
        }

        for (int j = 0; j < i; j++)
        {
            printf("%c", password[j]);
        }

        printf("\n");
    }

    return "hash_mock";
}