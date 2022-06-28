#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"


void carrega_listas(lCidade lista) {                                //Carrega Locais e PDI's do ficheiro para Lista Ligada
    FILE *file = fopen("./locais.txt", "r");
    if (file==NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    char line[SIZE];
    lpdi aux=cria_lista_pdi();
    while (fgets(line, sizeof(line), file)!=NULL) {
         if(!strchr(line, '|') && (strcmp(line, "\n"))) {
            insere_lista(lista, split_str(line), aux);
            aux=cria_lista_pdi();
         }
         else if (strchr(line, '|') && (strcmp(line, "\n")!=0)) {
            char **vec = (char **) malloc(3*sizeof(char *));
            split_string(line, vec);
            insere_lista_pdi(aux, *vec, *(vec+1), *(vec+2));
         }
    }
    fclose(file);
}

void tentativa_1(lfavCid lista, char** res) {
    lfavCid aux=lista->proximo;
    int x;
    int n=strlen(aux->cid_fav->nome);
    (*res) = (char*) malloc((n+2)*sizeof(char));
    strcpy(*res, aux->cid_fav->nome);
    aux=aux->proximo;
    while(aux) {
        strcat(*res, "|");
        n=strlen(aux->cid_fav->nome);
        x=strlen(*res);
        *res = (char*) realloc(*res, (n+x+2)*sizeof(char));
        strcat(*res, aux->cid_fav->nome);
        aux=aux->proximo;
    }
}


void tentativa_2(lfavPDI lista, char** res) {
    lfavPDI aux=lista->proximo;
    int x;
    int n=strlen(aux->pdi_fav->nome_pdi);
    *res = (char*) malloc((n+2)*sizeof(char));
    strcpy(*res, aux->pdi_fav->nome_pdi);
    aux=aux->proximo;
    while(aux) {
        strcat(*res, "|");
        n=strlen(aux->pdi_fav->nome_pdi);
        x=strlen(*res);
        *res = (char*) realloc(*res, (n+x+2)*sizeof(char));
        strcat(*res, aux->pdi_fav->nome_pdi);
        aux=aux->proximo;
    }
}

//Carrega a lista de UTILIZADORES PARA O FICHEIRO
void puts_Users(List lista) {
    FILE *file = fopen("./utilizadores_doc.txt", "w");
    if (file==NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    char *cidades="";
    char *pdis="";
    List aux=lista->next;
    while (aux) {
        fprintf(file, "%s|%s|%s|%s\n", aux->info.nome_utilizador, aux->info.morada, aux->info.data_de_nascimento, aux->info.numero_telefone);
        if(aux->info.Hot==NULL) {
            fprintf(file, "\n");
        }
        if(aux->info.Hot!=NULL) {
            fprintf(file, "%s\n", aux->info.Hot->nome_pdi);
        }
        if(lista_vazia_cid_fav(aux->info.lista_cid)) {
            fprintf(file, "\n");
        }
        if(!lista_vazia_cid_fav(aux->info.lista_cid)) {
            tentativa_1(aux->info.lista_cid, &cidades);
            fprintf(file, "%s\n", cidades);
        }
        if(lista_vazia_pdi_fav(aux->info.lista_pdi)) {
            fprintf(file, "\n");
        }
        if(!lista_vazia_pdi_fav(aux->info.lista_pdi)) {
            tentativa_2(aux->info.lista_pdi, &pdis);
            fprintf(file, "%s\n", pdis);
        }
        aux=aux->next;
        cidades="";
        pdis="";
    }
    fclose(file);
}

void split_cid(char* line, lfavCid lista, lCidade cidades, List utilizador) {
    int n=strlen(line);
    char *copia=(char *) malloc(sizeof(char)*(n+1));
    strcpy(copia, line);
    char *ptr=strtok(copia, "|\n");
    lCidade aux=NULL;
	while(ptr!=NULL) {
        if(pesquisa_lista(cidades, ptr)==NULL) {
            printf("Houve um problema a carregar os ficheiros...\nOs dados podem nao estar correctos.\nPrima ENTER para continuar...\n"); delay_1();
        }
        else {
            aux=pesquisa_lista(cidades, ptr);
            insere_lista_cid_fav(lista, aux);
            if(pesquisa_lista_aux_user(aux->lista_apont_users, utilizador)==NULL) {
                insere_lista_aux_user(aux->lista_apont_users, utilizador);
            }
        }
        ptr=strtok(NULL, "|\n");
	}
}

void split_pdi(char* line, lfavPDI lista, lCidade cidades, List utilizador) {
    int n=strlen(line);
    char *copia=(char *) malloc(sizeof(char)*(n+1));
    strcpy(copia, line);
    char *ptr=strtok(copia, "|\n");
    lpdi aux=NULL;
	while(ptr!=NULL) {
        if(encontra_pdi(cidades, ptr)==NULL) {
            printf("Houve um problema a carregar os ficheiros...\nOs dados podem nao estar correctos.\nPrima ENTER para continuar...\n"); delay_1();
        }
        else {
            aux=encontra_pdi(cidades, ptr);
            insere_lista_pdi_fav(lista, aux);
            if(pesquisa_lista_aux_user(aux->lista_apont_users, utilizador)==NULL) {
                insere_lista_aux_user(aux->lista_apont_users, utilizador);
            }
        }
        ptr=strtok(NULL, "|\n");
	}
}

void carrega_Users_2(List lista, lCidade cidades) {                             //Alterado - Assume que os dados estao correctos
    FILE *file = fopen("./utilizadores_doc.txt", "r");
    if (file==NULL) {
        file=fopen("./utilizadores_doc.txt", "w");
        fclose(file);
        file=fopen("./utilizadores_doc.txt", "r");
        if (file==NULL) {
            perror("Error while opening the file.\n");
            exit(EXIT_FAILURE);
        }
    }
    lCidade teste=cidades;
    lpdi hot;
    List user;
    USER aux;
    char line[SIZE];
    while (fgets(line, sizeof(line), file)!=NULL) {
        char **vec = (char **) malloc(4*sizeof(char *));
        split_string(line, vec);
        aux = cria_user(*vec, *(vec+1), *(vec+2), *(vec+3));
        insere_listaU(lista, aux);
        user=pesquisa_listaU(lista, aux);
        if(strcmp(fgets(line, sizeof(line), file), "\n")) {
            split_str(line);
            hot=encontra_pdi(teste, line);
            if(hot==NULL) {
                printf("Houve um problema a carregar os ficheiros...\nOs dados podem nao estar correctos.\nPrima ENTER para continuar...\n"); delay_1();
            }
            else {
                user->info.Hot=hot;
                if(pesquisa_lista_aux_user(hot->lista_apont_users, user)==NULL) {
                    insere_lista_aux_user(hot->lista_apont_users, user);
                }
            }
        }
        if(strcmp(fgets(line, sizeof(line), file), "\n")) {
            split_cid(line, user->info.lista_cid, teste, user);
        }
        if(strcmp(fgets(line, sizeof(line), file), "\n")) {
            split_pdi(line, user->info.lista_pdi, teste, user);
        }
    }
    fclose(file);
}
