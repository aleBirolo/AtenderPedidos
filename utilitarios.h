#ifndef UTILITARIOS
#define UTILITARIOS

#include <memory.h>
#define MIN(x,y) (x<=y ? x: y)

typedef enum
{
    verdadero = 1,
    falso =0
}booleano;

typedef struct s_nodo
{
    void *info;
    unsigned tamInfo;
    struct s_nodo *sig;
}t_nodo;

/// codProd = xxx-dddddd
typedef struct
{
    char codProd[11];
    char descripcion[25];
    float pu;
    int stock;
}t_registro;

typedef struct
{
    int dd,
        mm,
        aa;
}t_fecha;

typedef struct
{
    t_fecha fecha;
    int codCliente;
    char codProd[11];
    int cantPedida;
}t_pedido;

typedef int(*Cmp)(const void *, const void *);
typedef booleano (*Acum)(void *, const void *);
typedef void (*Mostrar) (const void *);


#endif // UTILITARIOS
