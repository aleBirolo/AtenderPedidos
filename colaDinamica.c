#include "cola.h"

void crearCola(t_cola *pc)
{
    pc->pri = pc->ult = NULL;
}

booleano colaVacia(const t_cola *pc)
{
    return pc->pri == NULL;
}

booleano colaLlena(const t_cola *pc, unsigned tamDato)
{
    t_nodo *auxNodo = malloc(sizeof(t_nodo));
    void *auxInfo = malloc(tamDato);

    free (auxNodo);
    free(auxInfo);

    return auxNodo == NULL || auxInfo == NULL;
}

void vaciarCola(t_cola *pc)
{
    t_nodo *elim;

    while (pc->pri)
    {
        elim=pc->pri;
        pc->pri= elim->sig;

        free(elim->info);
        free(elim);
    }

    pc->pri = pc->ult = NULL;
}

booleano encolar(t_cola *pc, const void *dato, unsigned tamDato)
{
    t_nodo *nue= malloc(sizeof(t_nodo));

    if (!nue)
        return falso;
    nue->info = malloc(tamDato);
    if (!nue->info)
    {
        free(nue);
        return falso;
    }

    memcpy(nue->info, dato, tamDato);
    nue->tamInfo = tamDato;
    nue->sig=NULL;

    if (!pc->pri)
        pc->pri=nue;
    else
        pc->ult->sig=nue;

    pc->ult=nue;

    return verdadero;
}

booleano desencolar(t_cola *pc, void *dato, unsigned tamDato)
{
    t_nodo *elim= pc->pri;

    if ( !pc->pri )
        return falso;

    memcpy(dato, elim->info, MIN(elim->tamInfo, tamDato));
    pc->pri = elim->sig;

    if (!pc->pri)
        pc->ult = NULL;

    free(elim->info);
    free(elim);

    return verdadero;
}

booleano verCola(t_cola *pc, void *dato, unsigned tamDato)
{
    t_nodo *aux= pc->pri;

    if ( !pc->pri )
        return falso;

    memcpy(dato, aux->info, MIN(aux->tamInfo, tamDato));

    return verdadero;
}
