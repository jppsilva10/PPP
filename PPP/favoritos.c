#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"

int insere_pdi_hot(List utilizador, lCidade city) {                 //Insere/Altera PDI HOT
    char line[BUFFERSIZE];
    if (utilizador->info.Hot!=NULL) {
        printf("Ja tem um PDI HOT definido (%s). Pretende alterar o seu PDI HOT?\nResponda \"Sim\" ou \"Nao\".\n", utilizador->info.Hot->nome_pdi);
        fgets(line, BUFFERSIZE, stdin);
        tira_new_line_char(line);
        while(strcmp(line, "Sim") || strcmp(line, "Nao")) {
            if(!strcmp(line, "Nao")) {
                return 0;
            }
            if(!strcmp(line, "Sim")) {
                break;
            }
            fgets(line, BUFFERSIZE, stdin);
            tira_new_line_char(line);
        }
    }
    char hot[NOME];
    printf("Qual a o PDI HOT que pretende escolher?\n");
    fgets(hot, NOME, stdin);
    tira_new_line_char(hot);
    lpdi hott=encontra_pdi(city, hot);
    if (hott==NULL) {
        printf("Ponto de Interesse nao econtrado, por favor tente novamente.");
        return 0;
    }
    if (pesquisa_lista_pdi_fav(utilizador->info.lista_pdi, hott)!=NULL) {
        printf("Este PDI pertence a sua lista de favoritos, pretende alterar o seu PDI Hot mesmo assim?\nResponda \"Sim\" ou \"Nao\".\n");
        printf("WARNING - Isto fara com que o PDI seja removido da sua lista de favoritos - GNINRAW\n");
        fgets(line, BUFFERSIZE, stdin);
        tira_new_line_char(line);
        while(strcmp(line, "Sim") || strcmp(line, "Nao")) {
            if(!strcmp(line, "Nao")) {
                return 0;
            }
            if(!strcmp(line, "Sim")) {
                break;
            }
            fgets(line, BUFFERSIZE, stdin);
            tira_new_line_char(line);
        }
        lpdi eliminado=utilizador->info.Hot;
        utilizador->info.Hot=hott;
        if(eliminado!=NULL) {
            elimina_lista_aux_user(eliminado->lista_apont_users, utilizador);
        }
        elimina_lista_pdi_fav(utilizador->info.lista_pdi, hott);
    }
    else if (pesquisa_lista_pdi_fav(utilizador->info.lista_pdi, hott)==NULL){
        lpdi eliminado=utilizador->info.Hot;
        utilizador->info.Hot=hott;
        if(eliminado!=NULL) {
            elimina_lista_aux_user(eliminado->lista_apont_users, utilizador);
        }
        if(pesquisa_lista_aux_user(hott->lista_apont_users, utilizador)==NULL) {
            insere_lista_aux_user(hott->lista_apont_users, utilizador);
        }
    }
    return 1;
}

int remove_pdi_hot(List utilizador, lCidade city) {
    if(utilizador->info.Hot==NULL) {
        printf("PDI Hot inexistente.\n");
        return 0;
    }
    lpdi eliminado=utilizador->info.Hot;
    utilizador->info.Hot=NULL;
    if(pesquisa_lista_aux_user(eliminado->lista_apont_users, utilizador)!=NULL) {
        elimina_lista_aux_user(eliminado->lista_apont_users, utilizador);
    }
    return 1;
}

int puts_pdi_fav(lfavPDI lista, List utilizador, lCidade cidades) {
    char line[NOME];
    printf("Qual o Ponto de Interesse que pretende escolher como favorito?\n");
    fgets(line, NOME, stdin);
    tira_new_line_char(line);
    if (encontra_pdi(cidades, line)==NULL) {
        if(!strcmp(line, "")) {
            printf("Nenhum PDI inserido. Por favor, tente novamente.\n");
            return 0;
        }
        while(encontra_pdi(cidades, line)==NULL) {
            if(!strcmp(line, "")) {
                printf("Nenhum PDI inserido. Por favor, tente novamente.\n");
                return 0;
            }
            printf("PDI nao encontrado. Por favor tente novamente.\n");
            fgets(line, NOME, stdin);
            tira_new_line_char(line);
        }
    }
    if(encontra_pdi(cidades, line)!=NULL) {
        lpdi res=encontra_pdi(cidades, line);
        if (pesquisa_lista_pdi_fav(lista, res)) {
            printf("PDI ja presente na lista de favoritos.\n");
            return 0;
        }
        else if (utilizador->info.Hot==res) {
            printf("Este PDI e o seu PDI Hot. Pretende continuar?\nResponda \"Sim\" ou \"Nao\".\n");
            printf("WARNING - Isto fara com que o PDI Hot seja removido e seja inserido na sua lista de favoritos - GNINRAW\n");
            fgets(line, NOME, stdin);
            tira_new_line_char(line);
            while(strcmp(line, "Sim") || strcmp(line, "Nao")) {
                if(!strcmp(line, "Nao")) {
                    return 0;
                }
                if(!strcmp(line, "Sim")) {
                    break;
                }
                fgets(line, NOME, stdin);
                tira_new_line_char(line);
            }
            utilizador->info.Hot=NULL;
            insere_lista_pdi_fav(lista, res);
        }
        else if(utilizador->info.Hot!=res) {
            insere_lista_pdi_fav(lista, res);
            if (pesquisa_lista_aux_user(res->lista_apont_users, utilizador)==NULL) {
                insere_lista_aux_user(res->lista_apont_users, utilizador);
            }
        }
    }
    return 1;
}



int remove_pdi_fav(lfavPDI lista, List utilizador, lCidade cidades) {
    if (conta_elementos_pdi_fav(lista)==0) {
        printf("A sua lista de Pontos de Interesse favoritos esta vazio. Nao pode remover favoritos.\n");
        return 0;
    }
    char line[NOME];
    printf("Qual o Ponto de Interesse que pretende remover dos seus favoritos?\n");
    fgets(line, NOME, stdin);
    tira_new_line_char(line);
    if (encontra_pdi(cidades, line)==NULL) {
        if(!strcmp(line, "")) {
            printf("Nenhum PDI reconhecido. Por favor, tente novamente.\n");
            return 0;
        }
        while(encontra_pdi(cidades, line)==NULL) {
            if(!strcmp(line, "")) {
                printf("Nenhum PDI Reconhecido. Por favor, tente novamente.\n");
                return 0;
            }
            printf("PDI nao encontrado. Por favor tente novamente.\n");
            fgets(line, NOME, stdin);
            tira_new_line_char(line);
        }
    }
    lpdi res=encontra_pdi(cidades, line);
    if (pesquisa_lista_pdi_fav(lista, res)==NULL) {
        printf("O PDI nao pertence a sua lista de favoritos.\n");
        return 0;
    }
    if(pesquisa_lista_pdi_fav(lista, res)!=NULL) {
        elimina_lista_pdi_fav(lista, res);
        if(pesquisa_lista_aux_user(res->lista_apont_users, utilizador)!=NULL) {
            elimina_lista_aux_user(res->lista_apont_users, utilizador);
        }
    }
    return 1;
}

int puts_cid_fav(lfavCid lista, List utilizador, lCidade cidades) {
    if (conta_elementos_cid_fav(lista)==3) {
        printf("Nao pode inserir mais cidades favoritas.\n");
        return 0;
    }
    char line[NOME];
    printf("Qual o Local que pretende escolher como favorito?\n");
    fgets(line, NOME, stdin);
    tira_new_line_char(line);
    if (pesquisa_lista(cidades, line)==NULL) {
        if(!strcmp(line, "")) {
            printf("Nenhum Local inserido. Por favor, tente novamente.\n");
            return 0;
        }
        while(pesquisa_lista(cidades, line)==NULL) {
            if(!strcmp(line, "")) {
                printf("Nenhum nome inserido. Por favor, tente novamente.\n");
                return 0;
            }
            printf("Local nao encontrado. Por favor tente novamente.\n");
            fgets(line, NOME, stdin);
            tira_new_line_char(line);
        }
    }
    if(pesquisa_lista(cidades, line)!=NULL) {
        lCidade res=pesquisa_lista(cidades, line);
        if (pesquisa_lista_cid_fav(lista, res)) {
            printf("Local ja presente na lista de favoritos.\n");
            return 0;
        }
        insere_lista_cid_fav(lista, res);
        if (pesquisa_lista_aux_user(res->lista_apont_users, utilizador)==NULL) {
            insere_lista_aux_user(res->lista_apont_users, utilizador);
        }
    }
    return 1;
}

int remove_cid_fav(lfavCid lista, List utilizador, lCidade cidades) {
    if (conta_elementos_cid_fav(lista)==0) {
        printf("A sua lista de Locais favoritos esta vazia. Nao pode remover favoritos.\n");
        return 0;
    }
    char line[NOME];
    printf("Qual o Local que pretende remover dos seus favorito?\n");
    fgets(line, NOME, stdin);
    tira_new_line_char(line);
    if (pesquisa_lista(cidades, line)==NULL) {
        if(!strcmp(line, "")) {
            printf("Nenhum Local reconhecido. Por favor, tente novamente.\n");
            return 0;
        }
        while(pesquisa_lista(cidades, line)==NULL) {
            if(!strcmp(line, "")) {
                printf("Nenhum nome inserido. Por favor, tente novamente.\n");
                return 0;
            }
            printf("Local nao encontrado. Por favor tente novamente.\n");
            fgets(line, NOME, stdin);
            tira_new_line_char(line);
        }
    }
    lCidade res=pesquisa_lista(cidades, line);
    if (pesquisa_lista_cid_fav(lista, res)==NULL) {
        printf("O Local nao pertence a sua lista de favoritos.\n");
        return 0;
    }
    if(pesquisa_lista_cid_fav(lista, res)!=NULL) {
        elimina_lista_cid_fav(lista, res);
        if(pesquisa_lista_aux_user(res->lista_apont_users, utilizador)!=NULL) {
            elimina_lista_aux_user(res->lista_apont_users, utilizador);
        }
    }
    return 1;
}
