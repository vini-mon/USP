#include <bits/stdc++.h>

using  namespace std;

const int maxn=1e6+ 10;

int a[maxn];

int main(){
    
    int loop;

    cin >> loop;

     while (loop-- ){

        int n;

        cin >> n;

        int sum = 0 ;

        for ( int i = 0 ;i<n;i++ ){

            cin >> a[i];

            if ( i == 0 ){

                sum = a[i];

            }else{
                
                sum = sum^a[i];

            }

        }

        if (sum== 0 ){

            cout<< 1 << endl;
        
        }else{
            
            cout<< 0 << endl;

        }
    }

}