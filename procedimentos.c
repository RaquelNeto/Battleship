/*<Este source file contem as funcoes que contem alguns procedimentos>*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "jogar.h"

void dificuldade (int *d){
    /*
     pede ao utilizador a dificuldade preendida de jogo no modo player vs computer.invocado pela funcao pvc
     */
    do{
        printf("Insira o nivel de dificuldade (1-Facil, 2-Medio, 3-Dificil, 4-Impossivel):");
        scanf("%d",d); 
        setbuf(stdin, NULL);//limpa o buffer 
    }while(*d!=1 && *d!=2 && *d!=3 && *d!=4);  
}

void imprimeTab(int **tab, int tamanho, int jogo, char nick[]){//Imprime os tabuleiros dos dois jogadores
    int i=0;
    int j=0;
    int c=0;
    
    printf("campo do %s\n",nick);
    
    if(tamanho<11){
        for(c=1;c<=tamanho;c++){//imprime o numero correspondente a coordenadas no eixo x quando tamanho <=10
                printf(" [%d]",c);  
            }
    }else
    {
        for(c=1;c<tamanho-tamanho+10;c++){ /*imprime o numero correspondente a coordenadas no eixo x para x<10 quando
                                            tamanho>10*/
                printf(" [%d]",c);  
            }
        for(c=tamanho-tamanho+10;c<=tamanho;c++){/*imprime numero correspondente a coordenadas no x para x>=10 
                                                 quando tamanho >10*/
                printf("[%d]",c);  
            }
    }
        printf("\n");
        
    for(i=1;i<=tamanho;i++){ 
          for(j=1;j<=tamanho;j++){
            
                if(tab[i][j]==0){//se não tiver sido selecionado e sem navio é imprimido ~
                    printf("| ~ ");
                }

                if(tab[i][j]==1 && jogo==0){ /* se não tiver sido selecionado e tiver navio e o jogo ainda não estiver 
                                              a decorrer é imprimido +*/
                    printf("|+++");
                }
                
                if(tab[i][j]==1 && jogo==1){ /* se não tiver sido selecionado e tiver navio e o jogo estiver a 
                                              decorrer é imprimido */
                    printf("| ~ ");
                }

                if(tab[i][j]==2 ){//se tiver sido selecionado e sem navio é imprimido 0
                    printf("| 0 ");
                }
                if(tab[i][j]==3){//se tiver sido selecionado e tiver navio é imprimido X
                    printf("|(X)");
                }
          }
          
          printf("|[%d]",i);//imprime o numero correspondente a coordenadas no eixo y
          printf("\n");
          
      }
        
    printf("\n");
}

void vidas(int tamanho, int *v1, int *v2){
    /*
     esta funcao decide o numero de vidas de cada jogador tendo em conta o tamanho de campo. recebe como 
     parametros o tamanho de campo e apontadres para as variaveis v1 e v2 que sao as vidas dos jogadores 
     que correspondem ao numero total de quadrados que os navios ocupam. invocado pelas funcoes pvp e pvc
     */
    switch (tamanho){
            case 5: //caso o tamanho seja 5 cada jogador tem 5 vidas 
                *v1=5;
                *v2=5;
                break;

            case 10://caso o tamanho seja 10 cada jogador tem 20 vidas 
                *v1=20;
                *v2=20;
                break;

            case 15://caso o tamanho seja 15 cada jogador tem 45 vidas 
                *v1=45;
                *v2=45;
                break;
        }           
}

void nickname(char *nick1, int num){
    /*
     pede o nickname que o utilizador pretende usar durante o jogo recebendo como argumento um apontador para o
     nickname e um inteiro num que indica o numero do jogador que se pretende que introduza o nickname
     */

    printf("Introduza o nickname do jogador %d:\n",num);
    
    setbuf(stdin, NULL); //limpar o buffer da string
    gets(nick1);//vai recolher para o vetor nick1 o nickname que for introduzido
}

int tam_camp (){
    /*
    função que pede ao jogador o tamanho do campo que pode ser 5 ou 10 ou 15. Invocado pelas funcoes pvp e pvc
    */

    int c = 0;

    do{ // enquanto o utilizador nao introduzir um tamanho de campo permitido repete o ciclo
        system("clear || cls");
        printf ("Escolha a dimensao do campo(5,10,15):\n   -> (5 = 25 quadrados = 5 navios);\n   -> (10 = 100 quadrados = 20 navios);\n   -> (15 = 225 quadrados = 45 navios);\n    Escolha: ");
        scanf ("%d",&c);
        setbuf(stdin, NULL);//limpa o buffer
    }while(c!=5 && c!=10 && c!=15);

    return c; // retorna o tamanho do campo
} 

void printVarPVC(struct JogoPVC jogopvc){
    /*funcao que imprime as informacoes de um jogo player vs computador que esteja guardado em ficheiro*/
    
    printf("Informacoes de jogo:\n\n");
    printf("\nTamanho do campo: %d", jogopvc.tamanho);    
    printf("\nNickname do jogador 1: %s", jogopvc.nick1);
    printf("\nNickname do jogador 2: %s", jogopvc.nick2);
    printf("\nVidas do %s: %d", jogopvc.nick1, jogopvc.v1);
    printf("\nVidas do %s: %d", jogopvc.nick2, jogopvc.v2);
    printf("\nRondas: %d", jogopvc.r);
    printf("\nDificuldade :%d \n", jogopvc.d);
}

void printVarPVP(struct JogoPVP jogopvp){
    /*funcao que imprime as informacoes de um jogo player vs player que esteja guardado em ficheiro*/
    
    printf("Informacoes de jogo:\n\n");
    printf("\nTamanho do campo: %d", jogopvp.tamanho);    
    printf("\nNickname do jogador 1: %s", jogopvp.nick1);
    printf("\nNickname do jogador2: %s", jogopvp.nick2);
    printf("\nVidas do %s: %d", jogopvp.nick1, jogopvp.v1);
    printf("\nVidas do %s: %d", jogopvp.nick2, jogopvp.v2);
    printf("\nRondas: %d \n", jogopvp.r);
}
    