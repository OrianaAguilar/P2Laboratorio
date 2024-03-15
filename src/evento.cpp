#include "../include/evento.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_evento {
    int id;
    char descripcion [MAX_DESCRIPCION];
    TFecha fecha; 
};

TEvento crearTEvento(int id, const char descripcion[MAX_DESCRIPCION], TFecha fecha) {
    TEvento nuevoEvento = NULL;
     nuevoEvento = new rep_evento;
     nuevoEvento->id = id;
     strcpy(nuevoEvento->descripcion, descripcion);
     nuevoEvento->fecha = fecha;
    return nuevoEvento;
}

void imprimirTEvento(TEvento evento) {
    if(evento != NULL){ //AGREGASTE ESTOOOOOOOOO
     printf("Evento %d: %s\nFecha: ", evento->id, evento->descripcion);
     imprimirTFecha(evento->fecha);
    }
}

void liberarTEvento(TEvento &evento) {
    liberarTFecha(evento->fecha);
    delete evento;
    evento = NULL;
}

int idTEvento(TEvento evento) {
    int res = 0;
    res = evento ->id;
    return res;
}

TFecha fechaTEvento(TEvento evento) {
    TFecha fecha = NULL;
    fecha = evento->fecha;
    return fecha;
}

void posponerTEvento(TEvento &evento, int dias) {
    aumentarTFecha(evento->fecha,dias);
}

TEvento copiarTEvento(TEvento evento) {
    TEvento eventoCopia = new rep_evento;
    eventoCopia->id = evento->id;
    strcpy(eventoCopia->descripcion, evento->descripcion);
    eventoCopia->fecha = copiarTFecha(evento->fecha);
    return eventoCopia;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
/////////////////////////////////
