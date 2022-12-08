#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <string.h>
#include "Gestion-atenciones.h"
#include "asignacion-turnos.h"
#include "pila.h"

///FUNCIONES PACIENTE
stPaciente cargarPaciente                   (int idPaciente,int DNI ){
    stPaciente aux;
    printf("------CARGA PACIENTE-------\n");
    aux.idPaciente=idPaciente;
    aux.DNI=DNI;
    printf("Nombre Paciente: \n");
    fflush(stdin);
    scanf("%s",&aux.nombrePaciente);
    printf("Apellido Paciente: \n");
    fflush(stdin);
    scanf("%s",&aux.apellidoPaciente);
    int obraSocial;
    do{
        printf("Obra Social: (1-SAMI,2-OSARPI,3-MEDIFE,4-IOMA,5-UNION PERSONAL,6-NINGUNA DE ESTAS) \n"); ///VALIDACION OBRA SOCIAL
        scanf("%d",&obraSocial);
        if(obraSocial<=6 && obraSocial>=1){
            aux.obraSocial=obraSocial;
        }else{
            printf("Obra social incorrecta ingrese nuevamente \n");
        }
    }while(obraSocial>6 || obraSocial<1);
    aux.estado=1;
    return aux;
}
void mostrarPaciente                        (stPaciente paciente){
    printf("PACIENTE: \n");
    printf("ID Paciente: %d\n",paciente.idPaciente);
    printf("Estado Paciente: %d\n",paciente.estado);
    printf("Nombre Paciente: %s\n",paciente.nombrePaciente);
    printf("Apellido Paciente: %s\n",paciente.apellidoPaciente);
    printf("DNI Paciente: %d\n",paciente.DNI);
    printf("Obra Social: %d (1-SAMI,2-OSARPI,3-MEDIFE,4-IOMA,5-UNION PERSONAL,6-NINGUNA DE ESTAS) \n",paciente.obraSocial);
}
void mostrarPacienteActivo                     (stPaciente paciente){
    if(paciente.estado==1){
        printf("PACIENTE: \n");
        printf("ID Paciente: %d\n",paciente.idPaciente);
        printf("Estado Paciente: %d\n",paciente.estado);
        printf("Nombre Paciente: %s\n",paciente.nombrePaciente);
        printf("Apellido Paciente: %s\n",paciente.apellidoPaciente);
        printf("DNI Paciente: %d\n",paciente.DNI);
        printf("Obra Social: %d (1-SAMI,2-OSARPI,3-MEDIFE,4-IOMA,5-UNION PERSONAL,6-NINGUNA DE ESTAS) \n",paciente.obraSocial);
    }
}
///FUNCIONES ESPECIALIDAD
stEspecialidad cargarEspecialidad           (int idEspecialidad){
    stEspecialidad aux;
    aux.idEspecialidad=idEspecialidad;
    printf("---------CARGA ESPECIALIDAD--------\n");
    printf("Nombre doctor: \n");
    fflush(stdin);
    scanf("%s",aux.nombreDoctor);
    printf("Nombre especialidad: \n");
    fflush(stdin);
    scanf("%s",aux.especialidadMedica);
    return aux;
}
void mostrarEspecialidad                    (stEspecialidad especialidad){
    printf("\n*********ESPECIALIDAD*********\n");
    printf("Especialidad: %d \n",especialidad.idEspecialidad);
    printf("Nombre doctor: %s \n",especialidad.nombreDoctor);
    printf("Nombre especialidad: %s \n",especialidad.especialidadMedica);
    printf("******************************\n");
}
///FUNCIONES ATENCION
stAtencion cargarAtencionStruct(int obraSocial,int idRegistro){
    stAtencion atencion;
    atencion.idAtencion=idRegistro;
    printf("Fecha atencion: \n");
    fflush(stdin);
    scanf("%s",&atencion.fechaAtencion);
    printf("Diagnostico atencion: \n");
    fflush(stdin);
    scanf("%s",&atencion.diagnostico);
    int gravedad;
    do{
        printf("Gravedad atencion: (1-LEVE,2-CUIDADO,3-URGENTE) \n");
        scanf("%d",&gravedad);
        if(gravedad<=3&&gravedad>=1){
            atencion.gravedad=gravedad;
        }else{
            printf("Gravedad erronea cargar nuevamente: \n");
        }
    }while(gravedad>3||gravedad<1);

    atencion.costoConsulta=calcularCostoAtencion(atencion.gravedad,obraSocial);
    return atencion;
}
void mostrarAtencionStruct(stAtencion atencion){
        printf("ID atencion: %d\n",atencion.idAtencion);
        printf("Diagnostico paciente: %s\n",atencion.diagnostico);
        printf("Fecha atencion: %s\n",atencion.fechaAtencion);
        printf("Costo atencion: %.2f \n",atencion.costoConsulta);
        printf("Gravedad atencion: %d (1-LEVE,2-CUIDADO,3-URGENTE)\n",atencion.gravedad);
}
///FUNCIONES ARCHIVO ATENCIONES
void cargarArchivoAtenciones                (char fileAtenciones[],stRegistroMedico atencion){
    FILE*archi=fopen(fileAtenciones,"ab");
    stRegistroMedico aux;
    if(archi){
            aux=atencion;
            fwrite(&aux,sizeof(stRegistroMedico),1,archi);
        fclose(archi);
    }
}
int contarAtenciones(char fileAtenciones[]){
    FILE*archi=fopen(fileAtenciones,"rb");
    stRegistroMedico aux;
    int cant=0;
    if(archi){
            fseek(archi,0,SEEK_END);
            cant=ftell(archi)/sizeof(stRegistroMedico);
        fclose(archi);
    }
    return cant;
}
void mostrarArchivoAtenciones               (char fileName[]){
    FILE*archi=fopen(fileName,"rb");
    stRegistroMedico aux;
    if(archi){
            while(fread(&aux,sizeof(stRegistroMedico),1,archi)>0){
                mostrarRegistroAtencion(aux);
            }
        fclose(archi);
    }
}
void cargarAtencion(char fileAtenciones[],char filePacientes[],nodoArbolPacientes*raiz,char arrayEspecialidades[],int validos){
    stPaciente paciente;
    printf("----Atencion Paciente----\n");
    paciente=atenderPaciente(filePacientes,raiz);
    stEspecialidad especialidad;
    especialidad=eleccionEspecialidad(arrayEspecialidades,validos);
    stRegistroMedico aux;
    int idRegistro=contarAtenciones(fileAtenciones);
    aux.idRegistro=idRegistro+1;
    aux.idEspecialidad=especialidad.idEspecialidad;
    aux.DNI=paciente.DNI;
    aux.atencion=cargarAtencionStruct(paciente.obraSocial,idRegistro);
    cargarArchivoAtenciones(fileAtenciones,aux);
}
float calcularCostoAtencion (int gravedad, int obraSocial){
    float costoAtencion;
    float costoGravedad=calcularCostoGravedad(gravedad);
    float descuentoObraSocial=calcularCostoObraSocial(obraSocial);
    costoAtencion=costoGravedad-descuentoObraSocial;
    if(costoAtencion<0){
        costoAtencion=0;
    }
    return costoAtencion;
}
float calcularCostoGravedad(int gravedad){
    float costoGravedad;
    switch(gravedad){
    case 1:
        costoGravedad=200;
        break;
    case 2:
        costoGravedad=400;
        break;
    case 3:
        costoGravedad=800;
        break;
    }
    return costoGravedad;
}
float calcularCostoObraSocial(int obraSocial){
    float descuentoObraSocial;
    switch(obraSocial){
    case 1:
        descuentoObraSocial=200;
        break;
    case 2:
        descuentoObraSocial=400;
        break;
    case 3:
        descuentoObraSocial=800;
        break;
    case 4:
        descuentoObraSocial=100;
        break;
    case 5:
        descuentoObraSocial=50;
        break;
    case 6:
        descuentoObraSocial=0;
        break;
    }
    return descuentoObraSocial;
}
void mostrarRegistroAtencion (stRegistroMedico aux){
    printf("------ATENCION----------\n");
    printf("ID atencion: %d\n",aux.idRegistro);
    printf("DNI paciente: %d\n",aux.DNI);
    mostrarAtencionStruct(aux.atencion);
}
///FUNCIONES LISTA-ATENCIONES
nodoListaAtencion* inicListaAtencion(){
    return NULL;
}
nodoListaAtencion* crearNodoListaAtencion(int DNI,stAtencion atencion){
    nodoListaAtencion*nuevoNodoAtencion=(nodoListaAtencion*)malloc(sizeof(nodoListaAtencion));
    nuevoNodoAtencion->DNI=DNI;
    nuevoNodoAtencion->atencion=atencion;
    nuevoNodoAtencion->siguiente=NULL;
    nuevoNodoAtencion->anterior=NULL;
    return nuevoNodoAtencion;
}
nodoListaAtencion* agregarPpioListaAtencion (nodoListaAtencion*listaAtencion,nodoListaAtencion*nuevoNodoAtencion){
    if(listaAtencion){
        nuevoNodoAtencion->siguiente=listaAtencion;
        if(listaAtencion->siguiente){
            listaAtencion->anterior=nuevoNodoAtencion;
        }
    }
    listaAtencion=nuevoNodoAtencion;
    return listaAtencion;
}
nodoListaAtencion* agregaFinalAtencion (nodoListaAtencion*listaAtencion,nodoListaAtencion*nuevoNodoAtencion){
    if(listaAtencion){
        nodoListaAtencion*ultimo=buscarUltimoListaAtencion(listaAtencion);
        ultimo->siguiente=nuevoNodoAtencion;
        nuevoNodoAtencion->anterior=ultimo;
    }else{
        listaAtencion=nuevoNodoAtencion;
    }
    return listaAtencion;
}
nodoListaAtencion* buscarUltimoListaAtencion(nodoListaAtencion*listaAtencion){
    nodoListaAtencion*ultimo=listaAtencion;
    if(ultimo->siguiente){
        ultimo=ultimo->siguiente;
    }
    return ultimo;
}
void mostrarListaAtencion (nodoListaAtencion*listaAtencion,nodoArbolPacientes*raiz){
    if(listaAtencion){
        nodoArbolPacientes* muestra=buscarPacienteArbol(raiz,listaAtencion->DNI);
        if(muestra->paciente.estado==1){
            mostrarPaciente(muestra->paciente);
            mostrarAtencionStruct(listaAtencion->atencion);
        }
        mostrarListaAtencion(listaAtencion->siguiente,raiz);
    }
}
void generarPilaSegunPaciente (nodoListaAtencion*listaAtencion,int DNI,Pila * historialClinico){
    nodoListaAtencion*seg=listaAtencion;
    while(seg){
        if(seg->DNI==DNI){ /// RECORREMOS LA LISTA, Y CADA VEZ QUE EL DNI SEA IGUAL AL QUE BUSCAMOS, APILAMOS EL ID ATENCION EN LA PILA DE ATENCIONES(HISTORIAL CLINICO)
            apilar(historialClinico,seg->atencion.idAtencion);
        }
        seg=seg->siguiente;
    }
}
void buscarAtencionSegunDNI (nodoListaAtencion*listaAtencion,int idAtencion,int idEspecialidad){
    nodoListaAtencion*seg=listaAtencion;
    int rta=-1;
    while(seg && rta==-1){
        if(seg->atencion.idAtencion==idAtencion){
            printf("\nID especialidad: %d\n",idEspecialidad);
            printf("ID paciente: %d \n",seg->DNI);
            mostrarAtencionStruct(seg->atencion);
            rta=0;
        }
        seg=seg->siguiente;
    }
}
///FUNCIONES ADL ATENCIONES
int agregarCelda(CeldaEspecialidad ADL[],int validos,CeldaEspecialidad nueva){
    ADL[validos]=nueva;
    validos++;
    return validos;
}
int existeCelda (CeldaEspecialidad ADL[],int validos,int idEspecialidad){
    int rta=-1;
    int i=0;
    while(i<validos && rta==-1){                                            //Mientras no encuentre el id y tenga datos
        if(ADL[i].idEspecialidad==idEspecialidad){
            rta=i;                                                          //Si lo encuentra retornamos la posicion, y cortamos la busqueda.
        }
        i++;
    }
    return rta;
}
int agregarADLatenciones (CeldaEspecialidad ADL[],int idEspecialidad,int validos,int DNI,stAtencion atencion){
    nodoListaAtencion*nuevoNodoAtencion=crearNodoListaAtencion(DNI,atencion);
    int i=existeCelda(ADL,validos,idEspecialidad);                    //Extraemos si la posicion de la celda si es que existe en el array
    if(i==-1){                                                              //Si no existe
        CeldaEspecialidad una;                                              //Creamos una celda nueva
        una.idEspecialidad=idEspecialidad;                                             //Asignamos los datos a la nueva celda.
        una.listaAtencion=NULL;
        validos=agregarCelda(ADL,validos,una);                              //Agregamos la nueva celda al array.
        i=validos-1;
    }
    ADL[i].listaAtencion=agregaFinalAtencion(ADL[i].listaAtencion,nuevoNodoAtencion);                         //Agregamos el nodo creado al arbol de la celda anteriormente validada.
    return validos;
}
int archivoToADLatenciones (CeldaEspecialidad ADL[],int dimension,char fileName[]){
    FILE*archi=fopen(fileName,"rb");
    stRegistroMedico aux;
    int DNI;
    int idEspecialidad;
    int validos=0;
    char diagnostico[20];
    char fechaAtencion[20];
    int gravedadAtencion;
    float costoAtencion;
    if(archi){
            while(fread(&aux,sizeof(stRegistroMedico),1,archi)>0 && validos<dimension){ //Mientras leamos datos.
                DNI=aux.DNI;                                                  //Inicializacion estructura Jugador desde un registro leido
                idEspecialidad=aux.idEspecialidad;
                validos=agregarADLatenciones(ADL,idEspecialidad,validos,DNI,aux.atencion);        //Agregamos el registro al arreglo, validando si existe o no y asignando correctamente la informacion.
            }
        fclose(archi);
    }
    return validos;
}
void mostrarADLatenciones (CeldaEspecialidad ADL[],int validos,stEspecialidad arrayEspecialidad[],int validosEspecialidad,nodoArbolPacientes* raiz){
    for(int i=0;i<validos;i++){
        stEspecialidad muestra=buscarEspecialidadArray(arrayEspecialidad,validosEspecialidad,ADL[i].idEspecialidad);
        mostrarEspecialidad(muestra);
        printf("MUESTRA LISTA ATENCIONES\n");
        mostrarListaAtencion(ADL[i].listaAtencion,raiz);
    }
}
///FUNCIONES CONSULTAS ADL
void consultaGanancia (CeldaEspecialidad ADL[],int validos,stEspecialidad arrayEspecialidad[],int validosEspecialidad){
    int especialidad;
    float costoTotal;
    char ctrl='s';
    do{
        mostrarArrayEspecialidad(arrayEspecialidad,validosEspecialidad); /// SE MUESTRA EL ARRAY DE ESPECIALIDADES PARA VISUALIZAR LA SELECCION
        printf ("Ingrese el ID de la especialidad a consultar:\n");
        scanf("%d",&especialidad);
        costoTotal = gananciaTotalEspecialidad (ADL,validos,arrayEspecialidad,validosEspecialidad,especialidad); /// SE RECORRE EL ADL, SE BUSCA LA ESPECIALIDAD CON EL ID Y SE CALCULA EL COSTO TOTAL DE LAS ATENCIONES
        printf("La ganancia total de la especialidad es de %.2f \n",costoTotal);
        printf("\nRealizar otra consulta? s|n\n");
        fflush(stdin);
        scanf("%c",&ctrl);
    }while(ctrl=='s'||ctrl=='S');
}
float gananciaTotalEspecialidad (CeldaEspecialidad ADL[],int validos,stEspecialidad arrayEspecialidad[],int validosEspecialidad,int especialidad){
    int flag = -1;
    int i=0;
    float costoTotal=0;
    while (i<validos && flag == -1) /// SE BUSCA EN EL ADL LA ESPECIALIDAD,CON EL ID RECIBIDO POR PARAMETRO.
    {
        if (ADL[i].idEspecialidad == especialidad) /// SI EL ID ESPECIALIDAD DE LA POSICION ACTUAL, COINCIDE CON EL INGRESADO POR PARAMETRO
        {
            costoTotal = costoDeEspecialidad(ADL[i].listaAtencion);  /// SE RECORRE LA LISTA PARA REALIZAR UN CONTEO DEL COSTO TOTAL DE LA ESPECIALIDAD
            flag = 1;
        }
        i++;
    }
    return costoTotal;
}
float costoDeEspecialidad (nodoListaAtencion* lista){
    float cant=0;
    nodoListaAtencion * seg  = lista;
    while (seg) /// SE RECORRE LA LISTA DE ATENCIONES
    {
        cant += seg->atencion.costoConsulta; /// SE GENERA UN ACUMULADOR DEL COSTO CONSULTA Y SE RETORNA
        seg = seg->siguiente;
    }
    return cant;
}
void consultaAtencionesObraSocial (CeldaEspecialidad ADL[],int validos,nodoArbolPacientes* raiz){
    int obraSocial;
    int cantidadAtenciones;
    char ctrl='s';
    do{
        printf("CONSULTA ATENCIONES POR OBRA SOCIAL\n");
        printf("\nIngrese ID de la obra social a consultar \n");
        printf("(1-SAMI,2-OSARPI,3-MEDIFE,4-IOMA,5-UNION PERSONAL,6-NINGUNA) \n");
        scanf("%d",&obraSocial);
        cantidadAtenciones = cantidadAtencionesPorObraSocial (ADL,validos,obraSocial,raiz); /// SE RECORRE EL ADL Y SE CUENTA LA CANTIDAD DE VECES QUE APARECE DICHA OBRA SOCIAL
        printf("La cantidad de atenciones de la obra social es de %d \n",cantidadAtenciones);
        printf("\nDesea realizar otra consulta? s|n \n");
        fflush(stdin);
        scanf("%c",&ctrl);
        system("cls");
    }while(ctrl=='s'||ctrl=='S');
}
int cantidadAtencionesPorObraSocial (CeldaEspecialidad ADL[],int validos,int obraSocial,nodoArbolPacientes* raiz){
    int cantAtenciones=0;
    for (int i=0;i<validos;i++) /// SE RECORRE EL ADL, Y SE GUARDA EN UN ACUMULADOR LA CANTIDAD DE ATENCIONES QUE COINCIDEN CON LA OBRA SOCIAL INGRESADA POR PARAMETRO
    {
        cantAtenciones += cantAtencionesPorObraLista (ADL[i].listaAtencion,obraSocial,raiz);
    }
    return cantAtenciones;
}
int cantAtencionesPorObraLista (nodoListaAtencion *lista,int obraSocial,nodoArbolPacientes* raiz){
    int cant=0;
    nodoListaAtencion * seg  = lista;
    while (seg)
    {
        nodoArbolPacientes* aux = buscarPacienteArbol(raiz,seg->DNI); /// SE BUSCA EN EL ARBOL DE PACIENTES Y SE COPIA EN UN AUX LA ESTRUCTURA, PARA EXTRAER LA OBRA SOCIAL.
        if (aux->paciente.obraSocial==obraSocial) /// SI COINCIDE LA OBRA SOCIAL DEL PACIENTE CON LA INGRESADA POR PARAMETRO SE SUMA EN UN CONTADOR.
        {
            cant++;
        }
        seg = seg->siguiente;
    }
    return cant;
}
void consultaHistorialMedico (CeldaEspecialidad ADL[],int validosAtencion,nodoArbolPacientes* raiz,int DNI){
    Pila historialClinico;
    inicpila(&historialClinico);
    nodoArbolPacientes*busqueda=buscarPacienteArbol(raiz,DNI); /// BUSCAMOS EL PACIENTE EN EL ARBOL CON EL DNI QUE TRAEMOS DE LA FILA
    printf("------------------------------------\n");
    printf("\nDNI paciente consultar: %d\n",DNI);
    if(busqueda){ /// SI EL DNI EXISTE EN EL ARBOL
            int DNIpaciente=busqueda->paciente.DNI; /// SE GUARDA EL DNI DEL PACIENTE BUSCADO EN EL ARBOL
        for(int i=0;i<validosAtencion;i++){
            generarPilaSegunPaciente(ADL[i].listaAtencion,DNIpaciente,&historialClinico); /// SE GENERA UNA PILA CON TODAS LAS ATENCIONES DE LA POSICION ACTUAL DEL ARREGLO
        }
            imprimirPilaHistorial(&historialClinico,ADL,validosAtencion); /// SE ENVIA A MOSTRAR LA PILA DE ATENCIONES (HISTORIAL CLINICO)
    }else{
        printf("El DNI consultado no existe en el registro \n");
    }
}
void imprimirPilaHistorial (Pila* historialClinico,CeldaEspecialidad ADL[],int validosAtencion){
    mostrar(historialClinico);
    printf("Historial Medico: \n");
    while(!pilavacia(historialClinico)){ /// MIENTRAS LA PILA DE HISTORIAL MEDICO NO ESTE VACIA
            int idAtencion=tope(historialClinico); /// EXTRAIGO EL TOPE DE LA PILA (ID ATENCION)
            int i=0;
        while(i<validosAtencion){
            buscarAtencionSegunDNI(ADL[i].listaAtencion,idAtencion,ADL[i].idEspecialidad); /// BUSCA LA ATENCION EN EL ADL Y SE EJECUTA LA MUESTRA
            i++;
        }
        desapilar(historialClinico); /// UNA VEZ ENCONTRADO Y MOSTRADO, SE DESAPILA, PARA EXTRAER EL PROXIMO ID ATENCION
    }
}
