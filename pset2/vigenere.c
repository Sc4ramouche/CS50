#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cypher(string p, string k);
bool is_keyword_valid(string k);

int main(int argc, string argv[])
{
    if (argc != 2 || !is_keyword_valid(argv[1]))
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }

    string key = argv[1];
    string plaintext = get_string("plaintext:");

    cypher(plaintext, key);

    printf("ciphertext:%s\n", plaintext);

    return 0;
}

void cypher(string p, string k)
{
    int alphabet_count = 26;
    // store ASCII boundaries for upper and lowercase letters
    int uppercase[2] = { 65, 90 };
    int lowercase[2] = { 97, 122 };

    int key_len = strlen(k);
    int key_count = 0;

    // iterate through given string
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        // current char of the key and integer key value
        int curr_key;
        int curr_char = k[key_count % key_len];

        // define key for current iteration
        if (isupper(curr_char))
        {
            curr_key = curr_char - uppercase[0];
        }
        else
        {
            curr_key = curr_char - lowercase[0];
        }

        // check if the character is actually a letter
        if (isalpha(p[i]))
        {
            // handle uppercase letters
            if (isupper(p[i]))
            {
                if (p[i] + curr_key > uppercase[1])
                {
                    p[i] = uppercase[0] + (curr_key - (uppercase[1] - p[i]) - 1);
                }
                else
                {
                    p[i] += curr_key;
                }
            }

            // handle lowercase letters
            if (islower(p[i]))
            {
                if (p[i] + curr_key > lowercase[1])
                {
                    p[i] = lowercase[0] + (curr_key - (lowercase[1] - p[i]) - 1);
                }
                else
                {
                    p[i] += curr_key;
                }
            }
            // change key
            key_count++;
        }
    }
}

bool is_keyword_valid(string k)
{
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!isalpha(k[i]))
        {
            return false;
        }
    }

    return true;
}