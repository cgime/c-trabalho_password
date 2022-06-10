#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define ARQ "senhas.dat"

typedef struct cadastro{
    char finalidade[21];
    char senha[21];
}CADASTRO;

FILE *fp;

int menu();
void get_senha( CADASTRO *pessoa);
void senha_manual(CADASTRO *pessoa);
void senha_automatica(CADASTRO *pessoa);
int oneisupper(char senha[]);
int oneislower(char senha[]);
int oneisespecial(char senha[]);
int oneisnumeric(char senha[]);
void inic();
void salvar_senha(CADASTRO pessoa);
int listar_finalidades();
void print_finalidades(CADASTRO pessoa, long int contador);
void mostrar_senha(int posicao);

void main(){
    puts("\n\n*****Bem vindo ao seu gerenciador de senhas!*****");
    inic();
    int fica_no_loop = TRUE;
    while (fica_no_loop){
        switch (menu()){
            case 1:{
                CADASTRO pessoa;
                puts("Digite a finalidade da senha: ");
                fflush(stdin);
                fgets(pessoa.finalidade, 20, stdin);
                get_senha(&pessoa);
                printf("\n\nSenha salva com sucesso!\n");
                printf("Finalidade: %s. --- senha: %s\n", pessoa.finalidade, pessoa.senha);
                salvar_senha(pessoa);
                break;
            }
            case 2:{ /* Apresentar senha salva*/
                printf("\n\n\n\n\nSenhas salvas pelo usuario:\n");
                printf("Escolha um numero relativo a senha que deseja visualizar:\n\n");
                int cont = listar_finalidades();
                mostrar_senha(escolher_finalidade(cont));
                break;
            }
            case 3:{ /* Apagar senha*/
                break;
            }
            case 4:{ /* Sair do programa*/
                fica_no_loop = FALSE;
                break;
            }
        }
        printf("\n\n");
        printf("Veio ate aqui\n");
    }
    puts("Programa encerrado!");
}

int menu(){ /*ESTÁ OK*/
    while(1){
        puts("\n\n*****MENU PRINCIPAL*****\n\n");
        puts("O que deseja fazer?");
        puts("1 - Criar nova senha");
        puts("2 - Apresentar senha salva");
        puts("3 - Apagar senha salva");
        puts("4 - Sair");
        int decisao;
        scanf(" %d", &decisao);
        if (decisao<1||decisao>4){
            puts("Entrada invalida. Tente novamente!");
            continue;
        }
        return decisao;
    }
}

void inic(){
    fp = fopen(ARQ, "r+b");
    if (fp == NULL){
        fp = fopen(ARQ, "w+b");
        if (fp == NULL){
            fprintf(stderr, "Nao foi possivel criar arquivo de dados!!!\n");
            exit(1);
        }
    }
    fclose(fp);
}

void get_senha(CADASTRO *pessoa){
    while(1){
        puts("Como deseja gerar sua senha?");
        puts("1 - Digitacao manual");
        puts("2 - Geracao automatica");
        int geracao;
        scanf(" %d", &geracao);
        if (geracao==1){
            senha_manual(pessoa);
            break;
        }
        else if (geracao==2){
            senha_automatica(pessoa);
            break;
        }
        else{
            puts("Entrada invalida. Tente novamente!");
            continue;
        }
    }
}

void senha_manual(CADASTRO *pessoa){ 
    /* Verifica se uma senha manual está de acordo com os parâmetros do programa */
    puts("Sua senha deve ter no minimo oito e no maximo 20 caracteres, pelo menos"
    "\numa letra maiuscula, pelo menos uma minuscula e um caractere numerico"
    "\nou especial (@, #, $, %%, ou &)");
    while(TRUE){
        int controle = FALSE;
        fflush(stdin);
        fgets(pessoa->senha, 20, stdin);
        if (strlen(pessoa->senha)<8){
            puts("Sua senha deve ter no minimo 8 caracteres.");
            controle = TRUE;
        }
        if (!oneisupper(pessoa->senha)){
            puts("Sua senha deve ter ao menos uma letra maiuscula!");
            controle = TRUE;
        }
        if (!oneislower(pessoa->senha)){
            puts("Sua senha deve ter ao menos uma letra minuscula!");
            controle = TRUE;
        }
        if (!oneisespecial(pessoa->senha) && !oneisnumeric(pessoa->senha)){
            puts("Sua senha deve possuir um caracter numerico ou um caractere especial!");
            controle = TRUE;
        }  

        if (controle){
            puts("Tente novamente!");
            continue;
        }
        else{
            break;
        }
    }
}

void senha_automatica(CADASTRO *pessoa){
    /* Cria uma senha automática segundo os parâmetros do problema */
    char senha_aux[21];
    //letra maiuscula - 40%; letra minuscula - 40%; numero + caracter especial - 20%
    srand((unsigned int)(time(NULL)));
    char numerosEespeciais[] = "0123456789@#$%&";
    char letras_ma[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char letras_mi[] = "abcdefghijklmnopqrstuvwxyz";
    int count_numEesp = 0;
    int count_letras_ma = 0;
    int count_letras_mi = 0;

    //letra maiuscula - 40%; letra minuscula - 40%; numero + caracter especial - 20%
    // para senha de 16 digitos: letra maiuscula - 6; letra minuscula - 7; numero + caracter especial - 3
    for (int i=0;i<16;i++){
        int aleatorio = rand() % 3;
        if (aleatorio==1 && count_letras_ma <7){
            senha_aux[i] = letras_ma[rand() % 26];
            count_letras_ma++;
        }
        else if (aleatorio==2 && count_letras_mi <6){
            senha_aux[i] = letras_mi[rand() % 26];
            count_letras_mi++;
        }
        else if (aleatorio==0 && count_numEesp <3){
            senha_aux[i] = numerosEespeciais[rand() % 15];
            count_numEesp++;
        }
        else{
            --i;
        }
    }
    senha_aux[16] = '\0';
    strcpy(pessoa->senha, senha_aux);
}

int oneisupper(char senha[]){ /*ESTÁ OK*/
    for (int i=0;senha[i]!='\0';i++){
        if (isupper(senha[i])){
            return TRUE;
        }
    }
    return FALSE;
}

int oneislower(char senha[]){ /*ESTÁ OK*/
    for (int i=0;senha[i] !='\0';i++){
        if(islower(senha[i])){
            return TRUE;
        }
    }
    return FALSE;
}

int oneisespecial(char senha[]){ /*ESTÁ OK*/
    for (int i=0;senha[i] !='\0';i++){
        if (senha[i]=='@'||senha[i]=='#'||senha[i]=='$'||senha[i]=='%'||senha[i]=='&'){
            return TRUE;
        }
    }
    return FALSE;
}

int oneisnumeric(char senha[]){ /*ESTÁ OK*/
    for (int i=0;senha[i]!='\0';i++){
        if (isdigit(senha[i])){
            return TRUE;
        }
    }
    return FALSE;
}

void salvar_senha(CADASTRO pessoa){ /* Ainda não finalizado*/
    fp = fopen(ARQ, "a+b");
    fseek(fp, 0L, SEEK_END);
    if (fwrite(&pessoa, sizeof(pessoa),1, fp) != 1){
        printf("Adicionar senha: Falhou a escrita do Registro!\n");
    }
    fclose(fp);
}

int listar_finalidades(){
    long int contador=0;
    CADASTRO info;
    fp = fopen(ARQ, "rb");
    rewind(fp);
    while (1){
        if (fread(&info, sizeof(CADASTRO), 1, fp) != 1){
            break;
        }
        print_finalidades(info, contador);
        contador++;
    }
    fclose(fp);
    return contador;
}

void print_finalidades(CADASTRO pessoa, long int contador){
    printf("%3d - %20s\n", contador+1, pessoa.finalidade);
}

int escolher_finalidade(int cont){
    int escolha = -1;
    while(escolha == -1){
        scanf(" %d", &escolha);
        if (escolha<0 || escolha>cont){
            puts("Valor invalido. Tente novamente!");
            continue;
        }
    }
    return escolha;
}

void mostrar_senha(int posicao){
    CADASTRO info;
    fp = fopen(ARQ, "rb");
    if (fp==NULL){
        puts("Erro na abertura do arquivo!");
        exit(1);
    }
    fseek(fp, (long) (posicao-1), SEEK_SET);
    if (fread(&info, sizeof(CADASTRO), 1, fp) != 1){
        puts("Nao foi possivel ler a informacao solicitada!");
        exit(1);
    }
    printf("Senha: %s\n", info.senha);
    puts("Pressione enter para continuar...");
    fflush(stdin);
    getchar();

    fclose(fp);
}

