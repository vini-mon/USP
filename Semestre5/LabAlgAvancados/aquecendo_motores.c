#include<stdio.h>
#include<string.h>

int main(){

    int n, m;
    int tamip = 0;
    int state = 0;

    scanf("%d %d", &n, &m);

    char ip[n][15];
    char name[n][15];

    char input1[15];
    char input2[15];

    for( int i = 0 ; i < n ; i++ ){

        scanf("%s", input1);
        scanf("%s", input2);

        for( int j = 0 ; j < tamip ; j++ ){

            if( strcmp(input2, ip[j]) == 0 ){

                state = 1;
                printf("repetido\n");
                break;

            }

        }

        if( state == 0 ){

            strcpy(name[i], input1);
            strcpy(ip[i], input2);
            tamip++;

        }

        state = 0;

    }

    char aux[15];

    for( int i = 0 ; i < m ; i++ ){

        scanf("%s", input1);
        scanf("%s", input2);

        strcpy(aux, input2);
        aux[strlen(aux)-1] = '\0';

        for( int j = 0 ; j < tamip ; j++ ){

            //printf("%s|%s\n", input2, ip[j]);

            if( strcmp(aux, ip[j]) == 0 ){

                printf("%s %s #%s\n", input1, input2, name[j]);

            }

        }

    }

    for( int i = 0 ; i < n ; i ++ ){

        //printf("%s|%s\n", name[i], ip[i]);

    }

}


/*

2 2
main 192.168.0.2
replica 192.168.0.1
block 192.168.0.1;
proxy 192.168.0.2;


*/
