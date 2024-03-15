#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct rep_colaDePrioridadPersona {
  TPersona* cola;
  TFecha* ids;
  nat cant;
  nat max;
  nat orden; //min = 0, max = 1
};


TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona cp = new rep_colaDePrioridadPersona;
  cp->orden = 0;
  cp->cant = 0;
  cp->max = N+1;
  cp->cola = new TPersona[N+1];
  cp->ids = new TFecha[N+1];
  for (nat i = 0; i < cp->max; i++) {
    cp->ids[i] = NULL;
    cp->cola[i] = NULL;
  }
  return cp;
} 

void swapPersonas(nat index1, nat index2 ,TColaDePrioridadPersona &cp){
 TPersona aux = cp->cola[index1];
 cp->cola[index1] = cp->cola[index2];
 cp->cola[index2] = aux;
} 

/*La función siftUp realiza el filtrado ascendente (también conocido como "sift-up" o "percolate-up") a partir de un índice dado. 
Se utiliza después de insertar un elemento en el heap para asegurarse de que dicho elemento se coloque en la posición correcta según la propiedad 
de ordenamiento del heap. El proceso implica comparar el valor del elemento con el valor de su padre y, si el valor del elemento es mayor 
(en un heap máximo) o menor (en un heap mínimo), se intercambian. Luego, se repite el proceso hasta que el elemento llegue a una posición 
donde ya no sea necesario realizar más intercambios.*/
void filtrado_ascendente(nat pos, TColaDePrioridadPersona &cp){
/*   if(pos == 0){
    return;
  }
  nat iPadre = (pos-1)/2;
//LE SACASTE LOS -1 A LOS PADRES DEL HEAP
  while(pos > 0 && compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->cola[pos])), fechaTEvento(primerEventoDeTPersona(cp->cola[iPadre]))) == -1){
    swapPersonas(pos, iPadre, cp);
    pos = iPadre;
    iPadre = (pos-1)/2;
  } */
  if(pos == 0){
    return;
  }
  nat iPadre = (pos)/2;

  if(cp->orden == 0){
    while(pos > 0 && compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->cola[pos])), fechaTEvento(primerEventoDeTPersona(cp->cola[iPadre]))) == -1){
      swapPersonas(pos, iPadre, cp);
      pos = iPadre;
      iPadre = (pos)/2;
  } 
  }else if(cp->orden == 1){
    while(pos > 0 && compararTFechas(fechaTEvento(primerEventoDeTPersona(cp->cola[pos])), fechaTEvento(primerEventoDeTPersona(cp->cola[iPadre]))) == 1){
      swapPersonas(pos, iPadre, cp);
      pos = iPadre;
      iPadre = (pos)/2;
  }
  }
}

TFecha obtenerFechaPrioridad(TPersona persona){
  return fechaTEvento(primerEventoDeTPersona(persona));
}

/*La función siftDown realiza el filtrado descendente (también conocido como "sift-down" o "percolate-down") a partir de un índice dado. Se utiliza después
 de extraer el elemento máximo (o mínimo) del heap para mantener la propiedad de ordenamiento. El proceso implica comparar el valor del elemento con los 
 valores de sus hijos y, si el valor del elemento es menor (en un heap máximo) o mayor (en un heap mínimo), se intercambian. Luego, se sigue descendiendo 
 en el heap hacia el hijo con el valor máximo (en un heap máximo) o mínimo (en un heap mínimo), y se repite el proceso hasta que el elemento llegue a una 
 posición donde ya no sea necesario realizar más intercambios.*/
void filtrado_descendente(nat pos, TColaDePrioridadPersona &cp){
   if(pos >= cp->cant){
    return;
  }
  nat iHijoIzq = pos*2+1;
  nat iHijoDer = pos*2+2;
  nat minIndex = pos;

   if(cp->orden == 0){
       if(iHijoIzq < cp->cant && (compararTFechas(obtenerFechaPrioridad(cp->cola[iHijoIzq]), obtenerFechaPrioridad(cp->cola[minIndex])) == -1)){
        minIndex = iHijoIzq;
      }
      if(iHijoDer < cp->cant && (compararTFechas(obtenerFechaPrioridad(cp->cola[iHijoDer]), obtenerFechaPrioridad(cp->cola[minIndex])) == -1)){
        minIndex = iHijoDer;
      }
   } 
   else if (cp->orden == 1){
       if(iHijoIzq < cp->cant && (compararTFechas(obtenerFechaPrioridad(cp->cola[iHijoIzq]), obtenerFechaPrioridad(cp->cola[minIndex])) == 1)){
        minIndex = iHijoIzq;
      }
      if(iHijoDer < cp->cant && (compararTFechas(obtenerFechaPrioridad(cp->cola[iHijoDer]), obtenerFechaPrioridad(cp->cola[minIndex])) == 1)){
        minIndex = iHijoDer;
   }
   }
   if(minIndex != pos){
    swapPersonas(pos, minIndex, cp);
    filtrado_descendente(minIndex, cp);
  }

//VERSION ITERATIVA PORQUE PENSE QUE FALLABA LA RECURSION PERO EN REALIDAD LA FALLADITA ERA YO
/*   nat minIndex = pos;
  while(minIndex < cp->cant){
    nat iHijoIzq = pos*2+1;
    nat iHijoDer = pos*2+2;
    
    if(iHijoIzq < cp->cant && (compararTFechas(obtenerFechaPrioridad(cp->cola[iHijoIzq]), obtenerFechaPrioridad(cp->cola[minIndex])) == -1)){
      minIndex = iHijoIzq;
    }
    if(iHijoDer < cp->cant && (compararTFechas(obtenerFechaPrioridad(cp->cola[iHijoDer]), obtenerFechaPrioridad(cp->cola[minIndex])) == -1)){
      minIndex = iHijoDer;
    }

    if(minIndex != pos){
      swapPersonas(pos, minIndex, cp);
      pos = minIndex;
  } else{
    break;
  }
  } */
} 

void invertirPrioridad(TColaDePrioridadPersona &cp) {
  if(cp->orden == 0){
    cp->orden = 1;
  } 
  else{
    cp->orden = 0;
  }
 
 int start = 0;
 int end = cp->cant - 1;
    while (start < end) {
        /* TPersona aux = cp->cola[start];
        cp->cola[start] = cp->cola[end];
        cp->cola[end] = aux; */
        swapPersonas(start, end, cp);   // Intercambiar elementos
       //filtrado_descendente(start, cp);
        // Mover los índices
        start++;
        end--;
    }
  
}

void liberarCP(TColaDePrioridadPersona &cp) {
  if(cp != NULL && cp->cant > 0){
    for(nat i = 0; i < cp->cant; i++){
      liberarTPersona(cp->cola[i]);
      cp->cola[i] = NULL;
     // cp->ids[i] = NULL;
    }
  }
  delete[] cp->cola;
  delete[] cp->ids;
  delete cp;
  cp = NULL;
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp) {
  if (cp->cant == cp->max || idTPersona(persona) > cp->max){
    return;
  }

  cp->cola[cp->cant] = persona;
 
  filtrado_ascendente(cp->cant, cp);
  cp->ids[idTPersona(persona)] = obtenerFechaPrioridad(persona);
  cp->cant++;
}

bool estaVaciaCP(TColaDePrioridadPersona cp) {
  return cp->cant == 0;
}

TPersona prioritaria(TColaDePrioridadPersona cp) {
  return cp->cola[0];
} 

void eliminarPrioritaria(TColaDePrioridadPersona &cp) {
  if(cp->cant == 0){
    return;
  }
  
  cp->ids[idTPersona(cp->cola[0])] = NULL;
  liberarTPersona(cp->cola[0]);
  cp->cola[0] = cp->cola[cp->cant-1];
  cp->cant--;
  filtrado_descendente(0, cp);
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
  if(cp->cant == 0 || id > cp->max || cp->ids[id] == NULL){
    return false;
  }
  return true;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp){
  if(!estaEnCP(id, cp)){
    return NULL;
  }
  return cp->ids[id];
}