#include <stdio.h>
#include <stdlib.h>

void main()
{
    unsigned int size = 4096;
    unsigned int n;
    printf("Enter page to check: ");
    scanf("%u",&n);
    unsigned int page=n/4096;
    unsigned int offset=n%4096;
    printf("The address %u is contained in:\n",n);
    printf("Page number: %u\n",page);
    printf("The offset is: %u\n",offset);
}