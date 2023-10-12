#include <cs50.h>
#include <stdio.h> 

int main(void)
{
    // Getting the start size
    int start;
    do 
    {
        start = get_int("Start size: ");
    }
    while (start < 9);
    // Getting the end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);
    //Calculating the year
    int year = 0, population = 0;
    
    if (start != end)
    {
        do
        {
            population = start + start / 3 - start / 4;
            start = population;
            year++;
        }
        while (population < end); 
    }
    
    //Printing the results
    printf("Years: %i\n", year);
}