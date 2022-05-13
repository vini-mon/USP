#include<iostream>
#include<vector>
#include<string.h>

using namespace std;

bool search( int index, int length, char* word, pair<int,int> walker, int n, int m, char **matrix ){

    if( index == length ){ return true; }

    bool found = false;

    char letter = word[index];

    char save = letter;

    if( walker.first-1 >= 0 && (matrix[walker.first-1][walker.second] == letter) ){

        //cout << "subi" << endl;

        matrix[walker.first][walker.second] = '*';

        walker.first = walker.first-1;

        found = search(index+1, length, word, walker, n, m, matrix);

        if( found ){ return true; }

        walker.first = walker.first+1;
        
        matrix[walker.first][walker.second] = save;

    }
    
    if( walker.second+1 < m && (matrix[walker.first][walker.second+1] == letter) ){
        
        //cout << "direita" << endl;

        matrix[walker.first][walker.second] = '*';

        walker.second = walker.second+1;

        found = search(index+1, length, word, walker, n, m, matrix);

        if( found ){ return true; }

        walker.second = walker.second-1;
        
        matrix[walker.first][walker.second] = save;

    }
    
    if( walker.first+1 < n && (matrix[walker.first+1][walker.second] == letter) ){

        //cout << "baixo" << endl;

        matrix[walker.first][walker.second] = '*';

        walker.first = walker.first+1;

        found = search(index+1, length, word, walker, n, m, matrix);

        if( found ){ return true; }

        walker.first = walker.first-1;
        
        matrix[walker.first][walker.second] = save;

    }
    
    if( walker.second-1 >= 0 && (matrix[walker.first][walker.second-1] == letter) ){

        //cout << "esquerda" << endl;

        matrix[walker.first][walker.second] = '*';

        walker.second = walker.second-1;

        found = search(index+1, length, word, walker, n, m, matrix);

        if( found ){ return true; }

        walker.second = walker.second+1;
        
        matrix[walker.first][walker.second] = save;

    }

    return false;

}

int main(){

    int n, m;
    int length;

    int index;

    char input;
    char word[10];

    bool found = false;

    pair<int,int> walker;

    cin >> n;
    cin >> m;

    char **matrix;

    matrix = (char**) calloc(n, sizeof(char*));

    for( int i = 0 ; i < n ; i++ ){

        matrix[i] = (char*) calloc(m, sizeof(char));

    }

    for( int i = 0 ; i < n ; i++ ){

        for( int j = 0 ; j < m ; j++ ){

            cin >> input;

            matrix[i][j] = input;

        }

    }

    cin >> length;

    cin >> word;

    for( int i = 0 ; i < n ; i++ ){

        for( int j = 0 ; j < m ; j++ ){

            if( word[0] == matrix[i][j] ){

                index = 1;

                walker.first = i;
                walker.second = j;

                // cima = i-1       j       0
                // dire = i         j+1     1
                // baix = i+1       j       2
                // esqu = i         j-1     3

                found = search(index, length, word, walker, n, m, matrix);

                if( found ){ 

                    break;

                }

            }

        }

        if( found ){ break; }

    }

    if( found ){

        cout << "Yes" << endl;

    }else{

        cout << "No" << endl;

    }

}

/*

3 4
ABCE
SFCS
ADEE
6
ABCCED


3 4
ABCE
SFCS
ADEE
3
SEE

*/