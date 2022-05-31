#ifndef COLA
#define COLA

#include <stdio.h>
#include <stdlib.h>
#include "utilitarios.h"

typedef struct
{
    t_nodo *pri,
           *ult;
}t_cola;

void crearCola(t_cola *pc);
booleano colaVacia(const t_cola *pc);
booleano colaLlena(const t_cola *pc, unsigned tamDato);
void vaciarCola(t_cola *pc);
booleano encolar(t_cola *pc, const void *dato, unsigned tamDato);
booleano desencolar(t_cola *pc, void *dato, unsigned tamDato);
booleano verCola(t_cola *pc, void *dato, unsigned tamDato);

#endif // COLA
