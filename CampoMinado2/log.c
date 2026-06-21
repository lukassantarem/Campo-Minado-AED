//log.c

#include <stdio.h>
#include <time.h>
#include "log.h" 
#include "matriz.h" 

//Função que inicializa o arquivo log e retorna o ponteiro para o arquivo
FILE* iniciarLog(){
	//Abre o arquivo de log em modo de escrita "w"
    FILE *logFile = fopen("log.txt", "w");
    if(logFile == NULL){
		//Caso acha uma falha ao tentar abrir o arquivo
        perror("Erro ao tentar abrir o log.txt");
        return NULL;
    }
	//Hora atual
    time_t atual = time(NULL);
    struct tm *tempoAtual = localtime(&atual);
    
	//Escreve no log a datae início do jogo
    fprintf(logFile, "INICIO DO JOGO : %02d/%02d/%04d, %02d:%02d:%02d\n",
    tempoAtual->tm_mday, tempoAtual->tm_mon + 1, tempoAtual->tm_year + 1900,
    tempoAtual->tm_hour, tempoAtual->tm_min, tempoAtual->tm_sec);

    return logFile;
}

//Função que registra uma mensagem no log
void registrarLog(FILE *logFile, const char *m){
    if (logFile != NULL){
		//Caso o arquivo estiver aberto, ele registra a mensagem no log
        fprintf(logFile, "%s\n", m);
    }
}

//Função que registra as coordenadas escolhidas pelo jogador no log
void registrarCoordenada(FILE *logFile, int x, int y){
    if(logFile != NULL && x >= 0 && y >= 0){
		//Registra as coordenadas no log
        fprintf(logFile, "O jogador selecionou as coordenadas :(%d, %d)\n", x, y);
    }
}

//Remove a chamada para revelarCampoCompleto dentro de registrarEstadoDoCampo para registrar no log (células abertas ou fechadas)
void registrarEstadoDoCampo(Celula **jogo, int tam, FILE *logFile){
    if(logFile == NULL || jogo == NULL){
		//Verifica se o log ou o campo forem inválidos, e retorna sem nada
        return;
    }

    fprintf(logFile, "\n\n\tCampo minado: \n\t  "); // Cabeçalho
    int i, j;

    for(i = 1; i <= tam; i++){
        fprintf(logFile, "%3d ", i); // Espaçamento para alinhamento
    }
    fprintf(logFile, "\n\t  ");
    
    for(i = 0; i < tam; i++){
        fprintf(logFile, "----");
    }
    fprintf(logFile, "-\n");

    // Imprime as linhas do campo, no caso as linhas e as células
    for(i = 0; i < tam; i++){
        fprintf(logFile, "\t%2d |", i + 1); // Linha
        for(j = 0; j < tam; j++){
            if(jogo[i][j].estaAberta){
                if(jogo[i][j].ehBomba){
                    fprintf(logFile, " -1 |"); // Representa as bombas
                }else{
                    fprintf(logFile, " %d |", jogo[i][j].vizinhos); // Exibe o número de bombas vizinhas
                }
            }else{
                fprintf(logFile, " x |");
            }
        }
        fprintf(logFile, "\n\t  ");
        for(j = 0; j < tam; j++){
            fprintf(logFile, "----");
        }
        fprintf(logFile, "-\n");
    }
}

//Função que fecha o log
void finalizarLog(FILE *logFile){
    if(logFile != NULL){
		//Fecha o arquivo de log, se ele estiver aberto
        fclose(logFile);
    }
}