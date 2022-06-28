#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"
#include <time.h>

void delay_1() {
    char line[SMALLBUFFER]="000";
    while(strcmp(line, "")!=0) {
        printf("\nPrima ENTER para continuar...\n\n");
        fgets(line, SMALLBUFFER, stdin);
        tira_new_line_char(line);
    }
}

int main() {
    char* line = (char *) calloc(BUFFERSIZE, sizeof(char));
    char* numero = (char*) calloc(NUMERO, sizeof(char));
    int n;
    int troca=0;
    lCidade lista=cria_lista();
    carrega_listas(lista);
    List lista_user=cria_listaU();
    carrega_Users_2(lista_user, lista);
    List user=NULL;
    lnewCidade nova_lista=cria_lista_new_cid();
    organiza(lista, nova_lista);
    while(1) {
        system("cls");
        printf("\t\tPROJECTO CONHECER PORTUGAL\n\n");
        printf("1 - Visualizar lista de utilizadores.\n");
        printf("2 - Registar.\n");
        printf("3 - Login.\n");
        printf("4 - Sair.\n\n");
        fgets(line, BUFFERSIZE, stdin);
        tira_new_line_char(line);
        n=atoi(line);
        switch(n) {
            case 1: system("cls"); imprime_listaU(lista_user); delay_1(); break;
            case 2: system("cls"); user=acrescenta_User(lista_user); delay_1();
            if(user==NULL) {
                break;
            }
            case 3: system("cls");
                if(user==NULL) {
                    printf("Insira o seu numero de telefone: ");
                    fgets(numero, NUMERO, stdin);
                    numero=tira_new_line_char(numero);
                    if (!pesquisa_listaU2(lista_user, numero)) {
                        printf("Utilizador nao encontrado.\nSe pretende utilizar os nossos servicos registe-se.\n");
                        strcpy(numero, ""); delay_1();
                        break;
                    }
                    user=pesquisa_listaU2(lista_user, numero);
                }
                while(user!=NULL) {
                    system("cls");
                    printf("Bem-vindo(a) %s\n\n", user->info.nome_utilizador);
                    printf("1 - Visualizar lista de Locais e respectivos PDI's.\n");
                    printf("2 - Visualizar lista de Locais e PDI's por popularidade.\n");
                    printf("3 - Visualiza lista de Locais (sem respectivos PDI's)\n");
                    printf("4 - Visualizar PDI's de um Local Especifico.\n");
                    printf("5 - Preferencias do Utilizador.\n");
                    printf("6 - Viagem.\n");
                    printf("7 - Alterar dados do Utilizador.\n");
                    printf("8 - Eliminar Conta.\n");
                    printf("9 - Logout\n\n");
                    fgets(line, BUFFERSIZE, stdin);
                    tira_new_line_char(line);
                    n=atoi(line);
                    switch(n) {
                        case 1: system("cls"); imprimir(lista); delay_1(); break;
                        case 2: if(troca) {
                                    ordena(nova_lista);
                                    troca=0;
                                }
                                system("cls"); imprime_lista_new_cid(nova_lista); delay_1(); break;
                        case 3: system("cls"); visualiza_locais(lista); delay_1(); break;
                        case 4: system("cls"); visualiza_pdis_one(lista); delay_1(); break;
                        case 5:
                            do {
                                system("cls");
                                printf("Bem-vindo(a) %s\n\n", user->info.nome_utilizador);
                                printf("1 - Insere/Altera PDI Hot.\n");
                                printf("2 - Remove PDI Hot.\n\n");
                                printf("3 - Insere Local favorito.\n");
                                printf("4 - Remove Local favorito.\n\n");
                                printf("5 - Insere PDI favorito.\n");
                                printf("6 - Remove PDI favorito.\n\n");
                                printf("7 - Visualiza PDI Hot.\n");
                                printf("8 - Visualiza lista de Locais favoritos.\n");
                                printf("9 - Visualiza lista de PDI favoritos.\n\n");
                                printf("10 - Voltar\n\n");
                                fgets(line, BUFFERSIZE, stdin);
                                tira_new_line_char(line);
                                n=atoi(line);
                                switch(n) {
                                    case 1: system("cls"); troca+=insere_pdi_hot(user, lista); delay_1(); break;
                                    case 2: system("cls"); troca+=remove_pdi_hot(user, lista); delay_1(); break;
                                    case 3: system("cls"); troca+=puts_cid_fav(user->info.lista_cid, user, lista); delay_1(); break;
                                    case 4: system("cls"); troca+=remove_cid_fav(user->info.lista_cid, user, lista); delay_1(); break;
                                    case 5: system("cls"); troca+=puts_pdi_fav(user->info.lista_pdi, user, lista); delay_1(); break;
                                    case 6: system("cls"); troca+=remove_pdi_fav(user->info.lista_pdi, user, lista); delay_1(); break;
                                    case 7: system("cls"); printf("PDI HOT: %s\n", user->info.Hot->nome_pdi); delay_1(); break;
                                    case 8: system("cls"); imprime_lista_cid_fav(user->info.lista_cid); delay_1(); break;
                                    case 9: system("cls"); imprime_lista_pdi_fav(user->info.lista_pdi); delay_1(); break;
                                    default: break;
                                }
                            } while(n!=10);
                            break;
                        case 6: if(conta_elementos_cid_fav(user->info.lista_cid)!=3) {
                                    system("cls");
                                    printf("Opcao bloqueada.\nEsta opcao so sera desbloqueada quando existir 3 Locais na sua lista de favoritos.\n"); delay_1();
                                    break;
                                }
                                do {
                                system("cls");
                                printf("Bem-vindo(a) %s\n\n", user->info.nome_utilizador);
                                printf("1 - Criar Viagem.\n");
                                printf("2 - Visualizar Viagem.\n");
                                printf("3 - Avaliar viagem.\n");
                                printf("4 - Voltar\n\n");
                                fgets(line, BUFFERSIZE, stdin);
                                tira_new_line_char(line);
                                n=atoi(line);
                                switch(n) {
                                    case 1: system("cls");
                                            if(troca) {
                                                ordena(nova_lista);
                                                troca=0;
                                            }
                                            cria_viagem_i(nova_lista, user); printf("Viagem Criada com Sucesso.\n"); delay_1(); break;

                                    case 2: system("cls");
                                            if(lista_vazia_new_cid(user->info.viagem)) {
                                                printf("Nao tem uma viagem criada.\n"); delay_1();
                                                break;
                                            }
                                            imprime_lista_new_cid(user->info.viagem); delay_1(); break;

                                    case 3: system("cls");
                                            if(lista_vazia_new_cid(user->info.viagem)) {
                                                printf("Nao tem uma viagem criada.\n"); delay_1();
                                                break;
                                            }
                                            avalia(user->info.viagem, nova_lista, lista_user); delay_1(); break;
                                    default: break;
                                }
                            } while(n!=4);
                            break;
                        case 7: do {
                                system("cls");
                                printf("Bem-vindo(a) %s\n\n", user->info.nome_utilizador);
                                printf("1 - Alterar Nome de Utilizador.\n");
                                printf("2 - Alterar Morada.\n");
                                printf("3 - Alterar Data-de-Nascimento.\n");
                                printf("4 - Alterar Numero de Telemovel.\n");
                                printf("5 - Voltar\n\n");
                                fgets(line, BUFFERSIZE, stdin);
                                tira_new_line_char(line);
                                n=atoi(line);
                                switch(n) {
                                    case 1: system("cls"); user=altera_nome(user, lista_user); delay_1(); break;
                                    case 2: system("cls"); altera_morada(user); delay_1(); break;
                                    case 3: system("cls"); altera_data_nascimento(user); delay_1(); break;
                                    case 4: system("cls"); altera_numero(user, lista_user); delay_1(); break;
                                    default: break;
                                }
                            } while(n!=5);
                            break;
                        case 8:
                            system("cls");
                            printf("Tem a certeza que pretende eliminar a sua conta?\nResponda \"Sim\" ou \"Nao\".\n");
                            fgets(line, BUFFERSIZE, stdin);
                            tira_new_line_char(line);
                            while(strcmp(line, "Sim") || strcmp(line, "Nao")) {
                                if(!strcmp(line, "Nao")) {
                                    break;
                                }
                                if(!strcmp(line, "Sim")) {
                                    elimina_listaU2(lista_user, user->info);
                                    printf("Conta Elimindada com Sucesso.\n");
                                    delay_1();
                                    goto label;
                                    break;
                                }
                                fgets(line, BUFFERSIZE, stdin);
                                tira_new_line_char(line);
                            } break;
label:                  case 9: user=NULL; break;
                    }
                    if(user==NULL) {
                        break;
                    }
                } break;
            case 4: system("cls");
                    printf("Pretende Guardar os dados alterados?\nResponda \"Sim\" ou \"Nao\".\n");
                    fgets(line, BUFFERSIZE, stdin);
                    tira_new_line_char(line);
                    while(strcmp(line, "Sim") || strcmp(line, "Nao")) {
                        if(!strcmp(line, "Nao")) {
                            break;
                        }
                        if(!strcmp(line, "Sim")) {
                            puts_Users(lista_user);
                            printf("Guardado com Sucesso\n");
                            break;
                        }
                        fgets(line, BUFFERSIZE, stdin);
                        tira_new_line_char(line);
                    }
                    destroi_lista(lista); destroi_listaU(lista_user); destroi_lista_new_cid(nova_lista);
                    return 0;
            default: break;
        }
    }
}
