#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "Gestion-atenciones.h"
#include "asignacion-turnos.h"
#include "gotoxy.h"
#define MAX 10

void inicSystem(char fileAtenciones[],char filePacientes[],char fileEspecialidades[]){
    stEspecialidad arrayEspecialidades[MAX];
    int validosEspecialidades=0;
    validosEspecialidades=archivoToArrayEspecialidad(fileEspecialidades,arrayEspecialidades,validosEspecialidades,MAX);
    int opt;
    Fila filaConsulta;
    inicFila(&filaConsulta);
    do{
        hospitalXc();
        CeldaEspecialidad ADL[MAX];
        int validosAtenciones=archivoToADLatenciones(ADL,MAX,fileAtenciones);
        nodoArbolPacientes*arbolPacientes=inicArbolPacientes();
        arbolPacientes=archivoToArbolPacientes(filePacientes,arbolPacientes);

        printf("---------MENU ATENCIONES PACIENTES--------- \n");
        printf("1. Cargar Atencion Paciente \n");
        printf("2. Mostrar atenciones por especialidad \n");
        printf("3. Generar Fila consulta historial clinico de un paciente \n");
        printf("4. Imprimir historial clinico de un paciente \n");
        printf("5. Ganancia maxima por Costo de una especialidad \n");
        printf("6. Cantidad total de atenciones en una Obra social \n\n");
        printf("7. Volver. \n");
        printf("8. Salir.  \n");

        printf("Opcion: ");
        scanf("%d",&opt);
        system("cls");
        switch(opt){
        case 1:
            cargarAtencion(fileAtenciones,filePacientes,arbolPacientes,arrayEspecialidades,validosEspecialidades);
            system("pause");
            system("cls");
            break;
        case 2:
            mostrarADLatenciones(ADL,validosAtenciones,arrayEspecialidades,validosEspecialidades,arbolPacientes);
            system("pause");
            system("cls");
            break;
        case 3:
            cargaFila(&filaConsulta);
            muestraFila(&filaConsulta);
            system("pause");
            system("cls");
            break;
        case 4:
            filaToConsulta(&filaConsulta,ADL,validosAtenciones,arbolPacientes);
            system("pause");
            system("cls");
            break;
        case 5:
            consultaGanancia(ADL,validosAtenciones,arrayEspecialidades,validosEspecialidades);
            system("pause");
            system("cls");
            break;
        case 6:
            consultaAtencionesObraSocial(ADL,validosAtenciones,arbolPacientes);
            system("pause");
            system("cls");
            break;
        case 8:
            exit(0);
            break;
        default:
            system("cls");
            break;
        }
    }while(opt!=7);
}

