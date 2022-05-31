#include "lista.h"

void crearLista(t_lista *pl)
{
    *pl=NULL;
}

booleano listaVacia(const t_lista *pl)
{
    return *pl==NULL;
}

booleano listaLlena(const t_lista *pl, unsigned tamDato)
{
    t_nodo *aux= malloc(sizeof(t_nodo));
    void *info = malloc (tamDato);

    free(aux);
    free(info);

    return !aux || !info;
}

void vaciarLista(t_lista *pl)
{
    t_nodo *elim;

    while (*pl)
    {
        elim=*pl;
        *pl=elim->sig;

        free(elim->info);
        free(elim);
    }
}


booleano enlistar_en_orden_sin_dup(t_lista *pl, const void *dato, unsigned tamDato, Cmp cmp, Acum acum)
{
    t_nodo *nue ;

    while ((*pl) && cmp( (*pl)->info, dato ) < 0)
        pl= &(*pl)->sig;

    if ( *pl && cmp( (*pl)->info, dato ) == 0)
    {
        acum( (*pl)->info, dato );
        return verdadero;
    }

    nue=malloc(sizeof(t_nodo));
    if (!nue)
        return falso;

    nue->info= malloc(tamDato);
    if (!nue->info)
    {
        free(nue);
        return falso;
    }

    memcpy(nue->info, dato, tamDato);
    nue->tamInfo = tamDato;

    /// pone al nodo antes
    if ( !*pl || (*pl)->sig )
    {
        nue->sig=*pl;
        *pl=nue;
    }
    else
    {
        (*pl)->sig = nue;
        nue->sig = NULL;
    }


    return verdadero;
}

booleano desenlistar_dato(t_lista *pl, void *dato, unsigned tamDato, Cmp cmp)
{
    t_nodo *elim;

    if (!*pl)
        return falso;

    while ((*pl)->sig && cmp( (*pl)->info, dato ) != 0 )
        pl=&(*pl)->sig;

    if ( *pl && cmp( (*pl)->info, dato ) != 0 )
        return falso;

    elim=*pl;

    memcpy(dato,elim->info, MIN(elim->tamInfo, tamDato) );

    if (elim->sig)
    {
        *pl=elim->sig;
    }
    else
    {
        *pl=NULL;
    }

    free(elim->info);
    free(elim);

    return verdadero;
}

booleano verListaDesdePpio(t_lista *pl, Mostrar mostrar)
{
    if (!*pl)
        return falso;

    while (*pl)
    {
        mostrar( (*pl)->info );
        pl=&(*pl)->sig;
    }

    return verdadero;
}
