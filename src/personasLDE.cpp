#include "../include/personasLDE.h"
#include <string.h>

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_nodoLDE {
    TPersona persona;
    rep_nodoLDE* sig;
    rep_nodoLDE* ant;
};
typedef struct rep_nodoLDE *TNodoLDE;

struct rep_personasLDE {
    nat cant = 0; 
    rep_nodoLDE* inicio; 
    rep_nodoLDE* fin; 
};

TPersonasLDE crearTPersonasLDE(){ //Lista vacia: inicio y final en NULL
    TPersonasLDE lista = new rep_personasLDE;
    lista->inicio = NULL;
    lista->fin = NULL;
    return lista;
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos){
    TNodoLDE nodo = new rep_nodoLDE;
    nodo->persona = persona;
    nodo->sig = NULL;
    nodo->ant = NULL;

    if (personas->inicio == NULL && personas->fin == NULL){ 
        personas->inicio = nodo;
        personas->fin = nodo;
        personas->cant = personas->cant + 1;
    } else{
        TNodoLDE iter = personas->inicio;
        nat i = 1;
        if (pos > personas->cant){ //insertar al final
            personas->fin->sig = nodo;
            nodo->ant = personas->fin;
            personas->fin = nodo;          

        } else if (pos == 1){
            personas->inicio = nodo;
            nodo->sig = iter;
            iter->ant = nodo;

        } else{
            while (iter->sig != NULL && pos > i){ //Busco la posición
                iter = iter->sig;
                i++;
            }
            nodo->sig = iter;
            iter->ant->sig = nodo;
            iter->ant = nodo;
            nodo->ant = iter->ant;
            
        }
        personas->cant++;  
    }
}

void liberarNodoLDE(TNodoLDE &nodo) {
    if (nodo != NULL) {
        liberarTPersona(nodo->persona);
        liberarNodoLDE(nodo->sig); // Liberar el siguiente nodo de manera recursiva
        delete nodo; // Liberar el nodo actual
        nodo = NULL;
    }
}

void liberarTPersonasLDE(TPersonasLDE &personasLDE) {
    if (personasLDE != NULL) {
        liberarNodoLDE(personasLDE->inicio); // Liberar todos los nodos de la lista
        delete personasLDE;  // Liberar la estructura rep_personasLDE
        personasLDE = NULL;
    }
}

void imprimirTPersonasLDE(TPersonasLDE personas){
    TNodoLDE iter = personas->inicio;
    while (iter != NULL){
        imprimirTPersona(iter->persona);
        iter = iter->sig;
    }
}

nat cantidadTPersonasLDE(TPersonasLDE personas){
    return personas->cant;
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas){
    if (personas != NULL){
        TNodoLDE nodo = personas->inicio; // Obtener el nodo a eliminar
        personas->inicio = nodo->sig; // Actualizar el inicio de la lista
       
       if (personas->inicio == NULL){ // caso 1: solo habia un nodo
            personas->fin = NULL;
       } else{
            nodo->sig->ant = NULL;
       }
       personas->cant = personas->cant - 1;
       nodo->sig = NULL;
       liberarNodoLDE(nodo);
       nodo = NULL; // Liberar el nodo
    }
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas){
    if (personas != NULL){
        TNodoLDE nodo = personas->fin; // Obtener el nodo a eliminar
        personas->fin = nodo->ant;

        if (personas->fin == NULL){
            personas->inicio = NULL;
        } else{
            nodo->ant->sig = NULL;
        }
        personas->cant = personas->cant - 1;
        nodo->ant = NULL;
        
        liberarNodoLDE(nodo);
        nodo = NULL;      
    }
} 

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id){
    TNodoLDE iter = personas->inicio;
    while (iter != NULL && idTPersona(iter->persona) != id){
         iter=iter->sig; 
    }
    return iter != NULL;   
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id){
    TNodoLDE iter = personas->inicio;
    while ((iter != NULL) && idTPersona(iter->persona) != id){
        iter = iter->sig;
    }
    return iter->persona;
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2) {
    TPersonasLDE listaC = new rep_personasLDE; 
    listaC->cant = personas1->cant + personas2->cant;

    if (personas1->cant == 0) { // Si la primera lista está vacía, la nueva lista es la segunda lista
        listaC->inicio = personas2->inicio;
        listaC->fin = personas2->fin;
    } else if (personas2->cant == 0) { // Si la segunda lista está vacía, la nueva lista es la primera lista
        listaC->inicio = personas1->inicio;
        listaC->fin = personas1->fin;
    } else { // Ambas listas tienen elementos
        personas1->fin->sig = personas2->inicio; 
        personas2->inicio->ant = personas1->fin; 
        listaC->inicio = personas1->inicio; 
        listaC->fin = personas2->fin; 
    }

    delete personas1; 
    delete personas2; 
    return listaC;
}


void insertarInicioDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){
    insertarTPersonasLDE(personas, persona, 1);

}

void insertarFinalDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){    
    insertarTPersonasLDE(personas, persona, personas->cant+1);

}

TPersona obtenerInicioDeTPersonasLDE(TPersonasLDE personas){
   return personas->inicio->persona;
}

TPersona obtenerFinalDeTPersonasLDE(TPersonasLDE personas){
    return personas->fin->persona;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

 void eliminarPersonaConNombreTPersonasLDE(TPersonasLDE &personas, const char nombre[100]){
    if(personas->inicio != NULL){
        if(strcmp(nombreTPersona(personas->inicio->persona), nombre) == 0){ // Nombre al inicio
            eliminarInicioTPersonasLDE(personas);
        } 
        else if(strcmp(nombreTPersona(personas->fin->persona), nombre) == 0){ // Nombre al final
            eliminarFinalTPersonasLDE(personas);
        }
        else{
            TNodoLDE iter = personas->inicio;
            //nat pos = 1;
            int comp = strcmp(nombreTPersona(iter->persona), nombre);
    
            while ((iter != NULL) && comp != 0) { 
                //pos++;
                iter = iter->sig;
                comp = strcmp(nombreTPersona(iter->persona), nombre);
            }
            if (iter->sig != NULL){ // fix for possible null pointer
                 iter->sig->ant = iter->ant;
            }
            if (iter->ant != NULL){ // fix for possible null pointer
                iter->ant->sig = iter->sig;
            }

            liberarTPersona(iter->persona);
            personas->cant--;
            delete iter;
            iter = NULL;
        }
    }
}


bool estaPersonaConNombreEnTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    if (personas == NULL || nombre == NULL){
        return false;
    }
    TNodoLDE iter = personas->inicio;

    while (iter != NULL) {
        /* const char* nombrePersona = nombreTPersona(iter->persona);
        if (nombrePersona != NULL && strcmp(nombrePersona, nombre) == 0) {
            return true; // Se encontró la persona con el nombre buscado
        } */
        if(nombreTPersona(iter->persona) != NULL && strcmp(nombreTPersona(iter->persona), nombre) == 0){
            return true;
        }
        iter = iter->sig;
    }

    return false; // No se encontró la persona con el nombre buscado
}


TPersona obtenerPersonaConNombreTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    if(personas == NULL){
        return NULL;
    }
    TNodoLDE iter = personas->inicio;
    //int comp = strcmp(nombreTPersona(iter->persona), nombre);
    while ((iter->sig != NULL) && (strcmp(nombreTPersona(iter->persona), nombre) != 0)) {
        iter = iter->sig;
    //    comp = strcmp(nombreTPersona(iter->persona), nombre);
    }
    if(iter == NULL){
        return NULL;
    }
    return (iter->persona);
}
///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

