#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int selectKnight(int last, vector<int> knights, int head){

    int rtn = -1;

    for( int i = 0 ; i < last ; i++ ){

        if( knights[i] >= head ){
/* 
            cout << "select " << knights[i] << endl;
 */
            rtn = i;

            break;

        }

    }

    return rtn;

}

int main(){

    int n, m;
    int coast;
    int win;
    int auxInt;
    vector<int>diametersHead;
    vector<int>knights;

    int kSelec, hSelec;
    int hQuant;

    cin >> n >> m;

    while( (n != 0) && (m != 0) ){

        win = 0;

        coast = 0;

        hSelec = 0;
        kSelec = 0;

        hQuant = n;

        for( int i = 0 ; i < n ; i++ ){

            cin >> auxInt;

            diametersHead.push_back(auxInt);

        }

        for( int i = 0 ; i < m ; i++ ){

            cin >> auxInt;

            knights.push_back(auxInt);

        }

        sort(diametersHead.begin(), diametersHead.end());
        sort(knights.begin(), knights.end());

        if(n > m || diametersHead[n-1] > knights[m-1]){

            win = 0;

        }else{

            do{

                if( hQuant == 0 ){ win = 1; break; }

                do{ if( diametersHead[hSelec] == -1 && hSelec < n ){ hSelec++; }else{ break; } }while(true);

                kSelec = selectKnight(m, knights, diametersHead[hSelec]);

                if(kSelec == -1){

                    win = 0;
                    break;

                }

                if( (win == 0) && ( knights[kSelec] >= diametersHead[hSelec]) ){

                    coast += knights[kSelec];
/* 
                    cout << "H " << diametersHead[hSelec] << " K " << knights[kSelec] << endl;
                    cout << "$" << coast << endl;
 */
                    knights[kSelec] = -1;
                    diametersHead[hSelec] = -1;

                    hQuant--;

                }

            }while(true);
        }

        if( win == 1 ){

            cout << coast << endl;

        }else{

            cout << "Loowater is doomed!" << endl;

        }

        cin >> n >> m;

        diametersHead.clear();
        knights.clear();

    }

    return 0;

}

/*

2 3
5
4
7
8
4
2 1
5
5
10
0 0



*/
