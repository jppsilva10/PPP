#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"



void procura_lista_new_pdi_2(lnewPDI lista, lpdi chave, lnewPDI *ant, lnewPDI *actual) {  //O que faz o Procura Lista?
    *ant = lista;
    *actual = lista->next;
    while((*actual)!=NULL && strcmp((*actual)->pdi_list->nome_pdi, chave->nome_pdi) != 0) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->pdi_list->nome_pdi, chave->nome_pdi)!=0) {
        *actual = NULL;
    }
}

lnewPDI pesquisa_lista_new_pdi_2(lnewPDI lista, lpdi varPDI) {
    lnewPDI ant, actual;
    procura_lista_new_pdi_2(lista, varPDI, &ant, &actual);
    return actual;
}

void insere_lista_new_pdi_2(lnewPDI lista, lpdi varPDI) {
    lnewPDI no = (lnewPDI) malloc(sizeof(LISTA_DE_PDI));
    if (no) {
        lnewPDI ant, inutil;
        no->pdi_list=varPDI;
        procura_lista_new_pdi_2(lista, varPDI, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}


void procura_lista_new_cid_2(lnewCidade lista, lCidade chave, lnewCidade *ant, lnewCidade *actual) {  //O que faz o Procura Lista?
    *ant = lista;
    *actual = lista->next;
    while((*actual)!=NULL && strcmp((*actual)->city->nome, chave->nome) != 0) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->city->nome, chave->nome)!=0) {
        *actual = NULL;
    }
}

void insere_lista_new_cid_sem_pdi_2(lnewCidade lista, lCidade varCID) {
    lnewCidade no = (lnewCidade) malloc(sizeof(LISTA_DE_CIDADES));
    if (no) {
        lnewCidade ant, inutil;
        no->city=varCID;
        no->pdi_list=cria_lista_new_pdi();
        procura_lista_new_cid_2(lista, varCID, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}

lnewCidade pesquisa_lista_new_cid_2(lnewCidade lista, lCidade varCid) {
    lnewCidade ant, actual;
    procura_lista_new_cid_2(lista, varCid, &ant, &actual);
    return actual;
}




/*PODE NAO SER DEFINITIVO*/
/*FUNÇÕES TESTE PARA COMPARAR PONTEIROS
SERÁ QUE, EM VE DE COMPARAR STRINGS, PODEMOS COMPARAR PONTEIROS? E ASSIM
ENCONTRAR A INFORMAÇÃO DE MODO MAIS EFICIENTE???*/

//Versoes do pesquisa lista e procura lista
void procura_lista_pdi_fav_i(lfavPDI lista, lpdi chave, lfavPDI *ant, lfavPDI *actual) {
    *ant = lista;
    *actual = lista->proximo;
    while((*actual)!=NULL && lista->pdi_fav!=chave) {
        *ant=*actual;
        *actual=(*actual)->proximo;
    }
    if ((*actual) != NULL && lista->pdi_fav!=chave) {
        *actual = NULL;
    }
}

lfavPDI pesquisa_lista_pdi_fav_i(lfavPDI lista, lpdi chave) {
    lfavPDI ant, actual;
    procura_lista_pdi_fav_i(lista, chave, &ant, &actual);
    return actual;
}

//Cidades favoritas
void procura_lista_cid_fav_i(lfavCid lista, lCidade chave, lfavCid *ant, lfavCid *actual) {
    *ant = lista;
    *actual = lista->proximo;
    while((*actual)!=NULL && lista->cid_fav!=chave) {
        *ant=*actual;
        *actual=(*actual)->proximo;
    }
    if ((*actual) != NULL && lista->cid_fav!=chave) {
        *actual = NULL;
    }
}

lfavCid pesquisa_lista_cid_fav_i(lfavCid lista, lCidade chave) {
    lfavCid ant, actual;
    procura_lista_cid_fav_i(lista, chave, &ant, &actual);
    return actual;
}

//lnewCid
void procura_lista_new_cid_i(lnewCidade lista, lCidade chave, lnewCidade *ant, lnewCidade *actual) {
    *ant = lista;
    *actual = lista->next;
    while((*actual)!=NULL && lista->city!=chave) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
    if ((*actual) != NULL && lista->city!=chave) {
        *actual = NULL;
    }
}

lnewCidade pesquisa_lista_new_cid_i(lnewCidade lista, lCidade chave) {
    lnewCidade ant, actual;
    procura_lista_new_cid_i(lista, chave, &ant, &actual);
    return actual;
}

//lnewPDI
void procura_lista_new_pdi_i(lnewPDI lista, lpdi chave, lnewPDI *ant, lnewPDI *actual) {
    *ant = lista;
    *actual = lista->next;
    while((*actual)!=NULL && lista->pdi_list!=chave) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
    if ((*actual) != NULL && lista->pdi_list!=chave) {
        *actual = NULL;
    }
}

lnewPDI pesquisa_lista_new_pdi_i(lnewPDI lista, lpdi chave) {
    lnewPDI ant, actual;
    procura_lista_new_pdi_i(lista, chave, &ant, &actual);
    return actual;
}

//lutil
void procura_lista_aux_user_i(lutil lista, List chave, lutil *ant, lutil *actual) {
    *ant = lista;
    *actual = lista->next;
    while((*actual)!=NULL && lista->utilizador!=chave) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
    if ((*actual) != NULL && lista->utilizador!=chave) {
        *actual = NULL;
    }
}

lutil pesquisa_lista_aux_user_i(lutil lista, List chave) {
    lutil ant, actual;
    procura_lista_aux_user_i(lista, chave, &ant, &actual);
    return actual;
}
