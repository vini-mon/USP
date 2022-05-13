#include<iostream>
#include<math.h>

using namespace std;

void bhaskara(unsigned long int c){

    unsigned long int x;
    unsigned long int delta;

    int a = 1;
    int b = 1;

    delta = (b*b) - (4*a*c);

    if( delta < 0 ){

        cout << "fudeu" << endl;

    }

    if( delta == 0 ){

        x = (-b)/(2*a);

    }else{

        x = ((-b) + sqrt(delta)) / 2 * a;

    }

    cout << x << endl;

}

int main(){

    unsigned long int coins;

    cin >> coins;

    bhaskara(-coins*2);

    return 0;

}