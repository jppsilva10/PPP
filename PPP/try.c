#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"
#define BUFFERSIZE 50

/*ZONA DE TESTES*/


char* tira_new_line_char(char* line) {
    int n=strlen(line);
    line[n-1]='\0';
    return line;
}


void visualiza_pdis_one(lCidade lista) {
    char line[BUFFERSIZE];
    lCidade local;
    printf("Pretende ver a lista de PDI's de que local?\n");
    fgets(line, BUFFERSIZE, stdin);
    tira_new_line_char(line);
    if(pesquisa_lista(lista, line)==NULL) {
        printf("Local nao encontrado! Por favor, tente novamente.\n");
        return;
    }
    else {
        local=pesquisa_lista(lista, line);
        imprime_lista_pdi(local->lista_pdi);
    }
}

//Modelo #1
void visualiza_locais(lCidade lista) {
    lCidade aux=lista->proximo;
    printf("LISTA DE LOCAIS:\n");
    while(aux) {
        printf("\t%s\n", aux->nome);
        aux=aux->proximo;
    }
}

/*FREE FUNCTIONS*/

