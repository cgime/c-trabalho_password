#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define TRUE 1
#define FALSE 0

typedef struct cadastro{
    char finalidade[21];
    char senha[21];
}CADASTRO;


int menu();
void get_senha( CADASTRO *pessoa);
void senha_manual(CADASTRO *pessoa);
void senha_automatica(CADASTRO *pessoa);
int oneisupper(char senha[]);
int oneislower(char senha[]);
int oneisespecial(char senha[]);
int oneisnumeric(char senha[]);

void main(){
    puts("\n\n*****Bem vindo ao seu gerenciador de senhas!*****\n\n");
    int fica_no_loop = TRUE;
    while (fica_no_loop){
        switch (menu()){
            case 1:{
                CADASTRO pessoa;
                puts("Digite a finalidade da senha: ");
                fflush(stdin);
                gets(pessoa.finalidade);
                get_senha(&pessoa);
                printf("\n\nSenha salva com sucesso!\n");
                printf("Finalidade: %s. --- senha: %s\n", pessoa.finalidade, pessoa.senha);
                // salvar_senha(pessoa);
                break;
            }
            case 2:{ /* Apresentar senha salva*/

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
    puts("Sua senha deve ter no minimo oito caracteres, pelo menos"
    " uma letra maiuscula, pelo menos uma minuscula e um caractere numerico"
    " ou especial (@, #, $, %%, ou &)");
    while(TRUE){
        int controle = FALSE;
        fflush(stdin);
        gets(pessoa->senha);
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

void senha_automatica(CADASTRO *pessoa){ /*Está ok */
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

// void salvar_senha(CADASTRO *pessoa){ /* Ainda não finalizado*/
    // FILE *senhas_salvas;
    // FILE* finalidades;
    // senhas_salvas = fopen("senhas_salvas.bin", "a+b");
    // if (senhas_salvas == NULL){
    //     puts("Erro ao tentar abrir arquivo de senhas!");
    //     exit(0);
    // }
    
    // finalidade = fopen("finalidades.bin", "a+b");
    // if (finalidade == NULL){
    //     puts("Erro ao tentar abrir arquivo de finalidades!");
    //     exit(0);
    // }

    // fwrite(finalidade, sizeof(char), strlen(finalidade)+1, finalidade);
    // fwrite(senha, sizeof(char), strlen(senha)+1, senhas_salvas);

    // fclose(senhas_salvas);
// }

// void print_finalidades(){ /* Ainda não finalizado */
//     char finalidade[20];
//     printf("%10s - %20s", "numero", "Finalidade");
//     for (int i=0;i<100;i++){
//         printf("%10d    %s\n", i+1, finalidade[i]);
//     }
    
//     puts("Selecione uma finalidade:");

// }

// void apagar_senha(){ /* Ainda não finalizado */

// }