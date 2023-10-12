#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Asking the user's name
    string name = get_string("What is your name? \n");
    // Printing Hello, user!
    printf("Hello, %s! Nice to meet you!\n", name);
}