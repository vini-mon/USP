#include<iostream>
#include<vector>
#include<iterator>
#include<math.h>

using namespace std;

vector<int> decToBin(int dec){

    int index = 4;

    vector<int>binary = {0,0,0,0,0};

    for( int i = 0 ; dec > 0 ; i++ ){

        binary[index] = dec % 2;

        dec = dec/2;

        index--;

    }

    return binary;

}

int binToDec( vector<int> bin ){

    int dec = 0;

    int index = 0;

    for( int i = 4 ; i >= 0 ; i-- ){

        dec += (bin[index] * (pow(2, i)));

        index++;

    }

    return dec;
    
}

vector<int> xorConvert(vector<int> a, vector<int> b){

    vector<int> result = {0,0,0,0,0};

    if( b.empty() ){

        return a;

    }

    for(int i = 0 ; i < 5 ; i++){

        if( a[i] != b[i] ){

            result[i] = 1;

        }else{

            result[i] = 0;

        }

    }

    return result;

}

int toSheet(int index, int max, vector<int>numbers, vector<int>subset){

    int sum = 0;

    if( index == max ){

        vector<int> convertA;
        vector<int> convertB;

        //cout << "tamanho" << subset.size() << endl;

        convertB = {0,0,0,0,0};

        for( auto itr = subset.begin() ; itr != subset.end() ; ){

            convertA = decToBin(*itr);

            itr++;

            if( sum == 0 && itr != subset.end() ){

                convertB = decToBin(*itr);

                convertB = xorConvert(convertA, convertB);

                sum = binToDec(convertB);

                //cout << sum << endl;

                itr++;

            }else{
                
                convertB = xorConvert(convertA, convertB);
                
                sum = binToDec(convertB);

                //cout << sum << endl;

			}

        }

        //cout << endl << "retorno: " << sum << endl;

        return sum;

    }

    sum += toSheet(index+1, max, numbers, subset);

    //cout << "voltou: " << sum << endl;    

    subset.push_back(numbers[index]);

    //cout << "foi?" << endl;

    sum += toSheet(index+1, max, numbers, subset);

    return sum;

}

int main(){

    int x, input;
    int sum = 0;

    vector<int>numbers;

    vector<int>subset;

    cin >> x;

    for( int i = 0 ; i < x ; i++ ){

        cin >> input;

        numbers.push_back(input);

    }

    sum = toSheet(0, x, numbers, subset);

    cout << sum << endl; 


}

/*

2
1 3

== 6



3
5 1 6

== 28




4
8 20 5 12

== 232




6
3 4 5 6 7 8

== 480





7
3 17 18 19 12 3 12 

== 1984

*/