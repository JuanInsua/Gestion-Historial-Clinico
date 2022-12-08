#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "menu-principal.h"
#include "menu-admin.h"
#include "gotoxy.h"

#define RAND_MAX 50
#define TECLA_BORRAR 8
#define TECLA_ENTER 13
#define TECLA_ESCAPE 27
#define ASTERISCO '*'
void enmascaraCadena(char *cadena, int longitud, char asterisco);
void leerContrasenaSinMostrarla(char *palabraSecretaDestino);

int main()
{
    char fileAtenciones[]="atenciones.bin";
    char filePacientes[]="pacientes.bin";
    char fileEspecialidades[]="especialidades.bin";
    int optA;
    char passwordAdmin[10]="AdminUTN";
    char inputPassword[30];
    do{
        hospitalXc();
        printf("---------INICIO---------\n");
        printf("1. Menu Administrador \n");
        printf("2. Iniciar Systema \n\n");
        printf("3. Salir \n");
        printf("Opcion: ");
        scanf("%d",&optA);
        switch(optA){
        case 1:
            leerContrasenaSinMostrarla(inputPassword);
            if(strcmp(inputPassword,passwordAdmin)==0){
                menuAdmin(fileAtenciones,filePacientes,fileEspecialidades);
            }else{
                printf("\nContrasenia incorrecta \n");            /// PASSWORD: AdminUTN
                system("pause");
            }
            memset(inputPassword, NULL, 30); //https://www.jpromero.com/2014/12/vaciar-cadena-en-c.html
            system("cls");
            break;
        case 2:
            inicSystem(fileAtenciones,filePacientes,fileEspecialidades);
            system("cls");
            break;
        case 3:
            exit(0);
            system("cls");
            break;
        default:
            printf("Opcion incorrecta\n");
            system("pause");
            system("cls");
            break;
        }
    }while(optA!=3);
    return 0;
}
void hospitalXc ()
{
    system("cls");
    gotoxy (1,0); color (3); printf ("   ________________________________________________________________________________________");
    gotoxy (1,2); color (4); printf ("   ##  ##  ######  ######  ######  ##  ######  ######  ##                              ");
    gotoxy (1,3); color (4); printf ("   ##  ##  ##  ##  ##      ##  ##  ##    ##    ##  ##  ##                              ");
    gotoxy (1,4); color (4); printf ("   ##  ##  ##  ##  ##      ##  ##  ##    ##    ##  ##  ##                              #####");
    gotoxy (1,5); color (4); printf ("   ##  ##  ##  ##  ##      ##  ##  ##    ##    ##  ##  ##                              #####");
    gotoxy (1,6); color (4); printf ("   ##  ##  ##  ##  ##      ##  ##  ##    ##    ##  ##  ##                              #####");
    gotoxy (1,7); color (4); printf ("   ######  ##  ##  ######  ######  ##    ##    ######  ##                         ###############");
    gotoxy (1,8); color (4); printf ("   ##  ##  ##  ##      ##  ##      ##    ##    ##  ##  ##                         ###############");
    gotoxy (1,9); color (4); printf ("   ##  ##  ##  ##      ##  ##      ##    ##    ##  ##  ##                              #####");
    gotoxy (1,10); color (4); printf("   ##  ##  ##  ##      ##  ##      ##    ##    ##  ##  ##                              #####");
    gotoxy (1,11); color (4); printf("   ##  ##  ##  ##      ##  ##      ##    ##    ##  ##  ##                              #####");
    gotoxy (1,12); color (4); printf("   ##  ##  ######  ######  ##      ##    ##    ##  ##  ######");
    gotoxy (1,14); color (3); printf("   ________________________________________________________________________________________\n");
}

void enmascaraCadena(char *cadena, int longitud, char asterisco)
{
    int i = 0;
    printf("\n*************INGRESANDO MENU ADMINISTRACION*************** \n");
    printf("Por favor ingrese clave del sistema\n");
    printf("\nPassword: \n");
    for (i = 0; i < longitud; i++)
    {
        printf("%c", asterisco);
    }
    return 0;
}

void leerContrasenaSinMostrarla(char *palabraSecretaDestino)
{
    int caracterLeido = 0;
    char temporal[2];
    palabraSecretaDestino[strlen(palabraSecretaDestino) - 1] = '\0';
    while (caracterLeido != TECLA_ENTER)
    {
        system("cls");
        enmascaraCadena(palabraSecretaDestino, strlen(palabraSecretaDestino), ASTERISCO);
        caracterLeido = getch();
                // https://parzibyte.me/blog/2019/11/02/c-char-a-string/
        temporal[0] = caracterLeido;
        temporal[1] = '\0';
        if (caracterLeido == TECLA_BORRAR)
        {
            if (strlen(palabraSecretaDestino) > 0)
            {
                // https://parzibyte.me/blog/2022/03/23/eliminar-ultimo-caracter-cadena-c/
                palabraSecretaDestino[strlen(palabraSecretaDestino) - 1] = '\0';
            }
        }
        else if (caracterLeido != TECLA_ENTER)
        {
            strncat(palabraSecretaDestino, temporal, 1);
        }
    }
    return 0;
}

