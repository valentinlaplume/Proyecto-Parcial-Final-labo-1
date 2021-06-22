#include "TransporteAereo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"
#include "laplume.h"

/* \brief Valida los campos y convierte al tipo de dato que corresponda en cada campo, y los carga en una variable TransporteAereo
 * \param TransporteMaritimo* TransporteAereo* pTransporteAereo,
                                          float constanteVolumetrica, float precioPorKg)
 * \return TransporteMaritimo* Retorna puntero a la PosicionArancelaria cargado
 */
TransporteAereo* transporteAereo_newParam(TransporteAereo* pTransporteAereo,
                                          float constanteVolumetrica, float precioPorKg)
{
	if(pTransporteAereo != NULL)
	{
		if(transporteAereo_setConstanteVolumetrica(pTransporteAereo, constanteVolumetrica) < 0 ||
		   transporteAereo_setPrecioPorKg(pTransporteAereo, precioPorKg)      < 0 ) // aca van los set
		{
			transporteAereo_delete(pTransporteAereo);
			pTransporteAereo = NULL;
		}
	}
	return pTransporteAereo;
}
//******************************************************************************** DESTRUCTOR
/* \brief Libera el espacio reservado en memoria para un TransporteAereo
 * \param this TransporteAereo*
 * \return void
 */
int transporteAereo_delete(TransporteAereo* this)
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
/** \brief Valida constanteVolumetrica del TransporteAereo y lo carga en la variable TransporteAereo
 * \param this TransporteAereo*
 * \param constanteVolumetrica float
 * \return int  -1 error, 0 si ok
 */
int transporteAereo_setConstanteVolumetrica(TransporteAereo* this, float constanteVolumetrica)
{
    int retorno = -1;
    if(this != NULL && isValidConstanteVolumetrica(constanteVolumetrica))
    {
        this->constanteVolumetrica = constanteVolumetrica;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene constanteVolumetrica del TransporteAereo
 * \param this TransporteAereo*
 * \param flagError int*
 * \return float retorna -1 ERROR, retorna constanteVolumetrica si ok
 */
float transporteAereo_getConstanteVolumetrica(TransporteAereo* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->constanteVolumetrica;
        *flagError = 0;
    }
    return aux;
}
/** \brief Valida metrosCubicos del TransporteAereo
 * \param constanteVolumetrica float
 * \return int retorna 1 si es valido, 0 no es valido
 */
int isValidConstanteVolumetrica(float constanteVolumetrica)
{
	int retorno = 0;
	if(constanteVolumetrica > 0)
	{
		retorno = 1;
	}
	return retorno;
}
//---------------------------------------------------
/** \brief Valida precioPorKg del TransporteAereo y lo carga en la variable TransporteAereo
 * \param this TransporteAereo*
 * \param precioPorKg float
 * \return int  -1 error, 0 si ok
 */
int transporteAereo_setPrecioPorKg(TransporteAereo* this, float precioPorKg)
{
    int retorno = -1;
    if(this != NULL && isValidPrecioPorKg(precioPorKg))
    {
        this->precioPorKg = precioPorKg;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene precioPorKg del TransporteAereo
 * \param this TransporteAereo*
 * \param flagError int*
 * \return float retorna -1 ERROR, retorna precioPorKg si ok
 */
float transporteAereo_getPrecioPorKg(TransporteAereo* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->precioPorKg;
        *flagError = 0;
    }
    return aux;
}
/** \brief Valida precioPorKg del TransporteAereo
 * \param precioPorKg float
 * \return int retorna 1 si es valido, 0 no es valido
 */
int isValidPrecioPorKg(float precioPorKg)
{
	int retorno = 0;
	if(precioPorKg > 0)
	{
		retorno = 1;
	}
	return retorno;
}
//******************************************************************************** LISTAR
/** \brief Lista un Transporte Aereo
 * \param pElement void*
 * \return int 0 si ok, -1 error
 */
int transporteAereo_imprimirTransporteAereo(TransporteAereo* pTransporteAereo)
{
	int retorno = -1;
	if(pTransporteAereo != NULL)
	{
		float constanteVolumetrica;
		float precioPorKg;
		int flagErrorA, flagErrorB;

		// Obtengo cada campo
		constanteVolumetrica = transporteAereo_getConstanteVolumetrica(pTransporteAereo, &flagErrorA);
		precioPorKg = transporteAereo_getPrecioPorKg(pTransporteAereo, &flagErrorB);
		if(!flagErrorA && !flagErrorB)
		{
			transporteAereo_encabezado(); // Imprimo encabezado
			printf("\n %-30.2f   USD %-30.2f",constanteVolumetrica,precioPorKg);
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief print encabezado al listar
 * \param void
 * \return void
 */
void transporteAereo_encabezado(void)
{
	char constanteVolumetrica[] = {"Constante Volumetrica"};
	char precioPorKg[] = {"Precio por [Kg]"};

	printf("\n \x1b[40m\x1b[33m%-30s %-30s\x1b[0m\x1b[0m ", constanteVolumetrica,precioPorKg);
}


