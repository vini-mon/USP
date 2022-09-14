#include <stdio.h>
 
 
static unsigned int decrement_25mi( unsigned int i); // Decrement 25000000x
static unsigned int decrement_50mi( unsigned int i); // Decrement 50000000x
static unsigned int decrement_100mi( unsigned int i); // Decrement 100000000x
 
 
int main(void)
{
       unsigned int j, i=0;
       for( j=0; j<100000000; j++) // Increment 100000000x
               i++;
       i = decrement_100mi(i); // Decrement 100000000x
       printf("Counter = %u\n", i); // Print value
       return 0;
}
 
 
 
static unsigned int decrement_25mi( unsigned int i)
{
       unsigned int j;
       for( j=0; j<25000000; j++)
               i--;
       return i;
}
 
 
static unsigned int decrement_50mi( unsigned int i)
{
       i = decrement_25mi(i);
       i = decrement_25mi(i);
       return i;
}
 
 
static unsigned int decrement_100mi( unsigned int i)
{
       i = decrement_50mi(i);
       i = decrement_25mi(i);
       i = decrement_25mi(i);
       return i;
}
