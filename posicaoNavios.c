/*<Este source file contem as funcoes que permite escolher as posicoes dos navios antes do jogo comecar tanto para 
 * player vs player como para player vs computador>*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogar.h"

void posicaoNaviosPL(int **tab1,char nick1[],int tamanho){ /* Função que pede aos jogadores onde eles querem 
                                                            posicionar os seus navios*/
    
    int i=0;
    int j=0;
    int c=0;
    int h=0;//orientação do navio a ser posicionado
    int qnt5=0;// quantidade de navios "super porta avioes"
    int qnt4=0;// quantidade de navios "porta avioes"
    int qnt3=0;// quantidade de navios "navio de guerra"
    int qnt2=0;// quantidade de navios "submarinos"
    int qnt1=0;// quantidade de navios "destruidor"
    int l=0; // se l=1 essa coordenada esta ocupada nao sendo possivel posicionar navio, se l=0 pode posicionar o navio
    int coord=0; // seletor de coordenadas manuais ou automaticas para os jogadores
    int cond=0; //se cond=1 entao nao pode colocar navios nessa posicao logo ja nao verifica as outras condicoes
    
    do{ /* o jogador vai escolher se quer posicionar seus navios de forma manual ou automatica, repetindo 
           o ciclo enquanto nao introduzir uma opcao valida*/
        printf("%s\nIntroduza 1 para inserir coordenadas manualmente ou 2 para inserir aleatoriamente(Pode demorar alguns segundos!):",nick1);
        scanf("%d",&coord);
        setbuf(stdin, NULL);
    }while(coord!=1 && coord!=2);
    
    if(coord==2){ /* se for escolhida coordenada automatica os navios do jogador sao posicionadas pela
                     funcao posicaoNaviosCPU, a mesma funcao usada para distribuir as posicoes dos navios do computador*/
        posicaoNaviosCPU(tab1, tamanho);
    }
    else{ /*se for escolhida posicoes manuais, o utilizador escolhe todas as posicoes dos seus navios*/
            switch (tamanho){ // analisa o tamanho de campo para decidir a quantidade de cada navio que pode ser usada
                    case 5://se o tamanho do campo for 5 a quantidade de quadrados totais ocupados por navios é 5
                        qnt1=3; // 3 navios de 1 quadrado
                        qnt2=1; // 1 navio de 2 quadrados
                        qnt3=0; // 0 navios de 3 quadrados
                        qnt4=0; // 0 navios de 4 quadrados
                        qnt5=0; // 0 navios de 5 quadrados
                        break;

                    case 10://se o tamanho do campo for 10 a quantidade de quadrados totais ocupados por navios é 20
                        qnt1=4; // 4 navios de 1 quadrado
                        qnt2=3; // 3 navios de 2 quadrados
                        qnt3=2; // 2 navios de 3 quadrados
                        qnt4=1; // 1 navio de 4 quadrados
                        qnt5=0; // 0 navios de 5 quadrados
                        break;

                    case 15://se o tamanho do campo for 15 a quantidade de quadrados totais ocupados por navios é 45
                        qnt1=15; // 15 navios de 1 quadrado
                        qnt2=4; // 4 navios de 2 quadrados
                        qnt3=3; // 3 navios de 3 quadrados
                        qnt4=2; // 2 navios de 4 quadrados
                        qnt5=1; // 1 navio de 5 quadrados
                        break;
                }

            system("clear || cls");
            imprimeTab(tab1,tamanho,0,nick1); // imprime o tabuleiro
            
                for (c=1;c<=qnt5;c++){ //Enquanto não atingir o limite máximo de navios de 5 unidades a colocar


                        do{ // pede a orientacao do navio e repete enquanto nao introduzir um valor valido
                            printf("Vez do %s \nIndique a orientacao dos super porta avioes(5 unidades) (0-vertical | 1-horizontal):",nick1);
                            scanf("%d",&h);
                            setbuf(stdin, NULL);
                        }while(h!=0 && h!=1);

                        printf("Introduza as posicoes dos navios super porta avioes(5 unidades) do jogador %s\n\n",nick1);
                        printf("X:");
                        scanf("%d",&j);
                        setbuf(stdin, NULL);//limpa o buffer
                        printf("Y:");
                        scanf("%d",&i);
                        setbuf(stdin, NULL);//limpa o buffer
                        printf("\n");

                        if(h==0 && (i<1 || i>tamanho-4 || j<1 || j>tamanho)){ 
                            /*com orientacao vertical se pela coordenada introduzida alguma parte do navio ficar fora do  
                             tabuleiro é indicado que a posicao introduzida esta fora do campo e l=1 indicando que essa 
                             coordenada esta ocupada permitindo voltar a repetir o ciclo e impedindo de serem colocados 
                             navios fora do tabuleiro de jogo*/
                            system("clear || cls");
                            printf("Introduza uma coordenada pertencente ao campo!\n\n");
                            l=1;//ocupado
                        }

                        if(h==1 && (i<1||i>tamanho||j<1||j>tamanho-4)){
                            /*com orientacao horizontal se pela coordenada introduzida alguma parte do navio ficar 
                             fora do tabuleiro é indicado que a posicao introduzida esta fora do campo e l=1 indicando  
                             que essa coordenada esta ocupada permitindo voltar a repetir o ciclo e impedindo de serem 
                             colocados navios fora do tabuleiro de jogo*/
                            system("clear || cls");
                            printf("Introduza uma coordenada pertencente ao campo!\n\n");
                            l=1;//ocupado
                        }
//Nao precisa de verificar se ha navios a volta porque e o primeiro a ser posicionado e so tem um igual

                    if(l==1){ // se a coordenada esta ocupada o ciclo repete
                        c--;
                    }    

                    if(h==0 && l==0){ // com orientacao vertical e coordenada livre posiciona os navios
                        tab1[i][j]=1;//passa a ter um navio  
                        tab1[i+1][j]=1;
                        tab1[i+2][j]=1;
                        tab1[i+3][j]=1;
                        tab1[i+4][j]=1;

                        system("clear || cls");
                    }
                    if(h==1 && l==0){ // com orientacao horizontal e coordenada livre posiciona os navios
                        tab1[i][j]=1; //passa a ter um navio  
                        tab1[i][j+1]=1;
                        tab1[i][j+2]=1;
                        tab1[i][j+3]=1;
                        tab1[i][j+4]=1;

                        system("clear || cls");
                    }

                    imprimeTab(tab1,tamanho,0,nick1); // imprime o tabuleiro
                    l=0; // a cordenada passa a estar livre para voltar a executar como inicialmente

                }

                for (c=1;c<=qnt4;c++){ //Enquanto não atingir o limite máximo de navios de 4 unidades a colocar

                        do{
                            printf("Vez do %s \nIndique a orientacao dos porta avioes(4 unidades) (0-vertical | 1-horizontal):",nick1);
                            scanf("%d",&h);
                            setbuf(stdin, NULL);
                        }while(h!=0 && h!=1);

                        printf("Introduza as posicoes dos navios porta avioes(4 unidades) do jogador %s\n\n",nick1);
                        printf("X:");
                        scanf("%d",&j);
                        setbuf(stdin, NULL);//limpa o buffer
                        printf("Y:");
                        scanf("%d",&i);
                        setbuf(stdin, NULL);//limpa o buffer
                        printf("\n");

                        if(h==0 && (i<1||i>tamanho-3||j<1||j>tamanho)){
                            system("clear || cls");
                            printf("Introduza uma coordenada pertencente ao campo!\n\n");
                            l=1;
                            cond=1; // cond=1 para que nao seja necessario verificar se tem navios a sua volta
                        }

                        if(h==1 && (i<1||i>tamanho||j<1||j>tamanho-3)){
                            system("clear || cls");
                            printf("Introduza uma coordenada pertencente ao campo!\n\n");
                            l=1;//ocupado
                            cond=1;
                        }

                        if(h==0 && cond==0 && (tab1[i][j]!=0 || tab1[i-1][j]!=0 || tab1[i-1][j+1]!=0 || tab1[i-1][j-1]!=0 || tab1[i][j+1]!=0 || tab1[i][j-1]!=0 || tab1[i+1][j]!=0 || tab1[i+1][j-1]!=0 || tab1[i+1][j+1]!=0 || tab1[i+2][j]!=0 || tab1[i+2][j+1]!=0 || tab1[i+2][j-1]!=0|| tab1[i+3][j]!=0 || tab1[i+3][j-1]!=0 || tab1[i+3][j+1]!=0 || tab1[i+4][j]!=0 || tab1[i+4][j+1]!=0 || tab1[i+4][j-1]!=0)){
                            /*verifica se com orientacao vertical e com coordenadas pertencentes ao campo se existem
                             no raio de uma unidade para que caso tenha seja impossivel de colocar o navio nessas
                             coordenadas*/
                                system("clear || cls");
                                printf("Essa coordenada esta ocupada ou esta demasiada proximo de outro navio. Tente novamente!\n\n");
                                l=1;
                        }

                        if(h==1 && cond==0 && (tab1[i][j]!=0 || tab1[i][j-1]!=0 || tab1[i+1][j-1]!=0 || tab1[i-1][j-1]!=0 || tab1[i-1][j]!=0 || tab1[i+1][j]!=0 || tab1[i][j+1]!=0 || tab1[i+1][j+1]!=0 || tab1[i-1][j+1]!=0 || tab1[i][j+2]!=0 || tab1[i-1][j+2]!=0 || tab1[i+1][j+2]!=0 || tab1[i][j+3]!=0 || tab1[i-1][j+3]!=0 || tab1[i+1][j+3]!=0 || tab1[i][j+4]!=0 || tab1[i-1][j+4]!=0 || tab1[i+1][j+4]!=0)){
                                system("clear || cls");
                                printf("Essa coordenada esta ocupada ou esta demasiada proximo de outro navio. Tente novamente!\n\n");
                                l=1;
                        }

                    if(l==1){
                        c--;
                    }    

                    if(h==0 && l==0){
                        tab1[i][j]=1;//passa a ter um navio  
                        tab1[i+1][j]=1;
                        tab1[i+2][j]=1;
                        tab1[i+3][j]=1;

                        system("clear || cls");
                    }
                    if(h==1 && l==0){
                        tab1[i][j]=1;//passa a ter um navio  
                        tab1[i][j+1]=1;
                        tab1[i][j+2]=1;
                        tab1[i][j+3]=1;

                        system("clear || cls");
                    }

                    imprimeTab(tab1,tamanho,0,nick1);
                    l=0;
                    cond=0;

                }

                for (c=1;c<=qnt3;c++){  //Enquanto não atingir o limite máximo de navios de 3 unidades a colocar

                        do{
                            printf("vez do %s \nIndique a orientacao dos navios de guerra (3 unidades) (0-vertical | 1-horizontal):",nick1);
                            scanf("%d",&h);
                            setbuf(stdin, NULL);
                        }while(h!=0 && h!=1);

                        printf("Introduza as posicoes dos navios de guerra(3 unidades) do jogador %s\n\n",nick1);
                        printf("X:");
                        scanf("%d",&j);
                        setbuf(stdin, NULL);//limpa o buffer
                        printf("Y:");
                        scanf("%d",&i);
                        setbuf(stdin, NULL);//limpa o buffer
                        printf("\n");

                        if(h==0 && (i<1||i>tamanho-2||j<1||j>tamanho)){
                            system("clear || cls");
                            printf("Introduza uma coordenada pertencente ao campo!\n\n");
                            l=1;
                            cond=1;
                        }

                        if(h==1 && (i<1||i>tamanho||j<1||j>tamanho-2)){
                            system("clear || cls");
                            printf("Introduza uma coordenada pertencente ao campo!\n\n");
                            l=1;
                            cond=1;
                        }

                        if(h==0 && cond==0 && (tab1[i][j]!=0 || tab1[i-1][j]!=0 || tab1[i-1][j+1]!=0 || tab1[i-1][j-1]!=0 || tab1[i][j+1]!=0 || tab1[i][j-1]!=0 || tab1[i+1][j]!=0 || tab1[i+1][j-1]!=0 || tab1[i+1][j+1]!=0 || tab1[i+2][j]!=0 || tab1[i+2][j+1]!=0 || tab1[i+2][j-1]!=0 || tab1[i+3][j]!=0 || tab1[i+3][j+1]!=0 || tab1[i+3][j-1]!=0)){
                                system("clear || cls");
                                printf("Essa coordenada esta ocupada ou esta demasiada proximo de outro navio. Tente novamente!\n\n");
                                l=1;
                        }

                        if(h==1 && cond==0 && (tab1[i][j]!=0 || tab1[i][j-1]!=0 || tab1[i+1][j-1]!=0 || tab1[i-1][j-1]!=0 || tab1[i-1][j]!=0 || tab1[i+1][j]!=0 || tab1[i][j+1]!=0 || tab1[i+1][j+1]!=0 || tab1[i-1][j+1]!=0 || tab1[i][j+2]!=0 || tab1[i-1][j+2]!=0 || tab1[i+1][j+2]!=0 || tab1[i][j+3]!=0 || tab1[i-1][j+3]!=0 || tab1[i+1][j+3]!=0)){
                                system("clear || cls");
                                printf("Essa coordenada esta ocupada ou esta demasiada proximo de outro navio. Tente novamente!\n\n");
                                l=1;
                        }

                        if(l==1){
                            c--;
                        }

                    if(h==0 && l==0){
                        tab1[i][j]=1;//passa a ter um navio  
                        tab1[i+1][j]=1;
                        tab1[i+2][j]=1;

                        system("clear || cls");
                    }
                    if(h==1 && l==0){
                        tab1[i][j]=1;//passa a ter um navio  
                        tab1[i][j+1]=1;
                        tab1[i][j+2]=1;

                        system("clear || cls");
                    }

                    imprimeTab(tab1,tamanho,0,nick1);
                    l=0;
                    cond=0;
                }

                for (c=1;c<=qnt2;c++){  //Enquanto não atingir o limite máximo de navios de 5 unidades a colocar

                        do{
                            printf("Vez do %s \nIndique a orientacao dos submarinos(2 unidades) (0-vertical | 1-horizontal):",nick1);
                            scanf("%d",&h);
                            setbuf(stdin, NULL);
                        }while(h!=0 && h!=1);

                        printf("Introduza as posicoes dos submarinos(2 unidades) do jogador %s\n\n",nick1);
                        printf("X:");
                        scanf("%d",&j);
                        setbuf(stdin, NULL);//limpa o buffer
                        printf("Y:");
                        scanf("%d",&i);
                        setbuf(stdin, NULL);//limpa o buffer
                        printf("\n");

                        if(h==0 && (i<1||i>tamanho-1||j<1||j>tamanho)){
                            system("clear || cls");
                            printf("Introduza uma coordenada pertencente ao campo!\n\n");
                            l=1;
                            cond=1;
                        }

                        if(h==1 && (i<1||i>tamanho||j<1||j>tamanho-1)){
                            system("clear || cls");
                            printf("Introduza uma coordenada pertencente ao campo!\n\n");
                            l=1;
                            cond=1;
                        }

                        if(h==0 && cond==0 &&(tab1[i][j]!=0 || tab1[i-1][j]!=0 || tab1[i-1][j+1]!=0 || tab1[i-1][j-1]!=0 || tab1[i][j+1]!=0 || tab1[i][j-1]!=0 || tab1[i+1][j]!=0 || tab1[i+1][j-1]!=0 || tab1[i+1][j+1]!=0 || tab1[i+2][j]!=0 || tab1[i+2][j-1]!=0 || tab1[i+2][j+1]!=0)){
                                system("clear || cls");
                                printf("Essa coordenada esta ocupada ou esta demasiada proximo de outro navio. Tente novamente!\n\n");
                                l=1;
                        }

                        if(h==1 && cond==0 && (tab1[i][j]!=0 || tab1[i][j-1]!=0 || tab1[i-1][j-1]!=0 || tab1[i+1][j-1]!=0 || tab1[i-1][j]!=0 || tab1[i+1][j]!=0 || tab1[i][j+1]!=0 || tab1[i+1][j+1]!=0 || tab1[i-1][j+1]!=0 ||tab1[i][j+2]!=0 || tab1[i+1][j+2]!=0 || tab1[i-1][j+2]!=0)){
                                system("clear || cls");
                                printf("Essa coordenada esta ocupada ou esta demasiada proximo de outro navio. Tente novamente!\n\n");
                                l=1;
                        }

                    if(l==1){
                        c--;
                    }    

                    if(h==0 && l==0){
                        tab1[i][j]=1;//passa a ter um navio  
                        tab1[i+1][j]=1;

                        system("clear || cls");
                    }
                    if(h==1 && l==0){
                        tab1[i][j]=1;//passa a ter um navio  
                        tab1[i][j+1]=1;

                        system("clear || cls");            
                    } 

                    imprimeTab(tab1,tamanho,0,nick1);
                    l=0;
                    cond=0;

                }

                for (c=1;c<=qnt1;c++){  //Enquanto não atingir o limite máximo de navios de 1 unidade a colocar

                        printf("Vez do %s \nIntroduza as posicoes dos destruidores(1 unidade) do jogador %s\n\n",nick1,nick1);
                        printf("X:");
                        scanf("%d",&j);
                        setbuf(stdin, NULL);//limpa o buffer
                        printf("Y:");
                        scanf("%d",&i);
                        setbuf(stdin, NULL);//limpa o buffer
                        printf("\n");

                        if(i<1||i>tamanho||j<1||j>tamanho){
                            system("clear || cls");
                            printf("Introduza uma coordenada pertencente ao campo!\n\n");
                            l=1;
                            cond=1;
                        }

                        if(cond==0 && (tab1[i][j]!=0 || tab1[i+1][j]!=0 || tab1[i-1][j]!=0 || tab1[i+1][j+1]!=0 ||tab1[i-1][j-1]!=0 || tab1[i+1][j-1]!=0 || tab1[i-1][j+1]!=0 || tab1[i][j+1]!=0 || tab1[i][j-1]!=0)){
                                system("clear || cls");
                                printf("Essa coordenada esta ocupada ou esta demasiada proximo de outro navio. Tente novamente!\n\n");
                                l=1;
                        }

                    if(l==1){
                        c--;
                    }
                    else{
                            tab1[i][j]=1;//passa a ter um navio  
                            system("clear || cls");
                    }


                    l=0;
                    imprimeTab(tab1,tamanho,0,nick1);

                    cond=0;
                }
    }
}
void posicaoNaviosCPU(int **tab1,int tamanho){//Função que pede aos jogadores onde eles querem posicionar os seus navios
    
    int i=0;
    int j=0;
    int c=0;
    int h=0; // orientação
    int l=0; // livre
    int cond=0;//se cond=1 entao nao pode colocar navios nessa posicao logo ja nao verifica as outras condicoes
    
    int qnt5=0; // quantidade de navios "super porta avioes"
    int qnt4=0; // quantidade de navios "porta avioes"
    int qnt3=0; // quantidade de navios "navio de guerra"
    int qnt2=0; // quantidade de navios "submarinos"
    int qnt1=0; // quantidade de navios "destruidor"
    
    switch (tamanho){ // analisa o tamanho de campo para decidir a quantidade de cada navio que pode ser usada
                    case 5://se o tamanho do campo for 5 a quantidade de quadrados totais ocupados por navios é 5
                        qnt1=3; // 3 navios de 1 quadrado
                        qnt2=1; // 1 navio de 2 quadrados
                        qnt3=0; // 0 navios de 3 quadrados
                        qnt4=0; // 0 navios de 4 quadrados
                        qnt5=0; // 0 navios de 5 quadrados
                        break;

                    case 10://se o tamanho do campo for 10 a quantidade de quadrados totais ocupados por navios é 20
                        qnt1=4; // 4 navios de 1 quadrado
                        qnt2=3; // 3 navios de 2 quadrados
                        qnt3=2; // 2 navios de 3 quadrados
                        qnt4=1; // 1 navio de 4 quadrados
                        qnt5=0; // 0 navios de 5 quadrados
                        break;

                    case 15://se o tamanho do campo for 15 a quantidade de quadrados totais ocupados por navios é 45
                        qnt1=15; // 15 navios de 1 quadrado
                        qnt2=4; // 4 navios de 2 quadrados
                        qnt3=3; // 3 navios de 3 quadrados
                        qnt4=2; // 2 navios de 4 quadrados
                        qnt5=1; // 1 navio de 5 quadrados
                        break;
                }                       
    
        for (c=1;c<=qnt5;c++){//Enquanto não atingir o limite máximo de navios de 5 unidades a colocar

                srand(time(NULL));
                i=rand() % tamanho+1; // gera um i aleatorio a variar entre 1 e tamanho
                j=rand() % tamanho+1; // gera um j aleatorio a variar entre 1 e tamanho
                h=rand() % 2; // gera uma orientacao aleatoria a variar entre 0 (vertical) e 1(horizontal)

                 if(h==0 && (i<1||i>tamanho-4||j<1||j>tamanho)){
                    /*com orientacao vertical se pela coordenada introduzida alguma parte do navio ficar fora do 
                    tabuleiro é indicado que a posicao introduzida esta fora do campo e l=1 indicando que essa
                    coordenada esta ocupada permitindo voltar a repetir o ciclo e impedindo de serem colocados navios
                    fora do tabuleiro de jogo*/
                    l=1;//ocupado
                    cond=1;
                }
                
                if(h==1 && (i<1||i>tamanho||j<1||j>tamanho-4)){
                    /*com orientacao horizental se pela coordenada introduzida alguma parte do navio ficar fora do 
                    tabuleiro é indicado que a posicao introduzida esta fora do campo e l=1 indicando que essa
                    coordenada esta ocupada permitindo voltar a repetir o ciclo e impedindo de serem colocados navios
                    fora do tabuleiro de jogo*/
                    l=1;//ocupado
                    cond=1;
                }
                
            if(l==1){ // se a coordenada estiver ocupada repete esse ciclo
                c--;
            }    

            if(h==0 && l==0){ // se a orientacao for vertical e a coordenada estiver livre
                tab1[i][j]=1;//passa a ter um navio  
                tab1[i+1][j]=1;
                tab1[i+2][j]=1;
                tab1[i+3][j]=1;
                tab1[i+4][j]=1;
            }
            if(h==1 && l==0){ // se a orientacao for horizontal e a coordenada estiver livre
                tab1[i][j]=1;//passa a ter um navio  
                tab1[i][j+1]=1;
                tab1[i][j+2]=1;
                tab1[i][j+3]=1;
                tab1[i][j+4]=1;
            }
                
            l=0; // a cordenada passa a estar livre para voltar a executar como inicialmente
            cond=0; // a condicao passa a valer zero para voltar a executar como inicialmente

        }
    
        for (c=1;c<=qnt4;c++){//Enquanto não atingir o limite máximo de navios de 4 unidadesa colocar

                srand(time(NULL));
                i=rand() % tamanho+1;//coordenadas
                j=rand() % tamanho+1;//coordenadas
                h=rand() % 2;//orientação

               if(h==0 && (i<1||i>tamanho-3||j<1||j>tamanho)){
                    l=1;
                    cond=1;
                }
                
                if(h==1 && (i<1||i>tamanho||j<1||j>tamanho-3)){
                    l=1;//ocupado
                    cond=1;
                }

                if(h==0 && cond==0 && (tab1[i][j]!=0 || tab1[i-1][j]!=0 || tab1[i-1][j+1]!=0 || tab1[i-1][j-1]!=0 || tab1[i][j+1]!=0 || tab1[i][j-1]!=0 || tab1[i+1][j]!=0 || tab1[i+1][j-1]!=0 || tab1[i+1][j+1]!=0 || tab1[i+2][j]!=0 || tab1[i+2][j+1]!=0 || tab1[i+2][j-1]!=0 || tab1[i+3][j]!=0 || tab1[i+3][j-1]!=0 || tab1[i+3][j+1]!=0 || tab1[i+4][j]!=0 || tab1[i+4][j-1]!=0 || tab1[i+4][j+1]!=0)){
                        l=1;//ocupado
                }
                
                if(h==1 && cond==0 && (tab1[i][j]!=0 || tab1[i][j-1]!=0 || tab1[i+1][j-1]!=0 || tab1[i-1][j-1]!=0 || tab1[i-1][j]!=0 || tab1[i+1][j]!=0 || tab1[i][j+1]!=0 || tab1[i+1][j+1]!=0 || tab1[i-1][j+1]!=0 || tab1[i][j+2]!=0 || tab1[i-1][j+2]!=0 || tab1[i+1][j+2]!=0 || tab1[i][j+3]!=0 || tab1[i-1][j+3]!=0 || tab1[i+1][j+3]!=0 || tab1[i][j+4]!=0 || tab1[i-1][j+4]!=0 || tab1[i+1][j+4]!=0)){
                        l=1;//ocupado
                }
                
            if(l==1){
                c--;
            }    

            if(h==0 && l==0){
                tab1[i][j]=1;//passa a ter um navio  
                tab1[i+1][j]=1;
                tab1[i+2][j]=1;
                tab1[i+3][j]=1;
            }
            if(h==1 && l==0){
                tab1[i][j]=1;//passa a ter um navio  
                tab1[i][j+1]=1;
                tab1[i][j+2]=1;
                tab1[i][j+3]=1;
            }
            l=0;

            cond=0;
        }
    
        for (c=1;c<=qnt3;c++){//Enquanto não atingir o limite máximo de navios de 3 unidades a colocar

                srand(time(NULL));
                i=rand() % tamanho+1;//coordenadas
                j=rand() % tamanho+1;//coordenadas
                h=rand() % 2;//orientação

                if(h==0 && (i<1||i>tamanho-2||j<1||j>tamanho)){
                    l=1;
                    cond=1;
                }
                
                if(h==1 && (i<1||i>tamanho||j<1||j>tamanho-2)){
                    l=1;
                    cond=1;
                }

                if(h==0 && cond==0 && (tab1[i][j]!=0 || tab1[i-1][j]!=0 || tab1[i-1][j-1]!=0 || tab1[i-1][j+1]!=0 || tab1[i][j+1]!=0 || tab1[i][j-1]!=0 || tab1[i+1][j]!=0 || tab1[i+1][j-1]!=0 || tab1[i+1][j+1]!=0 || tab1[i+2][j]!=0 || tab1[i+2][j+1]!=0 || tab1[i+2][j-1]!=0 || tab1[i+3][j]!=0 || tab1[i+3][j+1]!=0 || tab1[i+3][j-1]!=0)){
                        l=1;
                }
                
                if(h==1 && cond==0 && (tab1[i][j]!=0 || tab1[i][j-1]!=0 || tab1[i+1][j-1]!=0 || tab1[i-1][j-1]!=0 || tab1[i-1][j]!=0 || tab1[i+1][j]!=0 || tab1[i][j+1]!=0 || tab1[i+1][j+1]!=0 || tab1[i-1][j+1]!=0 || tab1[i][j+2]!=0 || tab1[i-1][j+2]!=0 || tab1[i+1][j+2]!=0 || tab1[i][j+3]!=0 || tab1[i-1][j+3]!=0 || tab1[i+1][j+3]!=0)){
                        l=1;
                }

                if(l==1){
                    c--;
                }

            if(h==0 && l==0){
                tab1[i][j]=1;//passa a ter um navio  
                tab1[i+1][j]=1;
                tab1[i+2][j]=1;
            }
            if(h==1 && l==0){
                tab1[i][j]=1;//passa a ter um navio  
                tab1[i][j+1]=1;
                tab1[i][j+2]=1;
            }
            l=0;
            cond=0;
        }
    
        for (c=1;c<=qnt2;c++){//Enquanto não atingir o limite máximo de navios de 2 unidades a colocar

                srand(time(NULL));
                i=rand() % tamanho+1;//coordenadas
                j=rand() % tamanho+1;//coordenadas
                h=rand() % 2;//orientação

                if(h==0 && (i<1||i>tamanho-1||j<1||j>tamanho)){
                    l=1;
                    cond=1;
                }
                
                if(h==1 && (i<1||i>tamanho||j<1||j>tamanho-1)){
                    l=1;
                    cond=1;
                }

                if(h==0 && cond==0 && (tab1[i][j]!=0 || tab1[i-1][j]!=0 || tab1[i-1][j+1]!=0 || tab1[i-1][j-1]!=0 || tab1[i][j+1]!=0 || tab1[i][j-1]!=0 || tab1[i+1][j]!=0 || tab1[i+1][j-1]!=0 || tab1[i+1][j+1]!=0 || tab1[i+2][j]!=0 || tab1[i+2][j-1]!=0 || tab1[i+2][j+1]!=0)){
                        l=1;
                }
                
                if(h==1 && cond==0 && (tab1[i][j]!=0 || tab1[i][j-1]!=0 || tab1[i-1][j-1]!=0 || tab1[i+1][j-1]!=0 || tab1[i-1][j]!=0 || tab1[i+1][j]!=0 || tab1[i][j+1]!=0 || tab1[i+1][j+1]!=0 || tab1[i-1][j+1]!=0 || tab1[i][j+2]!=0 || tab1[i+1][j+2]!=0 || tab1[i-1][j+2]!=0)){
                        l=1;
                }

            if(l==1){
                c--;
            }    
                
            if(h==0 && l==0){
                tab1[i][j]=1;//passa a ter um navio  
                tab1[i+1][j]=1;
            }
            if(h==1 && l==0){
                tab1[i][j]=1;//passa a ter um navio  
                tab1[i][j+1]=1;        
            } 
            l=0;
            cond=0;

        }
    
        for (c=1;c<=qnt1;c++){//Enquanto não atingir o limite máximo de navios de 1 unidade a colocar

                    srand(time(NULL));
                    i=rand() % tamanho+1;//coordenadas
                    j=rand() % tamanho+1;//coordenadas
                    h=rand() % 2;//orientação

                if(i<1||i>tamanho||j<1||j>tamanho){
                    l=1;
                    cond=1;
                }

                if(cond==0 && (tab1[i][j]!=0 || tab1[i+1][j]!=0 || tab1[i-1][j]!=0 || tab1[i+1][j+1]!=0 ||tab1[i-1][j-1]!=0 || tab1[i+1][j-1]!=0 || tab1[i-1][j+1]!=0 || tab1[i][j+1]!=0 || tab1[i][j-1]!=0)){
                        l=1;
                }
            
            if(l==1){
                c--;
            }
            else{
                    tab1[i][j]=1;//passa a ter um navio  
            }
                      
                    
            l=0;
            cond=0;
            }
}