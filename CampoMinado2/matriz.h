//matriz.h

#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct{
    int ehBomba; //Armazena 1 se for célula for uma bomba, caso ao contrário armazena 0
    int estaAberta; //Armazena 1 se a célula estiver aberta, caso ao contrário armazena 0
    int vizinhos; //Armazena o número de bombas ao redor da célula
}Celula;

//Função que aloca dinamicamente o campo de jogo
Celula **alocarCampo(int tam);

//Função qu libera a memória do campo de jogo
void liberarCampo(Celula **jogo, int tam);

//Função que inicializa o campo com bombas em ordens aleatórias e que tenha células fechadas
void inicializarCampo(Celula **jogo, int tam, int bombas);

//Função que calcula o número de bombas vizinhas de uma Célula
void calcularVizinhos(Celula **jogo, int tam, int x, int y);

//Função que imprime o campo minado, sendo representado por "x" as Células fechadas
void imprimirCampo(Celula **jogo, int tam);

//Função que revela o campo minado completo após game over ou vitória
void revelarCampoCompleto(Celula **jogo, int tam, FILE *logFile);

//Função que verifica se as coordenadas estão detro dos limites da matriz
int coordenadaValida(int l, int c, int tam);

#endif //Fim