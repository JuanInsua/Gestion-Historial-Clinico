#ifndef ASIGNACION-TURNOS_H_INCLUDED
#define ASIGNACION-TURNOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "string.h"
#include "Gestion-atenciones.h"

typedef struct{
    int DNI;
    struct nodoFila* seg;
}nodoFila;

typedef struct{
    nodoFila* primero;
    nodoFila* ultimo;
}Fila;

typedef struct{
    int idPaciente;
    int estado;                 //1-alta,0-baja
    int DNI;
	char nombrePaciente[30];
	char apellidoPaciente[30];
	int obraSocial;             //1-SAMI,2-OSARPI,3-MEDIFE,4-IOMA,5-UNION PERSONAL,6-NINGUNA
}stPaciente;                    ///ESTRUCTURA PACIENTE

typedef struct{
    int idEspecialidad;
    char nombreDoctor[30];
	char especialidadMedica[30];
}stEspecialidad;                ///ESTRUCTURA ESPECIALIDAD

typedef struct{
    stPaciente paciente;
    struct nodoArbolPacientes* izq;
    struct nodoArbolPacientes* der;
}nodoArbolPacientes;            ///NODO ARBOL BINARIO DE BUSQUEDA PACIENTE

///PROTOTIPADO ARBOL-PACIENTES
nodoArbolPacientes*inicArbolPacientes           ();
nodoArbolPacientes*crearNodoArbolPacientes      (stPaciente paciente);                              //CREAMOS NODO PACIENTE ASIGNANDO MEMORIA DINAMICA
nodoArbolPacientes*agregarArbolPacientes        (nodoArbolPacientes*raiz,stPaciente paciente);      //AGREGAMOS UN PACIENTE AL ABB, COMO ORDENAMIENTO UTILIZAMOS EL DNI
nodoArbolPacientes*buscarPacienteArbol          (nodoArbolPacientes*raiz,int DNI);               //BUSQUEDA DE UN PACIENTE MEDIANTE EL PARAMETRO DE ORDENAMIENTO (DNI)
nodoArbolPacientes*buscarPacienteArbolID        (nodoArbolPacientes*raiz,int idPaciente);           //BUSQUEDA DE UN PACIENTE MEDIANTE OTRO EL PARAMETRO (ID PACIENTE)
void preOrder                                   (nodoArbolPacientes*raiz);                          //MOSTRAMOS ARBOL EN ORDEN= RAIZ-IZQUIERDA-DERECHA
void inOrder                                    (nodoArbolPacientes*raiz);                          //MOSTRAMOS ARBOL EN ORDEN= IZQUIERDA-RAIZ-DERECHA
void postOrder                                  (nodoArbolPacientes*raiz);                          //MOSTRAMOS ARBOL EN ORDEN= IZQUIERDA-DERECHA-RAIZ
int contarPacientesArbol                        (nodoArbolPacientes*raiz);                          //RETORNAMOS LA CANTIDAD DE NODOS QUE HAY EN EL ARBOL
stPaciente atenderPaciente                      (char filePacientes[],nodoArbolPacientes* raiz);    //VALIDAMOS SI YA EXISTE EL PACIENTE EN EL ARBOL, SI EXISTE RETORNAMOS SU ESTRUCTURA Y DATOS,SI NO EXISTE LO CREAMOS Y RETORNAMOS
nodoArbolPacientes* archivoToArbolPacientes(char filePacientes[],nodoArbolPacientes*arbolPacientes);//PASAMOS TODOS LOS REGISTROS PACIENTES AL ARBOL DE PACIENTES
///PROTOTIPADO ARRAY ESPECIALIDAD
int agregarEspecialidad (stEspecialidad arrayEspecialidad[],int validos,stEspecialidad especialidad);                   //AGREGAMOS UNA STRUCT ESPECIALIDAD AL ARREGLO
int mostrarArrayEspecialidad (stEspecialidad arrayEspecialidad[],int validos);                                          //MOSTRAMOS EL ARRAY DE ESPECIALIDAD
stEspecialidad buscarEspecialidadArray (stEspecialidad arrayEspecialidad[],int validos,int numeroEspecialidad);         //BUSCAMOS UNA ESPECIALIDAD EN EL ARRAY SEGUN SU ID
stEspecialidad eleccionEspecialidad(stEspecialidad arrayEspecialidades[],int validos);                                  //SELECCIONAMOS UNA ESPECIALIDAD Y LA RETORNAMOS
///PROTOTIPADO ARCHIVO PACIENTES
void cargarArchivoPacientes (char filePacientes[],stPaciente paciente);             //CARGA ARCHIVO DE STRUCT PACIENTE
int contarPacientesArchivo(char filePacientes[]);                                   //RETORNAMOS LA CANTIDAD DE PACIENTES EN EL ARCHIVO
void mostrarArchivoPacientes (char filePacientes[]);                                //MOSTRAMOS EL ARCHIVO PACIENTES
int busquedaArchivoPaciente (char filePacientes[],int DNI);                      //BUSCAMOS EN EL ARCHIVO UN PACIENTE MEDIANTE SU DNI
void modificarArchivoPacientes (char filePacientes[]);                              //MODIFICAMOS UN PACIENTE EN EL ARCHIVO BUSCANDO SU DNI
void altaBajaArchivoPacientes (char filePacientes[]);                               //DAMOS DE ALTA O BAJA UN PACIENTE EN EL ARCHIVO BUSCANDO SU DNI
int modificarEstado (int estado);                                                   //MODIFICA EL ESTADO DEL PACIENTE Y LO RETORNA
///PROTOTIPADO ARCHIVO ESPECIALIDADES
void cargarArchivoEspecialidades (char fileEspecialidades[]);                       //CARGA ARCHIVO ESPECIALIDADES
void mostrarArchivoEspecialidades (char fileEspecialidades[]);                      //MUESTRA ARCHIVO ESPECIALIDADES
int archivoToArrayEspecialidad (char fileEspecialidad[],stEspecialidad arrayEspecialidad[],int validos,int dimension);//PASAJE ARCHIVO A ARRAY ESPECIALIDADES
void modificarArchivoEspecialidad (char fileEspecialidad[]);                        //MODIFICACION REGISTRO ESPECIALIDAD
int busquedaArchivoEspecialidad (char fileEspecialidad[],char nombreEspecialidad[]);//BUSCAR UN REGISTRO ESPECIALIDAD EN ARCHIVO MEDIANTE SU NOMBRE
///PROTOTIPADO LISTA CONSULTA HISTORIAL CLINICO
nodoFila* inicLista();
nodoFila* crearNodoListaConsulta(int DNI);                                          //CREA NODO DE LISTA CONSULTAS CON DNI
nodoFila* agregarAlFinal (nodoFila*listaConsulta,nodoFila*nuevoNodo);               //AGREGAMOS AL FINAL DE LA LISTA COMO COMPORTAMIENTO DE FILA
nodoFila* buscarUltimoConsulta (nodoFila*listaConsulta);                            //BUSCAMOS EL ULTIMO NODO PARA AGREGAR UNO PROXIMO AL FINAL
///PROTOTIPADO FILA CONSULTAS HISTORIAL CLINICO
void inicFila (Fila * fila);                                                        //INICIALIZAR FILA EN NULL
void agregarFila (Fila * fila,int DNI);                                             //AGREGAMOS UN DNI A LA FILA DE CONSULTA (SIMRPRE AL FINAL)
int extraerFila (Fila*fila);                                                        //EXTRACCION UNA CONSULTA DE LA FILA
int verPrimero (nodoFila*lista);                                                    //VISUALIZAR PRIMERO PARA RETORNO
nodoFila * borrarPrimero (nodoFila*lista);                                          //BORRADO DE UN NODO DE LA LISTA CONSULTA
void cargaFila(Fila * fila);                                                        //FUNCION CONTROLADORA DE CARGA FILA CONSULTA
void muestraFila (Fila * fila);                                                     //MUESTRA FILA CONSULTA GENERADA
#endif // ASIGNACION-TURNOS_H_INCLUDED
