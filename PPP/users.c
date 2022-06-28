#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hf_lists.h"

int verifica_morada(char* morada) {
    char *aux = (char *) malloc((strlen(morada)+1)*sizeof(char));
    strcpy(aux, morada);
    if(strchr(morada, '|') || (strlen(morada)<=8) || strchr(morada, '\t')) {
        return 0;
    }
    return 1;
}

int morada(char* morada) {
    char line[MORADA];
    printf("Insira a sua Morada: ");
    fgets(line, MORADA, stdin);
    tira_new_line_char(line);
    if (!verifica_morada(line)) {
        if(!strcmp(line, "")) {
            printf("Nenhum morada inserida. Por favor, tente novamente.\n");
            return 0;
        }
        while(!verifica_morada(line)) {
            if(!strcmp(line, "")) {
                printf("Nenhum morada inserida. Por favor, tente novamente.\n");
                return 0;
            }
            printf("Introduza de novo uma morada valida (Nao pode ser demasiado pequena):\n");
            fgets(line, MORADA, stdin);
            tira_new_line_char(line);
        }
    }
    strcpy(morada, line);
    return 1;
}

int verifica_nome(char* nome_user) {
    char *aux = (char *) malloc((strlen(nome_user)+1)*sizeof(char));
    strcpy(aux, nome_user);
    if(!strcmp(nome_user, "")) {
        return 0;
    }
    for (int i=0; aux[i]!='\0'; ++i) {
        if((aux[i]<'A' || aux[i]>'Z')&&(aux[i]<'a' || aux[i]>'z')&&(aux[i]!=' ')) {
                return 0;
        }
    }
    return 1;
}

int verifica_delimitador(char *cadeia) {
    char *aux = (char *) malloc((strlen(cadeia)+1)*sizeof(char));
    strcpy(aux, cadeia);
    int conta=0;
    for (int i=0; aux[i]!='\0'; ++i) {
        if (aux[i]=='/') {
            conta+=1;
        }
    }
    if (conta==2) {
        return 1;
    }
    return 0;
}

void split_string_data(char* line, char **vec) {
    int init_size = strlen(line);
    char *copia = (char *) malloc(sizeof(char)*(init_size+1));
    strcpy(copia, line);
    char *ptr = strtok(copia, "/\n");
    char **p=vec;
	while(ptr != NULL) {
        *p=ptr;
		ptr = strtok(NULL, "/\n");
        p+=1;
	}
}

int verifica_data(char* data) {
    char* aux = (char*) malloc((strlen(data)+1)*sizeof(char));
    strcpy(aux, data);
    char **vec = (char **) malloc(3*sizeof(char *));
    if (strlen(aux)!=10) {
        return 0;
    }
    if (!verifica_delimitador(aux)) {
        return 0;
    }
    split_string_data(aux, vec);
    int dia=atoi(*vec);
    int mes=atoi(*(vec+1));
    int ano=atoi(*(vec+2));
    free(vec);
    if (ano<1920 || ano>2019) {
        return 0;
    }
    if (mes<1 || mes>12) {
        return 0;
    }
    if (mes==2 && ano%4!=0 && (dia<1 || dia>28)) {                      //FEVEREIRO -> ANO NÃO BISSEXTO
        return 0;
    }
    if (mes==2 && ano%4==0 && (dia<1 || dia>29)) {                      //FEVEREIRO -> ANO BISSEXTO
        return 0;
    }
    if ((mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12) && (dia<1 || dia>31)) { //31 DIAS
        return 0;
    }
    if ((mes==4 || mes==6 || mes==9 || mes==11) && (dia<1 || dia>30)) {                                 //30 DIAS
        return 0;
    }
    return 1;
}

int verifica_num(char* phoneNum) {
    char* aux = (char*) malloc((strlen(phoneNum)+1)*sizeof(char));
    strcpy(aux, phoneNum);
    split_str(aux);
    int len=strlen(aux);
    if (len!=9) {
        return 0;
    }
    for (int i=0; aux[i]!='\0'; ++i) {
        if (aux[i]<'0' || aux[i]>'9' || aux[0]!='9') {
            return 0;
        }
    }
    int n=atoi(aux);
    return n;
}

USER inicia_user() {
    USER var;
    strcpy(var.nome_utilizador, "");
    strcpy(var.morada, "");
    strcpy(var.data_de_nascimento, "");
    strcpy(var.numero_telefone, "");
    var.Hot=NULL;
    var.lista_cid=NULL;
    var.lista_pdi=NULL;
    var.viagem=NULL;
    return var;
}

USER cria_user(char* nomeUSER, char* Address, char* birthDay, char* phoneNum) {
    USER var;
    strcpy(var.nome_utilizador, nomeUSER);
    strcpy(var.morada, Address);
    strcpy(var.data_de_nascimento, birthDay);
    strcpy(var.numero_telefone, phoneNum);
    var.Hot=NULL;
    var.lista_cid=cria_lista_cid_fav();
    var.lista_pdi=cria_lista_pdi_fav();
    var.viagem=cria_lista_new_cid();
    return var;
}

List cria_listaU() {
    USER nulo=inicia_user();
    List aux=(List) malloc (sizeof(List_node));
    if (aux) {
        aux->info=nulo;
        aux->next=NULL;
    }
    return aux;
}


int lista_vaziaU(List lista) {           /*Vazia se tiver apenas o header*/
    return (!lista->next) ? 1 : 0;
}

void procura_listaU(List lista, USER chave, List *ant, List *actual) {
    *ant = lista;
    *actual = lista->next;
    while((*actual)!=NULL && (strcmp(((*actual)->info).nome_utilizador, chave.nome_utilizador) < 0)) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
    if ((*actual) != NULL && (strcmp(((*actual)->info).nome_utilizador, chave.nome_utilizador) != 0)) {
        *actual = NULL;
    }
}

void procura_listaU2(List lista, char *phoneNum, List *ant, List *actual) {                     //Usado para o LOGIN
    *ant = lista;
    *actual = lista->next;
    while((*actual)!=NULL && (strcmp(((*actual)->info).numero_telefone, phoneNum) != 0)) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
    if ((*actual) != NULL && (strcmp(((*actual)->info).numero_telefone, phoneNum) != 0)) {
        *actual = NULL;
    }
}

void imprime_listaU(List list) {
    List aux = list->next;
    while (aux) {
        printf("NOME: %s\n", (aux->info).nome_utilizador);
        printf("MORADA: %s\n", (aux->info).morada);
        printf("DATA DE NASCIMENTO: %s\n", (aux->info).data_de_nascimento);
        printf("NUMERO DE TELEFONE: %s\n\n", (aux->info).numero_telefone);
        aux=aux->next;
    }
    printf("\n");
}

List destroi_listaU(List lista) {
    while(!lista_vaziaU(lista)) {
        List aux=lista;
        lista=lista->next;
        free(aux);
    }
    free(lista);
    return NULL;
}

void insere_listaU(List lista, USER chave) {
    List no = (List) malloc(sizeof(List_node));
    if (no) {
        List ant, inutil;
        no->info = chave;
        procura_listaU(lista, chave, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}

void elimina_listaU(List lista, USER chave) {
    List ant, actual;
    procura_listaU(lista, chave, &ant, &actual);
    if (actual) {
        ant->next = actual->next;
        free(actual);
    }
}

void elimina_listaU2(List lista, USER chave) {
    List ant, actual;
    procura_listaU2(lista, chave.numero_telefone, &ant, &actual);
    if (actual) {
        ant->next = actual->next;
        free(actual);
    }
}

List pesquisa_listaU(List lista, USER chave) {
    List ant, actual;
    procura_listaU(lista, chave, &ant, &actual);
    return actual;
}

List pesquisa_listaU2(List lista, char* phoneNum) {                 //Usado para o LOGIN
    List ant, actual;
    procura_listaU2(lista, phoneNum, &ant, &actual);
    return actual;
}

int conta_elementosU(List lista) {
    List aux=lista->next;
    int conta=0;
    while(aux) {
        aux=aux->next;
        conta+=1;
    }
    return conta;
}

int nome(char* nome) {
    char nome_utilizador[NOME];
    printf("Insira o seu nome: ");
    fgets(nome_utilizador, NOME, stdin);
    tira_new_line_char(nome_utilizador);
    if (!verifica_nome(nome_utilizador)) {
        if(!strcmp(nome_utilizador, "")) {
            printf("Nenhum nome inserido. Por favor, tente novamente.\n");
            return 0;
        }
        while(!verifica_nome(nome_utilizador)) {
            if(!strcmp(nome_utilizador, "")) {
                printf("Nenhum nome inserido. Por favor, tente novamente.\n");
                return 0;
            }
            printf("Introduza de novo um nome valido (sem caracteres especiais):\n");
            fgets(nome_utilizador, NOME, stdin);
            tira_new_line_char(nome_utilizador);
        }
    }
    strcpy(nome, nome_utilizador);
    return 1;
}

int data(char* data) {
    char data_de_nascimento[NUMERO];
    printf("Insira a sua data de nascimento (no formato DD/MM/AAAA): ");
    fgets(data_de_nascimento, NUMERO, stdin);
    tira_new_line_char(data_de_nascimento);
    if (!verifica_data(data_de_nascimento)) {
        if(!strcmp(data_de_nascimento, "")) {
            printf("Nenhuma data inserida. Por favor, tente novamente.\n");
            return 0;
        }
        while(!verifica_data(data_de_nascimento)) {
            if(!strcmp(data_de_nascimento, "")) {
                printf("Nenhuma data inserida. Por favor, tente novamente.\n");
                return 0;
            }
            printf("Introduza de novo uma data valida no formato DD/MM/AAAA:\n");
            fgets(data_de_nascimento, NUMERO, stdin);
            tira_new_line_char(data_de_nascimento);
        }
    }
    strcpy(data, data_de_nascimento);
    return 1;
}

int numero(List lista, char* number) {
    char numero_telefone[NUMERO];
    printf("Insira o seu numero de telemovel: ");
    fgets(numero_telefone, NUMERO, stdin);
    tira_new_line_char(numero_telefone);
    if (!verifica_num(numero_telefone)) {
        if(!strcmp(numero_telefone, "")) {
            printf("Nenhum numero de telemovel inserido. Por favor, tente novamente.\n");
            return 0;
        }
        while(!verifica_num(numero_telefone)) {
            if(!strcmp(numero_telefone, "")) {
                printf("Nenhum numero de telemovel inserido. Por favor, tente novamente.\n");
                return 0;
            }
            printf("Introduza de novo um numero de telemovel valido:\n");
            fgets(numero_telefone, NUMERO, stdin);
            tira_new_line_char(numero_telefone);
        }
    }
    if(pesquisa_listaU2(lista, numero_telefone)!=NULL) {
        printf("Utilizador ja existe. A Abortar operacao...\nSe pretende usar a aplicacao efectue o login por favor.\n");
        return 0;
    }
    strcpy(number, numero_telefone);
    return 1;
}

List acrescenta_User(List lista) {
    char nome_utilizador[NOME];
    int a=0, b=0, c=0, m=0;
    a=nome(nome_utilizador);
    if(a==0) {
        return NULL;
    }
    char linha[MORADA];
    m=morada(linha);
    if(m==0) {
        return NULL;
    }
    char data_de_nascimento[NUMERO];
    b=data(data_de_nascimento);
    if(b==0) {
        return NULL;
    }
    char numero_telefone[NUMERO];
    c=numero(lista, numero_telefone);
    if(c==0) {
        return NULL;
    }
    USER var=cria_user(nome_utilizador, linha, data_de_nascimento, numero_telefone);
    insere_listaU(lista, var);
    List utilizador=pesquisa_listaU(lista, var);
    return utilizador;
}

void altera_morada(List user) {
    char line[MORADA];
    int n=morada(line);
    if(n==0) {
        return;
    }
    strcpy(user->info.morada, line);
}

List altera_nome(List user, List lista) {
    char line[NOME];
    int n=nome(line);
    if(n==0) {
        return user;
    }
    strcpy(user->info.nome_utilizador, line);
    USER utilizador=user->info;
    elimina_listaU2(lista, utilizador);
    insere_listaU(lista, utilizador);
    user=pesquisa_listaU2(lista, utilizador.numero_telefone);
    return user;
}

void altera_data_nascimento(List user) {
    char line[NUMERO];
    int n=data(line);
    if(n==0) {
        return;
    }
    strcpy(user->info.data_de_nascimento, line);
}

void altera_numero(List user, List lista) {
    char line[NUMERO];
    int n=numero(lista, line);
    if(n==0) {
        return;
    }
    strcpy(user->info.numero_telefone, line);
}
