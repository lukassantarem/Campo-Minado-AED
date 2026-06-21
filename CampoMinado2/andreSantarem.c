//main

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"
#include "log.h"

//Função para registrar o início do log
void registrarInicio(FILE *logFile){
	registrarLog(logFile, "Jogo inicializado!");
}

//Função para registrar as coordenadas escolhidas pelo jogador
void registrarCoordenadas(FILE *logFile, int x, int y){
	char msg[50]; //Array para armazenar a m(mensagem)
	sprintf(msg, "Digite as coordenadas: (%d,%d)\n", x, y);
	registrarLog(logFile, msg);
}

//Função para registrar o estado atual do jogo no log
void estadoFinalDoJogo(Celula **jogo, int tam, FILE *logFile){
	registrarLog(logFile, "As coordenadas escolhidas pelo usuário foram:");
	registrarEstadoDoCampo(jogo, tam, logFile);
}

int main(void){
	FILE *logFile;
	Celula **jogo;
	int nivel, x, y;
	int tam, bombas;
	int celulasSemBombas = 0;
	
	//Inicialização do log
	logFile = iniciarLog();
	if(logFile == NULL){
	    printf("Erro ao tentar abrir o log\n");
	    return 1;
	}
	registrarInicio(logFile);
	
	//Escolha do nível de dificuldade
	while(1){
		printf("Escolha o nivel de dificuldade:\n1 - facil (10x10 com 15 minas)\n2 - medio (20x20 com 60 minas)\n3 - dificil (30x30 com 135 minas)\n");
		if(scanf("%d", &nivel)!= 1 || nivel < 1 || nivel > 3){
			printf("Erro! Insira um numero de 1 ate 3.\n");
			continue;
		}
		break;
	}

	//Definir o tamanho do campo e a quantidade de bombas de acordo com o nível selecionado
	if(nivel == 1){
		tam = 10;
		bombas = 15;
	}else if(nivel == 2){
		tam = 20;
		bombas = 60;
	}else if(nivel == 3){
		tam = 30;
		bombas = 135;
	}

	//Inicialização do campo
	jogo = alocarCampo(tam);
	inicializarCampo(jogo, tam, bombas);
	imprimirCampo(jogo, tam); //Imprime o campo inicial

	while(1){
	    
	    //Lê as cordenadas inseridas pelo usuário
	    if(scanf("%d,%d", &x, &y) != 2 || !coordenadaValida(x, y, tam)){
	        printf("Entrada invalida! Selecione uma entrada valida.\n");
			//Verifica se as coordenadas são válidas dentro do campo
		}

		if(!coordenadaValida(x, y, tam)){
			continue; //Repete a leitura das coordenadas até o usuário inserir a entrada correta
		}

		//Verifica se a célula já foi aberta
		if(jogo[x - 1][y - 1].estaAberta){
			printf("Coordenada ja foi selecionada! Escolha outra.\n");
			continue; //Repete a leitura das coordenadas até o usuário inserir a entrada correta
		}
		
		//Seleciona a célula como aberta e registra no log
		registrarCoordenada(logFile, x, y);
		jogo[x - 1][y - 1].estaAberta = 1;
		registrarEstadoDoCampo(jogo, tam, logFile); //Registra o estado final do log
		
		//Verifica se o jogar selecionou uma bomba
		if(jogo[x - 1][y - 1].ehBomba){
			printf("game over!\n");
			registrarLog(logFile, "Game over"); //chamada de função para registrar mensagens no arquivo de logo do jogo, a fim de indiciar que o jogador perdeu o jogo
			revelarCampoCompleto(jogo, tam, logFile); //Revela o campo completo
			
			//Finaliza o jogo
			liberarCampo(jogo, tam);
			finalizarLog(logFile);

			//termina do looping do jogo
			return 0;
		}else{
			//Calcula a atualização de células abertas sem bomba
			calcularVizinhos(jogo, tam, x - 1, y - 1);
			celulasSemBombas++;
			
			//Verifica se o jogador ganhou
			if(celulasSemBombas == tam * tam - bombas){
				printf("parabens, vc eh fera.\n");
				registrarLog(logFile, "Parabens, vc eh fera!"); //chamada de função para registrar mensagens no arquivo de logo do jogo, a fim de indiciar que o jogador ganhou o jogo
				revelarCampoCompleto(jogo, tam, logFile); //Revela o campo completo

				//Finaliza o jogo
				liberarCampo(jogo, tam);
				finalizarLog(logFile);
			
			//termina o looping do jogo
			return 0;
			}
		}
		imprimirCampo(jogo, tam); // Imprime o movimento do campo
	}
	return 0;
}