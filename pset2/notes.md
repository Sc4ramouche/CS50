# Crack

Implement a program that cracks passwords. Details: [CS50 problem set 2](https://docs.cs50.net/2018/x/psets/2/crack/crack.html).

## Specification

* Should accept single command line argument
* Assume password is no longer than 5 characters
* Assume each password is composed entirely of alphabetical characters (uppercase and/or lowercase)

## Algorithm description

Initial steps for **crack** is pretty simple: as we design crack to be command line program, our first move is to check if user did provide hash he wants to crack into original password. After that we take two first symbols of the hash - they serve as *salt* for `crypt` function (execute `man crypt` in your terminal for more info of just google how it works). Then we would pass provided hash to `crack` function. That's where the action begins.

There we would initialize array with allowed alphabetical characters. We have 52 characters for both lowercase and uppercase letter, so we initialize it like `allowed_characters[53]`. **53**? - yeah, we need array with length of *53* in this case. It's because strings in *C* are actually `char` type arrays with special character that takes the last place in the array: `'\0'` also called `null terminator`. Function `strlen()` seeks for that special `'\0'` characters and returns the number of characters that it found between beginning of the string and `null terminator`.

Alphabetical characters are snuggled between 65 (`'A'`) and 122 (`'z'`) numbers on decimal ASCII chart. There are some special symbols in this range, so we are usin `isalpha` to make sure we form correct array. As the last step we add `'\0'` as the last symbol to the allowed characters array.

After that we initialize with maximum of 5 steps as soon as we only check for passwords that are no longer than 5 characters long. In each iteration of that loop we create `char` array of corresponding size `i + 1` (we want extra character for `null terminator`). We populate it with the first symbols from `allowed_characters` array.

Then we initialize nested `while` loop wich runs until the leftmost character of the password array is not equal to the last symbol in `allowed_characters` array. It itself has another nested `for` loop that iterates through every allowed character. It changes the rightmost character of the password array we generated to the corresponding (actually next) allowed symbol.

Then we check if current state of passwords crypts into hash provided from command line. In that case, we return password. If it's not the case we check if there are any last allowed character in password state. If so, we change them to next not yet checked symbols.

Finally, if we have gone through all the possible combinations of the 5 characters long combinations we return `"Not found"`.

## Algorithm summary

1. Extract `hash` from command line arguments.
2. Extract `salt` from `hash` (salt for `crypt` function is first two characters of the generated hash);
3. Generate array of the allowed symbols due to specification of the problem.
4. For every possible length of the `password`:
    1. Generate `password` of current length populated with first symbols stated in allowed characters array.
    2. Iterate through every allowed character:
       1. Change the rightmost `password` character with next allowed character.
       2. Check if the current `password` combination successfully crypts into provided `hash`. Return `password` in that case.
       3. In case rightmost character reach last allowed character - check all `password` characters left to right if they are last as well. If that's the case - change symbol to the left of it to the next corresponding allowed character and reset characters to the right.
5. If we run through every possible combination of passwords - return `"Not found"`.

## Support functions

There were several support functions declared:

1. `void check(char password[], char characters[], char last)` - checks if any of the password positions reached `last` allowed character. If so, changes left one and resets symbols to the right.
2. `int find_index(char letter, char array[])` - find index of the `letter` in `array`.
3. `bool check_crypt(char password[], char salt[], char hash[])` - uses `crypt` with provided `salt` on `password` and compares with `hash`. **Note:** `strcmp` for that purpose.
4. `void get_salt(char salt[], char hash[])` - assigns two first symbols of the hash to the salt.
