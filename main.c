#include "main.h"

#define TAM_REG 3
#define TAM_PED 5
#define TAM_LINEA 500

int main()
{
    t_registro reg;
    t_pedido ped;
    t_lista lista_ped;
    t_cola cola;
    FILE *fp_bin,
         *fp_txt,
         *fp_txt_salida;
    char linea[TAM_LINEA]={};

    grabarArchivoBin(&fp_bin);
    crearLoteArchivoTxt(&fp_txt);

    crearLista(&lista_ped);
    abrirArchivo(&fp_txt, NOM_ARCH_TXT, "r");

    while (fgets(linea, TAM_LINEA,fp_txt ))
    {
        deLineaAEstructura(linea, &ped);
        enlistar_en_orden_sin_dup(&lista_ped, &ped, sizeof(t_pedido), compararClienteProducto, acumular);
    }

    printf ("\n Archivo de pedidos Bajado a una lista\n");
    verListaDesdePpio(&lista_ped, mostrarPedidos);
    fclose(fp_txt);

    printf ("\n Archivo de Registros de productos antes de actualizarse\n");
    mostrarArchivoBinario(&fp_bin);


    crearCola(&cola);
    abrirArchivo(&fp_bin, NOM_ARCH_BIN, "rb+");
    fread(&reg,sizeof(t_registro),1,fp_bin);

    while (!feof(fp_bin) && !listaVacia(&lista_ped))
    {
        strcpy(ped.codProd, reg.codProd);

        while (desenlistar_dato(&lista_ped, &ped, sizeof(t_pedido), compararProducto ) == verdadero)
        {
            if (ped.cantPedida > reg.stock)
                encolar(&cola,&ped, sizeof(t_pedido));
            else
            {
                reg.stock-=ped.cantPedida;
                fseek(fp_bin,(long)-sizeof(t_registro), SEEK_CUR);
                fwrite(&reg,sizeof(t_registro),1,fp_bin);
            }
        }

        fseek(fp_bin,0L, SEEK_CUR);
        fread(&reg,sizeof(t_registro),1,fp_bin);
    }

    fclose(fp_bin);

    printf ("\n Archivo de Registros de productos despues de actualizarse\n");
    mostrarArchivoBinario(&fp_bin);

    if (!colaVacia(&cola))
    {
        abrirArchivo(&fp_txt_salida, NOM_ARCH_TXT_SALIDA, "w");

        while (desencolar(&cola,&ped, sizeof(t_pedido)))
            grabarArchivoTxt(fp_txt_salida, &ped);
    }

    return 0;
}

int compararFecha( const t_fecha f1,const t_fecha f2)
{
    int cmp;

    cmp = f1.aa - f2.aa;
    if (cmp == 0)
    {
        cmp = f1.mm - f2.mm;
        if (cmp ==0)
            cmp= f1.dd - f2.dd;
    }

    return cmp;
}

int comparar_con_fecha (const void *d1, const void *d2)
{
    t_pedido *p1=(t_pedido *)d1,
             *p2=(t_pedido *)d2;
    int cmp;

    cmp = compararFecha(p1->fecha, p2->fecha);
    if (cmp == 0)
    {
        cmp = p1->codCliente - p2->codCliente;
        if (cmp == 0)
            cmp = strcmp(p1->codProd, p2->codProd);
    }


    return cmp;
}


int compararClienteProducto (const void *d1, const void *d2)
{
    t_pedido *p1=(t_pedido *)d1,
    *p2=(t_pedido *)d2;
    int cmp;

    cmp = p1->codCliente - p2->codCliente;
    if (cmp == 0)
        cmp = strcmp(p1->codProd, p2->codProd);

    return cmp;
}

int compararProducto (const void *d1, const void *d2)
{
    t_pedido *p1=(t_pedido *)d1,
             *p2 = (t_pedido *)d2;


    return strcmp(p1->codProd, p2->codProd);
}

booleano acumular (void *d1, const void *d2)
{
    t_pedido *p1=(t_pedido *)d1,
             *p2=(t_pedido *)d2;

    p1->cantPedida+= p2->cantPedida;
    p1->fecha= p2->fecha;

    return verdadero;
}

void mostrarPedidos (const void *d)
{
    t_pedido *ped=(t_pedido *)d;

    printf ("%d/%d/%d %d %s %d\n",  ped->fecha.dd,
                                    ped->fecha.mm,
                                    ped->fecha.aa,
                                    ped->codCliente,
                                    ped->codProd,
                                    ped->cantPedida);
}

void mostrarRegistros (const void *d)
{
    t_registro *reg=(t_registro *)d;

    printf ("%s %s %.2f %d\n", reg->codProd,
                               reg->descripcion,
                               reg->pu,
                               reg->stock);
}

booleano abrirArchivo (FILE **fp, const char *nom, const char *modo)
{
    *fp=fopen(nom, modo);

    if (!*fp)
    {
        printf ("\n No se pudo abrir el arhivo %s en modo %s", nom, modo);
        return falso;
    }
    return verdadero;
}

void grabarArchivoBin (FILE **fp)
{
    t_registro reg[TAM_REG]={};
    int i;

    abrirArchivo(fp, NOM_ARCH_BIN, "wb");

        strcpy (reg[0].codProd ,"ppp-000001" );
        strcpy (reg[0].descripcion ,"producto 1" );
                reg[0].pu = 10;
                reg[0].stock = 500;

        strcpy (reg[1].codProd , "ppp-000002");
        strcpy (reg[1].descripcion , "producto 2" );
                reg[1].pu = 5;
                reg[1].stock = 300;

        strcpy (reg[2].codProd ,"ppp-000003" );
        strcpy (reg[2].descripcion ,"producto 3" );
                reg[2].pu = 50;
                reg[2].stock = 1000;

    for (i=0; i<TAM_REG; i++)
        fwrite(&reg[i],sizeof(t_registro),1, *fp);

    fclose(*fp);
}

void crearLoteArchivoTxt (FILE **fp)
{
    t_pedido ped[TAM_PED]={};
    int i;

    abrirArchivo(fp, NOM_ARCH_TXT, "w");

            ped[0].fecha.dd = 10;
            ped[0].fecha.mm = 11;
            ped[0].fecha.aa = 2021;
            ped[0].codCliente = 111;
    strcpy( ped[0].codProd,"ppp-000001" );
            ped[0].cantPedida= 45;

			ped[1].fecha.dd = 10;
            ped[1].fecha.mm = 11;
            ped[1].fecha.aa = 2021;
            ped[1].codCliente = 111;
    strcpy( ped[1].codProd,"ppp-000002" );
            ped[1].cantPedida= 100;

			ped[2].fecha.dd = 13;
            ped[2].fecha.mm = 11;
            ped[2].fecha.aa = 2021;
            ped[2].codCliente = 222;
    strcpy( ped[2].codProd,"ppp-000003" );
            ped[2].cantPedida=80;

			ped[3].fecha.dd = 11;
            ped[3].fecha.mm = 11;
            ped[3].fecha.aa = 2021;
            ped[3].codCliente = 333;
    strcpy( ped[3].codProd,"ppp-000002" );
            ped[3].cantPedida= 1550;

			ped[4].fecha.dd = 12;
            ped[4].fecha.mm = 11;
            ped[4].fecha.aa = 2021;
            ped[4].codCliente = 111;
    strcpy( ped[4].codProd,"ppp-000001" );
            ped[4].cantPedida= 500;

    for (i=0; i<TAM_PED; i++)
        grabarArchivoTxt(*fp, &ped[i]);
    fclose(*fp);
}

void grabarArchivoTxt (FILE *fp, t_pedido *ped)
{

    fprintf(fp,"%d/%d/%d %d %s %d\n",   ped->fecha.dd,
                                        ped->fecha.mm,
                                        ped->fecha.aa,
                                        ped->codCliente,
                                        ped->codProd,
                                        ped->cantPedida );
}

booleano deLineaAEstructura (char *linea, t_pedido *ped)
{
    char *aux=linea;

    aux=strrchr(linea,' ');
    sscanf(aux +1,"%d", &ped->cantPedida);
    *aux='\0';

    aux=strrchr(linea,' ');
    strcpy( ped->codProd, aux+1);
    *aux='\0';

    aux=strrchr(linea,' ');
    sscanf(aux +1,"%d", &ped->codCliente);
    *aux='\0';

    aux=strrchr(linea,'/');
    sscanf(aux +1,"%d", &ped->fecha.aa);
    *aux='\0';

    aux=strrchr(linea,'/');
    sscanf(aux +1,"%d", &ped->fecha.mm);
    *aux='\0';

    sscanf(linea,"%d", &ped->fecha.dd);

    return verdadero;
}

void mostrarArchivoBinario(FILE **fp)
{
    t_registro reg;

    abrirArchivo(fp, NOM_ARCH_BIN, "rb");
    fread(&reg,sizeof(t_registro),1,*fp);
    while (!feof(*fp) )
    {
        mostrarRegistros(&reg);
        fread(&reg,sizeof(t_registro),1,*fp);
    }
    fclose(*fp);
}
