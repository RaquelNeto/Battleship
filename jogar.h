#ifndef JOGAR_H
#define JOGAR_H

#ifdef __cplusplus
extern "C" {
#endif

struct JogoPVP{ // estrutura que contem os dados do jogo player vs player
    char nick1[10];
    char nick2[10];
    int v1;
    int v2;
    int r;
    int tamanho;  
    int **tab1;
    int **tab2;
};

struct JogoPVC{ // estrutura que contem os dados do jogo player vs computador
    char nick1[11];
    char nick2[11];
    int v1;
    int v2;
    int r;
    int tamanho; 
    int d;
    int fase;
    int b;
    int pi;
    int pj;
    int **tab1;
    int **tab2;
    int tabuleiro1[20][20];
    int tabuleiro2[20][20];
    int terminado;
};

struct Estatisticas{ // estrutura que contem as estatisticas de todos os jogos feitos em player vs computador
    int jogostotal;
    int jogostotalvit;
    int jogosfaciltot;
    int jogosmediotot;
    int jogosdificiltot;
    int jogosimpossiveltot;
    int jogosfacilvit;
    int jogosmediovit;
    int jogosdificilvit;
    int jogosimpossivelvit;
    int rondastotal;
    
    
};

//prototipos
void estatisticasleitura();
void estatisticaspreencher(int v1, int rondas, int tamanho, int dificuldade);
void menuScore();
void reiniciar();
void mostrarScore(int tamanho);
void scoreboard(int dificuldade, int rondas, char nick[]);
void executarPVC(struct JogoPVC* jogopvc, int continuar);
void executarPVP(struct JogoPVP* jogopvp, int continuar);
void printVarPVC(struct JogoPVC jogopvc);
void printVarPVC(struct JogoPVC jogopvc);
void gravarPVP(struct JogoPVP jogopvp);
void gravarPVC(struct JogoPVC jogopvc);
void continuarPVP();
void continuarPVC();
void jogarP1(int **tab1,int **tab2,int tamanho, char nick1[], char nick2[], int *v1,int *v2);
void jogarCPU(int **tab1,int **tab2,int tamanho, char nick1[], char nick2[], int *v1,int *v2, int d, int *a, int *b, int *pi, int *pj, int r);
void pvp();
void pvc();
void posicaoNaviosPL(int **tab1,char nick1[],int tamanho);
void posicaoNaviosCPU(int **tab1,int tamanho);
void imprimeTab(int **tab, int tamanho, int jogo, char nick[]);
void vidas(int tamanho, int *v1, int *v2);
void nickname(char *nick1, int num);
int tam_camp ();
void dificuldade (int *d);

#ifdef __cplusplus
}
#endif

#endif /* JOGAR_H */