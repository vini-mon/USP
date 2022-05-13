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

    for(int i = 0 ; i < 5 ; i++){

        if( a[i] != b[i] ){

            result[i] = 1;

        }else{

            result[i] = 0;

        }

    }

    return result;

}

int main(){

    int x, input;
    int sum = 0;

    vector<int>numbers;
    
    vector<int>convertA;
    vector<int>convertB;

    cin >> x;

    for( int i = 0 ; i < x ; i++ ){

        cin >> input;

        numbers.push_back(input);

    }

    convertB = decToBin(0);

    for( auto itr = numbers.begin() ; itr != numbers.end() ; itr++ ){

        int pivo = *itr;

        convertA = decToBin(pivo);

        sum += pivo;

        auto walker = itr;

        walker++;

        while( walker != numbers.end() ){

            convertB = decToBin(*walker);

            convertB = xorConvert(convertA, convertB);

            sum += binToDec(convertB);

            //cout << pivo << " " << *walker << " = " << sum << endl;

            walker++;

        }

        //cout << "p " << pivo << endl;

    }

    //cout << "result " << sum << endl;
    //cout << "---------" << endl;

    if( x >= 3 ){

        int sumAux = 0;

        for( auto itr = numbers.begin() ; itr != numbers.end() ; ){

            //cout << *itr << endl;

            convertA = decToBin(*itr);

            itr++;

            if( itr != numbers.end() ){

                //cout << "*" << *itr << endl;

                convertB = decToBin(*itr);

                convertB = xorConvert(convertA, convertB);

                sumAux = binToDec(convertB);

                //cout << sum;

                itr++;

            }else{

                //cout << "cabou!" << endl;

                convertB = xorConvert(convertA, convertB);
                
                sumAux = binToDec(convertB);

			}

            //cout << "---" << endl;

        }

        //cout << "result " << sumAux << endl;

        sum += sumAux;

    }

    cout << sum << endl;

}

/*

2
1 3

*/