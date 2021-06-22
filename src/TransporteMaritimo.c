
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

#include "utn.h"
#include "laplume.h"
#include "TransporteMaritimo.h"

/* \brief Valida los campos y convierte al tipo de dato que corresponda en cada campo, y los carga en una variable TransporteMaritimo
 * \param TransporteMaritimo* pTransporteMaritimo,
		float metrosCubicos, float precioContenedor
 * \return TransporteMaritimo* Retorna puntero a la PosicionArancelaria cargado
 */
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
/* \brief Libera el espacio reservado en memoria para un TransporteMaritimo
 * \param this TransporteMaritimo*
 * \return void
 */
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
/** \brief Valida metrosCubicos del TransporteMaritimo y lo carga en la variable TransporteMaritimo
 * \param this TransporteMaritimo*
 * \param metrosCubicos float
 * \return int  -1 error, 0 si ok
 */
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
/** \brief Obtiene metrosCubicos del TransporteMaritimo
 * \param this TransporteMaritimo*
 * \param flagError int*
 * \return float retorna -1 ERROR, retorna metrosCubicos si ok
 */
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
/** \brief Valida metrosCubicos del TransporteMaritimo
 * \param metrosCubicos float
 * \return int retorna 1 si es valido, 0 no es valido
 */
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
/** \brief Valida precioContenedor del TransporteMaritimo y lo carga en la variable TransporteMaritimo
 * \param this TransporteMaritimo*
 * \param precioContenedor float
 * \return int  -1 error, 0 si ok
 */
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
/** \brief Obtiene precioContenedor del TransporteMaritimo
 * \param this TransporteMaritimo*
 * \param flagError int*
 * \return float retorna -1 ERROR, retorna precioContenedor si ok
 */
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
/** \brief Valida precioContenedor del Articulo
 * \param precioContenedor float
 * \return int retorna 1 si es valido, 0 no es valido
 */
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
/** \brief Lista un Transporte Maritimo
 * \param pElement void*
 * \return int 0 si ok, -1 error
 */
int transporteMaritimo_imprimirTransporteMaritimo(TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	if(pTransporteMaritimo != NULL)
	{
		float metrosCubicos;
		float precioContenedor;
		int flagErrorA, flagErrorB;

		// Obtengo cada campo
		metrosCubicos = transporteMaritimo_getMetrosCubicos(pTransporteMaritimo, &flagErrorA);
		precioContenedor = transporteMaritimo_getPrecioContenedor(pTransporteMaritimo, &flagErrorB);
		if(!flagErrorA && !flagErrorB)
		{
			transporteMaritimo_encabezado();
			printf("\n m^3 %-30.2f USS %-30.2f",metrosCubicos, precioContenedor);
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief print encabezado al listar
 * \param void
 * \return void
 */
void transporteMaritimo_encabezado(void)
{
	char metrosCubicos[] = {"Metros Cubicos"};
	char precioContenedor[] = {"Precio Contenedor"};

	//printf("\n\x1b[34m ----------------------------------------------------------------------------------------------------------------------------------  \x1b[0m");
	printf("\n \x1b[40m\x1b[36m%-30s %-30s\x1b[0m\x1b[0m ", metrosCubicos,precioContenedor);
}
