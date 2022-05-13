#include<iostream>
#include<map>
#include<set>

using namespace std;

int main(){

    map<char, char>planilha;

    int continuar = 0;
    char chave;
    char texto;

    cin >> texto;

    do{

        if( !isdigit(texto) ){

            if( isupper(texto) ){

                chave = texto;

            }else{

                //buscar no mapa

                for( auto itr = planilha.begin() ; itr != planilha.end() ; itr++ ){

                    if( itr->first != chave ){

                        if( itr->second == texto ){

                            char chave_remove = itr->first;
                            char texto_remove = itr->second;

                            planilha.erase(chave_remove, texto_remove);

                        }

                    }

                }

            }

        }

        cin >> texto;

    }while(texto != 1);

}
