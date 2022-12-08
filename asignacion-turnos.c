#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <string.h>
#include "Gestion-atenciones.h"
#include "asignacion-turnos.h"

///FUNCIONES ARBOL-PACIENTES
nodoArbolPacientes*inicArbolPacientes           ()
{
    return NULL;
}
nodoArbolPacientes*crearNodoArbolPacientes      (stPaciente paciente)
{
    nodoArbolPacientes*nuevoNodoArbolPaciente=(nodoArbolPacientes*)malloc(sizeof(nodoArbolPacientes));
    nuevoNodoArbolPaciente->paciente=paciente;
    nuevoNodoArbolPaciente->izq=NULL;
    nuevoNodoArbolPaciente->der=NULL;
    return nuevoNodoArbolPaciente;
}
nodoArbolPacientes*agregarArbolPacientes        (nodoArbolPacientes*raiz,stPaciente paciente)
{
    if(raiz)
    {
        if(raiz->paciente.DNI > paciente.DNI)
        {
            raiz->izq=agregarArbolPacientes(raiz->izq,paciente);
        }
        else
        {
            raiz->der=agregarArbolPacientes(raiz->der,paciente);
        }
    }
    else
    {
        raiz=crearNodoArbolPacientes(paciente);
    }
    return raiz;
}
nodoArbolPacientes*buscarPacienteArbol          (nodoArbolPacientes*raiz,int DNI)
{
    nodoArbolPacientes*aux=NULL;
    if(raiz)
    {
        if(raiz->paciente.DNI==DNI)
        {
            aux=raiz;
        }
        else
        {
            if(raiz->paciente.DNI>DNI)
            {
                aux=buscarPacienteArbol(raiz->izq,DNI);
            }
            else
            {
                aux=buscarPacienteArbol(raiz->der,DNI);
            }
        }
    }
    else
    {
        printf("Arbol sin datos\n");
    }
    return aux;
}
nodoArbolPacientes*buscarPacienteArbolID          (nodoArbolPacientes*raiz,int idPaciente)
{
    nodoArbolPacientes*aux=NULL;
    if(raiz)
    {
        if(raiz->paciente.idPaciente==idPaciente)
        {
            aux=raiz;
        }
        else
        {
            nodoArbolPacientes*derecha=raiz->der;
            if(derecha->paciente.idPaciente!=idPaciente)
            {
                aux=buscarPacienteArbolID(raiz->der,idPaciente);
            }
            else
            {
                aux=buscarPacienteArbolID(raiz->izq,idPaciente);
            }
        }
    }
    else
    {
        printf("Arbol pacientes vacio \n");
    }
    return aux;
}
void preOrder                                   (nodoArbolPacientes*raiz)
{
    if(raiz)
    {
        mostrarPaciente(raiz->paciente);
        preOrder(raiz->izq);
        preOrder(raiz->der);
    }
}
void inOrder                                    (nodoArbolPacientes*raiz)
{
    if(raiz)
    {
        inOrder(raiz->izq);
        mostrarPaciente(raiz->paciente);
        inOrder(raiz->der);
    }
}
void postOrder                                  (nodoArbolPacientes*raiz)
{
    if(raiz)
    {
        postOrder(raiz->izq);
        postOrder(raiz->der);
        mostrarPaciente(raiz->paciente);
    }
}
int contarPacientesArbol(nodoArbolPacientes*raiz)
{
    int cant;
    if(raiz==NULL)
    {
        cant=0;
    }
    else
    {
        cant=1+contarPacientesArbol(raiz->izq)+contarPacientesArbol(raiz->der);
    }
    return cant;
}
stPaciente atenderPaciente                      (char filePacientes[],nodoArbolPacientes* raiz)
{
    int DNI;
    printf("DNI paciente a verificar: \n");
    scanf("%d",&DNI);
    nodoArbolPacientes* pacienteBuscado=buscarPacienteArbol(raiz,DNI);
    stPaciente aux;
    if(pacienteBuscado==NULL)
    {
        int cantPacientes=contarPacientesArbol(raiz);
        aux=cargarPaciente(cantPacientes+1,DNI);
        cargarArchivoPacientes(filePacientes,aux);
    }
    else
    {
        aux=pacienteBuscado->paciente;
    }
    return aux;
}
nodoArbolPacientes* archivoToArbolPacientes(char filePacientes[],nodoArbolPacientes*arbolPacientes)
{
    FILE*archi=fopen(filePacientes,"rb");
    stPaciente paciente;
    if(archi)
    {
        while(fread(&paciente,sizeof(stPaciente),1,archi)>0)
        {
            arbolPacientes=agregarArbolPacientes(arbolPacientes,paciente);
        }
        fclose(archi);
    }
    return arbolPacientes;
}
///FUNCIONES ARRAY ESPECIALIDAD
int agregarEspecialidad (stEspecialidad arrayEspecialidad[],int validos,stEspecialidad especialidad)
{
    arrayEspecialidad[validos]=especialidad;
    validos++;
    return validos;
}
int mostrarArrayEspecialidad (stEspecialidad arrayEspecialidad[],int validos)
{
    for(int i=0; i<validos; i++)
    {
        mostrarEspecialidad(arrayEspecialidad[i]);
    }
}
stEspecialidad eleccionEspecialidad(stEspecialidad arrayEspecialidades[],int validos)
{
    mostrarArrayEspecialidad(arrayEspecialidades,validos);
    int numeroEspecialidad;
    printf("Elegir numero especialidad: \n");
    scanf("%d",&numeroEspecialidad);
    stEspecialidad aux;
    aux = buscarEspecialidadArray(arrayEspecialidades,validos,numeroEspecialidad);
    return aux;
}
stEspecialidad buscarEspecialidadArray (stEspecialidad arrayEspecialidad[],int validos,int numeroEspecialidad)
{
    stEspecialidad especialidad;
    int flag=-1;
    int i=0;
    while(i<validos && flag==-1)
    {
        if(arrayEspecialidad[i].idEspecialidad==numeroEspecialidad)
        {
            especialidad=arrayEspecialidad[i];
            flag=0;
        }
        i++;
    }
    return especialidad;
}
///FUNCIONES ARCHIVO PACIENTES
void cargarArchivoPacientes (char filePacientes[],stPaciente paciente)
{
    FILE*archi=fopen(filePacientes,"ab");
    if(archi)
    {
        fwrite(&paciente,sizeof(stPaciente),1,archi);
        fclose(archi);
    }
}
int contarPacientesArchivo(char filePacientes[])
{
    FILE*archi=fopen(filePacientes,"rb");
    int cant;
    stPaciente aux;
    if(archi)
    {
        fseek(archi,0,SEEK_END);
        cant=ftell(archi)/sizeof(stPaciente);
        fclose(archi);
    }
    return cant;
}
void mostrarArchivoPacientes (char filePacientes[])
{
    FILE*archi=fopen(filePacientes,"rb");
    stPaciente paciente;
    if(archi)
    {
        while (fread(&paciente,sizeof(stPaciente),1,archi)>0)
        {
            mostrarPaciente(paciente);
        }
        fclose(archi);
    }
}
int busquedaArchivoPaciente (char filePacientes[],int DNI)
{
    FILE * archi = fopen (filePacientes,"rb");
    stPaciente aux;
    int pos=-1;
    int i=0;
    if (archi)
    {
        while (pos==-1 && fread(&aux,sizeof(stPaciente),1,archi)>0)
        {
            if(aux.DNI==DNI)
            {
                pos=i;
            }
            i++;
        }
        fclose(archi);
    }
    return pos;
}
void modificarArchivoPacientes (char filePacientes[])
{
    int DNI;
    int posRegistro;
    stPaciente aux;
    printf ("Ingrese el DNI del paciente a modificar \n");
    scanf("%d",&DNI);
    posRegistro = busquedaArchivoPaciente (filePacientes,DNI);
    FILE * archi = fopen (filePacientes,"r+b");
    if (archi)
    {
        fseek(archi,sizeof(stPaciente)*posRegistro,SEEK_SET);
        fread(&aux,sizeof(stPaciente),1,archi);
        int nuevoDNI;
        printf("DNI:\n");
        scanf("%d",&nuevoDNI);
        aux = cargarPaciente(aux.idPaciente,nuevoDNI);
        fseek(archi,sizeof(stPaciente)*(-1),SEEK_CUR);
        fwrite(&aux,sizeof(stPaciente),1,archi);
        fclose(archi);
    }
}
void altaBajaArchivoPacientes (char filePacientes[])
{
    int DNI;
    int posRegistro;
    stPaciente aux;
    printf ("Ingrese el DNI del paciente a modificar \n");
    scanf("%d",&DNI);
    posRegistro = busquedaArchivoPaciente (filePacientes,DNI);
    FILE * archi = fopen (filePacientes,"r+b");
    if (archi)
    {
        fseek(archi,sizeof(stPaciente)*posRegistro,SEEK_SET);
        fread(&aux,sizeof(stPaciente),1,archi);
        aux.estado=modificarEstado(aux.estado);
        fseek(archi,sizeof(stPaciente)*(-1),SEEK_CUR);
        fwrite(&aux,sizeof(stPaciente),1,archi);
        fclose(archi);
    }
}
int modificarEstado (int estado)
{
    char modif='s';
    printf("-------MODIFICACION ESTADO----------\n");
    printf("Estado actual paciente: %d\n",estado);
    printf("Desea modificarlo? s|n \n");
    fflush(stdin);
    scanf("%c",&modif);
    if(modif=='s' || modif=='S')
    {
        if(estado==0)
        {
            estado=1;
        }
        else
        {
            estado=0;
        }
    }
    printf("Estado actual actualizado: %d\n",estado);
    return estado;
}
///FUNCIONES ARCHIVO ESPECIALIDADES
int contarEspecialidades (char fileEspecialidades[])
{
    FILE*archi=fopen(fileEspecialidades,"rb");
    int cant=0;
    stEspecialidad aux;
    if(archi)
    {
        fseek(archi,0,SEEK_END);
        cant=ftell(archi)/sizeof(stEspecialidad);
        fclose(archi);
    }
    return cant;
}
void cargarArchivoEspecialidades (char fileEspecialidades[])
{
    FILE*archi=fopen(fileEspecialidades,"ab");
    stEspecialidad especialidad;
    int idEspecialidad=contarEspecialidades(fileEspecialidades);
    if(archi)
    {
        especialidad=cargarEspecialidad(idEspecialidad+1);
        fwrite(&especialidad,sizeof(stEspecialidad),1,archi);
        fclose(archi);
    }
}
void mostrarArchivoEspecialidades (char fileEspecialidades[])
{
    FILE*archi=fopen(fileEspecialidades,"rb");
    stEspecialidad especialidad;
    if(archi)
    {
        while (fread(&especialidad,sizeof(stEspecialidad),1,archi)>0)
        {
            mostrarEspecialidad(especialidad);
        }
        fclose(archi);
    }
}
int archivoToArrayEspecialidad (char fileEspecialidad[],stEspecialidad arrayEspecialidad[],int validos,int dimension)
{
    FILE*archi=fopen(fileEspecialidad,"rb");
    stEspecialidad aux;
    if(archi)
    {
        while(fread(&aux,sizeof(stEspecialidad),1,archi)>0 && validos<=dimension)
        {
            validos=agregarEspecialidad(arrayEspecialidad,validos,aux);
        }
        fclose(archi);
    }
    return validos;
}
int busquedaArchivoEspecialidad (char fileEspecialidad[],char nombreEspecialidad[])
{
    FILE*archi=fopen(fileEspecialidad,"rb");
    int posArchivo=-1;
    int i=0;
    stEspecialidad aux;
    while(posArchivo==-1 && fread(&aux,sizeof(stEspecialidad),1,archi)>0)
    {
        if(strcmpi(aux.especialidadMedica,nombreEspecialidad)==0)
        {
            posArchivo=i;
        }
        i++;
    }
    fclose(archi);
    return posArchivo;
}
void modificarArchivoEspecialidad (char fileEspecialidad[])
{
    char nombreEspecialidad[20];
    int posRegistro;
    stEspecialidad aux;
    mostrarArchivoEspecialidades(fileEspecialidad);
    printf ("Ingrese el Nombre de la especialidad a modificar \n");
    fflush(stdin);
    scanf("%s",&nombreEspecialidad);
    posRegistro = busquedaArchivoEspecialidad (fileEspecialidad,nombreEspecialidad);
    FILE * archi = fopen (fileEspecialidad,"r+b");
    if (archi)
    {
        fseek(archi,sizeof(stEspecialidad)*posRegistro,SEEK_SET);
        fread(&aux,sizeof(stEspecialidad),1,archi);
        aux = cargarEspecialidad(aux.idEspecialidad);
        fseek(archi,sizeof(stEspecialidad)*(-1),SEEK_CUR);
        fwrite(&aux,sizeof(stEspecialidad),1,archi);
        fclose(archi);
    }
}
///FUNCIONES LISTA CONSULTA HISTORIAL CLINICO
nodoFila* inicLista()
{
    return NULL;
}
nodoFila* crearNodoListaConsulta(int DNI)
{
    nodoFila * nuevoNodo = (nodoFila*) malloc(sizeof(nodoFila));
    nuevoNodo->DNI=DNI;
    nuevoNodo->seg=NULL;
}
nodoFila* agregarAlFinalConsulta (nodoFila*listaConsulta,nodoFila*nuevoNodo)
{
    if(listaConsulta)
    {
        nodoFila*ultimo=buscarUltimoConsulta(listaConsulta);
        ultimo->seg=nuevoNodo;
    }
    else
    {
        listaConsulta=nuevoNodo;
    }
    return listaConsulta;
}
nodoFila* buscarUltimoConsulta (nodoFila*listaConsulta)
{
    nodoFila*ultimo=listaConsulta;
    while(ultimo->seg)
    {
        ultimo=ultimo->seg;
    }
    return ultimo;
}
void mostrarListaConsulta(nodoFila*listaConsulta)
{
    if(listaConsulta)
    {
        printf("DNI Consulta: %d\n",listaConsulta->DNI);
        mostrarListaConsulta(listaConsulta->seg);
    }
}
///FUNCIONES FILA CONSULTAS HISTORIAL CLINICO
void inicFila (Fila * fila)
{
    fila->primero=inicLista();
    fila->ultimo=inicLista();
}
void agregarFila (Fila * fila,int DNI)
{
    nodoFila*nuevoNodo=crearNodoListaConsulta(DNI);
    if(fila->primero)
    {
        fila->primero=agregarAlFinalConsulta(fila->primero,nuevoNodo);
    }
    else
    {
        fila->primero=nuevoNodo;
    }
    fila->ultimo=nuevoNodo;
}
int extraerFila (Fila*fila)
{
    int resp=0;
    if(fila->primero)
    {
        resp=verPrimero(fila->primero);
        fila->primero=borrarPrimero(fila->primero);
        if(fila->primero==NULL)
        {
            fila->ultimo=inicLista();
        }
    }
    return resp;
}
int verPrimero (nodoFila*lista)
{
    int resp=0;
    if(lista)
    {
        resp=lista->DNI;
    }
    return resp;
}
nodoFila * borrarPrimero (nodoFila*lista)
{
    nodoFila*aBorrar=lista;
    if(lista)
    {
        lista=lista->seg;
        free(aBorrar);
    }
    return lista;
}
void cargaFila(Fila * fila)
{
    char ctrl='s';
    int DNI;
    printf("GENERAR FILA CONSULTA HISTORIAL CLINICO:\n");
    while(ctrl=='s' || ctrl=='S')
    {
        printf("\nIngresar DNI paciente consulta historia clinica: \n");
        scanf("%d",&DNI);
        agregarFila(fila,DNI);
        printf("\nDesea cargar mas DNI a la fila de consultas? \n");
        fflush(stdin);
        scanf("%c",&ctrl);
    }
}
void muestraFila (Fila * fila)
{
    if(fila->primero)
    {
        printf("MUESTRA FILA CONSULTAS \n");
        mostrarListaConsulta(fila->primero);
    }
}
void filaToConsulta(Fila*fila,CeldaEspecialidad ADL[],int validosAtencion,nodoArbolPacientes*raiz)
{
    char ctrl='s';
    int DNI=0;
    muestraFila(fila);
    do
    {
        if(ctrl=='s'||ctrl=='S')
        {
            if(fila->primero)
            {
                DNI=extraerFila(fila); /// EXTRAEMOS UN DNI DE LA FILA CONSULTA HISTORIAL CLINICO
                consultaHistorialMedico(ADL,validosAtencion,raiz,DNI); /// LLAMAMOS A LA FUNCION DE CONSULTA HISTORIAL Y LE PASAMOS EL DNI QUE EXTRAEMOS DE LA FILA
            }
            else
            {
                printf("\nNo hay consultas por atender \n");
                ctrl='n';
            }
        }

    }
    while(ctrl=='s'||ctrl=='S');
}
