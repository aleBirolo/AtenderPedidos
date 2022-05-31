#ifndef MAIN
#define MAIN


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"
#include "lista.h"

#define NOM_ARCH_BIN "prodEnStock.bin"
#define NOM_ARCH_TXT "pedidos.txt"
#define NOM_ARCH_TXT_SALIDA "pedidosNoAtendidos.txt"

int compararFecha( t_fecha f1, t_fecha f2);
int comparar_con_fecha (const void *d1, const void *d2);
int compararClienteProducto (const void *d1, const void *d2);
int compararProducto (const void *d1, const void *d2);
booleano acumular (void *d1, const void *d2);
void mostrarPedidos (const void *d);
void mostrarRegistros (const void *d);

booleano abrirArchivo (FILE **fp, const char *nom, const char *modo);
void grabarArchivoBin (FILE **fp);
void crearLoteArchivoTxt (FILE **fp);
void grabarArchivoTxt (FILE *fp, t_pedido *ped);
booleano deLineaAEstructura (char *linea, t_pedido *ped);
void mostrarArchivoBinario(FILE **fp);
#endif // MAIN
