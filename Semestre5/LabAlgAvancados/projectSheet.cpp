#include<iostream>
#include<map>
#include<set>
#include<string>
#include<vector>
#include<iterator>
#include<ctype.h>
#include <algorithm>

using namespace std;

bool sortbysec(const pair<string,int> &a, const pair<string,int> &b)
{
    if( a.second == b.second ){

        return (a.first < b.first);

    }

    return (a.second > b.second);
}

int main(){

    string input;
    string index;
    
    map<string, set<string>>projetos;
    map<string, set<string>>::iterator itr;

    set<string> alunos;
    set<string> inscritos;

    vector<pair<string, int>>apresentacao;

    int quebra;
    int controle = 0;

    getline(cin, input);

    do{

        quebra = 0;

        if( input[0] != '1' ){

            for( long unsigned int i = 0 ; i < input.length() ; i++ ){

                if( input[i] != toupper(input[i]) ){

                    quebra = 1;

                    break;

                }

            }

            if( quebra == 0 ){

                if(alunos.empty()){

                    if( controle == 1 ){

                        projetos.insert( pair<string, set<string>>(index, alunos) );

                        controle = 0;

                    }

                    index = input;

                    controle = 1;

                }else{

                    projetos.insert( pair<string, set<string>>(index, alunos) );

                    alunos.clear();
                    index = input;

                    controle = 1;

                }
                
            }else{

                bool retorno;

                retorno = false;

                for( itr = projetos.begin() ; itr != projetos.end() ; itr++ ){

                    for( auto itrS = itr->second.begin() ; itrS != itr->second.end() ; itrS++ ){

                        if( input.compare(*itrS) == 0 ){

                            itrS = itr->second.erase(itrS);

                            retorno = true;

                            break;

                        }

                    }

                }

                if( retorno == false ){

                    if( inscritos.find(input) == inscritos.end() ){

                        alunos.insert(input);
                        inscritos.insert(input);

                        controle = 0;

                    }

                }

            }
        
        }else{

            projetos.insert( pair<string, set<string>>(index, alunos) );

            for( itr = projetos.begin() ; itr != projetos.end() ; itr++ ){

                apresentacao.push_back( make_pair(itr->first, itr->second.size()) );

            }

            sort(apresentacao.begin(), apresentacao.end(), sortbysec);

            for( auto itrI = apresentacao.begin() ; itrI != apresentacao.end() ; itrI++ ){

                cout << itrI->first << " " << itrI->second << endl;

            }
            
            projetos.clear();
            apresentacao.clear();
            controle = 0;
            inscritos.clear();
            index.clear();
            alunos.clear();

            quebra = 0;

        }
        
        getline(cin, input);

    }while( input.compare("0") != 0 );

}

/*

UBQTS TXT
tthumb
LIVESPACE BLOGJAM
philton
aeinstein
YOUBOOK
j97lee
sswxyzy
j97lee
aeinstein
SKINUX
1
0


*/