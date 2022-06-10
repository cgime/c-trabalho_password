#include<stdio.h>
#include<stdlib.h>

typedef struct senha{
    int id;
    char finalidade[50];
    float SENHA;
}senha;

void main()
{
    FILE *senhas_salvas;
    FILE *senhas_salvas_auxilixar;
    senha esc[500];
    
    int x = 0;
            
            senhas_salvas = fopen("senhas_salvas.dat", "rb");
            senhas_salvas_auxilixar = fopen("senhas_salvas_auxiliar.dat","ab");
            int mat;
            printf("digite o item a ser apagado: ");
            fflush(stdin);
            scanf("%d",&mat);
            while(fread(&esc[x], sizeof(esc), 1, senhas_salvas)>0)
            {
                if(esc[x].id != mat)
                {
                    fwrite(&esc[x], sizeof(esc), 1, senhas_salvas_auxilixar);
                    x++;
                }
            }
            fclose(senhas_salvas);
            fclose(senhas_salvas_auxilixar);
            remove("senhas_salvas.dat");
            rename("senhas_salvas_auxiliar.dat","senhas_salvas.dat");
            printf("\nExclusao Concluida Com Sucesso !\n\n");
}