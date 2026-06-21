//matriz.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"
#include "log.h"

//Função que aloca dinamicamente o campo de jogo
Celula **alocarCampo(int tam){
	Celula **jogo = (Celula **)malloc(tam * sizeof(Celula *));
	int i;
    
	//Verifica se a alocação foi feita da forma correta
    if(jogo == NULL){
        perror("Erro ao tentar alocar a matriz");
        exit(1);
    }

	//Aloca a memória para cada linha do campo
	for(i = 0; i < tam; i++){
		jogo[i] = (Celula* )malloc(tam* sizeof(Celula));
        if(jogo == NULL){
            perror("Erro ao tentar alocar a matriz");
            exit(1); //Encerra o programa caso aja erro na alocação
            }
        }
        return jogo;
    }

//Função qu libera a memória do campo de jogo
void liberarCampo(Celula **jogo, int tam){
	int i;
	//Libera a memória alocada para cada linha do campo
	for(i = 0; i < tam; i++){
		free(jogo[i]);
	}
	free(jogo);
}

//Função que inicializa o campo com bombas em ordens aleatórias e que tenha Células fechadas
void inicializarCampo(Celula **jogo, int tam, int bombas){
	srand(time(NULL));
	int bombasColocadas = 0;
	int i, j;
	
	//Inicializa todas as células com valores padrões
	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			jogo[i][j].ehBomba = 0; //Células inicialmente não são bombas
			jogo[i][j].vizinhos = 0; //Não possui vizinhos
			jogo[i][j].estaAberta = 0; //Células começam fechadas
		}
	}
	
	//É colocado as bombas aleatoriamente
	while(bombasColocadas < bombas){
		int l = rand() % tam;
		int c = rand() % tam;
		
		if(!jogo[l][c].ehBomba){
			jogo[l][c].ehBomba = 1;
			bombasColocadas++;
		}
	}
}

//Função que calcula o número de bombas vizinhas de uma Célula
void calcularVizinhos(Celula **jogo, int tam, int x, int y){
	int i, j;
	int bombasVizinhas = 0;
	
	//Verifica as células vizinhas
	for(i = -1; i <= 1; i++){
		for(j = -1; j <= 1; j++){
			int nvLinha = x + i;
			int nvColuna = y + j;
			
			if(nvLinha >= 0 && nvLinha < tam && nvColuna >= 0 && nvColuna < tam){
				if(jogo[nvLinha][nvColuna].ehBomba){ //Se a célula vizinha for uma bomba
                    bombasVizinhas++; //Incrementa o contador das bombas vizinhas
                }
			}
		}
	}
	jogo[x][y].vizinhos = bombasVizinhas; //Atualiza o número de vizinhos para a célula atual
}

//Função que imprime o campo minado, sendo representado por "x" as Células fechadas
void imprimirCampo(Celula **jogo, int tam){
	printf("\n\n\tCampo minado: \n\t  "); //Cabeçalho
	int i, j;
	
	for(i = 1; i <= tam; i++){
		printf("%3d ", i); //Espaçamento de 3 para alienação
	}
	printf("\n\t  ");
	
	for(i = 0; i < tam; i++){
		printf("----");
	}
	printf("-\n");
	
	//Imprime as linhas do campo completo, no caso as linhas e as Células
	for(i = 0; i < tam; i++){
		printf("\t%2d |", i + 1); //Linha
		for(j = 0; j < tam; j++){
			if(jogo[i][j].estaAberta){
				if(jogo[i][j].ehBomba){
					printf(" -1 |"); //Representa as bombas
				}else{
					printf(" %d |", jogo[i][j].vizinhos); //Exibe o número de bombas vizinhas
				}
			}else{
				printf(" x |");
			}
		}
		printf("\n\t  ");
		for(j = 0; j < tam; j++){
			printf("----");
		}
		printf("-\n");
	}
}
//O primeiro número digitado representa as linhas e o segundo as colunas


//Função que revela o campo minado completo após game over ou vitória
void revelarCampoCompleto(Celula **jogo, int tam, FILE *logFile){
    printf("\n\n\tCampo completo: \n\t  "); //Cabeçalho
    registrarLog(logFile, "Campo Completo"); //Registrar no log
	int i, j;

    for(i = 1; i <= tam; i++){
        printf("%3d ", i); //espaçamento para alinhamento
    }
    printf("\n\t  ");
    for (i = 0; i < tam; i++){
        printf("----");
    }
    printf("-\n");

    for(i = 0; i < tam; i++){
        printf("\t%2d |", i + 1);
        for(j = 0; j < tam; j++){
            if(jogo[i][j].ehBomba){
                printf(" -1 |");
            }else{
                printf(" %d |", jogo[i][j].vizinhos);
            }
        }
        printf("\n\t  ");
        for(j = 0; j < tam; j++){
            printf("----");
        }
        printf("-\n");
    }
}

//Função que verifica se as coordenadas estão detro dos limites da matriz
int coordenadaValida(int l, int c, int tam){
	return l >= 1 && l <= tam && c >= 1 && c <= tam; //Verifica se as coordenadas estão dentro dos limites
}