#include "../include/agendaLS.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_agendaLS{
    TEvento evento;
    TAgendaLS sig;
};

TAgendaLS crearAgendaLS(){
    return NULL;
}

void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento){
    TAgendaLS nodo = new rep_agendaLS;
    nodo->evento = evento;

    if (agenda == NULL){
        nodo->sig = NULL;
        agenda = nodo;
    }
    else if ((compararTFechas(fechaTEvento(nodo->evento), fechaTEvento(agenda->evento)) <= 0)){
        nodo->sig = agenda;
        agenda = nodo;
    }
    else{
        TAgendaLS iter = agenda;
        while ((iter->sig != NULL) && (compararTFechas(fechaTEvento(nodo->evento), fechaTEvento(iter->sig->evento)) > 0)){
            iter = iter->sig;
        }
        nodo->sig = iter->sig;
        iter->sig = nodo;
    }
}

void imprimirAgendaLS(TAgendaLS agenda){ 
    while (agenda != NULL){
        imprimirTEvento(agenda->evento);
        agenda = agenda->sig;
    }
}

void liberarAgendaLS(TAgendaLS &agenda){
    TAgendaLS iter = agenda; // Puntero auxiliar para recorrer agenda
    while (iter != NULL){
        liberarTEvento(iter->evento);    // Liberar memoria del evento del nodo actual
        TAgendaLS siguiente = iter->sig; // Guardar referencia al siguiente nodo
        delete iter;                     // Liberar memoria del nodo actual
        iter = siguiente;                // Avanzar al siguiente nodo
    }
    agenda = NULL; // Actualizar el puntero de la agenda para que apunte a NULL
}

bool esVaciaAgendaLS(TAgendaLS agenda){
    return (agenda == NULL);
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda){ 
    TAgendaLS agendaCopia = NULL;

    while (agenda != NULL){
        // Crear un nuevo nodo para la copia de la agenda
        TAgendaLS nodo = new rep_agendaLS;
        nodo->evento = copiarTEvento(agenda->evento);
        nodo->sig = NULL;

        if (agendaCopia == NULL){
            // Si la copia esta vacia pongo el nuevo nodo al inicio de la copia
            agendaCopia = nodo;
        }
        else{
            // Si la copia no esta vacia creo un iterador para moverme en la copia y encontrar el ultimo nodo
            TAgendaLS iter = agendaCopia;
            while (iter->sig != NULL){
                iter = iter->sig;
            }
            iter->sig = nodo;
        }

        agenda = agenda->sig; // Esto solo lo puedo hacer porque la agenda fue pasada por copia (Tengo una copia del puntero)
    }
    return agendaCopia;
}

bool estaEnAgendaLS(TAgendaLS agenda, int id){
    while ((agenda != NULL) && idTEvento(agenda->evento) != id){
        agenda = agenda->sig;
    }
    return (agenda != NULL);
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id){
    while ((agenda != NULL) && idTEvento(agenda->evento) != id){
        agenda = agenda->sig;
    }
    return agenda->evento;
}

void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n){
    TEvento evento = obtenerDeAgendaLS(agenda, id);
    posponerTEvento(evento, n);

    TAgendaLS anterior = NULL;
    TAgendaLS iter = agenda;
    TAgendaLS posterior = NULL;
    // Buscamos el evento anterior y posterior a nuestro evento pospuesto
    while (iter->sig != NULL && (idTEvento(iter->evento) != id)){
        anterior = iter;
        iter = iter->sig;
    }
    posterior = iter->sig;

    if (compararTFechas(fechaTEvento(iter->evento), fechaTEvento(iter->sig->evento)) > 0){
        if (iter->sig != NULL && anterior != NULL && posterior != NULL){
            // Caso 1 El evento estaba en el medio
            anterior->sig = posterior;
        }
        else if (iter->sig != NULL && posterior != NULL){
            // Caso 2 no hay anterior porque el EVENTO ESTABA AL PRINCIPIO
            agenda = posterior;
            anterior = posterior;
            posterior = posterior->sig;
        }

        while (posterior != NULL && compararTFechas(fechaTEvento(iter->evento), fechaTEvento(posterior->evento)) > 0){
            anterior = anterior->sig;
            posterior = posterior->sig;
        }
        if (posterior != NULL){
            anterior->sig = iter;
            iter->sig = posterior;
        }
        else{
            anterior->sig = iter;
            iter->sig = NULL;
        }
    }
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha){
    if(hayEventosFechaLS(agenda,fecha)){
    while(agenda!=NULL && compararTFechas(fecha, fechaTEvento(agenda->evento))!=0){
        agenda = agenda->sig;
    }
    while(compararTFechas(fecha, fechaTEvento(agenda->evento))==0){
        imprimirTEvento(agenda->evento);
        agenda = agenda->sig;
    }
    }
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha){
    TAgendaLS iter = agenda;
    while(iter != NULL && (compararTFechas(fecha, fechaTEvento(iter->evento)) != 0)) {
        iter = iter->sig;
    }

    return (iter!=NULL);
}

void removerDeAgendaLS(TAgendaLS &agenda, int id){
    TAgendaLS iter = agenda;
    TAgendaLS anterior=NULL;
    while ((iter!=NULL) && (id != idTEvento(iter->evento))){
        anterior=iter;
        iter = iter->sig;
    }  
    if(anterior == NULL){ //Esta al principio de la lista
        agenda=agenda->sig;
    }else{ //Esta al final o en el medio de la lista
        anterior->sig = iter->sig;
    }
    liberarTEvento(iter->evento);
    delete(iter);
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TEvento primerEventoAgendaLS(TAgendaLS agenda){
    return agenda->evento;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////