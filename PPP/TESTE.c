#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"


lnewPDI cria_lista_new_pdi() {
    lnewPDI aux = (lnewPDI) malloc (sizeof(LISTA_DE_PDI));
    if (aux) {
        aux->pdi_list=NULL;
        aux->next=NULL;
    }
    return aux;
}

int lista_vazia_new_pdi(lnewPDI lista) {           //Vazia se tiver apenas o header
    return (!lista->next) ? 1 : 0;
}

void procura_lista_new_pdi(lnewPDI lista, lpdi chave, lnewPDI *ant, lnewPDI *actual) {  //O que faz o Procura Lista?
    *ant = lista;
    *actual = lista->next;
    while((*actual)!=NULL && conta_elementos_aux_user(((*actual)->pdi_list)->lista_apont_users) >= conta_elementos_aux_user(chave->lista_apont_users)) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
    if ((*actual) != NULL && conta_elementos_aux_user(((*actual)->pdi_list)->lista_apont_users) != conta_elementos_aux_user(chave->lista_apont_users)) {
        *actual = NULL;
    }
}

void insere_lista_new_pdi(lnewPDI lista, lpdi varPDI) {
    lnewPDI no = (lnewPDI) malloc(sizeof(LISTA_DE_PDI));
    if (no) {
        lnewPDI ant, inutil;
        no->pdi_list=varPDI;
        procura_lista_new_pdi(lista, varPDI, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}

void elimina_lista_new_pdi(lnewPDI lista, lpdi varPDI) {
    lnewPDI ant, actual;
    procura_lista_new_pdi(lista, varPDI, &ant, &actual);
    if (actual) {
        ant->next = actual->next;
        free(actual);
    }
}

lnewPDI pesquisa_lista_new_pdi(lnewPDI lista, lpdi varPDI) {
    lnewPDI ant, actual;
    procura_lista_new_pdi(lista, varPDI, &ant, &actual);
    return actual;
}

int conta_elementos_new_pdi(lnewPDI lista) {
    lnewPDI aux=lista->next;
    int conta=0;
    while(aux) {
        aux=aux->next;
        ++conta;
    }
    return conta;
}

void imprime_lista_new_pdi(lnewPDI lista) {            //ERRO
    lnewPDI list = lista->next;
    while (list) {
        printf("\tNOME: %s\n", list->pdi_list->nome_pdi);
        printf("\tDESCRICAO: %s\n", list->pdi_list->descricao);
        printf("\tHORARIO: %s\n", list->pdi_list->horario);
        printf("\tVOTOS: %d\n", conta_elementos_aux_user(list->pdi_list->lista_apont_users));
        printf("\n");
        list=list->next;
    }
    printf("\n");
}

void imprime_lista_new_cid(lnewCidade lista) {
    lnewCidade list = lista->next;
    while(list) {
        printf("CIDADE: %s\n", list->city->nome);
        printf("VOTOS: %d\n", conta_elementos_aux_user(list->city->lista_apont_users));
        imprime_lista_new_pdi(list->pdi_list);
        list=list->next;
    }
    printf("\n");
}

lnewCidade cria_lista_new_cid() {
    lnewCidade aux = (lnewCidade) malloc (sizeof(LISTA_DE_CIDADES));
    if (aux) {
        aux->city=NULL;
        aux->pdi_list=NULL;
        aux->next=NULL;
    }
    return aux;
}

int lista_vazia_new_cid(lnewCidade lista) {           //Vazia se tiver apenas o header
    return (!lista->next) ? 1 : 0;
}

void procura_lista_new_cid(lnewCidade lista, lCidade chave, lnewCidade *ant, lnewCidade *actual) {  //O que faz o Procura Lista?
    *ant = lista;
    *actual = lista->next;
    while((*actual)!=NULL && conta_elementos_aux_user(((*actual)->city)->lista_apont_users) >= conta_elementos_aux_user(chave->lista_apont_users)) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
    if ((*actual) != NULL && conta_elementos_aux_user(((*actual)->city)->lista_apont_users) != conta_elementos_aux_user(chave->lista_apont_users)) {
        *actual = NULL;
    }
}

void insere_lista_new_cid(lnewCidade lista, lCidade varCID, lnewPDI varPDI) {
    lnewCidade no = (lnewCidade) malloc(sizeof(LISTA_DE_CIDADES));
    if (no) {
        lnewCidade ant, inutil;
        no->city=varCID;
        no->pdi_list=varPDI;
        procura_lista_new_cid(lista, varCID, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}


void insere_lista_new_cid_sem_pdi(lnewCidade lista, lCidade varCID) {
    lnewCidade no = (lnewCidade) malloc(sizeof(LISTA_DE_CIDADES));
    if (no) {
        lnewCidade ant, inutil;
        no->city=varCID;
        no->pdi_list=cria_lista_new_pdi();
        procura_lista_new_cid(lista, varCID, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}

void elimina_lista_new_cid(lnewCidade lista, lCidade varCID) {
    lnewCidade ant, actual;
    procura_lista_new_cid(lista, varCID, &ant, &actual);
    if (actual) {
        ant->next = actual->next;
        free(actual);
    }
}

lnewCidade pesquisa_lista_new_cid(lnewCidade lista, lCidade varCid) {
    lnewCidade ant, actual;
    procura_lista_new_cid(lista, varCid, &ant, &actual);
    return actual;
}

int conta_elementos_new_cid(lnewCidade lista) {
    lnewCidade aux=lista->next;
    int conta=0;
    while(aux) {
        aux=aux->next;
        ++conta;
    }
    return conta;
}

void organiza(lCidade lista, lnewCidade new_list) {
    lCidade aux=lista->proximo;
    lnewPDI aux3;
    lpdi aux2;
    while(aux) {
        aux2=aux->lista_pdi;
        aux2=aux2->proximo;
        aux3=cria_lista_new_pdi();
        while(aux2) {
            insere_lista_new_pdi(aux3, aux2);
            aux2=aux2->proximo;
        }
        insere_lista_new_cid(new_list, aux, aux3);
        aux=aux->proximo;
    }
}
