#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"

lnewCidade destroi_lista_new_cid(lnewCidade lista) {
    while(!lista_vazia_new_cid(lista)) {
        lnewCidade aux = lista;
        lista=lista->next;
        free(aux);
    }
    free(lista);
    return NULL;
}

void insere_viagem_cidades(lnewCidade viagem, List user)
{
    lfavCid aux=user->info.lista_cid;
    aux=aux->proximo;
    while(aux) {
        insere_lista_new_cid_sem_pdi(viagem, aux->cid_fav);
        aux=aux->proximo;
    }
    return;
}

void insere_viagem_pdi_hot(lnewCidade viagem, lnewCidade cidades, List user)
{
    lpdi pdi_hot = user->info.Hot;
    if(pdi_hot==NULL) {
        return;
    }
    lnewCidade local=viagem->next;
    lnewCidade aux2;
    while(local) {
        aux2=pesquisa_lista_new_cid_2(cidades, local->city);
        if(pesquisa_lista_new_pdi_2(aux2->pdi_list, pdi_hot) != NULL) {
            insere_lista_new_pdi(local->pdi_list, pdi_hot);
        }
        local=local->next;
    }
}


void insere_viagem_pdis_favoritos(lnewCidade viagem, lnewCidade cidades, List user)
{
    if(lista_vazia_pdi_fav(user->info.lista_pdi)) {
        return;
    }
    lnewCidade local=viagem->next;
    lnewCidade aux;
    lnewPDI aux2;
    while(local) {
        aux=pesquisa_lista_new_cid_2(cidades, local->city);
        aux2=aux->pdi_list;
        aux2=aux2->next;
        while(aux2) {
            if(pesquisa_lista_pdi_fav(user->info.lista_pdi, aux2->pdi_list)!=NULL && conta_elementos_new_pdi(local->pdi_list)<3) {
                insere_lista_new_pdi(local->pdi_list, aux2->pdi_list);
            }
            aux2=aux2->next;
        }
        local=local->next;
    }
}

void insere_viagem_pdis_populares(lnewCidade viagem, lnewCidade cidades, List user)
{
    lnewCidade local=viagem->next;
    lnewCidade aux;
    lnewPDI aux2;
    while(local) {
        aux=pesquisa_lista_new_cid_2(cidades, local->city);
        aux2=aux->pdi_list;
        aux2=aux2->next;
        while(aux2) {
            if(conta_elementos_new_pdi(local->pdi_list)<3 && pesquisa_lista_new_pdi_2(local->pdi_list, aux2->pdi_list)==NULL) {
                insere_lista_new_pdi(local->pdi_list, aux2->pdi_list);
            }
            aux2=aux2->next;
        }
        local=local->next;
    }
}

void cria_viagem_i(lnewCidade cidades, List user){
    if(conta_elementos_cid_fav(user->info.lista_cid)!=3) {
        printf("O Plano de Viagem so pode ser criado quando tiver 3 locais favoritos.\n");
        return;
    }
    if(!lista_vazia_new_cid(user->info.viagem)) {
        char line[NUMERO];
        printf("Ja possui uma viagem definida. Pretende criar outra viagem?\nResponda \"Sim\" ou \"Nao\".\n");
        fgets(line, NUMERO, stdin);
        tira_new_line_char(line);
        while(strcmp(line, "Sim") || strcmp(line, "Nao")) {
            if(!strcmp(line, "Nao")) {
                return;
            }
            if(!strcmp(line, "Sim")) {
                user->info.viagem=destroi_lista_new_cid(user->info.viagem);
                user->info.viagem=cria_lista_new_cid();
                break;
            }
            fgets(line, NUMERO, stdin);
            tira_new_line_char(line);
        }
    }
    insere_viagem_cidades(user->info.viagem, user);
    insere_viagem_pdi_hot(user->info.viagem, cidades, user);
    insere_viagem_pdis_favoritos(user->info.viagem, cidades, user);
    insere_viagem_pdis_populares(user->info.viagem, cidades, user);
}
