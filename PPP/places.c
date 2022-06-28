#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"

//Funções das CIDADES

lCidade cria_lista() {
    lCidade aux = (lCidade) malloc (sizeof(Cidade));
    if (aux) {
        strcpy(aux->nome, "");
        aux->lista_pdi=NULL;
        aux->lista_apont_users=NULL;
        aux->proximo=NULL;
    }
    return aux;
}

int lista_vazia(lCidade lista) {           //Vazia se tiver apenas o header
    return (!lista->proximo) ? 1 : 0;
}

void procura_lista(lCidade lista, char* nomeC, lCidade *ant, lCidade *actual) {
    *ant = lista;
    *actual = lista->proximo;
    while((*actual)!=NULL && (strcmp((*actual)->nome, nomeC)<0)) {
        *ant=*actual;
        *actual=(*actual)->proximo;
    }
    if ((*actual) != NULL && (strcmp((*actual)->nome, nomeC)!=0)) {
        *actual = NULL;
    }
}

void imprime_lista(lCidade lista) {
    lCidade list = lista->proximo;
    while (list) {
        printf("%s, ", list->nome);
        list=list->proximo;
    }
    printf("\n");
}

lCidade destroi_lista(lCidade lista) {
    while(!lista_vazia(lista)) {
        lCidade aux = lista;
        lista=lista->proximo;
        free(aux);
    }
    free(lista);
    return NULL;
}

void insere_lista(lCidade lista, char* nomeC, lpdi listpdi) {
    lCidade no = (lCidade) malloc(sizeof(Cidade));
    if (no) {
        lCidade ant, inutil;
        strcpy(no->nome, nomeC);
        no->lista_pdi=listpdi;
        no->lista_apont_users=cria_lista_aux_user();
        procura_lista(lista, nomeC, &ant, &inutil);
        no->proximo = ant->proximo;
        ant->proximo = no;
    }
}

void elimina_lista(lCidade lista, char* nomeC) {
    lCidade ant, actual;
    procura_lista(lista, nomeC, &ant, &actual);
    if (actual) {
        ant->proximo = actual->proximo;
        free(actual);
    }
}

lCidade pesquisa_lista(lCidade lista, char *nomeC) {
    lCidade ant, actual;
    procura_lista(lista, nomeC, &ant, &actual);
    return actual;
}

int conta_elementos(lCidade lista) {
    lCidade aux=lista->proximo;
    int conta=0;
    while(aux) {
        aux=aux->proximo;
        ++conta;
    }
    return conta;
}


//Funções dos PONTOS DE INTERESSE

lpdi cria_lista_pdi() {
    lpdi aux = (lpdi) malloc (sizeof(Ponto_de_Interesse));
    if (aux) {
        strcpy(aux->nome_pdi, "");
        strcpy(aux->descricao, "");
        strcpy(aux->horario, "");
        aux->lista_apont_users=NULL;
        aux->proximo=NULL;
    }
    return aux;
}

int lista_vazia_pdi(lpdi lista) {
    return (!lista->proximo) ? 1 : 0;
}

void procura_lista_pdi(lpdi lista, char* nomePDI, lpdi *ant, lpdi *actual) {
    *ant = lista;
    *actual = lista->proximo;
    while((*actual)!=NULL && (strcmp((*actual)->nome_pdi, nomePDI)<0)) {
        *ant=*actual;
        *actual=(*actual)->proximo;
    }
    if ((*actual) != NULL && (strcmp((*actual)->nome_pdi, nomePDI)!=0)) {
        *actual = NULL;
    }
}

void imprime_lista_pdi(lpdi lista) {
    lpdi list = lista->proximo;
    while (list) {
        printf("\tNOME: %s\n", list->nome_pdi);
        printf("\tDESCRICAO: %s\n", list->descricao);
        printf("\tHORARIO: %s\n", list->horario);
        printf("\n");
        list=list->proximo;
    }
    printf("\n");
}

lpdi destroi_lista_pdi(lpdi lista) {
    lpdi aux;
    while(!lista_vazia_pdi(lista)) {
        aux = lista;
        lista = lista->proximo;
        free(aux);
    }
    free(lista);
    return NULL;
}

void insere_lista_pdi(lpdi lista, char* nomePDI, char* description, char* schedule) {
    lpdi no = (lpdi) malloc(sizeof(Ponto_de_Interesse));
    if (no) {
        lpdi ant, inutil;
        strcpy(no->nome_pdi, nomePDI);
        strcpy(no->descricao, description);
        strcpy(no->horario, schedule);
        no->lista_apont_users=cria_lista_aux_user();
        procura_lista_pdi(lista, nomePDI, &ant, &inutil);
        no->proximo = ant->proximo;
        ant->proximo = no;
    }
}

void elimina_lista_pdi(lpdi lista, char* nomePDI) {
    lpdi ant, actual;
    procura_lista_pdi(lista, nomePDI, &ant, &actual);
    if (actual) {
        ant->proximo = actual->proximo;
        free(actual);
    }
}

lpdi pesquisa_lista_pdi(lpdi lista, char* nomePDI) {
    lpdi ant, actual;
    procura_lista_pdi(lista, nomePDI, &ant, &actual);
    return actual;
}

int conta_elementos_pdi(lpdi lista) {
    lpdi aux=lista->proximo;
    int conta=0;
    while(aux) {
        aux=aux->proximo;
        ++conta;
    }
    return conta;
}

//Outras Funções

void imprimir(lCidade lista) {                      //Imprime lista de cidades e correspondente lista de PDI's
    lCidade list = lista->proximo;
    while (list) {
        printf("CIDADE: %s\n", list->nome);
        imprime_lista_pdi(list->lista_pdi);
        list=list->proximo;
    }
    printf("\n");
}


void split_string(char* line, char **vec) {
    int init_size = strlen(line);
    char *copia = (char *) malloc(sizeof(char)*(init_size+1));
    strcpy(copia, line);
    char *ptr = strtok(copia, "|\n");
    char **p=vec;
	while(ptr != NULL) {
        *p=ptr;
		ptr = strtok(NULL, "|\n");
        p+=1;
	}
}

char* split_str(char* line) {
    int init_size = strlen(line);
    char *copia = (char *) malloc(sizeof(char)*(init_size+1));
    strcpy(copia, line);
    char *ptr = strtok(line, "\n");
	return ptr;
}

//___________________________________________________________________________________________________________________________
lpdi encontra_pdi(lCidade lista, char* nomePDI) {               //TESTE FUNÇÃO ENCONTRA PDI NUMA LISTA DE CIDADES
    lCidade aux=lista->proximo;
    lpdi res;
    while(aux) {
        res=pesquisa_lista_pdi(aux->lista_pdi, nomePDI);
        if(res!=NULL) {
            break;
        }
        aux=aux->proximo;
    }
    return res;
}


//Lista de PDI's Favoritos
lfavPDI cria_lista_pdi_fav() {
    lfavPDI aux=(lfavPDI) malloc (sizeof(PDI_Favoritos));
    if (aux) {
        aux->pdi_fav=NULL;
        aux->proximo=NULL;
    }
    return aux;
}


int lista_vazia_pdi_fav(lfavPDI lista) {           /*Vazia se tiver apenas o header*/
    return (!lista->proximo) ? 1 : 0;
}

void procura_lista_pdi_fav(lfavPDI lista, lpdi chave, lfavPDI *ant, lfavPDI *actual) {
    *ant = lista;
    *actual = lista->proximo;
    while((*actual)!=NULL && (strcmp((*actual)->pdi_fav->nome_pdi, chave->nome_pdi)<0)) {
        *ant=*actual;
        *actual=(*actual)->proximo;
    }
    if ((*actual) != NULL && (strcmp((*actual)->pdi_fav->nome_pdi, chave->nome_pdi)!=0)) {
        *actual = NULL;
    }
}

void imprime_lista_pdi_fav(lfavPDI lista) {
    lfavPDI list = lista->proximo;
    printf("PDI's FAVORITOS: ");
    while (list) {
        printf("%s, ", list->pdi_fav->nome_pdi);
        list=list->proximo;
    }
    printf("\n");
}

lfavPDI destroi_lista_pdi_fav(lfavPDI lista) {
    while(!lista_vazia_pdi_fav(lista)) {
        lfavPDI aux=lista;
        lista=lista->proximo;
        free(aux);
    }
    free(lista);
    return NULL;
}



void insere_lista_pdi_fav(lfavPDI lista, lpdi chave) {
    lfavPDI no = (lfavPDI) malloc(sizeof(PDI_Favoritos));
    if (no) {
        lfavPDI ant, inutil;
        no->pdi_fav = chave;
        procura_lista_pdi_fav(lista, chave, &ant, &inutil);
        no->proximo = ant->proximo;
        ant->proximo = no;
    }
}

void elimina_lista_pdi_fav(lfavPDI lista, lpdi chave) {
    lfavPDI ant, actual;
    procura_lista_pdi_fav(lista, chave, &ant, &actual);
    if (actual) {
        ant->proximo = actual->proximo;
        free(actual);
    }
}

lfavPDI pesquisa_lista_pdi_fav(lfavPDI lista, lpdi chave) {
    lfavPDI ant, actual;
    procura_lista_pdi_fav(lista, chave, &ant, &actual);
    return actual;
}

int conta_elementos_pdi_fav(lfavPDI lista) {
    lfavPDI aux=lista->proximo;
    int conta=0;
    while(aux) {
        aux=aux->proximo;
        conta+=1;
    }
    return conta;
}

//Lista de Apontadores para cidades
lfavCid cria_lista_cid_fav() {
    lfavCid aux = (lfavCid) malloc (sizeof(CID_Favoritas));
    if (aux) {
        aux->cid_fav=NULL;
        aux->proximo=NULL;
    }
    return aux;
}


int lista_vazia_cid_fav(lfavCid lista) {           /*Vazia se tiver apenas o header*/
    return (!lista->proximo) ? 1 : 0;
}

void procura_lista_cid_fav(lfavCid lista, lCidade chave, lfavCid *ant, lfavCid *actual) {
    *ant = lista;
    *actual = lista->proximo;
    while((*actual)!=NULL && (strcmp((*actual)->cid_fav->nome, chave->nome)<0)) {
        *ant=*actual;
        *actual=(*actual)->proximo;
    }
    if ((*actual) != NULL && (strcmp((*actual)->cid_fav->nome, chave->nome)!=0)) {
        *actual = NULL;
    }
}

void imprime_lista_cid_fav(lfavCid lista) {
    lfavCid list = lista->proximo;
    printf("CIDADES FAVORITAS: ");
    while (list) {
        printf("%s, ", list->cid_fav->nome);
        list=list->proximo;
    }
    printf("\n");
}

lfavCid destroi_lista_cid_fav(lfavCid lista) {
    while(!lista_vazia_cid_fav(lista)) {
        lfavCid aux=lista;
        lista=lista->proximo;
        free(aux);
    }
    free(lista);
    return NULL;
}

void insere_lista_cid_fav(lfavCid lista, lCidade chave) {
    lfavCid no = (lfavCid) malloc(sizeof(CID_Favoritas));
    if (no) {
        lfavCid ant, inutil;
        no->cid_fav = chave;
        procura_lista_cid_fav(lista, chave, &ant, &inutil);
        no->proximo = ant->proximo;
        ant->proximo = no;
    }
}

void elimina_lista_cid_fav(lfavCid lista, lCidade chave) {
    lfavCid ant, actual;
    procura_lista_cid_fav(lista, chave, &ant, &actual);
    if (actual) {
        ant->proximo = actual->proximo;
        free(actual);
    }
}

lfavCid pesquisa_lista_cid_fav(lfavCid lista, lCidade chave) {
    lfavCid ant, actual;
    procura_lista_cid_fav(lista, chave, &ant, &actual);
    return actual;
}

int conta_elementos_cid_fav(lfavCid lista) {
    lfavCid aux=lista->proximo;
    int conta=0;
    while(aux) {
        aux=aux->proximo;
        conta+=1;
    }
    return conta;
}
