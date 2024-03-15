#include "../include/aplicaciones.h"
#include "../include/tablaPersonas.h"
#include "../include/colaDePrioridadPersona.h"
#include "../include/persona.h"

void listarEnOrden(TTablaPersonas t, char** nombres, nat n){
    if(n == 0) return;
    
    TColaDePrioridadPersona cola = crearCP(MAX_ID);

    for (nat i = 0; i < n; i++){
        TPersona persona = copiarTPersona(obtenerPersonaDeTTablaPersonas(t, nombres[i]));
        
        if (persona != NULL){
            insertarEnCP(persona, cola);
        }
        eliminarPersonaDeTTablaPersonas(t, nombres[i]);
    }

    while(!estaVaciaCP(cola)){
        imprimirTPersona(prioritaria(cola));
        eliminarPrioritaria(cola);
    }
    
    liberarCP(cola);
    //liberarTTablaPersonas(t);
}