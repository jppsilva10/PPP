#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"


double percentagem_favoritos(lnewCidade viagem, List list_users) //Quais os utilizadores que têm as suas cidades favoritas incluidas na viagem?
{
    lutil contador = cria_lista_aux_user();
    lnewCidade list1 = viagem->next;
    List aux=list_users->next;
    while(list1) {
        while(aux) {
            if(pesquisa_lista_cid_fav(aux->info.lista_cid, list1->city)!=NULL && pesquisa_lista_aux_user(contador, aux)==NULL) {
                insere_lista_aux_user(contador, aux);
            }
            aux=aux->next;
        }
        aux=list_users->next;
        list1=list1->next;
    }
    int total_users = conta_elementosU(list_users);
    int numero_de_users= conta_elementos_aux_user(contador);
    double resultado = (double) numero_de_users / (double) total_users;
    resultado=resultado*100;
    return resultado;
}

double percentagem_hot(lnewCidade viagem, List list_users)
{
    List list1 = list_users->next;
    lnewCidade list2 = viagem->next;
    int numero_de_users=0;
    int total_users=conta_elementosU(list_users);
    double resultado;
    while(list2) {
        while(list1) {
            if(list1->info.Hot!=NULL) {
                if(pesquisa_lista_pdi(list2->city->lista_pdi, list1->info.Hot->nome_pdi)!=NULL) {
                    numero_de_users+=1;
                }
            }
            list1=list1->next;
        }
        list1=list_users->next;
        list2=list2->next;
    }
    resultado = (double) numero_de_users / (double) total_users;
    resultado=resultado*100;
    return resultado;
}

int conta_votos_users(lnewCidade lista)
{
    lnewCidade list1=lista->next;
    lnewPDI list2;
    int n=0;
        while(list1) {
            list2 = list1->pdi_list;
            list2=list2->next;
            while(list2) {
                n+=conta_elementos_aux_user(list2->pdi_list->lista_apont_users);
                list2=list2->next;
            }
            list1=list1->next;
        }
    return n;
}

double percentagem_preferncias_pdi(lnewCidade viagem, lnewCidade locais) //locais é a lista principal organizada por poularidade
{
    int votos=conta_votos_users(viagem);
    int total_users=conta_votos_users(locais);
    double resultado = (double) votos / (double) total_users;
    resultado=resultado*100;
    return resultado;
}

void avalia(lnewCidade viagem, lnewCidade locais, List lista_user) {
    double a, b, c;
    a=percentagem_favoritos(viagem, lista_user);
    printf("Percentagem de utilizadores que tem pelo menos 1 local favorito entre os incluidos na viagem - %0.2lf%%\n", a);
    b=percentagem_hot(viagem, lista_user);
    printf("Percentagem de utilizadores cujo PdI \"Hot\" esta incluido nesta viagem - %0.2lf%%\n", b);
    c=percentagem_preferncias_pdi(viagem, locais);
    printf("Percentagem das preferencias de PDI - %0.2lf%%\n", c);
}
