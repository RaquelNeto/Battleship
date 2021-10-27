/*<Este source file contem as funcoes relativas as scores e estatisticas>*/

#include <stdio.h>
#include <stdlib.h>
#include "jogar.h"
#include "limits.h"

void menuScore(){
    /*
     Menu scoreboard onde o utilizador pode escolher entre varias scores e estatisticas para vizualizar
     */
    int op=0;
    int conf=0; // confirmar que realmente quer executar determinada acao
    
    do{ // mostra o menuScore enquanto nao introduzir 6 para voltar para o menu anterior
    
        do{ // enquanto nao for introduzida um opcao valida o menu repete-se
            printf("MENU pontuacoes\n\n");
            printf("(1) Reiniciar pontuacoes\n(2) Pontuacoes 5x5\n(3) Pontuacoes 10x10\n(4) Pontuacoes 15x15\n(5) Estatisticas\n(6) Sair\n\n");
            printf("Digite a sua opcao:");
            scanf("%d",&op);
            setbuf(stdin, NULL);//limpa o buffer
        }while(op!=1 && op!=2 && op!=3 && op!=4 && op!=5 && op!=6);

        system("clear || cls");

        switch (op){

            case 1: // se for introduzida a opcao 1 chama a funcao reiniciar para reiniciar as scores
                
                    do{ // pergunta se o utilizador realmente quer concluir a acao de apagar as scores
                        system("clear || cls");
                        printf("Tem a certeza? Prima 0 para cancelar e prima 1 para confirmar:");
                        scanf("%d",&conf);
                        setbuf(stdin, NULL);//limpa o buffer
                    }while(conf!=0 && conf!=1);

                    system("clear || cls");

                    if (conf==1){ // se o utilizador confirmar que quer reiniciar as scores chama a funcao reiniciar
                        reiniciar();
                        printf("Scores reiniciadas!\n\n");
                    }
                    break;

            case 2: /* se for introduza a opcao 2 chama a funcao mostrarScore e passa como argumento o numero 5, 
                     para mostrar as scores relativas aos jogos em tabuleiros de 5*5*/
                mostrarScore(5);
                system("clear || cls");
                break;

            case 3: /* se for introduza a opcao 3 chama a funcao mostrarScore e passa como argumento o numero 10, 
                     para mostrar as scores relativas aos jogos em tabuleiros de 10*10 */
                mostrarScore(10);
                system("clear || cls");
                break;

            case 4: /* se for introduza a opcao 4 chama a funcao mostrarScore e passa como argumento o numero 15, 
                     para mostrar as scores relativas aos jogos em tabuleiros de 15*15 */
                mostrarScore(15);
                system("clear || cls");
                break;

            case 5: /* se for introduzida a opcao 5 chama a funcao estatisticasLeituran para apresentar estatisticas
                    gerais de jogo*/
                estatisticasleitura();
                system("clear || cls");
                break;
            case 6: /* se for introduzida a opcao 6 volta para o menu anterior*/
                system("clear || cls");
                break;

        }
    
    }while(op!=6);
        
}

void reiniciar(){
    /*funcao utilizada para reiniciar todas as scores e estatisticas de jogo*/
    
    struct Estatisticas estatisticas;
    
    int scoreboard[11];
    int i=0;
    
    /***********reinicia todas as estatisticas de jogo***************/
    estatisticas.jogosdificiltot=0;
    estatisticas.jogosdificilvit=0;
    estatisticas.jogosfaciltot=0;
    estatisticas.jogosfacilvit=0;
    estatisticas.jogosimpossiveltot=0;
    estatisticas.jogosimpossivelvit=0;
    estatisticas.jogosmediotot=0;
    estatisticas.jogosmediovit=0;
    estatisticas.jogostotal=0;
    estatisticas.rondastotal=0;
    
    /********reinicia as scores*********/
    for(i=0;i<11;i++){
        scoreboard[i]=999;
    }
    
    /*Abre os ficheiros das estatisticas e scores e grava nesses ficheiros os dados reiniciados**/
    FILE *sf;
    FILE *sm;
    FILE *sd;
    FILE *est;
    
    sf=fopen ("score5x5.bin","wb+");
    sm=fopen ("score10x10.bin","wb+");
    sd=fopen ("score15x15.bin","wb+");
    est=fopen ("estatisticas.bin","wb+");

    if (sf==NULL || sm==NULL || sd==NULL || est==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fwrite (scoreboard,sizeof(scoreboard),1,sf);
        fwrite (scoreboard,sizeof(scoreboard),1,sm);
        fwrite (scoreboard,sizeof(scoreboard),1,sd);
        fwrite (&estatisticas,sizeof(estatisticas),1,est);
        }
     fclose(sf);
     fclose(sm);
     fclose(sd);
     fclose(est);
}

void mostrarScore(int tamanho){
    /*funcao utilizada para mostrar as scores do utilizador*/
    
    int scoreboard[11];
    int i=0;
    int sair=0;
    
    /*Abre o ficheiro relativo as scores que sao pretendidas pelo utilizador*/
    FILE *fp;
    switch (tamanho){
        case 5:
            fp=fopen ("score5x5.bin","rb");
            break;
            
        case 10:
            fp=fopen ("score10x10.bin","rb");
            break;
            
        case 15:
            fp=fopen ("score15x15.bin","rb");
            break;
    }

            if (fp==NULL){//se algum dos ficheiros nao existir chama a funcao reiniciar para criar os ficheiros reiniciados
                perror("Ocorreu um erro: ");
                reiniciar();
                printf("Tente novamente.");
            } 
            else{ // printa as scores pedidas pelo utilizador
                fread (scoreboard,sizeof(scoreboard),1,fp);
                fclose(fp); 

                printf("MELHORES PONTUACOES:\n\n");

                for(i=0; i<10; i++){
                    if(scoreboard[i]!=999){ // so mostra as pontuacoes de jogos realizados, nao mostra os 999
                        printf("posicao %d: %d rondas\n",i+1,scoreboard[i]);
                    }else if(i==0){ // se na primeira posicao do vetor tiver 999, entao diz ao utilizador que nao ha pontucoes
                        printf("Sem pontuacoes!");
                    }
                }
            }
            
    do{ /*pede ao utilizador para introduzir 1 para sair para o menu inicial.*/
          printf("\n\nIntroduza 1 para sair: ");
          scanf("%d",&sair);
          setbuf(stdin, NULL);//limpa o buffer
    }while(sair!=1);
    
}

void scoreboard(int tamanho, int rondas, char nick[]){ // preencher o scoreboard no final de cada jogo
    
    int scoreboard[11];
    int i=0;
    int j=0;

        FILE *fpr;

        switch (tamanho){ /* abre o ficheiro relativo ao tamanho de jogo que foi executado e passa suas informacoes 
                          para o vetor scoreboard*/
            case 5:
                fpr=fopen ("score5x5.bin","rb");
                break;

            case 10:
                fpr=fopen ("score10x10.bin","rb");
                break;

            case 15:
                fpr=fopen ("score15x15.bin","rb");
                break;
            }

        if (fpr==NULL){
            perror("Ocorreu um erro: ");
        } 
        else{
            fread (scoreboard,sizeof(scoreboard),1,fpr);
        }
        fclose(fpr); 

        for(i=0;i<10;i++){ // verifica se o utilizador bateu algum dos recordes da scoreboard
                    if(rondas<scoreboard[i]){ /* se bateu algum recorde puxa as scores batids uma posicao para tras e escreve
                                              o novo recorde na sua posicao*/
                        for(j=9;j>i;j--){
                            scoreboard[j]=scoreboard[j-1];
                        }
                        scoreboard[i]=rondas;
                        rondas=INT_MAX; /* o numero de rondas recebe INT_MAX para não ser introduzido na scoreboard mais 
                                        nenhuma vez*/
                    }
                }

        FILE *fpw; // abre o ficheiro das scores e guarda as novas informacoes
        
        switch (tamanho){
            case 5:
                fpw=fopen ("score5x5.bin","wb");
                break;

            case 10:
                fpw=fopen ("score10x10.bin","wb");
                break;

            case 15:
                fpw=fopen ("score15x15.bin","wb");
                break;
        }

        if (fpw==NULL){
            perror("Ocorreu um erro: ");
        } 
        else{
            fwrite (scoreboard,sizeof(scoreboard),1,fpw);
        }

        fclose(fpw);
    
}

void estatisticaspreencher(int v1, int rondas, int tamanho, int dificuldade){
    /*funcao utilizada para guardar as estatisticas de todos os jogos player vs computer*/

    struct Estatisticas estatisticas;
   
    FILE *fp; // abre o ficheiro relativo as estatisticas e passa suas informacoes para a estrutura estatisticas
    fp=fopen ("estatisticas.bin","rb");
        
    if (fp==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fread (&estatisticas,sizeof(estatisticas),1,fp);
    }
    fclose(fp);
    
    estatisticas.jogostotal++; // o total de jogos executados incrementa uma unidade
    estatisticas.rondastotal=estatisticas.rondastotal+rondas; /* ao total de rondas é adicionada as rondas realizadas no 
                                                              ultimo jogo*/ 
    
        switch (dificuldade){ // analiza a difiucldade do ultimo jogo
            case 1: // se foi um jogo com dificuldade facil incrementa uma unidade o total de jogos faceis
                estatisticas.jogosfaciltot++;
                
                if(v1!=0){ /* em caso de vitoria incrementa uma unidade aos jogos vencidos dessa dificuldade e ao total de 
                            jogos vencidos*/
                    estatisticas.jogosfacilvit++;
                    estatisticas.jogostotalvit++;
                }
                break;
                
            case 2: // se foi um jogo com dificuldade medio incrementa uma unidade o total de jogos medios
                estatisticas.jogosmediotot++;
                
                if(v1!=0){/* em caso de vitoria incrementa uma unidade aos jogos vencidos dessa dificuldade e ao total de 
                            jogos vencidos*/
                    estatisticas.jogosmediovit++;
                    estatisticas.jogostotalvit++;
                }
                break;
                
            case 3: // se foi um jogo com dificuldade dificil incrementa uma unidade o total de jogos dificeis
                estatisticas.jogosdificiltot++;
                
                if(v1!=0){/* em caso de vitoria incrementa uma unidade aos jogos vencidos dessa dificuldade e ao total de 
                            jogos vencidos*/
                    estatisticas.jogosdificilvit++;
                    estatisticas.jogostotalvit++;
                }
                break;
                
            case 4: // se foi um jogo com dificuldade impossivel incrementa uma unidade o total de jogos impossiveis
                estatisticas.jogosimpossiveltot++;
                
                if(v1!=0){/* em caso de vitoria incrementa uma unidade aos jogos vencidos dessa dificuldade e ao total de 
                            jogos vencidos*/
                    estatisticas.jogosimpossivelvit++;
                    estatisticas.jogostotalvit++;
                }
                break;
        }
        
    FILE *fpw; // grava as novas estatisticas no ficheiro
    fpw=fopen ("estatisticas.bin","wb");
        
    if (fpw==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fwrite (&estatisticas,sizeof(estatisticas),1,fpw);
    }
    fclose(fpw);

}

void estatisticasleitura(){ /*funcao utilizada para a vizualizacao das esttisticas de todos os jogos*/
    int sair=0;
    
    struct Estatisticas estatisticas;
    
    FILE *fp; // abre o ficheiro que contem as estatisticas
    fp=fopen ("estatisticas.bin","rb");
        
    if (fp==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fread (&estatisticas,sizeof(estatisticas),1,fp);
    }
    fclose(fp);
    
    printf("ESTATISTICAS (vitorias/total):\n\n"); // printa as estatisticas
    printf("\nTotal de jogos: %d/%d",estatisticas.jogostotalvit, estatisticas.jogostotal);
    printf("\nTotal de rondas: %d", estatisticas.rondastotal);
    printf("\nTotal de jogos facil: %d/%d",estatisticas.jogosfacilvit, estatisticas.jogosfaciltot);
    printf("\nTotal de jogos medio: %d/%d",estatisticas.jogosmediovit, estatisticas.jogosmediotot);
    printf("\nTotal de jogos dificil: %d/%d",estatisticas.jogosdificilvit, estatisticas.jogosdificiltot);
    printf("\nTotal de jogos impossivel: %d/%d",estatisticas.jogosimpossivelvit, estatisticas.jogosimpossiveltot);
    
    do{ /*pede ao utilizador para introduzir 1 para sair para o menu inicial.*/
          printf("\n\nIntroduza 1 para sair: ");
          scanf("%d",&sair);
          setbuf(stdin, NULL);//limpa o buffer
    }while(sair!=1);
    
}