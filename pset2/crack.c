#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

string crack(string hash, char salt[]);
void check(char password[], char characters[], char last);
int find_index(char letter, char array[]);
bool check_crypt(char password[], char salt[], char hash[]);
void get_salt(char salt[], char hash[]);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // extract provided hash
    string hash = argv[1];

    // get salt from hash
    char salt[3];
    salt[2] = '\0';
    get_salt(salt, hash);

    // printf("%s\n", crypt("hi", "50"));
    string password = crack(hash, salt);
    int n = strlen(password);

    // as we are not introduced to concept of pointers
    // there is little hacky way to print the password
    char pwd[n + 1];
    for (int i = 0; i < n; i++)
    {
        pwd[i] = password[i];
    }
    pwd[n] = '\0';

    printf("%s\n", pwd);

    return 0;
}

/*
  tries to brute force given hash.
  iterates through every password no longer than 5 symbols long.
  checks only for alphabetical passwords.
  returns cracked password or "Not found" in case of failure.
*/
string crack(string hash, char salt[])
{
    // form array of allowed characters
    char allowed_characters[53];
    int count = 0;

    for (int p = 65; p <= 122; p++)
    {
        char c = p;
        if (isalpha(c))
        {
            allowed_characters[count] = c;
            count++;
        }
    }

    allowed_characters[52] = '\0';
    // allowed characters length
    int length = strlen(allowed_characters);

    // each password is no longer than 5 character
    for (int i = 1; i <= 5; i++)
    {
        // create i length password
        char password[i + 1];
        password[i] = '\0';

        // populate initial password with first allowed symbols
        for (int z = 0; z < i; z++)
        {
            password[z] = allowed_characters[0];
        }

        // while leftmost character in password hits the last allowed symbol
        while (password[0] != allowed_characters[length - 1])
        {
            // Iterate through allowed_characters array
            for (int k = 0, n = strlen(allowed_characters); k < n; k++)
            {
                // change rightmost symbol for next allowed symbol
                password[i - 1] = allowed_characters[k];

                // check if the current combination of characters is hashed as user input
                if (check_crypt(password, salt, hash))
                {
                    string answer = password;
                    return answer;
                }

                // if rightmost character hits last allowed symbol
                if (k == n - 1)
                {
                    check(password, allowed_characters, allowed_characters[k]);
                }
            }
        }
    }

    return "Not found";
}

/*
  checks if we have to swap symbols to the left of last one.
  goes left to right from the second symbol.
  if current symbol is the last in the allowed symbols array -
  changes left one to the next allowed symbol.
*/
void check(char password[], char characters[], char last)
{
    for (int i = 1, n = strlen(password); i < n; i++)
    {
        if (password[i] == last)
        {
            int next = find_index(password[i - 1], characters);
            password[i - 1] = characters[next + 1];

            for (int k = i; k < n; k++)
            {
                password[k] = characters[0];
            }

            break;
        }
    }
}

/*
  finds the index of the value in provided array
  if it is absent - returns 0
*/
int find_index(char letter, char array[])
{
    for (int i = 0, n = strlen(array); i < n; i++)
    {
        if (array[i] == letter)
        {
            return i;
        }
    }

    return 0;
}

/*
  compares crypt output with provided string to the hash provided
*/
bool check_crypt(char password[], char salt[], char hash[])
{
    return strcmp(crypt(password, salt), hash) == 0 ? true : false;
}

/*
  assigns two first symbols of the hash to the salt
*/
void get_salt(char salt[], char hash[])
{
    for (int i = 0; i < 2; i++)
    {
        salt[i] = hash[i];
    }
}