/*<Este source file contem as funcoes relativas a jogabilidade do utilizador humano (funcao que permite colocar coordenadas 
para atacar, funcao inicia os procedimentos para o jogo entre dois jogadores humanos e funcao que permite executar o jogo)>*/

#include <stdio.h>
#include <stdlib.h>
#include "jogar.h"

void jogarP1(int **tab1,int **tab2,int tamanho, char nick1[], char nick2[], int *v1,int *v2){
    /*
    Esta funcao permite o jogador colocar as coordenadas para atacar os navios, verificando se as
    coordenadas colocadas pelo jogador estao livres ou pertencem ao campo, caso a coordenada colocada nao seja possivel
    pede uma coordenada nova.
    Invocado pelas funcoes executarPVC e executar PVP
    */
    
    int i=0;
    int j=0;
    
    do{ // Enquanto o jogador acertar nas posições dos navios é ele que continua a jogar
        if(*v1!=0 && *v2!=0){
            do{//Enquanto o jogador não colocar coordenadas livres pede novas coordenadas
                
                do{//Enquanto o jogador não colocar coordenadas que fazem parte do campo de jogo pede novas coordenadas
                    printf("\nVez do %s\nIntroduza as coordenadas a atacar:\n",nick1);
                    printf("X:");
                    scanf("%d",&j);
                    setbuf(stdin, NULL);//limpa o buffer
                    printf("Y:");
                    scanf("%d",&i);
                    setbuf(stdin, NULL);//limpa o buffer
                    
                    if(i<1||i>tamanho||j<1||j>tamanho){ //indica ao jogador caso ele introduza uma coordenada fora do campo
                        printf("\nIntroduza uma coordenada pertencente ao campo!\n\n");
                    }
                    
                }while(i<1||i>tamanho||j<1||j>tamanho);
                
                if(tab2[i][j]==2 || tab2[i][j]==3){ //indica ao jogador caso ele ja tenha introduzido essa coordenada
                    printf("\nJa introduziu esta coordenada. Tente novamente!\n\n");
                }
                
            }while(tab2[i][j]==2 || tab2[i][j]==3);
        }
        //0-não selecionado sem navio; 1-não selecionado com navio; 2- selecionado sem navio; 3- selecionado com navio
        
        if(tab2[i][j]==1 || tab2[i][j]==3){ //Se o jogador colocou uma coordenada com navio
            if(*v1!=0 && *v2!=0 && tab2[i][j]==1){/*se o jogador colocou uma coordenada com navio e nao selecionada
                e ao mesmo tempo o jogo nao acabou*/
               
                tab2[i][j]=3; //A posição do tabuleiro passa a a valer 3(selecionado com navio)
                
                system("clear || cls");
                
                printf("ACERTOU!\n\n");//Indica que acertou
                
                imprimeTab(tab2,tamanho,1,nick2); /*Imprime o tabuleiro correspondente ao jogador cujo nick foi 
                                                   indicado na linha acima*/
                
                *v1=*v1-1; // o numero de vidas do oponente baixa uma unidade
            }
        }
        else{//Se o jogador errou a posição do navio do adversario
            tab2[i][j]=2; //A posição do tabuleiro passa a a valer 2(selecionado sem navio)
            system("clear || cls");
            printf("ERROU!\n\n");//Indica que errou
        }  
    }while(tab2[i][j]==3 && *v1!=0 && *v2 !=0);
}

void pvp(){
    /*
    funcao que inicia uma serie de procedimentos antes de iniciar o jogo(tamanho do campo, nicknames, vidas, rondas,
    tabuleiros e posicoes dos navios) e posteriormente inicia o jogo chamando para isso a funcao executarPVP
    */
    
    struct JogoPVP jogopvp;
     
    jogopvp.tamanho=0; //tamanho do campo
    jogopvp.v1=0;//Navios a salvo do jogador 1
    jogopvp.v2=0;//Navios a salvo do jogador 2
    jogopvp.r=1;//rondas
    
    int i=0;
    int j=0; 
    
    jogopvp.tamanho=tam_camp();//chama a função tam_camp para definir o tamanho do campo
     
    /***********cria o tabuleiro 1*************/  
    jogopvp.tab1 = (int **)malloc((jogopvp.tamanho+2)*sizeof(int*));//cria uma coluna |
    //                                                                                v

    for(i=0;i<=jogopvp.tamanho+1;i++){
        jogopvp.tab1[i]= (int *)malloc((jogopvp.tamanho+2)*sizeof(int));//cria as linhas ->
        
        if (jogopvp.tab1[i] == NULL){
                printf("Nao existe memoria.");
                exit(0);
        }
    }
    
    //inicializa o tabuleiro 1
    for(i=0;i<=jogopvp.tamanho+1;i++){
        for(j=0;j<=jogopvp.tamanho+1;j++){
            jogopvp.tab1[i][j]=0;
        }
    }
      
    /*************cria o tabuleiro 2**************/  

    jogopvp.tab2 = (int **)malloc((jogopvp.tamanho+2)*sizeof(int*));//cria uma coluna |
    //                                                                                v
    for(i=0;i<=jogopvp.tamanho+1;i++){
        jogopvp.tab2[i]= (int *)malloc((jogopvp.tamanho+2)*sizeof(int));//cria as linhas ->
        
        if (jogopvp.tab2[i] == NULL){
                printf("Nao existe memoria.");
                exit(0);
        }
    }
     
    //inicializa o tabuleiro 2
    for(i=0;i<=jogopvp.tamanho+1;i++){
        for(j=0;j<=jogopvp.tamanho+1;j++){
            jogopvp.tab2[i][j]=0;
        }
    }
      
    system("clear || cls");
      
    nickname(jogopvp.nick1,1);
        /*chama a função nickname para definir o nome do jogador 1, passa como argumento o vetor para
        guardar o nome e o numero "1" para indicar que é o nome do jogador 1 que é pretendido*/     
    system("clear || cls");
      
    nickname(jogopvp.nick2,2);
        /*chama a função nickname para definir o nome do jogador 2, passa como argumento o vetor para
        guardar o nome e o numero "2" para indicar que é o nome do jogador 2 que é pretendido*/   
    system("clear || cls");
      
    vidas(jogopvp.tamanho, &(jogopvp.v1), &(jogopvp.v2));
        /*chama a funcao vidas para definir a quantidade de vidas iniciais dos dois jogadores, 
        passando como argumento o tamanho do campo e o endereco de memoria das vidas dos dois jogadores*/
      
    posicaoNaviosPL(jogopvp.tab1,jogopvp.nick1,jogopvp.tamanho);
        /*chama a funcao posicaoNaviosPL para posicionar os navios do jogador 1 passando como argumentos o 
        tabuleiro do jogador 1, o seu nickname e o tamanho do campo*/ 
    system("clear || cls");
      
    posicaoNaviosPL(jogopvp.tab2,jogopvp.nick2,jogopvp.tamanho);
        /*chama a funcao posicaoNaviosPL para posicionar os navios do jogador 1 passando como argumentos o 
        tabuleiro do jogador 1, o seu nickname e o tamanho do campo*/ 
    system("clear || cls");
      
    printf("INICIO DO JOGO\n\n");

    executarPVP(&(jogopvp),0);
        /*chama a funcao executarPVP que inicia e corre o jogo ate alguem vencer o jogo, passando como argumento a 
        estrutura que contem os dados de jogo e tambem o numero "0" indicando que este é um jogo novo e nao um jogo que 
        esta a ser continuado*/
  }

void executarPVP(struct JogoPVP* jogopvp, int continuar){
    /*
     Inicia o jogo e executa enquanto nao houver um vencedor. chamado pela funcao pvp
     */
    
    int i=0;
    int j=0;
    int sair=0;//sair no final do jogo
    
    if(continuar==1){ /* se for um jogo que esteja a ser continuado carrega os dados de ficheiro para as variaveis 
                      e estruturas*/
        
        int tabuleiropvp1[17][17]; // matriz onde tabuleiro de jogo sera pre carregado
        int tabuleiropvp2[17][17];
        
        FILE *pvptab1; //abre o ficeiro que contem o tabuleiro de jogo 1 e carrega as informacoes na matriz tabuleiropvp1
        pvptab1=fopen ("tabuleiropvp1.bin","rb");

        if (pvptab1==NULL){
            perror("Ocorreu um erro: ");
        } 
        else{
            fread (tabuleiropvp1,sizeof(tabuleiropvp1),1,pvptab1);  
        }
        
        FILE *pvptab2; //abre o ficeiro que contem o tabuleiro de jogo 2 e carrega as informacoes na matriz tabuleiropvp2
        pvptab2=fopen ("tabuleiropvp2.bin","rb");

        if (pvptab2==NULL){
            perror("Ocorreu um erro: ");
        } 
        else{
            fread (tabuleiropvp2,sizeof(tabuleiropvp2),1,pvptab2);
        }
        
            /*********cria o tabuleiro 1***********/ 

         jogopvp->tab1 = (int **)malloc((jogopvp->tamanho+2)*sizeof(int*));//cria uma coluna |
         //                                                                                  V

         for(i=0;i<=jogopvp->tamanho+1;i++){
            jogopvp->tab1[i]= (int *)malloc((jogopvp->tamanho+2)*sizeof(int));//cria as linhas ->
         
            if (jogopvp->tab1[i] == NULL){
                printf("Nao existe memoria.");
                exit(0);
            }
         }
         
         //inicializa o tabuleiro 1 com as informacoes de tabuleiropvp1
         for(i=0;i<=jogopvp->tamanho+1;i++){
            for(j=0;j<=jogopvp->tamanho+1;j++){
                jogopvp->tab1[i][j]=tabuleiropvp1[i][j];
            }
        }
         /************cria o tabuleiro 2***************/

         jogopvp->tab2 = (int **)malloc((jogopvp->tamanho+2)*sizeof(int*));//cria uma coluna |
         //                                                                                  V

         for(i=0;i<=jogopvp->tamanho+1;i++){
            jogopvp->tab2[i]= (int *)malloc((jogopvp->tamanho+2)*sizeof(int));//cria as linhas ->
            
         if (jogopvp->tab2[i] == NULL){
                printf("Nao existe memoria.");
                exit(0);
            }
         }
         
         
         //inicializa o tabuleiro 2 com as informacoes de tabuleiropvp2
        
         for(i=0;i<=jogopvp->tamanho+1;i++){
            for(j=0;j<=jogopvp->tamanho+1;j++){
                jogopvp->tab2[i][j]=tabuleiropvp2[i][j];;
            }
        }
        fclose(pvptab1); // fecha os ficheiros que contem os tabuleiros de jogo
        fclose(pvptab2);
    }
    
          
    do{//Executa o jogo enquanto não houver um jogador que tenha destruido todos os navios adversários
           
            imprimeTab(jogopvp->tab1,jogopvp->tamanho,1,jogopvp->nick1);
                /*Imprime o tabuleiro correspondente ao jogador cujo nick foi indicado na linha acima*/
            imprimeTab(jogopvp->tab2,jogopvp->tamanho,1,jogopvp->nick2);
                /*Imprime o tabuleiro correspondente ao jogador cujo nick foi indicado na linha acima*/
            printf("vidas restantes  do %s:%d\nVidas restantes  do %s:%d\nRonda n %d\n",jogopvp->nick1,jogopvp->v1,jogopvp->nick2,jogopvp->v2,jogopvp->r);       
                /*Indica as vidas restantes dos dois jogadores*/
            jogarP1(jogopvp->tab1,jogopvp->tab2,jogopvp->tamanho,jogopvp->nick1,jogopvp->nick2,&(jogopvp->v2),&(jogopvp->v1));
                /*Chama a funcao jogarP1 que permite o jogador 1 jogar, passando como argumento os dois tabuleiros,
                 o tamanho, os dois nicknames e os enderecos de memoria das vidas dois dois jogadores*/
            
            imprimeTab(jogopvp->tab1,jogopvp->tamanho,1,jogopvp->nick1);
            imprimeTab(jogopvp->tab2,jogopvp->tamanho,1,jogopvp->nick2);
            printf("vidas restantes  do %s:%d\nVidas restantes  do %s:%d\nRonda n %d\n",jogopvp->nick1,jogopvp->v1,jogopvp->nick2,jogopvp->v2,jogopvp->r);
            
            jogarP1(jogopvp->tab2,jogopvp->tab1,jogopvp->tamanho,jogopvp->nick2,jogopvp->nick1,&(jogopvp->v1),&(jogopvp->v2));  
                /*Chama a funcao jogarP1 que permite o jogador 2 jogar, passando como argumento os dois tabuleiros,
                 o tamanho, os dois nicknames e os enderecos de memoria das vidas dois dois jogadores*/
            
            jogopvp->r++; /*o numero de rondas é incrementado em uma unidade*/

            gravarPVP(*jogopvp); // grava o jogo no final de cada ronda, passando como argumento a estrutura de jogo
            
        
    }while(jogopvp->v1!=0 && jogopvp->v2!=0);
      
    system("clear || cls");
      
    imprimeTab(jogopvp->tab1,jogopvp->tamanho,1,jogopvp->nick1);/*é imprimido os dois tabuleiros no final do jogo*/
    imprimeTab(jogopvp->tab2,jogopvp->tamanho,1,jogopvp->nick2);
      
    printf("Total de rondas jogadas: %d\n",jogopvp->r);
      
    if(jogopvp->v1==0){ /*é indicado o vencedor do jogo. se as vidas do jogador 1 for 0 entao o vencedor é o jogador 2*/
        printf("O vencedor e: %s",jogopvp->nick2);
    }
   
    if(jogopvp->v2==0){/*é indicado o vencedor do jogo. se as vidas do jogador 2 for 0 entao o vencedor é o jogador 1*/
        printf("O vencedor e: %s",jogopvp->nick1);
    }
      
    free(jogopvp->tab1);/*liberta  memoria ocupada pelo tabuleiro 1*/
    jogopvp->tab1=NULL;/*o apontador fica a apontar para null*/
    
    free(jogopvp->tab2);/*liberta  memoria ocupada pelo tabuleiro 2*/
    jogopvp->tab2=NULL;/*o apontador fica a apontar para null*/

    do{ /*pede ao utilizador para introduzir 1 para sair para o menu inicial.*/
          printf("\n\nIntroduza 1 para sair: ");
          scanf("%d",&sair);
          setbuf(stdin, NULL);//limpa o buffer
    }while(sair!=1);
    
}