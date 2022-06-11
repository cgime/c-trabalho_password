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
int oneIsUpper(char senha[]);
int oneIsLower(char senha[]);
int oneIsEspecial(char senha[]);
int oneisnumeric(char senha[]);
void inic();
void salvar_senha(CADASTRO pessoa);
int listar_finalidades();
void print_finalidades(CADASTRO pessoa, long int contador);
void mostrar_finalidade_senha(int posicao);
void limpar_tela();
int isfempty();
void continuar();

void main(){
    limpar_tela();
    puts("\n\n*****Bem vindo ao seu gerenciador de senhas!*****");
    inic();
    if (isfempty()){
        puts("\nAinda nao ha senhas salvas!");
    }
    int fica_no_loop = TRUE;
    while (fica_no_loop){
        switch (menu()){
            case 1:{
                CADASTRO pessoa;
                limpar_tela();
                puts("Digite a finalidade da senha: ");
                fflush(stdin);
                fgets(pessoa.finalidade, 20, stdin);
                get_senha(&pessoa);
                salvar_senha(pessoa);
                printf("Senha salva com sucesso!\n");
                continuar();
                limpar_tela();
                break;
            }
            case 2:{ /* Apresentar senha salva*/
                limpar_tela();
                if (isfempty()){
                    puts("\nAinda nao ha senhas salvas!\n\n");
                    continuar();
                    limpar_tela();
                    break;
                }
                printf("Escolha um numero relativo a senha que deseja visualizar:\n\n");
                int cont = listar_finalidades();
                mostrar_finalidade_senha(escolher_finalidade(cont));
                continuar();
                limpar_tela();
                break;
            }
            case 3:{ /* Apagar senha*/
                limpar_tela();
                if (isfempty()){
                    puts("\nAinda nao ha senhas salvas!\n\n");
                    continuar();
                    limpar_tela();
                    break;
                }
                printf("Escolha um numero relativo a senha que deseja excluir:\n\n");
                int cont = listar_finalidades();
                apagar_senha(escolher_finalidade(cont));
                puts("Senha apagada com sucesso!");
                continuar();
                limpar_tela();
                break;
            }
            case 4:{ /* Sair do programa*/
                fica_no_loop = FALSE;
                break;
            }
            default:{
                limpar_tela();
                continue;
            }
        }
        printf("\n\n");
    }
    puts("Programa encerrado pelo usuario!\n\n");
}

int menu(){ /*Menu principal da aplicação*/
    puts("\n\n**********MENU PRINCIPAL**********");
    puts("Gerenciador de senhas versao 2022!\n\n");
    puts("O que deseja fazer?");
    puts("1 - Criar nova senha");
    puts("2 - Apresentar senha salva");
    puts("3 - Apagar senha salva");
    puts("4 - Sair");
    int decisao;
    fflush(stdin);
    scanf("%d", &decisao);
    return decisao;
}

void inic(){/*Verifica se existe o arquivo binário. Se não existir, cria um novo*/
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

void get_senha(CADASTRO *pessoa){/*Menu de escolhar para tipo de entrada de senha*/
    while(1){
        limpar_tela();
        puts("Como deseja gerar sua senha?");
        puts("1 - Digitacao manual");
        puts("2 - Geracao automatica");
        int geracao;
        scanf(" %d", &geracao);
        if (geracao==1){
            limpar_tela();
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

void senha_manual(CADASTRO *pessoa){/* Verifica se uma senha manual está de acordo com os parâmetros do programa */
    while(TRUE){
        puts("Sua senha deve ter no minimo oito e no maximo 20 caracteres, pelo menos"
        "\numa letra maiuscula, pelo menos uma letra minuscula e um caractere numerico"
        "\nou especial (@, #, $, %, ou &):");
        int controle = FALSE;
        fflush(stdin);
        gets(pessoa->senha);
        if (strlen(pessoa->senha)<8){
            puts("Sua senha deve ter no minimo 8 caracteres.");
            controle = TRUE;
        }
        if (!oneIsUpper(pessoa->senha)){
            puts("Sua senha deve ter ao menos uma letra maiuscula!");
            controle = TRUE;
        }
        if (!oneIsLower(pessoa->senha)){
            puts("Sua senha deve ter ao menos uma letra minuscula!");
            controle = TRUE;
        }
        if (!oneIsEspecial(pessoa->senha) && !oneisnumeric(pessoa->senha)){
            puts("Sua senha deve possuir um caracter numerico ou um caractere especial permitido!");
            controle = TRUE;
        }
        if (oneCharNotAllowed(pessoa->senha)){
            puts("Sua senha deve possuir um caractere especial permitido!");
            controle = TRUE;
        }

        if (controle){
            puts("Tente novamente!");
            continuar();
            limpar_tela();
            continue;
        }
        else{
            break;
        }
    }
}

void senha_automatica(CADASTRO *pessoa){/* Cria uma senha automática segundo os parâmetros do problema */
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

int oneIsUpper(char senha[]){ /*Verifica se a senha possui ao menos uma letra maiscula*/
    for (int i=0;senha[i]!='\0';i++){
        if (isupper(senha[i])){
            return TRUE;
        }
    }
    return FALSE;
}

int oneIsLower(char senha[]){ /*Verifica se a senha possui ao menos uma letra minuscula*/
    for (int i=0;senha[i] !='\0';i++){
        if(islower(senha[i])){
            return TRUE;
        }
    }
    return FALSE;
}

int oneIsEspecial(char senha[]){/*Verifica se ao menos um digito na senha é caracter especial*/
    for (int i=0;senha[i] !='\0';i++){
        if (senha[i]=='@'||senha[i]=='#'||senha[i]=='$'||senha[i]=='%'||senha[i]=='&'){
            return TRUE;
        }
    }
    return FALSE;
}

int oneCharNotAllowed(char senha[]){
    for (int i=0;senha[i] !='\0';i++){
        if (isalnum(senha[i])){
            continue;
        }
        if (senha[i]=='@'||senha[i]=='#'||senha[i]=='$'||senha[i]=='%'||senha[i]=='&'){
            continue;
        }
        else{
            return TRUE;
        }
    }
    return FALSE;
}

int oneisnumeric(char senha[]){ /*Verifica se ao menos um digito na senha é numérico*/
    for (int i=0;senha[i]!='\0';i++){
        if (isdigit(senha[i])){
            return TRUE;
        }
    }
    return FALSE;
}

void salvar_senha(CADASTRO pessoa){ /*Realiza a persistência dos dados em arquivo binario*/
    fp = fopen(ARQ, "a+b");
    if (fp==NULL){
        puts("Não foi possivel salvar a senha!");
        exit(1);
    }
    fseek(fp, 0L, SEEK_END);
    if (fwrite(&pessoa, sizeof(pessoa),1, fp) != 1){
        printf("Adicionar senha: Falhou a escrita do Registro!\n");
        exit(1);
    }
    fclose(fp);
}

int listar_finalidades(){/*Coloca na tela as finalidades das senhas e retorna a quantidade de senhas*/
    long contador=0;
    CADASTRO info;
    fp = fopen(ARQ, "rb");
    if (fp==NULL){
        puts("Nao foi possivel visualizar as finalidades!!");
        exit(1);
    }
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

void print_finalidades(CADASTRO pessoa, long int contador){/* Mostra ao usuario as finalidades das senhas salvas */
    printf("%3d - %20s\n", contador+1, pessoa.finalidade);
}

int escolher_finalidade(int cont){/*Retorna o numero da finalidade escolhida pelo usuario */
    int escolha = -1;
    while(escolha == -1){
        scanf(" %d", &escolha);
        if (escolha<1 || escolha>cont){
            puts("Valor invalido. Tente novamente!");
            continue;
        }
    }
    return escolha;
}

void mostrar_finalidade_senha(int posicao){/*Procura a posição da senha e finalidade no arquivo e printa na tela*/
    CADASTRO info;
    fp = fopen(ARQ, "rb");
    if (fp==NULL){
        puts("Erro na abertura do arquivo!");
        exit(1);
    }
    fseek(fp, (long) (posicao-1)*sizeof(CADASTRO), SEEK_SET);

    if (fread(&info, sizeof(CADASTRO), 1, fp) != 1){
        puts("Nao foi possivel ler a informacao solicitada!");
        exit(1);
    }
    printf("Finalidade: %20s    Senha: %20s\n", info.finalidade, info.senha);

    fclose(fp);
}

void limpar_tela(){/* Limpa a tela; semelhante ao cls */
    for(int i=0;i<100;i++){
        putchar('\n');
    }
}

void apagar_senha(int posicao){/*Apaga a senha na posição escolhida pelo usuário*/
    CADASTRO info;
    FILE *temp;
    temp = fopen("temp.dat", "wb");
    if (temp==NULL){
        printf("Erro na abertura do arquivo %s!\n", "temp.dat");
        exit(1);
    }

    fp = fopen(ARQ, "rb");
    if (fp==NULL){
        puts("Erro na abertura do arquivo!");
        exit(1);
    }

    rewind(fp);
    unsigned long int count = 1;
    while(fread(&info, sizeof(CADASTRO), 1, fp)==1){
        if (count != (posicao)){
            if (fwrite(&info, sizeof(CADASTRO), 1, temp)!=1){
                printf("Erro na gravacao do dado %d!\n", count);
                exit(1);
            };
            count++;
        }
        else{
            count++;
        }
    }
    
    fclose(fp);
    fclose(temp);
    remove(ARQ);
    rename("temp.dat", ARQ);
}

int isfempty(){/*Retorna TRUE se o arquivo está vazio, FALSE else*/
    if ((fp = fopen(ARQ, "rb"))==NULL){
        puts("Erro! Nao foi possivel abrir o arquivo!");
        exit(1);
    }
    if (fgetc(fp)!=EOF){
        fclose(fp);
        return FALSE;
    }
    fclose(fp);
    return TRUE;
}

void continuar(){/*Controle de fluxo para o usuário*/
    puts("Digite enter para continuar...");
    fflush(stdin);
    getchar();
}

