#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gotoxy.h"

void menuAdmin(char fileAtenciones[],char filePacientes[],char fileEspecialidades[]){
    char optB;
    do{
        hospitalXc();
        printf("---------MENU ADMINISTRADOR---------\n");
        printf("1.Mostrar archivo atenciones \n");
        printf("2.Mostrar archivo pacientes\n");
        printf("3.Mostrar archivo especialidades\n");
        printf("4.Cargar archivo especialidades\n");
        printf("5.Modificar archivo pacientes\n");
        printf("6.Modificar archivo especialidades\n");
        printf("7.Alta/Baja Pacientes \n\n");
        printf("8.Volver\n");
        printf("9.Salir \n");
        printf("Opcion: ");
        scanf("%d",&optB);
        system("cls");
        switch(optB){
        case 1:
            mostrarArchivoAtenciones(fileAtenciones);
            system("pause");
            system("cls");
            break;
        case 2:
            mostrarArchivoPacientes(filePacientes);
            system("pause");
            system("cls");
            break;
        case 3:
            mostrarArchivoEspecialidades(fileEspecialidades);
            system("pause");
            system("cls");
            break;
        case 4:
            cargarArchivoEspecialidades(fileEspecialidades);
            system("pause");
            system("cls");
            break;
        case 5:
            modificarArchivoPacientes(filePacientes);
            system("pause");
            system("cls");
            break;
        case 6:
            modificarArchivoEspecialidad(fileEspecialidades);
            system("pause");
            system("cls");
            break;
        case 7:
            altaBajaArchivoPacientes(filePacientes);
            system("pause");
            system("cls");
            break;
        case 9:
            exit(0);
            break;
        default:
            break;
        }
    }while(optB!=8);
}
