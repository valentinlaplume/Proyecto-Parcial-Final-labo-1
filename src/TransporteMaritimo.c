
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

#include "utn.h"
#include "laplume.h"
#include "TransporteMaritimo.h"

/*TransporteMaritimo* transporteMaritimo_new(void)
{
	return (TransporteMaritimo*)malloc(sizeof(TransporteMaritimo));
}*/

TransporteMaritimo* transporteMaritimo_newParam(TransporteMaritimo* pTransporteMaritimo,
		                                        float metrosCubicos, float precioContenedor)
{
	if(pTransporteMaritimo != NULL)
	{
		if(transporteMaritimo_setMetrosCubicos(pTransporteMaritimo, metrosCubicos) < 0 ||
		   transporteMaritimo_setPrecioContenedor(pTransporteMaritimo, precioContenedor)      < 0 ) // aca van los set
		{
			transporteMaritimo_delete(pTransporteMaritimo);
			pTransporteMaritimo = NULL;
		}
	}
	return pTransporteMaritimo;
}
//******************************************************************************** DESTRUCTOR
int transporteMaritimo_delete(TransporteMaritimo* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}
//******************************************************************************** SET - GET - IS VALID
int transporteMaritimo_setMetrosCubicos(TransporteMaritimo* this, float metrosCubicos)
{
    int retorno = -1;
    if(this != NULL && isValidMetrosCubicos(metrosCubicos))
    {
        this->metrosCubicos = metrosCubicos;
        retorno = 0;
    }
    return retorno;
}

float transporteMaritimo_getMetrosCubicos(TransporteMaritimo* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->metrosCubicos;
        *flagError = 0;
    }
    return aux;
}

int isValidMetrosCubicos(float metrosCubicos)
{
	int retorno = 0;
	if(metrosCubicos > 0)
	{
		retorno = 1;
	}
	return retorno;
}
//---------------------------------------------------
int transporteMaritimo_setPrecioContenedor(TransporteMaritimo* this, float precioContenedor)
{
    int retorno = -1;
    if(this != NULL && isValidPrecioContenedor(precioContenedor))
    {
        this->precioContenedor = precioContenedor;
        retorno = 0;
    }
    return retorno;
}

float transporteMaritimo_getPrecioContenedor(TransporteMaritimo* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->precioContenedor;
        *flagError = 0;
    }
    return aux;
}

int isValidPrecioContenedor(float precioContenedor)
{
	int retorno = 0;
	if(precioContenedor > 0)
	{
		retorno = 1;
	}
	return retorno;
}

//******************************************************************************** LISTAR
int transporteMaritimo_imprimirTransporteMaritimo(TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	if(pTransporteMaritimo != NULL)
	{
		float metrosCubicos;
		float precioMetroCubico;
		int flagErrorA, flagErrorB;

		// Obtengo cada campo
		metrosCubicos = transporteMaritimo_getMetrosCubicos(pTransporteMaritimo, &flagErrorA);
		precioMetroCubico = transporteMaritimo_getPrecioContenedor(pTransporteMaritimo, &flagErrorB);
		if(!flagErrorA && !flagErrorB)
		{
			printf("\n\x1b[34m -------------------------------------------- \x1b[0m");
			printf("\n Metros Cubicos \t Precio Contenedor");
			printf("\n m^3 %.2f \t\t USS %.2f",metrosCubicos, precioMetroCubico);
			printf("\n\x1b[34m -------------------------------------------- \x1b[0m");
			retorno = 0;
		}
	}
	return retorno;
}
