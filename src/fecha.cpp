#include "../include/fecha.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////
struct rep_fecha {
    nat dia, mes, anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = NULL;
    nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    delete fecha;
    fecha = NULL;
}

void imprimirTFecha(TFecha fecha) {
    printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio);
}

nat diasMes (nat mes, nat anio){
   nat dia;
    switch (mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: dia = 31;
        break;
        case 4: case 6: case 9: case 11: dia=30; 
        break;
        case 2: if ((anio%4==0 && anio%100!=0) || anio%400==0) dia=29;
                else dia=28;
    }
    return dia;
}

void aumentarTFecha(TFecha &fecha, nat dias) {
    fecha->dia += dias;
    while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {

        fecha->dia -= diasMes(fecha->mes, fecha->anio);
        fecha->mes++;

        if (fecha->mes > 12) { 
            fecha->mes = 1;
            fecha->anio++;
        }
    }
}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 0;
    if ((fecha1 -> anio != fecha2 -> anio) || (fecha1 -> mes != fecha2 -> mes) || (fecha1 -> dia != fecha2 -> dia)){
        if ((fecha1 -> anio < fecha2 -> anio) || ((fecha1 -> anio == fecha2 -> anio) && (fecha1 -> mes < fecha2-> mes ))||
        ((fecha1 -> anio == fecha2 -> anio) && (fecha1 -> mes == fecha2 -> mes) && (fecha1 -> dia < fecha2 -> dia))){
            res = -1;
        } else 
            res = 1;
    }
    return res;
}

TFecha copiarTFecha(TFecha fecha) {
    TFecha fechaCopia = new rep_fecha;
    fechaCopia->dia = fecha->dia;
    fechaCopia->mes = fecha->mes;
    fechaCopia->anio = fecha->anio;
    return fechaCopia;
}
/////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
/////////////////////////////////
