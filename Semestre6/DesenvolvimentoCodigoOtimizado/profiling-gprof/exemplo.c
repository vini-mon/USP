#include <stdio.h>

void some_other_test(void)
{
    printf("\n Inside the function some_other_test() \n");
    int i = 0;
    for(;i<=0XFFFFFFF;i++);
}

void yet_another_test(void)
{
    printf("\n Inside the function yet_other_test() \n");
    int i = 0;
    for(;i<=0XFFFFFFF;i++);
}

void another_test(void)
{
    printf("\n Inside the function another_test() \n");
    int i = 0;
    for(;i<=0XFFF;i++);

    yet_another_test();
}

void test(void)
{
    printf("\n Inside the function test() \n");
    int i = 0;
    for(;i<=0XFFFFFF;i++);

    another_test();
}

int main(void)
{
    printf("\n Inside the function main() \n");
    int i = 0;
    for(;i<=0XFFFFF;i++);

    test();
    some_other_test();

    return 0;
}
