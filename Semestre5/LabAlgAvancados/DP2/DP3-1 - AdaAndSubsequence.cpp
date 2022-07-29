#include<iostream>
#include<string>

using namespace std;

int main(){

    int n, m;
    int cost[26];
    string subA, subB;

    cin >> n >> m;

    int dp[n+1][m+1];

    for(int i = 0; i <= n; i++){
        
        for( int j = 0; j <= m; j++){
            dp[i][j] = 0;
        }

    }

    for( int i = 0 ; i < 26 ; i++ ){

        cin >> cost[i];

    }

    cin >> subA >> subB;

    for( int i = 1 ; i <= n ; i++ ){

        for( int j = 1 ; j <= m ; j++ ){

            dp[i][j] = max( dp[i-1][j], dp[i][j-1] );

            if( subA[i-1] == subB[j-1] ){


                dp[i][j] = max( dp[i][j], dp[i-1][j-1] + cost[ (int) (subA[i-1]-'a') ] );

            }

        }

    }

    cout << dp[n][m] << endl;

}