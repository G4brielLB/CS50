#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Getting the Card Number
    long initcard = get_long("Number: ");
    // Initializing the variables
    long card = (initcard);
    int initsize = 0, size = sizeof(card), doubles = 0, single = 0, digit;
    // Getting the lenght of card
    do
    {
        card /= 10;
        initsize++;
    }
    while (card != 0);
    card = (initcard);
    // Luhn's Algorithm
    while (true)
    {
        // Lenght of the card divided by 2 == 0
        if (initsize % 2 == 0)
        {
            // Breaking the loop, because already has the necessary info
            if (card / 10 == 0)
            {
                card = initcard / pow(10, initsize - 2);
                break;
            }
            digit = card % 10;
            single += digit;
            card = card / 10;
            size = sizeof(card);
            // Multiplying the other digits by 2
            digit = card % 10;
            if (digit * 2 >= 10)
            {
                digit *= 2;
                doubles += digit % 10;
                doubles += digit / 10;
            }
            else
            {
                doubles += 2 * digit;
            }
            card = card / 10;
            size = sizeof(card);
        }
        // Lenght of the card divided by 2 != 0
        else
        {
            digit = card % 10;
            single += digit;
            card = card / 10;
            size = sizeof(card);
            // Multiplying the other digits by 2
            digit = card % 10;
            if (digit * 2 >= 10)
            {
                digit *= 2;
                doubles += digit % 10;
                doubles += digit / 10;
            }
            else
            {
                doubles += 2 * digit;
            }
            card = card / 10;
            size = sizeof(card);
            // Breaking the loop, because already has the necessary info
            if (card / 10 == 0)
            {
                doubles += card;
                card = initcard / pow(10, initsize - 2);
                break;
            }
        }
    }
    // Validating the Card
    if ((doubles + single) % 10 != 0)
    {
        printf("INVALID\n");
    }
    // AMEX Card
    else if ((card == 34 || card == 37) && initsize == 15)
    {
        printf("VALID\n");
        printf("AMEX\n");
    }
    // MASTERCARD Card 
    else if ((card == 51 || card == 52 || card == 53 || card == 54 || card == 55) && initsize == 16)
    {
        printf("VALID\n");
        printf("MASTERCARD\n");
    }
    // VISA Card
    else if ((13 <= initsize && initsize <= 16) && (card / 10) == 4)
    {
        printf("VALID\n");
        printf("VISA\n");
    }
    // Card not valid
    else
    {
        printf("INVALID\n");
    }
}

