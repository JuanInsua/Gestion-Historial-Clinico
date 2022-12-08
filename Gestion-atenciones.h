#ifndef GESTION-ATENCIONES_H_INCLUDED
#define GESTION-ATENCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "string.h"
#include "asignacion-turnos.h"

typedef struct{
    int idAtencion;
 	char fechaAtencion[11];
 	char diagnostico[100];
 	int gravedad;               //1-LEVE,2-CUIDADO,3-URGENTE
	float costoConsulta;
}stAtencion;                        ///ESTRUCTURA DE ATENCION

typedef struct{
    int idRegistro;
    stAtencion atencion;
	int DNI;
	int idEspecialidad;
} stRegistroMedico;                 ///REGISTRO DE ATENCION CONTENIENDO LOS ID DE UN PACIENTE, UN ID ESPECIALIDAD, Y UNA ATENCION CON SUS DATOS.

typedef struct{
    int idEspecialidad;
    struct nodoListaAtencion* listaAtencion;
}CeldaEspecialidad;                 ///CELDA DEL ARRAY DE LISTA, EL CUAL CONTIENE UN ID ESPECIALIDAD

typedef struct{
    stAtencion atencion;
    int DNI;
    struct nodoListaAtencion*siguiente;
    struct nodoListaAtencion*anterior;
}nodoListaAtencion;                 ///NODO DEL ARRAY DE LISTA, EL CUAL CONTIENE UN ID PACIENTE, Y UNA ATENCION CON SUS DATOS.

///PROTOTIPADO PACIENTE
stPaciente cargarPaciente                   (int idPaciente,int DNI );               //CARGA UN PACIENTE
void mostrarPaciente                        (stPaciente paciente);                      //MUESTRA UN PACIENTE
void mostrarPacienteActivo                     (stPaciente paciente);                  //MUESTRA UN PACIENTE ACTIVO
///PROTOTIPADO ESPECIALIDAD
stEspecialidad cargarEspecialidad           ();                                         //CARGA UNA ESPECIALIDAD
void mostrarEspecialidad                    (stEspecialidad especialidad);              //MUESTRA UNA ESPECIALIDAD
///FUNCIONES ATENCION
stAtencion cargarAtencionStruct(int obraSocial,int idRegistro);
void mostrarAtencionStruct(stAtencion atencion);
///PROTOTIPADO ARCHIVO ATENCIONES
void cargarArchivoAtenciones                (char fileAtenciones[],stRegistroMedico atencion);  //GENERAMOS UN REGISTRO ATENCION Y LO CARGAMOS AL ARCHIVO
void mostrarArchivoAtenciones               (char fileName[]);                                  //MOSTRAMOS UN REGISTRO ATENCION
void cargarAtencion(char fileAtenciones[],char filePacientes[],nodoArbolPacientes*raiz,char arrayEspecialidades[],int validos);    // GENERAMOS UNA ATENCION VALIDANDO SI EXISTE EL PACIENTE EN EL SISTEMA Y LO CARGAMOS AL ARCHIVO
float calcularCostoAtencion                 (int gravedad, int obraSocial);             //CALCULAMOS EL COSTO DE LA ATENCION PARA CARGARLO EN LA ATENCION
float calcularCostoGravedad                 (int gravedad);                             //GENERAMOS EL COSTO SEGUN LA GRAVEDAD DE LA ATENCION
float calcularCostoObraSocial               (int obraSocial);                           //GENERAMOS EL DESCUENTO SEGUN LA OBRA SOCIAL DEL PACIENTE
///PROTOTIPADO LISTA-ATENCIONES
nodoListaAtencion* inicListaAtencion        ();
nodoListaAtencion* crearNodoListaAtencion   (int idPaciente,stAtencion atencion);                                   //CREAMOS NODO DE LA LISTA DE ATENCION
nodoListaAtencion* agregarPpioListaAtencion (nodoListaAtencion*listaAtencion,nodoListaAtencion*nuevoNodoAtencion);  //AGREGANMOS NODO ATENCION AL PRINCIPIO DE LA LISTA
nodoListaAtencion* agregarFinalAtencion     (nodoListaAtencion*listaAtencion,nodoListaAtencion*nuevoNodoAtencion);  //AGREGANMOS NODO ATENCION AL FINAL DE LA LISTA
nodoListaAtencion* buscarUltimoListaAtencion(nodoListaAtencion*listaAtencion);                                      //BUSCAMOS EL ULTIMO DE LA LISTA
nodoListaAtencion* buscarListaAtencion      (nodoListaAtencion*listaAtencion,int idPaciente);                       //BUSCAMOS NODO EN LA LISTA POR ID
void buscarAtencionSegunDNI (nodoListaAtencion*listaAtencion,int idAtencion,int idEspecialidad);
void mostrarListaAtencion                   (nodoListaAtencion*listaAtencion,nodoArbolPacientes*raiz);              //MOSTRAMOS LA LISTA DE ATENCION DE FORMA RECURSIVA
//void buscarAtencionSeguinPaciente (nodoListaAtencion*listaAtencion,int idPaciente,Pila * historialClinico);
///PROTOTIPADO ADL ATENCIONES
int agregarCelda                            (CeldaEspecialidad ADL[],int validos,CeldaEspecialidad nueva);          //AGREGAMOS UNA CELDA ESPECIALIDAD AL ADL
int existeCelda                             (CeldaEspecialidad ADL[],int validos,int idEspecialidad);               //VALIDAMOS SI EXISTE ESPECIALIDAD EN EL ADL
int agregarADLatenciones                    (CeldaEspecialidad ADL[],int idEspecialidad,int validos,int idPaciente,stAtencion atencion);    //AGREGAMOS UNA CELDA VALIDANDO SI EXISTE, Y UN NODO A LA LISTA
int archivoToADLatenciones                  (CeldaEspecialidad ADL[],int dimension,char fileName[]);                                        //PASAMOS TODOS LOS REGISTROS DEL ARCHIVO ATENCIONES AL ADL
void mostrarADLatenciones                   (CeldaEspecialidad ADL[],int validos,stEspecialidad arrayEspecialidad[],int validosEspecialidad,nodoArbolPacientes* raiz);  //MUESTRA ADL
///PROTOTIPADO CONSULTAS ADL
void consultaGanancia                       (CeldaEspecialidad ADL[],int validos,stEspecialidad arrayEspecialidad[],int validosEspecialidad);   //CONSULTAMOS CUANTO ES LA GANANCIA DE UNA ESPECIALIDAD EN EL ADL SEGUN SUS ATENCIONES
float gananciaTotalEspecialidad             (CeldaEspecialidad ADL[],int validos,stEspecialidad arrayEspecialidad[],int validosEspecialidad,int especialidad);  //GENERAMOS EL VALOR TOTAL DEL COSTO ATENCION RESTANDO DESCUENTO
float costoDeEspecialidad                   (nodoListaAtencion* lista);                                             //GENERAMOS EL COSTO TOTAL POR ATENCION DE UNA ESPECIALIDAD EN PARTICULAR
void consultaAtencionesObraSocial           (CeldaEspecialidad ADL[],int validos,nodoArbolPacientes* raiz);         //CONSTULTA CUANTAS ATENCIONES TUVO UNA OBRA SOCIAL INGRESADA POR USUARIO
int cantidadAtencionesPorObraSocial         (CeldaEspecialidad ADL[],int validos,int obraSocial,nodoArbolPacientes* raiz);  //GENERAMOS LA CANTIDAD DE ATENCIONES RECORRIENDO LA OBRA SOCIAL
int cantAtencionesPorObraLista              (nodoListaAtencion *lista,int obraSocial,nodoArbolPacientes* raiz);             //GNENERAMOS LA CANTIDAD DE ATENCIONES POR OBRA SOCIAL RECORRIENDO LA LISTA ATENCIONES
void consultaHistorialMedico (CeldaEspecialidad ADL[],int validosAtencion,nodoArbolPacientes* raiz,int DNI);                //CONSULTA HISTORIAL MEDICO DESDE UNA FILA PREVIAMENTE CARGADA
#endif // GESTION-ATENCIONES_H_INCLUDED
