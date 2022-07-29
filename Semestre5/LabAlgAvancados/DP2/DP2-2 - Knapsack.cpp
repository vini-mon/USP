#include<iostream>
#include<vector>

using namespace std;
 
int main(){

    int item, weight;
    cin >> item >> weight;

    long long arr[item][2];
    vector<long long> dp(weight+1,0);
    
    for( int i = 0 ; i < item ; i++ ) {

        cin >> arr[i][0] >> arr[i][1];

    }
 
    for( int i = 0 ; i < item ; i++ ){

        for( int j = weight; j >= max(0LL, arr[i][0]) ; j-- ){

            dp[j] = max( dp[j - arr[i][0]] + arr[i][1], dp[j] );

            //cout << dp[j] << " ";

        }

    }
    
    cout << dp[weight];
}
