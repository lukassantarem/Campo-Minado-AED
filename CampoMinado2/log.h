//log.h

#ifndef LOG_H
#define LOG_H
#include <stdio.h>
#include "matriz.h"

//Função que inicializa o arquivo log e retorna o ponteiro para o arquivo
FILE *iniciarLog();

//Função que registra uma mensagem no log
void registrarLog(FILE *logFile, const char *m);

//Função que registra o estado final do jogo no log (campo minado completo)
void estadoFinalDoJogo(Celula **jogo, int tam, FILE *logFile);

//Função que registra as coordenadas escolhidas pelo jogador no log
void registrarCoordenada(FILE *logFile, int x, int y);

//Remove a chamada para revelarCampoCompleto dentro de registrarEstadoDoCampo para registrar no log, sendo o campo com células abertas ou fechadas
void registrarEstadoDoCampo(Celula **jogo, int tam, FILE *logFile);

//Função que fecha o log
void finalizarLog(FILE *logFile);

//Função que revela o campo completo e o registra no log, isso ocorre após o game over ou a vitória
void revelarCampoCompleto(Celula **jogo, int tam, FILE *logFile);

#endif //Fim
