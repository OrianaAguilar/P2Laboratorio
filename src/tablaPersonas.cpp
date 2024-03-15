#include "../include/tablaPersonas.h"

struct rep_tablaPersonas {
    TPersonasLDE* tabla;
    int cant;
    int tam;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max){
    TTablaPersonas tabla = new rep_tablaPersonas;
    tabla->tam = max;
    tabla->cant = 0;
    tabla->tabla = new TPersonasLDE[max]; 

    for(int i = 0; i < max; i++){
        tabla->tabla[i] = crearTPersonasLDE();
    }
    return tabla;
}

void insertarPersonaEnTabla(TTablaPersonas &tabla, TPersona persona){
    if(tabla->cant < tabla->tam){
        int pos = funcionDeDispersion(nombreTPersona(persona)) % tabla->tam;
        TPersonasLDE lista = tabla->tabla[pos];
        insertarInicioDeTPersonasLDE(lista, persona);
        tabla->tabla[pos] = lista;
        tabla->cant++;
    }
}

void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
    eliminarPersonaConNombreTPersonasLDE(tabla->tabla[funcionDeDispersion(nombre) % tabla->tam], nombre);
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    //return obtenerInicioDeTPersonasLDE(tabla->tabla[funcionDeDispersion(nombre) % tabla->tam]) != NULL;
    int pos = funcionDeDispersion(nombre) % tabla->tam;
    if (tabla == NULL || tabla->tabla[pos] == NULL || cantidadTPersonasLDE(tabla->tabla[pos]) == 0){ 
        return false;
    }
    return estaPersonaConNombreEnTPersonasLDE(tabla->tabla[pos], nombre);
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    return obtenerPersonaConNombreTPersonasLDE(tabla->tabla[funcionDeDispersion(nombre) % tabla->tam], nombre);
}

void liberarTTablaPersonas(TTablaPersonas &tabla){
    if(tabla != NULL){
        for(int i = 0; i < tabla->tam ; i++){
            liberarTPersonasLDE(tabla->tabla[i]);
            tabla->tabla[i] = NULL;
        }
    }
    delete[] tabla->tabla;
    delete tabla;
    tabla = NULL;
}

void imprimirTTablaPersonas(TTablaPersonas tabla){
    for(int i = 0; i < tabla->tam ; i++){
        imprimirTPersonasLDE(tabla->tabla[i]);
    }
}