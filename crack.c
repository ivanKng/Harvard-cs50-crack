#define _XOPEN_SOURCE
#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

/*
CS50 passwords
50xcIMJ0y.RXo = YES
50mjprEcqC/ts = CA
50GApilQSG3E2 = UPenn
50n0AAUD.pL8g = lloyd
50CcfIk1QrPr6 = maybe
509nVI8B9VfuA = TF
50JIIyhDORqMU = nope
50JGnXUgaafgc = ROFL
51u8F0dkeDSbY = NO
50cI2vYkF0YU2 = LOL
*/

/*Todo:
crack program must have 2 arguments:
    if user fails to provide 2 arguments, prompt user and return false
set letter count
*/
int main(int argc, string argv[])
{
    if (argc != 2)  //prompt user for 2 arguments: program name + hash
    {
        printf("./crack + hash");   //otherwise prompt user for program + hash and return false
        return 1;
    }

    int letter_count = 52; //cover range of lower && uppercase letters
    string letter = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";    //decrypt from string containing both lower & uppercase letters
    char salt[2];   //element [0] = '5', element [1] = '0', element [2] = '\0' in total there 3 elements in the array.
    string hash = argv[1];  //store second argument into variable hash
    memcpy(salt, hash, 2); //copy string 1 into comparison string 2
    char key_length[6] = "\0"; //the key_length determines the max number of password chars the program will cycle through

    //create a for loop to iterate over the passwords of up to 5 characters
    for (int fifth = 0; fifth < letter_count; fifth++) //loop should iterate over passwords with 5 chars
    {
        for (int fourth = 0; fourth < letter_count; fourth++)  //loop should iterate over passwords with 4 chars
        {
            for (int third = 0; third < letter_count; third++)  //loop should iterate over passwords with 3 chars
            {
                for (int second = 0; second < letter_count; second++)  //loop should iterate over passwords with 2 chars
                {
                    for (int first = 0; first < letter_count; first++) //loop should iterate over passwords with 1 char
                    {
                        key_length[0] = letter[first];  //iterating however long key_length up to max 5 chars
                        key_length[1] = letter[second];
                        key_length[2] = letter[third];
                        key_length[3] = letter[fourth];
                        key_length[4] = letter[fifth];

                        if (strcmp(crypt(key_length, salt), hash) == 0) //crypt() encodes the key_length && salt and strcmp compares the 2 hashes. if == the password is printed
                        {
                            printf("%s\n", key_length);
                            return 0;   //adding return 0; will end the decryption of password otherwise decryption seems to be looping forever
                        }
                    }
                }
            }
        }
    }
    printf("unable to crack password\n");
    return 1;
}
