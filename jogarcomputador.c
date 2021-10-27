/*<Este source file contem as funcoes relativas a jogabilidade do computador (funcao que permite o computador colocar 
coordenadas para atacar, funcao inicia os procedimentos para o jogo entre computador e jogador humano e funcao que permite 
executar o jogo)>*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogar.h"

void jogarCPU(int **tab1,int **tab2,int tamanho, char nick1[], char nick2[], int *v1,int *v2, int d, int *fase, int *b, int *pi, int *pj, int r){
    /*
    Esta funcao permite o computador colocar as coordenadas para atacar os navios, verificando se as
    coordenadas colocadas pelo computador estao livres ou pertencem ao campo, caso a coordenada colocada nao seja possivel
    o computador introduz uma nova. O computador joga por fases dependendo se acertou o navio adversario
    Invocado pela funcao executarPVC
    */
    int i=0; // coordenada que o cpu vai atacar
    int j=0; // coordenada que o cpu vai atacar
    int t=0; //tiro random
    int rep=0; // repetidor de ciclo, se rep=0-> nao repete, se rep=1-> repete
    int exe3=0; // se fase=3 ja foi executado exe3=1, se não foi executado exe3=0
    int pa=0; //probabilidade de acertar dependendo da dificuldade
    int a=0; //se 0 vai errar se 1 vai acertar
    int x=0;
    int y=0;
    
    do{//Enquanto o computador acertar nas posições dos navios é ele que continua a jogar
       
        rep=0;//o repetidor de ciclo vale zero, sendo alterado caso seja necessario introduzir uma coordenada nova
        
        if(*v1!=0 && *v2!=0 && *fase==0){  
            /*se ambos os jogadores tem navios e o computador se encontra em fase 0, entao o computador joga coordenadas
             aleatorias*/

            srand(time(NULL));
            pa=(rand() % 100)+1;/*gera numeros entre 1 e 100*/
            
            switch (d){ // analisa a dificuldad de jogo para determinar a probabilidade do computador acertar o navio
                case 1: // se estiver em dificuldade 1 (facil) tem 10% probabilidade de acertar o tiro aleatorio
                    if(pa<=10){ // se pa<10 entao a=1(acerta)
                        a=1;
                    }else{
                        a=0; // se pa>=10 entao a=0(erra)
                    }
                    break;
                    
                case 2: // se estiver em dificuldade 2 (medio) tem 25% probabilidade de acertar o tiro aleatorio
                    if(pa<=25){ // se pa<25 entao a=1(acerta)
                        a=1;
                    }else{
                        a=0; // se pa>=25 entao a=0(erra)
                    }
                    break;
                    
                case 3: // se estiver em dificuldade 3 (dificil) tem 40% probabilidade de acertar o tiro aleatorio
                    if(pa<=40){ // se pa>40 entao a=1(acerta)
                        a=1;
                    }else{
                        a=0; // se pa<=40 entao a=0(erra)
                    }
                    break;
                    
                case 4: // se estiver em dificuldade 4 (impossivel) tem 85% probabilidade de acertar o tiro aleatorio
                    if(pa<=85){ // se pa>85 entao a=1(acerta)
                        a=1;
                    }else{
                        a=0; // se pa<=85 entao a=0(erra)
                    }
                    break;
            }

            do{/*se o computador escolheu uma coordenada ja selecionada, ou se acertou quando era suposto errar ou
                 se errou quando era suposto acertar, volta a repetir o ciclo*/
              
                if(a==0){ // se o computador tiver de errar escolhe coordenadas aleatorias
                    srand(time(NULL));
                    i=(rand() % tamanho)+1;/*gera numeros entre 1 e tamanho*/
                    j=(rand() % tamanho)+1;
                }
                else{ // se o computador tive de acertar percorre a matriz em busca de navios
                    for(x=1; x<=tamanho; x++){
                        for(y=1; y<=tamanho; y++){
                            if(tab2[x][y]==1){ /* quando encontrar um navio as coordenadas a atacar correspondem a essa 
                                                  posicao*/
                                i=x;
                                j=y;
                            }
                        }
                    }
                }
            }while(tab2[i][j]==2 || tab2[i][j]==3 || (tab2[i][j]==0 && a==1) || (tab2[i][j]==1 && a==0));

            
        }
        
        if(*v1!=0 && *v2!=0 && *fase==1){
            /*se ambos os jogadores tem navios e o computador se encontra em fase 1, entao o computador vai tentar
             acertar nas coordenadas a volta do navio acertado aleatoriamente se tiver alguma livre*/
               
                if(tab2[*pi+1][*pj]==0 || tab2[*pi+1][*pj]==1 || tab2[*pi-1][*pj]==0 || tab2[*pi-1][*pj]==1 || tab2[*pi][*pj+1]==0 || tab2[*pi][*pj+1]==1  || tab2[*pi][*pj-1]==0 || tab2[*pi][*pj-1]==1){
                   //se a volta da coordenada acertada aleatoriamente tiver algum navio nao selecionado

                    do{//escolhe uma coordenada para rodar e volta a escolher outra se a escolhida ja tiver sido selecionada
                        srand(time(NULL));
                        t=(rand() % 4) + 1; //entre 1 e 4

                        if(t==1){ //se t=1 entao i vale mais uma unidade e j mantem-se igual
                            i=*pi+1;
                            j=*pj;
                        }
                        if(t==2){ //se t=2 entao i vale menos uma unidade e j mantem-se igual
                            i=*pi-1;
                            j=*pj;
                        }
                        if(t==3){ //se t=3 entao i mantem-se igual e j vale mais uma unidade
                            i=*pi;
                            j=*pj+1;
                        }
                        if(t==4){ //se t=4 entao i mantem-se igual e j vale menos uma unidade
                            i=*pi;
                            j=*pj-1;
                        }
                    }while(tab2[i][j]!=0 && tab2[i][j]!=1);
                }
                else{ // caso a volta do navio acertado aleatoriamente nao tiver espacos livres 
                    *fase=0; //a fase volta a valer "0"
                    rep=1; //o ciclo de escolha de coordenada para atacar e repetido
                }

                if(i<1 || i > tamanho || j<1 || j>tamanho){ //se for introduzida uma coordenada fora do tabuleiro
                    rep=1; //o ciclo de escolha de coordenada para atacar e repetido
                }
   
        }
        
        if(*v1!=0 && *v2!=0 && *fase==2){
            /*se ambos os jogadores tem navios e o computador se encontra em fase 2, entao o computador vai percorrer 
             uma linha ja definida entre o navio selecionado da fase 0 e da fase 1*/
            
                if(*b==0){ //se a orientacao for vertical
                        if(tab2[*pi+1][*pj]==0){ // se para pj e pi+1 tiver um quadrado nao selecionado 
                            i=*pi+1; // entao i=pi+1
                        }

                        if(tab2[*pi-1][*pj]==0){ // se para pj e pi-1 tiver um quadrado nao selecionado 
                            i=*pi-1; // entao i=pi-1
                        }

                        if(tab2[*pi+1][*pj]==1){ // se para pj e pi+1 tiver um quadrado nao selecionado
                            i=*pi+1; // entao i=pi+1
                        }

                        if(tab2[*pi-1][*pj]==1){ // se para pj e pi-1 tiver um quadrado nao selecionado
                            i=*pi-1; // entao i=pi-1
                        }


                        if(tab2[*pi+1][*pj]==2){ // se para pj e pi+1 tiver um quadrado selecionado sem navio
                            *fase=3; // entra em fase 3
                        }

                        if(tab2[*pi-1][*pj]==2){ // se para pj e pi-1 tiver um quadrado selecionado sem navio
                            *fase=3; // entra em fase 3
                        }

                }
                
                if(*b==1){ // se a orientacao for horizontal
                        if(tab2[*pi][*pj+1]==0){ // se para pj+1 e pi tiver um quadrado nao selecionado 
                            j=*pj+1; // entao j=pj+1
                        }

                        if(tab2[*pi][*pj-1]==0){ // se para pj-1 e pi tiver um quadrado nao selecionado
                            j=*pj-1; // entao j=pj-1
                        }

                        if(tab2[*pi][*pj+1]==1){ // se para pj+1 e pi tiver um quadrado nao selecionado 
                            j=*pj+1; // entao j=pj+1
                        }

                        if(tab2[*pi][*pj-1]==1){ // se para pj-1 e pi tiver um quadrado nao selecionado
                            j=*pj-1; // entao j=pj-1
                        }


                        if(tab2[*pi][*pj+1]==2){ // se para pj+1 e pi tiver um quadrado selecionado sem navio
                            *fase=3; // entra em fase 3
                        }

                        if(tab2[*pi][*pj-1]==2){ // se para pj+1 e pi tiver um quadrado selecionado sem navio
                            *fase=3; // entra em fase 3
                        }

                }
                
                if(i>tamanho || i<1 || j>tamanho || j<1){ // se for selecionada uma coordenada fora do tabuleiro
                    *fase=3; //entra em fase 3
                    rep=1; // o ciclo de escolha de coordenada para atacar e repetido
                }
            
        }
        
        if(*v1!=0 && *v2!=0 && *fase==3){
            /*se ambos os jogadores tem navios e o computador se encontra em fase 3, entao o computador vai percorrer 
             a linha ja definida na fase 2 ao contrario para encontrar os quadrados restantes do navio*/
            
            if(*b==0){ //se a orientacao e vertical
                        if(tab2[*pi+1][*pj]==3){ // se em j=pj e i=pi+1 tiver o quadrado ja selecionado
                            do{ // a coordenada i passa a valer pi+1 enquanto tiver quadrados ja selecionados
                                *pi=*pi+1;
                                i=*pi;
                                j=*pj;
                            }while(tab2[i][*pj]==3);
                            
                            if(i>tamanho){ //  se i for maior que o tamanho do campo, entao i vale menos uma unidade
                                i=*pi-1;
                            }  
                            
                        }

                        if(tab2[*pi-1][*pj]==3){ // se em j=pj e i=pi-1 tiver o navio ja selecionado
                            do{ // a coordenada i passa a valer pi-1 enquanto tiver navios ja selecionados
                                *pi=*pi-1;
                                i=*pi;
                                j=*pj;
                            }while(tab2[i][*pj]==3);
                            
                            if(i>tamanho){ //  se i for maior que o tamanho do campo, entao i vale mais uma unidade
                                i=*pi+1;
                            }
                        }
                        
                        
            }
            if(*b==1){ // se a orientacao e horizontal 
                        if(tab2[*pi][*pj+1]==3){ // se em i=pi+1 e j=pj tiver o quadrado ja selecionado
                            do{ // a coordenada j passa a valer pj+1 enquanto tiver quadrados ja selecionados
                                *pj=*pj+1;
                                j=*pj;
                                i=*pi;
                            }while(tab2[*pi][j]==3);
                            
                            if(j>tamanho){ // se j for maior que o tamanho entao j vale menos uma unidade
                                j=*pj-1;
                            }
                        }

                        if(tab2[*pi][*pj-1]==3){ // se em i=pi-1 e j=pj tiver o quadrado ja selecionado
                            do{ // a coordenada j passa a valer pj-1 enquanto tiver quadrados ja selecionados
                                *pj=*pj-1;
                                j=*pj;
                                i=*pi;
                            }while(tab2[*pi][j]==3);
                            
                            if(j>tamanho){
                                j=*pj+1; // se j for maior que o tamanho entao j vale mais uma unidade
                            }
                        }
            }
            exe3=1; // a fase 3 ja foi executada
        }
        
        //0-não selecionado sem navio; 1-não selecionado com navio; 2- selecionado sem navio; 3- selecionado com navio
           
        
        if(*v1!=0 && *v2!=0 && tab2[i][j]==0){ // Se errou a posição do navio do adversario

            tab2[i][j]=2; // A posição do tabuleiro passa a a valer 1(selecionado sem navio)   

            switch(*fase){ // analisa em que fase esta
                case 0: // se estiver em fase 0 continua na fase 0
                    *fase=0;
                    break;

                case 1: // se estiver na fase 1 continua em fase 1
                    *fase=1;
                    break;

                case 2: // se estiver em fase 2 passa a fase 3
                    *fase=3;
                    break;

                case 3: /* se estiver em fase 3 passa a fase 0 e exe3 passa a valer 0 indicando que ainda nao foi 
                        executado no novo ciclo*/
                    *fase=0;
                    exe3=0;
                    break;
            }  

            system("clear || cls");
            printf("ERROU!\n\n");//Indica que errou
        }  

        if(*v1!=0 && *v2!=0 && tab2[i][j]==1){ // se acertou a posicao dos navios adversarios

            tab2[i][j]=3; // A posição do tabuleiro passa a a valer 3(selecionado com navio)

            switch(*fase){ // analisa a fase em que esta
                    
                    case 0: // se estiver em fase 0 passa para fase 1
                        *fase=1;
                        break;

                    case 1: // se estiver em fase 1 determina a horientacao do navio
                        if(*pi-i!=0){ /*se a diferença no eixo yy entre a coordenada acertada inicialmente e a 
                                      acertada ao rodar for diferente de zero*/
                            *b=0; // orientacao vertical

                        }else{ /*se a diferença no eixo xx entre a coordenada acertada inicialmente e a 
                                acertada ao rodar for diferente de zero*/
                            *b=1; // orientacao horizontal
                        }

                        *fase=2; // passa a fase 2
                        break;

                    case 2: // se estiver em fase 2 continua em fase 2
                        *fase=2;
                        break;

                    case 3: // se estiver em fase 3 continua em fase 3
                        *fase=3;
                        break;
            }

            *pi=i; // pi fica com a mesma condenada de i
            *pj=j; // pj fica com a mesma condenada de j

            system("clear || cls");

            printf("ACERTOU!\n\n");//Indica que acertou
            imprimeTab(tab2,tamanho,1,nick2); /*Imprime o tabuleiro correspondente ao jogador cujo nickname foi 
                                              indicado na linha acima*/

            *v1=*v1-1; // o oponente perde uma vida
        }

        if(*v1!=0 && *v2!=0 && tab2[i][j]==2){ // se o cpu escolheu coordenadas que ja foram selecionadas e sem navio

            switch (*fase){ // analisa a fase em que esta
                    
                case 2: // se estiver em fase 2 passa a fase 3 e o ciclo é repetido
                    *fase=3;
                    rep=1;
                    break;

                case 3: // se estiver em fase 3
                    if(exe3==1){ // se a fase 3 ja estiver sido executada 
                        *fase=0; // passa  a fase 0
                        exe3=0; // o indicador se fase 3 passa a 0
                        rep=1; // repete o ciclo
                    }
                    break;
               
            }

        }
        
    }while((tab2[i][j]==3 || rep==1) && *v1!=0 && *v2!=0);
}

void pvc(){
    /*
    funcao que inicia uma serie de procedimentos antes de iniciar o jogo(tamanho do campo, nicknames, vidas, rondas,
    tabuleiros e posicoes dos navios) e posteriormente inicia o jogo chamando para isso a funcao executarPVC
    */
    
    struct JogoPVC jogopvc;
    
    int i=0;
    int j=0;
    
    jogopvc.terminado=0;
    jogopvc.tamanho=0; //tamanho do campo
    strcpy(jogopvc.nick2,"Computador");
    jogopvc.v1=0; //Navios vivos do jogador 1
    jogopvc.v2=0; //Navios vivos do jogador 2
    jogopvc.r=1; //O jogo comeca na ronda 1
    jogopvc.d=0; //dificuldade de jogo
    jogopvc.fase=0; //0-não acertou | 1- acertou o tiro aleatorio 
              //2- acertou ao rodar a coordenada | 3- errou ao percorrer o navio
    jogopvc.b=0; //orientacao do navio mirado: 0-vertical | 1- horizontal
    jogopvc.pi=0; //auxiliar de posicao de a coordenada i
    jogopvc.pj=0; //auxiliar de posicao de a coordenada j
      
    system("clear || cls");
    
    dificuldade(&(jogopvc.d)); // chama a funcao dificuldade para o utiliador escolher a dificuldade de jogo
      
    jogopvc.tamanho=tam_camp(); // chama a função tam_camp para definir o tamanho do campo
      
    /**********cria o tabuleiro 1***********/

    jogopvc.tab1 = (int **)malloc((jogopvc.tamanho+2)*sizeof(int*));//cria uma coluna |
    //                                                                                v

    for(i=0;i<=jogopvc.tamanho+1;i++){
        jogopvc.tab1[i]= (int *)malloc((jogopvc.tamanho+2)*sizeof(int));//cria as linhas ->
        
        if (jogopvc.tab1[i] == NULL){
                printf("Nao existe memoria.");
                exit(0);
        }
     }
     
     //inicializa o tabuleiro 1
    for(i=0;i<=jogopvc.tamanho+1;i++){
        for(j=0;j<=jogopvc.tamanho+1;j++){
            jogopvc.tab1[i][j]=0;
        }
    }
      
    /*************cria o tabuleiro 2************/

    jogopvc.tab2 = (int **)malloc((jogopvc.tamanho+2)*sizeof(int*));//cria uma coluna |
     //                                                                                v

    for(i=0;i<=jogopvc.tamanho+1;i++){
        jogopvc.tab2[i]= (int *)malloc((jogopvc.tamanho+2)*sizeof(int));//cria as linhas ->
        
        if (jogopvc.tab2[i] == NULL){
                printf("Nao existe memoria.");
                exit(0);
        }
     }
     //inicializa o tabuleiro 2
    for(i=0;i<=jogopvc.tamanho+1;i++){
        for(j=0;j<=jogopvc.tamanho+1;j++){
            jogopvc.tab2[i][j]=0;
        }
    }
     
    system("clear || cls");
      
    nickname(jogopvc.nick1, 1); 
    /*chama a função nickname para definir o nome do jogador 1, passa como argumento o vetor para
    guardar o nome e o numero "1" para indicar que é o nome do jogador 1 que é pretendido*/ 
      
    vidas(jogopvc.tamanho, &(jogopvc.v1), &(jogopvc.v2));
    /*chama a funcao vidas para definir a quantidade de vidas iniciais dos dois jogadores, 
    passando como argumento o tamanho do campo e o endereco de memoria das vidas dos dois jogadores*/

    system("clear || cls");
      
    posicaoNaviosPL(jogopvc.tab1, jogopvc.nick1, jogopvc.tamanho);
    /*chama a funcao posicaoNaviosPL para posicionar os navios do jogador 1 passando como argumentos o 
    tabuleiro do jogador 1, o seu nickname e o tamanho do campo*/ 
      
    system("clear || cls");
      
    posicaoNaviosCPU(jogopvc.tab2, jogopvc.tamanho);
    /*chama a funcao posicaoNaviosCPU para posicionar os navios do computador passando como argumentos o 
    tabuleiro do computador e o tamanho do campo*/ 
      
    system("clear || cls");
      
    printf("INICIO DO JOGO\n\n");
      
    executarPVC(&(jogopvc),0);
        /*chama a funcao executarPVC que inicia e corre o jogo ate alguem vencer o jogo, passando como argumento a 
        estrutura que contem os dados de jogo e tambem o numero "0" indicando que este é um jogo novo e nao um jogo que 
        esta a ser continuado*/
  }

void executarPVC(struct JogoPVC* jogopvc, int continuar){  
    /*
     Inicia o jogo e executa enquanto nao houver um vencedor. chamado pela funcao pvc
     */
    
    int i=0;
    int j=0;
    int sair=0;//sair no final do jogo
    
    if(continuar==1){ /* se for um jogo que esteja a ser continuado carrega os dados de ficheiro para as variaveis 
                      e estruturas*/
        
        int tabuleiropvc1[17][17]; // matriz onde tabuleiro de jogo sera pre carregado
        int tabuleiropvc2[17][17];
        
        FILE *pvctab1; //abre o ficeiro que contem o tabuleiro de jogo 1 e carrega as informacoes na matriz tabuleiropvc1
        pvctab1=fopen ("tabuleiropvc1.bin","rb");

        if (pvctab1==NULL){
            perror("Ocorreu um erro: ");
        } 
        else{
            fread (tabuleiropvc1,sizeof(tabuleiropvc1),1,pvctab1);  
        }
        
        FILE *pvctab2; //abre o ficeiro que contem o tabuleiro de jogo 1 e carrega as informacoes na matriz tabuleiropvc1
        pvctab2=fopen ("tabuleiropvc2.bin","rb");

        if (pvctab2==NULL){
            perror("Ocorreu um erro: ");
        } 
        else{
            fread (tabuleiropvc2,sizeof(tabuleiropvc2),1,pvctab2);
        }
        
        /************cria o tabuleiro 1************/  

        jogopvc->tab1 = (int **)malloc((jogopvc->tamanho+2)*sizeof(int*));//cria uma coluna |
        //                                                                                  v

        for(i=0;i<=jogopvc->tamanho+1;i++){
            jogopvc->tab1[i]= (int *)malloc((jogopvc->tamanho+2)*sizeof(int));//cria as linhas ->
            
            if (jogopvc->tab1[i] == NULL){
                printf("Nao existe memoria.");
                exit(0);
            }
        }


        //inicializa o tabuleiro 1 com as informacoes de tabuleiropvc1
        for(i=0;i<=jogopvc->tamanho+1;i++){
            for(j=0;j<=jogopvc->tamanho+1;j++){
                jogopvc->tab1[i][j]=tabuleiropvc1[i][j];
            }
        }
        /***************cria o tabuleiro 2 ***************/ 

        jogopvc->tab2 = (int **)malloc((jogopvc->tamanho+2)*sizeof(int*));//cria uma coluna |
        //                                                                                 v

        for(i=0;i<=jogopvc->tamanho+1;i++){
            jogopvc->tab2[i]= (int *)malloc((jogopvc->tamanho+2)*sizeof(int));//cria as linhas ->
            
            if (jogopvc->tab2[i] == NULL){
                printf("Nao existe memoria.");
                exit(0);
        }
         }
        //inicializa o tabuleiro 2 com as informacoes de tabuleiropvc2
        
        for(i=0;i<=jogopvc->tamanho+1;i++){
            for(j=0;j<=jogopvc->tamanho+1;j++){
                jogopvc->tab2[i][j]=tabuleiropvc2[i][j];;
            }
        }
        
        fclose(pvctab1); // fecha os ficheiros que contem os tabuleiros de jogo
        fclose(pvctab2);
    }
    
    do{//Executa o jogo enquanto não houver um jogador que tenha destruido todos os navios adversários
            imprimeTab(jogopvc->tab1,jogopvc->tamanho,1,jogopvc->nick1);
                //Imprime o tabuleiro correspondente ao jogador cujo nick foi indicado na linha acima
            imprimeTab(jogopvc->tab2,jogopvc->tamanho,1,jogopvc->nick2);
                //Imprime o tabuleiro correspondente ao jogador cujo nick foi indicado na linha acima
            printf("vidas restantes  do %s:%d\nVidas restantes  do %s:%d\nRonda n %d\n",jogopvc->nick1,jogopvc->v1,jogopvc->nick2,jogopvc->v2,jogopvc->r);
            jogarP1(jogopvc->tab1,jogopvc->tab2,jogopvc->tamanho,jogopvc->nick1,jogopvc->nick2,&(jogopvc->v2),&(jogopvc->v1));
                /*Chama a funcao jogarP1 que permite o jogador 1 jogar, passando como argumento os dois tabuleiros,
                o tamanho, os dois nicknames e os enderecos de memoria das vidas dois dois jogadores*/
           
            imprimeTab(jogopvc->tab1,jogopvc->tamanho,1,jogopvc->nick1);
            imprimeTab(jogopvc->tab2,jogopvc->tamanho,1,jogopvc->nick2);
            printf("vidas restantes  do %s:%d\nVidas restantes  do %s:%d\nRonda n %d\n",jogopvc->nick1,jogopvc->v1,jogopvc->nick2,jogopvc->v2,jogopvc->r);
            jogarCPU(jogopvc->tab2,jogopvc->tab1,jogopvc->tamanho,jogopvc->nick2,jogopvc->nick1,&(jogopvc->v1),&(jogopvc->v2),jogopvc->d,&(jogopvc->fase),&(jogopvc->b),&(jogopvc->pi),&(jogopvc->pj),jogopvc->r);
                /*Chama a funcao jogarCPU que permite o computador jogar, passando como argumento os dois tabuleiros,
                o tamanho, os dois nicknames, os enderecos de memoria das vidas dois dois jogadores, a dificuldade de
                jogo, a fase em que se encontra, a orientacao o navio atual, as ultimas coordenadas acertadas e o 
                numero de rondas */
            jogopvc->r++; // o numero de rondas aumenta uma unidade
        
            gravarPVC(*jogopvc);// grava o jogo no final de cada ronda, passando como argumento a estrutura de jogo
            
    }while(jogopvc->v1!=0 && jogopvc->v2!=0);
    
    system("clear || cls");
      
    imprimeTab(jogopvc->tab1,jogopvc->tamanho,1,jogopvc->nick1); /*é imprimido os dois tabuleiros no final do jogo*/
    imprimeTab(jogopvc->tab2,jogopvc->tamanho,1,jogopvc->nick2);
      
    printf("Total de rondas jogadas: %d\n",jogopvc->r);
      
    if(jogopvc->v1==0){ /*é indicado o vencedor do jogo. se as vidas do jogador 1 for 0 entao o vencedor é o computador*/
        printf("O vencedor e: %s",jogopvc->nick2);
    }
   
    if(jogopvc->v2==0){ /*é indicado o vencedor do jogo. se as vidas do computador for 0 entao o vencedor é o jogador 1*/
        printf("O vencedor e: %s",jogopvc->nick1);
        if(jogopvc->terminado==0){ /* o resultado so conta para o scoreboard se esse jogo ainda nao foi contabilizado
                                    impedindo de contabilizar duas vezes caso o utilizador tente continuar um jogo 
                                    ja finalizado*/
            scoreboard(jogopvc->tamanho, jogopvc->r, jogopvc->nick1);
        }
    }
    if(jogopvc->terminado==0){
        estatisticaspreencher(jogopvc->v1,jogopvc->r,jogopvc->tamanho,jogopvc->d);
    }
    jogopvc->terminado=1;// indica que o jogo terminou

    gravarPVC(*jogopvc); // grava o jogo depois de terminado
    
    free(jogopvc->tab1); /*liberta  memoria ocupada pelo tabuleiro 1*/
    jogopvc->tab1=NULL; /*o apontador fica a apontar para null*/
    
    free(jogopvc->tab2); /*liberta  memoria ocupada pelo tabuleiro 2*/
    jogopvc->tab2=NULL; /*o apontador fica a apontar para null*/
    
    
    
    do{ /*pede ao utilizador para introduzir 1 para sair para o menu inicial.*/
        printf("\n\nIntroduza 1 para sair: ");
        scanf("%d",&sair);
        setbuf(stdin, NULL);//limpa o buffer
    }while(sair!=1);
       
}