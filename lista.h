#ifndef LISTA
#define LISTA

#include <stdio.h>
#include <stdlib.h>
#include "utilitarios.h"

typedef t_nodo *t_lista;

void crearLista(t_lista *pl);
booleano listaVacia(const t_lista *pl);
booleano listaLlena(const t_lista *pl, unsigned tamDato);
void vaciarLista(t_lista *pl);
booleano enlistar_en_orden_sin_dup(t_lista *pl, const void *dato, unsigned tamDato, Cmp cmp, Acum acum);
booleano desenlistar_dato(t_lista *pl, void *dato, unsigned tamDato, Cmp cmp);
booleano verListaDesdePpio(t_lista *pl, Mostrar mostrar);
#endif // LISTA
