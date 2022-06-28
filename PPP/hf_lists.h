#ifndef HF_LISTS_H_INCLUDED
#define HF_LISTS_H_INCLUDED

#define SIZE 500
#define BUFFERSIZE 50
#define NOME 100
#define MORADA 200
#define SMALLBUFFER 5
#define NUMERO 15

typedef struct util* lutil;

typedef struct pdi* lpdi;
typedef struct pdi {
    char nome_pdi[100];          //Nome
    char descricao[500];        //Descrição
    char horario[100];          //Horario
    lutil lista_apont_users;
    lpdi proximo;               //Ponteiro pra a próxima lista ligada
} Ponto_de_Interesse;

//Lista de Cidades
typedef struct cidade* lCidade;
typedef struct cidade {
	char nome[100];              //Nome da Cidade
	lpdi lista_pdi;             //Ponteiro para a Lista Ligada de PDI's
    lutil lista_apont_users;
    lCidade proximo;            //Ponteiro para a próxima cidade
} Cidade;

//Org
typedef struct newPDI* lnewPDI;
typedef struct newPDI {
    lpdi pdi_list;
    lnewPDI next;
} LISTA_DE_PDI;

typedef struct newCidade* lnewCidade;
typedef struct newCidade {
    lCidade city;
    lnewPDI pdi_list;
    lnewCidade next;
} LISTA_DE_CIDADES;

typedef struct favPDI* lfavPDI;                         //Lista Ligada de apontadores
typedef struct favPDI {
	lpdi pdi_fav;
	lfavPDI proximo;
} PDI_Favoritos;

typedef struct favCid* lfavCid;                         //Lista Ligada de Apontadores
typedef struct favCid {
	lCidade cid_fav;
	lfavCid proximo;
} CID_Favoritas;

//Lista de Utilizadores
typedef struct {
    char nome_utilizador[100];               //Nome do Utilizador
    char morada[200];                       //Morada do Utilizador
    char data_de_nascimento[11];            //Data de Nascimento do Utilizador
    char numero_telefone[10];               //Número de Telefone do Utilizador
    lpdi Hot;                               //lpdi* HOT;
    lfavCid lista_cid;
    lfavPDI lista_pdi;
    lnewCidade viagem;
} USER;

typedef struct lnode* List;
typedef struct lnode {
	USER info;
	List next;
} List_node;

typedef struct util* lutil;                         //Lista Ligada de Apontadores
typedef struct util {
	List utilizador;
	lutil next;
} LIST_USER;


lCidade cria_lista();
int lista_vazia(lCidade );
void procura_lista(lCidade , char* , lCidade* , lCidade* );
void imprime_lista(lCidade );
lCidade destroi_lista(lCidade );
void insere_lista(lCidade , char* , lpdi );
void elimina_lista(lCidade , char* );
lCidade pesquisa_lista(lCidade , char* );
int conta_elementos(lCidade );

lpdi cria_lista_pdi();
int lista_vazia_pdi(lpdi );
void procura_lista_pdi(lpdi , char* , lpdi* , lpdi* );
void imprime_lista_pdi(lpdi );
lpdi destroi_lista_pdi(lpdi );
void insere_lista_pdi(lpdi , char* , char* , char* );
void elimina_lista_pdi(lpdi , char* );
lpdi pesquisa_lista_pdi(lpdi , char* );
int conta_elementos_pdi(lpdi );


//Funções que manipulam listas ligadas de Utilizadores (List):
//(Funções adaptadas das Aulas Práticas)

USER inicia_user();
USER cria_user(char* , char* , char* , char* );
List cria_listaU();
int lista_vaziaU(List );
void procura_listaU(List , USER , List* , List* );
void procura_listaU2(List , char *, List* , List* );
void imprime_listaU(List );
List destroi_listaU(List );
void insere_listaU(List , USER );
void elimina_listaU(List , USER );
void elimina_listaU2(List , USER );
List pesquisa_listaU(List , USER );
List pesquisa_listaU2(List , char* );
int conta_elementosU(List );


//Funções que manipulam Listas Ligadas de Apontadores (lfavPDI):
//(Funções adaptadas das Aulas Práticas)

lfavPDI cria_lista_pdi_fav();
int lista_vazia_pdi_fav(lfavPDI );
void procura_lista_pdi_fav(lfavPDI , lpdi , lfavPDI* , lfavPDI* );
void imprime_lista_pdi_fav(lfavPDI );
lfavPDI destroi_lista_pdi_fav(lfavPDI );
void insere_lista_pdi_fav(lfavPDI , lpdi );
void elimina_lista_pdi_fav(lfavPDI , lpdi );
lfavPDI pesquisa_lista_pdi_fav(lfavPDI , lpdi );
int conta_elementos_pdi_fav(lfavPDI );


//Funções que manipulam Listas Ligadas de Apontadores (lfavCid):
//(Funções adaptadas das Aulas Práticas)

 lfavCid cria_lista_cid_fav();
int lista_vazia_cid_fav(lfavCid );
void procura_lista_cid_fav(lfavCid , lCidade , lfavCid* , lfavCid* );
void imprime_lista_cid_fav(lfavCid );
lfavCid destroi_lista_cid_fav(lfavCid );
void insere_lista_cid_fav(lfavCid , lCidade );
void elimina_lista_cid_fav(lfavCid , lCidade );
lfavCid pesquisa_lista_cid_fav(lfavCid , lCidade );
int conta_elementos_cid_fav(lfavCid );


//Funções que manipulam Listas Ligadas de Apontadores (lutil):
//(Funções adaptadas das Aulas Práticas)

lutil cria_lista_aux_user();
int lista_vazia_aux_user(lutil );
void procura_lista_aux_user(lutil , List , lutil* , lutil* );
void insere_lista_aux_user(lutil , List );
void elimina_lista_aux_user(lutil , List );
lutil pesquisa_lista_aux_user(lutil , List );
int conta_elementos_aux_user(lutil );
void imprime_lista_aux_user(lutil );
void imprime_apont_pdi(lpdi );
void imprime_apont_cid(lCidade );


//Funções que manipulam Listas Ligadas de Apontadores (lnewPDI):
//(Funções adaptadas das Aulas Práticas)

lnewPDI cria_lista_new_pdi();
int lista_vazia_new_pdi(lnewPDI );
void procura_lista_new_pdi(lnewPDI , lpdi , lnewPDI* , lnewPDI* );
void insere_lista_new_pdi(lnewPDI , lpdi );
void elimina_lista_new_pdi(lnewPDI , lpdi );
lnewPDI pesquisa_lista_new_pdi(lnewPDI , lpdi );
int conta_elementos_new_pdi(lnewPDI );
void imprime_lista_new_pdi(lnewPDI );

//Funções que manipulam Listas Ligadas de Apontadores (lnewCid):
//(Funções adaptadas das Aulas Práticas)

lnewCidade cria_lista_new_cid();
int lista_vazia_new_cid(lnewCidade );
void procura_lista_new_cid(lnewCidade , lCidade , lnewCidade* , lnewCidade* );
void insere_lista_new_cid(lnewCidade , lCidade , lnewPDI );
void insere_lista_new_cid_sem_pdi(lnewCidade , lCidade );
void elimina_lista_new_cid(lnewCidade , lCidade );
lnewCidade pesquisa_lista_new_cid(lnewCidade , lCidade );
int conta_elementos_new_cid(lnewCidade );
void organiza(lCidade , lnewCidade );
void imprime_lista_new_cid(lnewCidade );
lnewCidade destroi_lista_new_cid(lnewCidade );

//Funções Auxiliares:
void procura_lista_new_pdi_2(lnewPDI , lpdi , lnewPDI* , lnewPDI* );
lnewPDI pesquisa_lista_new_pdi_2(lnewPDI , lpdi );
void insere_lista_new_pdi_2(lnewPDI , lpdi );
void procura_lista_new_cid_2(lnewCidade , lCidade , lnewCidade* , lnewCidade* );
void insere_lista_new_cid_sem_pdi_2(lnewCidade , lCidade );
lnewCidade pesquisa_lista_new_cid_2(lnewCidade , lCidade );


//Verificação de dados inseridos pelo Utilizador durante o seu Registo:
//(Funções usadas na função acrescenta_User2)

int verifica_nome(char* );
int verifica_delimitador(char *);
void split_string_data(char* , char **);
int verifica_data(char* );
int verifica_num(char* );
int verifica_morada(char* );

void acrescenta_User2(List );

//Funções que modificam as preferências de cada utilizador
//PDI Hot e lista de favoritos:
int insere_pdi_hot(List , lCidade );
int remove_pdi_hot(List , lCidade );
int puts_pdi_fav(lfavPDI , List , lCidade );
int remove_pdi_fav(lfavPDI , List , lCidade );
int puts_cid_fav(lfavCid , List , lCidade );
int remove_cid_fav(lfavCid , List , lCidade );

//Construção da Viagem (para cada utilizador):
void insere_viagem_cidades(lnewCidade , List );
void insere_viagem_pdi_hot(lnewCidade , lnewCidade , List );
void insere_viagem_pdis_favoritos(lnewCidade , lnewCidade , List );
void insere_viagem_pdis_populares(lnewCidade , lnewCidade , List );
void cria_viagem_i(lnewCidade , List );


//Avaliação da Viagem gerada automaticamente:
double percentagem_favoritos(lnewCidade , List );
double percentagem_hot(lnewCidade , List );
int conta_votos_users(lnewCidade );
double percentagem_preferncias_pdi(lnewCidade , lnewCidade );
void avalia(lnewCidade , lnewCidade , List );

//Outras Funções:
void imprimir(lCidade );
lpdi encontra_pdi(lCidade , char* );


//Funções que envolvem ficheiros:
void split_string(char* , char **);
char *split_str(char* );
void split_cid(char* , lfavCid , lCidade , List );
void split_pdi(char* , lfavPDI , lCidade , List );
void carrega_Users_2(List , lCidade );
void carrega_listas(lCidade );
void tentativa_1(lfavCid , char** );
void tentativa_2(lfavPDI , char** );
void puts_Users(List );

void delay_1();

//Registo de Novo UTILIZADOR:
int nome(char* );
int data(char* );
int numero(List , char* );
int morada(char* );
List acrescenta_User(List );

//Altera dados do utilizador:
void altera_morada(List );
List altera_nome(List , List );
void altera_data_nascimento(List );
void altera_numero(List , List );

//PDI's favoritos
void procura_lista_pdi_fav_i(lfavPDI , lpdi , lfavPDI* , lfavPDI* );
lfavPDI pesquisa_lista_pdi_fav_i(lfavPDI , lpdi );

//Cidades favoritas
void procura_lista_cid_fav_i(lfavCid , lCidade , lfavCid* , lfavCid* );
lfavCid pesquisa_lista_cid_fav_i(lfavCid , lCidade );

//lnewCid
void procura_lista_new_cid_i(lnewCidade , lCidade , lnewCidade* , lnewCidade* );
lnewCidade pesquisa_lista_new_cid_i(lnewCidade , lCidade );

//lnewPDI
void procura_lista_new_pdi_i(lnewPDI , lpdi , lnewPDI* , lnewPDI* );
lnewPDI pesquisa_lista_new_pdi_i(lnewPDI , lpdi );

//lutil
void procura_lista_aux_user_i(lutil , List , lutil* , lutil* );
lutil pesquisa_lista_aux_user_i(lutil , List );


//ALGORITMO DE ORDENAÇÃO
void ordena_new_cid(lnewCidade );
void ordena_new_pdi(lnewPDI );
void ordena(lnewCidade );

char* tira_new_line_char(char* );

void visualiza_pdis_one(lCidade );
void visualiza_locais(lCidade );

#endif // HF_LISTS_H_INCLUDED
