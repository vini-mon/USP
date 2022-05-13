#include<iostream>
#include<string>
#include<vector>

using namespace std;

vector<int> fix( vector<int> numbers, int j, int fim ){

    for(int i = j ; i < fim ; i++){

        numbers[i] = numbers[i+1];
        numbers[i+1] = '\0';

    }

    return numbers;

}

int main(){

    int n;
    int max, min;
    int count;
    
    string input;
    string reader;

    int insert;
    int insert2;
    vector<int>numbers;
    vector<int>numbers2;

    vector<int>op;
    vector<int>op2;

    cin >> n;

    for( int i = 0 ; i < n ; i++ ){

        count = 0;

        insert = 0;

        reader.insert(0, "00");

        cin >> input;

        for( int j = 0 ; j < input.length() ; j++ ){
            
            if( input[j] != '+' && input[j] != '*' ){

                if( reader[1] == '0' ){

                    reader[1] = input[j];

                }else{

                    reader[0] = reader[1];
                    reader[1] = input[j];

                }

            }else{
                
                numbers.push_back(atoi(reader.c_str()));    

                if( input[j] == '+' ){

                    op.push_back(0);

                }else{

                    op.push_back(1);

                }

                insert++;
                
                reader[0] = '0';
                reader[1] = '0';

            }

        }

        numbers.push_back(atoi(reader.c_str()));

        insert++;
/* 
        for( int j = 0 ; j < insert ; j++ ){

            cout << j << " " << numbers[j] << endl;

        }

        for( int j = 0 ; j < insert-1 ; j++ ){

            cout << j << " " << op[j] << endl;

        }
 */

        insert2 = insert;

        for( int p = 0 ; p < numbers.size() ; p++ ){

            numbers2.push_back(numbers[p]);

        }

        for( int p = 0 ; p < op.size() ; p++ ){

            op2.push_back(op[p]);

        }

        int result;

        for( int j = 0 ; j < insert-1 ; j++ ){

            if( op[j] == 1 ){

                result = numbers[j] * numbers[j+1];

                numbers[j] = result;

                numbers = fix(numbers, j+1, insert);
                op = fix(op, j, insert);

                j--;

                insert--;

            }

        }

        for( int j = 0 ; j < insert-1 ; j++ ){


            if( op[j] == 0 ){

                result = numbers[j] + numbers[j+1];

                numbers[j] = result;

                numbers = fix(numbers, j+1, insert);
                op = fix(op, j, insert);

                j--;

                insert--;

            }

        }

        min = numbers[0];
        
        insert = insert2;

        for( int p = 0 ; p < numbers2.size() ; p++ ){

            numbers.push_back(numbers2[p]);

        }

        for( int p = 0 ; p < op2.size() ; p++ ){

            op.push_back(op2[p]);

        }

        for( int j = 0 ; j < insert-1 ; j++ ){

            if( op[j] == 0 ){

                result = numbers[j] + numbers[j+1];

                numbers[j] = result;

                numbers = fix(numbers, j+1, insert);
                op = fix(op, j, insert);

                j--;

                insert--;

            }

        }

        for( int j = 0 ; j < insert-1 ; j++ ){


            if( op[j] == 1 ){

                result = numbers[j] * numbers[j+1];

                numbers[j] = result;

                numbers = fix(numbers, j+1, insert);
                op = fix(op, j, insert);

                j--;

                insert--;

            }

        }
        
        max = numbers[0];

        cout << "The maximum and minimum are " << max << " and " << min << "." << endl;

        input.clear();

    }
    
}

/*

3
1+2*3*4+5
4*18+14+7*10
3+11+4*1*13*12*8+3*3+8

*/