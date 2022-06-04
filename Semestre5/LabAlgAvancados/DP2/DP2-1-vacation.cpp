#define ACTIVITIES 3

#include<iostream>

using namespace std;

int main(){

    int days;
    int i, j;

    int previous = -1, previousAct = -1;

    unsigned long int happiness = 0, maior, input;

    cin >> days;

    unsigned long int vacation[days][ACTIVITIES];

    for( i = 0 ; i < days ; i++ ){

        for( j = 0 ; j < ACTIVITIES ; j++ ){

            cin >> input;
            vacation[i][j] = input;

        }

    }

    for( i = 0 ; i < days ; i++ ){

        maior = 0;

        for( j = 0 ; j < ACTIVITIES ; j++ ){

            if( vacation[i][j] > maior && previousAct != j ){

                //cout << previous << " != " << j << endl;

                maior = vacation[i][j];

                previous = j;

            }

        }

        //cout << maior << " " << previousAct << endl;

        previousAct = previous;

        happiness += maior;

    }

    cout << happiness;


}

/*

3
10 40 70
20 50 80
30 60 90

== 210




7
6 7 8
8 8 3
2 5 2
7 8 6
4 6 8
2 3 4
7 5 1

== 46

*/