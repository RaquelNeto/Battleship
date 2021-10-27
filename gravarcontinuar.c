/*<Este source file contem as funcoes que permitem gravar o jogo de player vs player e player vs computador e tambem 
continuar um jogo player vs player e um jogo player vs computador>*/

#include <stdio.h>
#include <stdlib.h>
#include "jogar.h"


void gravarPVP(struct JogoPVP jogopvp){ /*funcao utilizada para gravar o jogo player vs player*/
    int i=0;
    int j=0;
    
    int tabuleiropvp1[17][17]; // matriz usada para auxiliar a gravar o tabuleiro de jogo
    int tabuleiropvp2[17][17];
    
    /****abrir e gravar no ficheiro de jogo******/
    FILE *pvpjogo;
    pvpjogo=fopen ("jogopvp.bin","wb+");
        
    if (pvpjogo==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fwrite (&jogopvp,sizeof(jogopvp),1,pvpjogo);
    }
    fclose(pvpjogo);
    
    /*****criar tabuleiros para guardar em ficheiro*******/
    
    for(i=0; i<jogopvp.tamanho+1;i++){
        for(j=0; j<jogopvp.tamanho+1;j++){
            tabuleiropvp1[i][j]=jogopvp.tab1[i][j];
        }
    }
    
    for(i=0; i<jogopvp.tamanho+1;i++){
        for(j=0; j<jogopvp.tamanho+1;j++){
            tabuleiropvp2[i][j]=jogopvp.tab2[i][j];
        }
    }
    
    /******guardar tabuleiro 1 em ficheiro*******/
    
    FILE *pvptab1;
    pvptab1=fopen ("tabuleiropvp1.bin","wb+");
        
    if (pvptab1==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fwrite (tabuleiropvp1,sizeof(tabuleiropvp1),1,pvptab1);
    }
    fclose(pvptab1);
    
    /******guardar tabuleiro 2 em ficheiro*******/
    
    FILE *pvptab2;
    pvptab2=fopen ("tabuleiropvp2.bin","wb+");
        
    if (pvptab2==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fwrite (tabuleiropvp2,sizeof(tabuleiropvp2),1,pvptab2);
    }
    fclose(pvptab2);
} 
    

void gravarPVC(struct JogoPVC jogopvc){ /*funcao utilizada para gravar o jogo player vs computador*/
    int i=0;
    int j=0;
    
    int tabuleiropvc1[17][17]; // matriz usada para auxiliar a gravar o tabuleiro de jogo
    int tabuleiropvc2[17][17];
    
    /****abrir e gravar no ficheiro de jogo******/
    FILE *pvcjogo;
    pvcjogo=fopen ("jogopvc.bin","wb+");
        
    if (pvcjogo==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fwrite (&jogopvc,sizeof(jogopvc),1,pvcjogo);
    }
    fclose(pvcjogo);
    
    /*****criar tabuleiros para guardar em ficheiro*******/
    
    for(i=0; i<jogopvc.tamanho+1;i++){
        for(j=0; j<jogopvc.tamanho+1;j++){
            tabuleiropvc1[i][j]=jogopvc.tab1[i][j];
        }
    }
    
    for(i=0; i<jogopvc.tamanho+1;i++){
        for(j=0; j<jogopvc.tamanho+1;j++){
            tabuleiropvc2[i][j]=jogopvc.tab2[i][j];
        }
    }
    
    /******guardar tabuleiro 1 em ficheiro*******/
    
    FILE *pvctab1;
    pvctab1=fopen ("tabuleiropvc1.bin","wb+");
        
    if (pvctab1==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fwrite (tabuleiropvc1,sizeof(tabuleiropvc1),1,pvctab1);
    }
    fclose(pvctab1);
    
    /******guardar tabuleiro 2 em ficheiro*******/
    
    FILE *pvctab2;
    pvctab2=fopen ("tabuleiropvc2.bin","wb+");
        
    if (pvctab2==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fwrite (tabuleiropvc2,sizeof(tabuleiropvc2),1,pvctab2);
    }
    fclose(pvctab2);
}

void continuarPVP(){ /*funcao utilizada para continuar o jogo player vs player*/
    
    struct JogoPVP jogopvp;
    
    int confirmacao=-1; // confirmar que quer continuar o jogo guardado
    
    FILE *fp; // abre o ficheiro de jogo
    fp=fopen ("jogopvp.bin","rb");
        
    if (fp==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fread (&jogopvp,sizeof(jogopvp),1,fp);    
    }
    fclose(fp);
    
    printVarPVP(jogopvp); // chama a funcao printVarPVP para mostrar as estatisticas do jogo guardado
    
    do{ // pergunta se o jogador realmente quer continuar esse jogo, recomecar ou sair para o menu anterior
        printf("\nPretende continuar o jogo? Insira 0 para continuar, 1 para reiniciar o jogo e 2 para sair:");
        scanf("%d",&confirmacao);
        
        
        if(confirmacao==0){ // se o jogador quiser continuar chama a funcao executarPVP para continuar o jogo guardado
            system("clear || cls");
            executarPVP(&(jogopvp),1);
            system("clear || cls");
        }
        
        if(confirmacao==1){ // se o jogador quiser recomecar o jogo chama a funcao pvp que permite comecar um jogo novo
            pvp();
        } 
        
    }while(confirmacao!=0 && confirmacao!=1 && confirmacao!=2);
   
    system("clear || cls");
}

void continuarPVC(){ /*funcao utilizada para continuar o jogo player vs computador*/
    
    struct JogoPVC jogopvc;
    
    int confirmacao=-1; // confirmar que quer continuar o jogo guardado

    FILE *fp; // abre o ficheiro de jogo
    fp=fopen ("jogopvc.bin","rb");
        
    if (fp==NULL){
        perror("Ocorreu um erro: ");
    } 
    else{
        fread (&jogopvc,sizeof(jogopvc),1,fp);    
    }
    fclose(fp);
    
    printVarPVC(jogopvc);  // chama a funcao printVarPVC para mostrar as estatisticas do jogo guardado
    
    do{ // pergunta se o jogador realmente quer continuar esse jogo, recomecar ou sair para o menu anterior
        printf("\nPretende continuar o jogo? Insira 0 para continuar, 1 para reiniciar o jogo e 2 para sair:");
        scanf("%d",&confirmacao);
        
        if(confirmacao==0){ // se o jogador quiser continuar chama a funcao executarPVC para continuar o jogo guardado
            system("clear || cls");
            executarPVC(&(jogopvc),1);
            system("clear || cls");
        }
        
        if(confirmacao==1){  // se o jogador quiser recomecar o jogo chama a funcao pvc que permite comecar um jogo novo
            pvc();
        }
        
    }while(confirmacao!=0 && confirmacao!=1 && confirmacao!=2);
   
    system("clear || cls");
}