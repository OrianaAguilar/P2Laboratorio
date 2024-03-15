Código de Trigo:
TPersonasABB crearTPersonasABB()
{
    TPersonasABB nuevo = NULL;
    return nuevo;
}

bool esVacioTPersonasABB(TPersonasABB personasABB)
{
    bool vacio = (personasABB == NULL);
    return vacio;
}

void liberarTPersonasABB(TPersonasABB &personasABB)
{
    if (personasABB != NULL)
    {
        if (personasABB->izq != NULL)
        {
            liberarTPersonasABB(personasABB->izq);
            liberarTPersonasABB(personasABB);
        }
        else if (personasABB->der != NULL)
        {
            liberarTPersonasABB(personasABB->der);
            liberarTPersonasABB(personasABB);
        }
        else
        {
            liberarTPersona(personasABB->persona);
            personasABB->izq = NULL;
            personasABB->der = NULL;
            delete personasABB;
            personasABB = NULL;
        }
    }
}

TPersonasABB deserializarTPersonasABB(TPilaPersona pilaPersonas)
{
    if (pilaPersonas != NULL && cantidadEnTPilaPersona(pilaPersonas) != 0)
    {
        TColaPersonasABB cola = NULL;
        cola = crearTColaPersonasABB();
        TPersonasABB arbol = new rep_personasAbb;
        arbol->der = NULL;
        arbol->izq = NULL;
        arbol->persona = copiarTPersona(cimaDeTPilaPersona(pilaPersonas));
        encolarEnTColaPersonasABB(arbol, cola);
        desapilarDeTPilaPersona(pilaPersonas);
        while (cantidadEnTColaPersonasABB(cola) != 0)
        {
            TPersonasABB padre = frenteDeTColaPersonasABB(cola);
            if (cantidadEnTPilaPersona(pilaPersonas) != 0)
            {
                TPersonasABB nuevohijoizq = new rep_personasAbb;
                nuevohijoizq->der = NULL;
                nuevohijoizq->izq = NULL;
                nuevohijoizq->persona = copiarTPersona(cimaDeTPilaPersona(pilaPersonas));
                padre->izq = nuevohijoizq;
                encolarEnTColaPersonasABB(nuevohijoizq, cola);
                desapilarDeTPilaPersona(pilaPersonas);
            }
            if (cantidadEnTPilaPersona(pilaPersonas) != 0)
            {
                TPersonasABB nuevohijoder = new rep_personasAbb;
                nuevohijoder->der = NULL;
                nuevohijoder->izq = NULL;
                nuevohijoder->persona = copiarTPersona(cimaDeTPilaPersona(pilaPersonas));
                padre->der = nuevohijoder;
                encolarEnTColaPersonasABB(nuevohijoder, cola);
                desapilarDeTPilaPersona(pilaPersonas);
            }
            desencolarDeTColaPersonasABB(cola);
        }
        liberarTColaPersonasABB(cola);
        liberarTPilaPersona(pilaPersonas);
        return arbol;
    }
    else
    {
        return NULL;
    }
}


Código de Mendoza:
TPersonasABB crearTPersonasABB() 
{
    TPersonasABB personasABB = NULL;
    return personasABB;
}

bool esVacioTPersonasABB(TPersonasABB personasABB) 
{
    bool bandera = (personasABB == NULL);
    return bandera;
}

void liberarTPersonasABB(TPersonasABB &personasABB) 
{
    if (personasABB != NULL)
    {
        if (personasABB->izq != NULL)
        {
            liberarTPersonasABB(personasABB->izq);
            liberarTPersonasABB(personasABB);
        }
        else if (personasABB->der != NULL)
        {
            liberarTPersonasABB(personasABB->der);
            liberarTPersonasABB(personasABB);
        }
        else
        {
            liberarTPersona (personasABB->persona);
            personasABB->izq = NULL;
            personasABB->der = NULL;
            delete personasABB;
            personasABB = NULL;
        }
    }
}


TPersonasABB deserializarTPersonasABB(TPilaPersona pilaPersonas) 
{
    TPersonasABB arbol = NULL;
    if (pilaPersonas == NULL)
    {
        return arbol;
    }
    else 
    {
        TColaPersonasABB auxiliar = crearTColaPersonasABB();
        TPersonasABB arbol = new rep_personasAbb;
        arbol->persona = copiarTPersona(cimaDeTPilaPersona(pilaPersonas));
        arbol->izq = arbol->der = NULL;
        encolarEnTColaPersonasABB(arbol, auxiliar);
        desapilarDeTPilaPersona(pilaPersonas);
        while (cantidadEnTColaPersonasABB(auxiliar) != 0)
        {
            TPersonasABB raiz = frenteDeTColaPersonasABB(auxiliar);
            if (cantidadEnTPilaPersona(pilaPersonas) != 0)
            {
                TPersonasABB arbolizq = new rep_personasAbb;
                arbolizq->izq = arbolizq->der = NULL;
                arbolizq->persona = copiarTPersona(cimaDeTPilaPersona(pilaPersonas));
                raiz->izq = arbolizq;
                encolarEnTColaPersonasABB(arbolizq, auxiliar);
                desapilarDeTPilaPersona(pilaPersonas);
            }
            if (cantidadEnTPilaPersona(pilaPersonas) != 0)
            {
                TPersonasABB arbolder = new rep_personasAbb;
                arbolder->izq = arbolder->der = NULL;
                arbolder->persona = copiarTPersona(cimaDeTPilaPersona(pilaPersonas));
                raiz->der = arbolder;
                encolarEnTColaPersonasABB(arbolder, auxiliar);
                desapilarDeTPilaPersona(pilaPersonas);
            }
            desencolarDeTColaPersonasABB(auxiliar);
        }
        liberarTColaPersonasABB(auxiliar);
        liberarTPilaPersona(pilaPersonas);
        return arbol;
    }
}