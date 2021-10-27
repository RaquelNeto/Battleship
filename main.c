#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogar.h"

void menu2(){
/*
    Segundo menu contendo os diferentes modos de jogo;invocado pelo menu1
*/
    
     int op; //selecionar opção do modo de jogo
     
     do{ //apresenta o menu com os modos de jogo e repete o cilco quando for introduzida uma opção diferente as permitidas
        system("clear || cls");
        printf("SELECIONE O MODO DE JOGO\n\n(1) Player vs Player\n(2) Player vs Computer\n(3) Voltar\n\nDigite a sua opcao:");
        scanf("%d",&op); //ler a opção dentro do modo de jogo
        setbuf(stdin, NULL);//limpa o buffer
        
     }while(op!=1 && op!=2 && op!=3);
     
     
     switch(op) {
             case 1://Caso introduza "1" inicia o jogo em modo player vs player, chamando para isso a funcao pvp
                    system("clear || cls");                           
                 pvp();
                 break;
                 
             case 2://Caso introduza "2" inicia o jogo em modo player vs computador, chamando para isso a funcao pvc
                    system("clear || cls");                           
                 pvc();
                 break;
                 
             case 3://volta ao menu anterior
                    system("clear || cls");                           
                 break;
     }
     
 }

void instrucoes(){
/*
 esta funcao contem as instrucoes de jogo divididas em duas paginas, sendo possivel retroceder,avancar e sair das
 instrucoes em qualquer pagina
*/
    int op;
    int i=0;
    int j=0;
    int c=0;

    do{//quando pressionar "3" sai das instrucoes e volta para a funcao menu1
        do{//mostra a primeira pagina das intrucoes enquanto nao introduzir "2" para a proxima pagina ou "3" para sair
            system("clear || cls");
            printf("BATTLESHIP GAME: 2016/17;");
            printf("\n\n*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/**********");
            printf("\n\nINSTRUCOES DE JOGO:");
            printf("\n\n O jogo consiste em conseguir adivinhar todos os navios do adversario.");
            printf("\n\n Quando o jogador acerta num navio adversario, continua a jogar; Se errar, passa a vez ao adversario;");   
            printf("\n\n Vence o jogador que conseguir acertar em todos os navios adversarios primeiro;");
            printf("\n\n*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/**********/*********/*********/*********");
            printf("\n\n COMO ENTRAR NO JOGO:");
            printf("\n\n Inicialmente escolhe-se a opcao de jogo:  \n\n   -> Player vs Player; \n   -> Player vs Computador;");
            printf("\n\n Depois de inserir o tamanho do campo,inserir o(s) nome(s) do(s) jogador(es), pode escolher colocar as posicoes dos seus navios no seu campo: ");
            printf("\n\n   -> Manualmente: Escolhe as posicoes no seu campo como desejar;");
            printf("\n\n   -> Aleatoriamente: O computador renderiza coordenandas aleatorias colocando os seus navios no campo aleatoriamente;");
            printf("\n\n Caso escolha colocar os navios manualmente, ira colocar a orientacao dos seus navios: \n\n   -> Horizontal; \n\n   -> Vertical;");
            printf("\n\n NOTA: Caso escolha a colocacao aleatoria dos navios, o computador tambem escolhe aleatoriamente a orientacao dos mesmos;");
            printf("\n\n E acabou de entrar no jogo.");
            printf("\n\n*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/**********");
            printf("\n\nPrima (2) para a proxima pagina.\nPrima (3) para sair");
            printf("\nOpcao: ");
            scanf("%d",&op);
            setbuf(stdin, NULL);//limpa o buffer
        }while(op!=2 && op != 3);
        
        do{//mostra a segunda pagina das intrucoes enquanto nao introduzir "1" para a pagina anterior ou "3" para sair  
            if(op!=1 && op!=3){// se introduzir um numero diferente de "1"ou"3" continua nesta pagina
                system("clear || cls");
                printf("\n\n COMO JOGAR:");
                printf("\n\n Ao entrar no jogo, ira aparecer o(s) tabuleiro(s) de jogo do genero:");
                printf("\n\n");
                printf("__________________________________________\n");
                printf("                                          |\n");
                printf("   ");
                for(c=1; c<=5; c++){
                    printf(" [%d]", c);
                }
                
                printf("                   |");
                printf("\n");

                for(i=1;i<=5;i++){ 
                    printf("   ");
                    
                    for(j=1;j<=5;j++){
                        printf("| ~ ");
                    }
                    printf("|[%d]               |\n", i);
                }
                
                printf("                                          |");
                printf("\n   Introduza as coordenandas a atacar:    |");
                printf("\n   X:                                     |");
                printf("\n   Y:                                     |");
                printf("\n__________________________________________|");
                printf("\n\n Quando escolher as coordenadas pode ter acertado ou nao em alguma parte do navio:");
                printf("\n\n    -> Caso tenho tenha acertado:\n");
                printf("_______________\n");
                printf("               |\n");
                printf("   X:2         |\n");
                printf("   Y:3         |\n");
                printf("               |\n");
                printf("   [2]         |\n");
                printf("  |XXX|[3]     |\n");
                printf("_______________|");
                printf("\n\n    -> Caso tenho tenha falhado:\n\n");
                printf("_______________\n");
                printf("               |\n");
                printf("   X:2         |\n");
                printf("   Y:3         |\n");
                printf("               |\n");
                printf("   [2]         |\n");
                printf("  |000|[3]     |\n");
                printf("_______________|");
                printf("\n\n*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/**********");
                printf("\n\n BOA SORTE NO JOGO!!");
                //printf("\n\n*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/*********/**********");
                printf("\n\nPrima (1) para pagina anterior; \nPrima (3) para sair;");
                printf("\nOpcao: ");
                scanf("%d",&op);
                setbuf(stdin, NULL);//limpa o buffer
            }   
        }while(op!=1 && op!=3);
        
    }while(op!=3); 
}   


void menu1 (int *i) {
    
/*
    esta funcao contem o menu inicial com as opcoes basicas de jogar, continuarpvp, continuarpvc instrucoes, 
    scoreboard e sair;invocado pela main
*/

    int op=0; //selecionar a opção dentro do menu

    do{ // apresenta o menu inicial enquanto nao for colocada uma opcao valida
            system("clear || cls");

            /*Os printf abaixo contem a palavra "battleship" personalizada no menu inicial*/        
            printf("______  ___ _____ _____ _      _____ _____ _   _ ___________"); 
            printf("\n");
            printf("| ___ \\/ _ \\_   _|_   _| |    |  ___/  ___| | | |_   _| ___ \\\n");  
            printf("| |_/ / /_\\ \\| |   | | | |    | |__ \\ `--.| |_| | | | | |_/ /");
            printf("\n");
            printf("| ___ \\  _  || |   | | | |    |  __| `--. \\  _  | | | |  __/"); 
            printf("\n");
            printf("| |_/ / | | || |   | | | |____| |___/\\__/ / | | |_| |_| |");    
            printf("\n");
            printf("\\____/\\_| |_/\\_/   \\_/ \\_____/\\____/\\____/\\_| |_/\\___/\\_|");  
            printf("\n\n");



            printf("MENU PRINCIPAL\n\n(1) Jogar\n(2) ContinuarPVP\n(3) ContinuarPVC\n(4) Scoreboard\n(5) Instrucoes\n(6) Sair\n\nDigite a sua opcao:");
            /*Opções do menu inicial*/

            scanf("%d",&op);//ler a opção dentro do menu
            setbuf(stdin, NULL);//limpa o buffer

    }while(op!=1 && op!=2 && op!=3 && op!=4 && op!=5 && op!=6);
   
    
    switch(op) {
            case 1: // se for selecionado "1" vai para o menu2 para escolher a opcao de jogo
                system("clear || cls");   
                menu2();
                break;

            case 2: // se for selecionado "2" continua um jogo player vs player nao terminado
                system("clear || cls");
                continuarPVP();
                break;

            case 3: // se for selecionado "3" continua um jogo player vs computer nao terminado
                system("clear || cls");
                continuarPVC();             
                break;

            case 4: // se for selecionado "4" vai para o menuScore apresentando diversas opcoes sobre diferentes scores 
                system("clear || cls");
                menuScore();
                break;
            case 5:// se for selecionado "5"  mostra as instrucoes de jogo   
                system("clear || cls");
                instrucoes();
                break;
                
            case 6://altera o valor de "i" nao permitindo que a funcao menu1 seja chamada novamente terminando o programa
                system("clear || cls");
                printf("Ate a proxima!\n\n");
                *i=1;
                break;
            
     }  

 }

int main(int argc, char** argv){
    int i=0;
    
    while(i==0){//enquanto "i" valer "0" o programa nao termina chamando sempre a funcao menu1 
        menu1 (&i);
    }
     
     return (EXIT_SUCCESS);
 }