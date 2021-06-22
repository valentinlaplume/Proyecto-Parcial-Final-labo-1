#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Dictionary.h"
#include "eGeneral.h"
#include "eGeneral.h"
#include "Informe.h"

#include "eGeneral.h"
#include "Calculos.h"

//******************************************************************************* CONSTRUCTORES
eGeneral* eGeneral_new(void)
{
	return (eGeneral*) malloc(sizeof(eGeneral));
}

eGeneral* eGeneral_newParam(int idArticuloGeneral, float fob, float peso, float ancho, float altura, float profundidad,
							float porcentajeSeguro, float porcentajeImportacion, float porcentajeTasaEstadistica)
{
	eGeneral* pGeneral = eGeneral_new();
	if(pGeneral != NULL )
	{
		if( // Datos Articulo
		    eGeneral_setIdArticuloGeneral(pGeneral, idArticuloGeneral)            < 0 ||
			eGeneral_setFob(pGeneral, fob)                                        < 0 ||
			eGeneral_setPeso(pGeneral, peso)                                      < 0 ||
			eGeneral_setAncho(pGeneral, ancho)                                    < 0 ||
			eGeneral_setAltura(pGeneral, altura)                                  < 0 ||
			eGeneral_setProfundidad(pGeneral, profundidad)                        < 0 ||
			// Datos Posicion Arancelaria
		    eGeneral_setPorcentajeSeguro(pGeneral, porcentajeSeguro)                   < 0 ||
		    eGeneral_setPorcentajeImportacion(pGeneral, porcentajeImportacion)         < 0 ||
		    eGeneral_setPorcentajeTasaEstadistica(pGeneral, porcentajeTasaEstadistica) < 0)
		{
			printf("\n * eGeneral no valido cargado de eGenerals.csv");
			eGeneral_delete(pGeneral);
			pGeneral = NULL;
		}
	}
	return pGeneral;
}

/* \brief Libera el espacio reservado en memoria para un eGeneral
 * \param this eGeneral*
 * \return void
 */
int eGeneral_delete(eGeneral* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

//----------------------------------------------------------------------------------------
/** \brief Valida un Costo Transporte Maritimo y lo carga en la variable eGeneral
 * \param this eGeneral*
 * \param costoTransporteMaritimo float
 * \return int  -1 error, 0 si ok
 */
int eGeneral_setCostoTransporteMaritimo(eGeneral* this, float costoTransporteMaritimo)
{
    int retorno = -1;
    if(this != NULL && costoTransporteMaritimo > 0)
    {
        this->costoTransporteMaritimo = costoTransporteMaritimo;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene Costo Transporte Maritimo del eGeneral
 * \param this eGeneral*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna Valor Fob si ok
 */
float eGeneral_getCostoTransporteMaritimo(eGeneral* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->costoTransporteMaritimo;
        *flagError = 0;
    }
    return aux;
}
//---------------------------------------------------------------------------------------
/** \brief Valida un Costo Transporte Aereo y lo carga en la variable eGeneral
 * \param this eGeneral*
 * \param costoTransporteAereo float
 * \return int  -1 error, 0 si ok
 */
int eGeneral_setCostoTransporteAereo(eGeneral* this, float costoTransporteAereo)
{
    int retorno = -1;
    if(this != NULL && costoTransporteAereo > 0)
    {
        this->costoTransporteAereo = costoTransporteAereo;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene Costo Transporte Aereo del eGeneral
 * \param this eGeneral*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna Valor Fob si ok
 */
float eGeneral_getCostoTransporteAereo(eGeneral* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->costoTransporteAereo;
        *flagError = 0;
    }
    return aux;
}
//************************************************************************************* DATOS DE eGeneralS
/** \brief Valida un ID y lo carga en la variable eGeneral
 * \param this eGeneral*
 * \param ideGeneral int
 * \return int  -1 error, 0 si ok
 */
int eGeneral_setIdArticuloGeneral(eGeneral* this, int idArticuloGeneral)
{
	int retorno = -1;
	if(this != NULL && isValidId(idArticuloGeneral) )
	{
		this->idArticuloGeneral = idArticuloGeneral;
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene Id eGeneral del eGeneral
 * \param this eGeneral*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna Id eGeneral si ok
 */
int eGeneral_getIdArticuloGeneral(eGeneral* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->idArticuloGeneral;
		*flagError = 0;
	}
	return auxId;
}
//---------------------------------------------------
/** \brief Valida un valor Fob y lo carga en la variable eGeneral
 * \param this eGeneral*
 * \param fob char*
 * \return int  -1 error, 0 si ok
 */
int eGeneral_setFob(eGeneral* this, float fob)
{
    int retorno = -1;
    if(this != NULL && isValidFob(fob))
    {
        this->fob = fob;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene Valor Fob del eGeneral
 * \param this eGeneral*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna Valor Fob si ok
 */
float eGeneral_getFob(eGeneral* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->fob;
        *flagError = 0;
    }
    return aux;
}

//---------------------------------------------------
/** \brief Valida un Peso y lo carga en la variable eGeneral
 * \param this eGeneral*
 * \param peso char*
 * \return int  -1 error, 0 si ok
 */
int eGeneral_setPeso(eGeneral* this, float peso)
{
    int retorno = -1;
    if(this != NULL && isValidPeso(peso))
    {
        this->peso = peso;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene Peso del eGeneral
 * \param this eGeneral*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna Peso si ok
 */
float eGeneral_getPeso(eGeneral* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->peso;
        *flagError = 0;
    }
    return aux;
}
//---------------------------------------------------
/** \brief Valida una Altura y lo carga en la variable eGeneral
 * \param this eGeneral*
 * \param altura float
 * \return int  -1 error, 0 si ok
 */
int eGeneral_setAltura(eGeneral* this, float altura)
{
    int retorno = -1;
    if(this != NULL && isValidAltura(altura))
    {
        this->altura = altura;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene Altura del eGeneral
 * \param this eGeneral*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna Altura si ok
 */
float eGeneral_getAltura(eGeneral* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->altura;
        *flagError = 0;
    }
    return aux;
}
//---------------------------------------------------
/** \brief Valida una Ancho del eGeneral y lo carga en la variable eGeneral
 * \param this eGeneral*
 * \param altura float
 * \return int  -1 error, 0 si ok
 */
int eGeneral_setAncho(eGeneral* this, float ancho)
{
    int retorno = -1;
    if(this != NULL && isValidAncho(ancho))
    {
        this->ancho = ancho;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene Ancho del eGeneral
 * \param this eGeneral*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna Ancho si ok
 */
float eGeneral_getAncho(eGeneral* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->ancho;
        *flagError = 0;
    }
    return aux;
}
//---------------------------------------------------
/** \brief Valida Profundidad del eGeneral y lo carga en la variable eGeneral
 * \param this eGeneral*
 * \param altura float
 * \return int  -1 error, 0 si ok
 */
int eGeneral_setProfundidad(eGeneral* this, float profundidad)
{
    int retorno = -1;
    if(this != NULL && isValidProfundidad(profundidad))
    {
        this->profundidad = profundidad;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene Profundidad del eGeneral
 * \param this eGeneral*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna Profundidad si ok
 */
float eGeneral_getProfundidad(eGeneral* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->profundidad;
        *flagError = 0;
    }
    return aux;
}



//************************************************************************************* DATOS DE POSICION ARANCELARIA
int eGeneral_setPorcentajeSeguro(eGeneral* this, float porcentajeSeguro)
{
    int retorno = -1;
    if(this != NULL && isValidPorcentajeSeguro(porcentajeSeguro))
    {
        this->porcentajeSeguro = porcentajeSeguro;
        retorno = 0;
    }
    return retorno;
}

float eGeneral_getPorcentajeSeguro(eGeneral* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->porcentajeSeguro;
        *flagError = 0;
    }
    return aux;
}

//-----------------------------------------------------------------------------
int eGeneral_setPorcentajeImportacion(eGeneral* this, float porcentajeImportacion)
{
    int retorno = -1;
    if(this != NULL && isValidPorcentajeImportacion(porcentajeImportacion))
    {
        this->porcentajeImportacion = porcentajeImportacion;
        retorno = 0;
    }
    return retorno;
}

float eGeneral_getPorcentajeImportacion(eGeneral* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->porcentajeImportacion;
        *flagError = 0;
    }
    return aux;
}

//-----------------------------------------------------------------------------
int eGeneral_setPorcentajeTasaEstadistica(eGeneral* this, float porcentajeTasaEstadistica)
{
    int retorno = -1;
    if(this != NULL && isValidPorcentajeTasaEstadistica(porcentajeTasaEstadistica))
    {
        this->porcentajeTasaEstadistica = porcentajeTasaEstadistica;
        retorno = 0;
    }
    return retorno;
}

float eGeneral_getPorcentajeTasaEstadistica(eGeneral* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->porcentajeTasaEstadistica;
        *flagError = 0;
    }
    return aux;
}
