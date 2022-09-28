#include <demo_thread.h>
#include <stdio.h>

void helloTen()
{
    for (int i = 0; i < 50; i++)
    {
        printf("10\n");
    }
    
}

void helloFive()
{
    for (int i = 0; i < 1000; i++)
    {
        printf("5\n");
    }
    
}