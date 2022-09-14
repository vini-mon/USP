#include <math.h>
#include <stdio.h>

#define LEN     10000


void mult_by_scalar(double ary[], int len, double num);
void add_vector(double arya[], double aryb[], int len);
double value;
void printit(double value);

 

int main()
{
    double ary1[LEN];
    double ary2[LEN];
    int i;

 
    for (i=0;  i<LEN;  i++) {
        ary1[i] = 0.0;
        ary2[i] = sqrt((double)i);
    }
    mult_by_scalar(ary1, LEN, 3.14159);
    mult_by_scalar(ary2, LEN, 2.71828);
    for (i=0;  i<20;  i++)
        add_vector(ary1, ary2, LEN);
}

 

void mult_by_scalar(double ary[], int len, double num)
{
    int i;


    for (i=0;  i<len;  i++)
     {
        ary[i] *= num;
        value = ary[i];
        printit(value);
      }
}

 

void add_vector(double arya[], double aryb[], int len)
{
    int i;


    for (i=0;  i<len;  i++)
      {
        arya[i] += aryb[i];
        value = arya[i];
        printit(value);
      }
}

 

void printit(double value)
{
        printf("Value = %f\n", value);
}


