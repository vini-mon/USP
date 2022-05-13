#include<iostream>
#include<stack>
#include<vector>

using namespace std;

stack<int> imprimePilha(stack<int>p){

     do{

        cout << p.top() << endl;

        p.pop();

    }while(!p.empty());

    return p;

}

int main(){


    int a, n, aux;

    stack<int>pilha;

    cin >> a;

    for( int j = 0 ; j < a ; j++ ){

        cin >> n;

        for( int i = 0 ; i < n ; i++ ){

            cin >> aux;

            pilha.push(aux);

        }

        pilha = imprimePilha(pilha);

        if( j != a-1 )cout << endl;

    }

}

/*

2
5
1
2
3
4
5
3
10
20
30


*/
