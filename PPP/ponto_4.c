#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"

lutil cria_lista_aux_user() {
    lutil aux = (lutil) malloc (sizeof(LIST_USER));
    if (aux) {
        aux->utilizador=NULL;
        aux->next=NULL;
    }
    return aux;
}

int lista_vazia_aux_user(lutil lista) {           //Vazia se tiver apenas o header
    return (!lista->next) ? 1 : 0;
}

void procura_lista_aux_user(lutil lista, List chave, lutil *ant, lutil *actual) {
    *ant = lista;
    *actual = lista->next;
    while((*actual)!=NULL && (strcmp((*actual)->utilizador->info.numero_telefone, chave->info.numero_telefone) != 0)) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
    if ((*actual) != NULL && (strcmp((*actual)->utilizador->info.numero_telefone, chave->info.numero_telefone) != 0)) {
        *actual = NULL;
    }
}

void insere_lista_aux_user(lutil lista, List var) {
    lutil no = (lutil) malloc(sizeof(LIST_USER));
    if (no) {
        lutil ant, inutil;
        no->utilizador=var;
        procura_lista_aux_user(lista, var, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}

void elimina_lista_aux_user(lutil lista, List var) {
    lutil ant, actual;
    procura_lista_aux_user(lista, var, &ant, &actual);
    if (actual) {
        ant->next = actual->next;
        free(actual);
    }
}

lutil pesquisa_lista_aux_user(lutil lista, List var) {
    lutil ant, actual;
    procura_lista_aux_user(lista, var, &ant, &actual);
    return actual;
}

int conta_elementos_aux_user(lutil lista) {
    lutil aux=lista->next;
    int conta=0;
    while(aux) {
        aux=aux->next;
        ++conta;
    }
    return conta;
}

void imprime_lista_aux_user(lutil lista) {
    lutil list = lista->next;
    printf("LISTA DE UTILIZADORES: ");
    while (list) {
        printf("%s, ", list->utilizador->info.numero_telefone);
        list=list->next;
    }
    printf("\n");
}

void imprime_apont_pdi(lpdi lista) {
    lpdi list = lista->proximo;
    while (list) {
        if(!lista_vazia_aux_user(list->lista_apont_users)) {
            printf("PDI: %s\n\t", list->nome_pdi);
            imprime_lista_aux_user(list->lista_apont_users);
            printf("\t");
        }
        list=list->proximo;
    }
    printf("\n");
}

void imprime_apont_cid(lCidade lista) {
    lCidade aux = lista->proximo;
    while (aux) {
        if(!lista_vazia_aux_user(aux->lista_apont_users)) {
            printf("CIDADE: %s\n", aux->nome);
            imprime_lista_aux_user(aux->lista_apont_users); printf("\t");
        }
        imprime_apont_pdi(aux->lista_pdi); printf("\n");
        aux=aux->proximo;
    }
    printf("\n");
}

lutil destroi_lista_aux_user(lutil lista) {
    while(!lista_vazia_aux_user(lista)) {
        lutil aux=lista;
        lista=lista->next;
        free(aux);
    }
    free(lista);
    return NULL;
}

void ordena_new_cid(lnewCidade lista) {
    lnewCidade aux=lista;
    lnewCidade ant, actual, prox;
    ant=aux;
    actual=ant->next;
    prox=actual->next;
    while (prox!=NULL) {
        if(conta_elementos_aux_user(actual->city->lista_apont_users) < conta_elementos_aux_user(prox->city->lista_apont_users)) {
            actual->next=prox->next;
            ant->next=prox;
            prox->next=actual;
            aux=lista;
        }
        else {
            aux=aux->next;
        }
        ant=aux;
        actual=ant->next;
        prox=actual->next;
    }
}

void ordena_new_pdi(lnewPDI lista) {
    lnewPDI aux=lista;
    lnewPDI ant, actual, prox;
    ant=aux;
    actual=ant->next;
    prox=actual->next;
    while (prox!=NULL) {
        if(conta_elementos_aux_user(actual->pdi_list->lista_apont_users) < conta_elementos_aux_user(prox->pdi_list->lista_apont_users)) {
            actual->next=prox->next;
            ant->next=prox;
            prox->next=actual;
            aux=lista;
        }
        else {
            aux=aux->next;
        }
        ant=aux;
        actual=ant->next;
        prox=actual->next;
    }
}

void ordena(lnewCidade lista) {
    lnewCidade aux=lista;
    ordena_new_cid(aux);
    aux=aux->next;
    while(aux) {
        ordena_new_pdi(aux->pdi_list);
        aux=aux->next;
    }
}
