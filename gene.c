#include<stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
        return (0);
    int i = 0;
    while(i < atoi(argv[1]))   
    {
        printf("%s", argv[2]);
        i++;
    }
    return 0;
}