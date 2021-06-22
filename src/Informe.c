
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Dictionary.h"

#include "Controller.h"
#include "Parser.h"
#include "Serializer.h"

#include "utn.h"
#include "laplume.h"

#include "Articulo.h"
#include "PosicionArancelaria.h"
#include "TransporteAereo.h"
#include "TransporteMaritimo.h"

#include "Calculos.h"
#include "Informe.h"

// Entidad general
#include "eGeneral.h"

/** \brief Pide los datos del Articulo para a ser dada de Alta
 * \param (char* nombre, char* codigo, char* descripcion, char* paisDeFabricacion,
		  float* fob, float* peso, float* ancho, float* altura, float* profundidad)
	punteros a las variables a ser escritas.

 * \return int 0 si ok, -1 error
 */
int informe_pedirDatosArticulo(char* nombre, char* codigo, char* descripcion, char* paisDeFabricacion,
		                       float* fob, float* peso, float* ancho, float* altura, float* profundidad)
{
	int retorno = -1;
	if(nombre != NULL && codigo != NULL && descripcion != NULL &&
	   paisDeFabricacion != NULL && fob  != NULL && peso != NULL && ancho != NULL && altura != NULL && profundidad != NULL )
	{
		if(!utn_getNombre(nombre, NOMBRE_LEN, "\n > Ingrese nombre del articulo: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
		   !utn_getAlfanumerico(codigo, CODIGO_LEN, " > Ingrese el codigo del articulo: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
		   !utn_getTexto(descripcion, DESCRIPCION_LEN, " > Ingrese descripcion del articulo: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
		   !utn_getNombre(paisDeFabricacion, PAIS_LEN, " > Ingrese pais de fabricación del articulo: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
		   !utn_getNumeroFloat(fob, " > Ingrese valor fob del articulo: USS ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
		   !utn_getNumeroFloat(peso, " > Ingrese peso en [kg] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
		   !utn_getNumeroFloat(ancho, "\n > DIMENSIONES:\n > Ingrese ancho[cm] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
		   !utn_getNumeroFloat(altura, " > Ingrese altura[cm] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
		   !utn_getNumeroFloat(profundidad, " > Ingrese profundidad[cm] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2))
		{
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief Pide los datos de la Posicion Arancelaria a ser dada de Alta
 * \param (char* nomenclador, float* porcentajeSeguro, float* porcentajeImportacion,
		   float* porcentajeTasaEstadistica, int* tipoLicencia)
	punteros a las variables a ser escritas.

 * \return int 0 si ok, -1 error
 */
int informe_pedirDatosPosicionArancelaria(char* nomenclador, float* porcentajeSeguro, float* porcentajeImportacion,
		                                  float* porcentajeTasaEstadistica, int* tipoLicencia)
{
	int retorno = -1;
	if(nomenclador != NULL && porcentajeSeguro != NULL && porcentajeImportacion != NULL && porcentajeTasaEstadistica != NULL && tipoLicencia != NULL)
	{
		if(!utn_getTexto(nomenclador, NOMENCLADOR_LEN, "\n > Ingrese nomenclador: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
		   !utn_getNumeroFloat(porcentajeSeguro, " > Ingrese porcentaje de seguro: %", "\x1b[31m * ERROR \x1b[0m", 0.1, 100, 2) &&
		   !utn_getNumeroFloat(porcentajeImportacion, " > Ingrese porcentaje de importacion: %", "\x1b[31m * ERROR \x1b[0m", 0.1, 100, 2) &&
		   !utn_getNumeroFloat(porcentajeTasaEstadistica, " > Ingrese porcentaje de tasa estadística: %", "\x1b[31m * ERROR \x1b[0m", 0.1, 100, 2) &&
		   !utn_getNumero(tipoLicencia, " > Ingrese tipo de licencia [0]AUTOMATICA - [1]NO AUTOMATICA: ", "\x1b[31m * ERROR \x1b[0m", 0, 1, 2))
		{
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Lista Posiciones Arancelarias Con Sus Articulos
 * \param listaArticulos LinkedList*
 * \param listaPosicionesArancelarias LinkedList*
 * \return int 0 si ok, -1 error
 */
int informe_listarPosicionArancelariaConSusArticulo(LinkedList* listaArticulos, LinkedList* listaPosicionesArancelarias)
{
	int retorno = -1;
	int i, k;
	if(listaArticulos != NULL && listaPosicionesArancelarias != NULL)
	{
		int lenArticulos;
		int lenPosicionesArancelarias;

		lenArticulos = ll_len(listaArticulos);
		lenPosicionesArancelarias = ll_len(listaPosicionesArancelarias);

		Articulo* pArticulo;
		PosicionArancelaria* pPosicionArancelaria;
		int idPosAranArticulo, idPosAran, flagErrorA, flagErrorPA;
		// ---------------------------------------------------------------------
		for(i=0; i<lenPosicionesArancelarias; i++)
		{
			pPosicionArancelaria = (PosicionArancelaria*)ll_get(listaPosicionesArancelarias, i);
			idPosAran = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagErrorPA);
			printf("\n\n");
			posicionArancelaria_imprimirUnaPosicionArancelaria(pPosicionArancelaria);
			for(k=0; k<lenArticulos; k++)
			{
				pArticulo = (Articulo*)ll_get(listaArticulos, k);
				idPosAranArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagErrorA);
				// ------------------------------------
				if(!flagErrorA && !flagErrorPA &&
				   idPosAranArticulo == idPosAran)
				{
					articulo_imprimirUnArticulo(pArticulo);
				}
				// ------------------------------------
			}
		}
		// ---------------------------------------------------------------------
		retorno = 0;
	}
	return retorno;
}
/** \brief Listar Articulos con su costo final por Transporte Aereo
 * \param listaArticulos LinkedList*
 * \param listaPosicionesArancelarias LinkedList*
 * \param pTransporteAereo TransporteAereo*
 * \return int 0 si ok, -1 error
 */
int informe_listarArticulosConCostoFinalTransporteAereo(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
                                                        TransporteAereo* pTransporteAereo)
{
	int retorno = -1;
	Articulo* pArticulo;
	PosicionArancelaria* pPosicionArancelaria;
	if(listaArticulos != NULL && listaPosicionArancelaria != NULL && pTransporteAereo != NULL )
	{
		int i, k;
		int lenArticulos, lenPosicionArancelaria;
		//float resultadoTransporteAereo;
		lenArticulos = ll_len(listaArticulos);
		lenPosicionArancelaria = ll_len(listaPosicionArancelaria);
		int idPosAranArticulo, idPosicionArancelaria, flagErrorA, flagErrorB;

		float resultadoTransporteAereo;
	// ------------------------------------------------------------------------------------------------------
		for(i=0; i<lenArticulos; i++)
		{
			pArticulo = (Articulo*) ll_get(listaArticulos, i);
			if(pArticulo != NULL)
			{
				idPosAranArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagErrorA);
				articulo_imprimirUnArticulo(pArticulo); // Imprimo Articulo
				// ------------------------------------------------------------------------
				for(k=0; k<lenPosicionArancelaria; k++)
				{
					pPosicionArancelaria = (PosicionArancelaria*) ll_get(listaPosicionArancelaria, k);
					if(pPosicionArancelaria != NULL)
					{
						idPosicionArancelaria = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagErrorB);
						if(!flagErrorA && !flagErrorB &&
						   idPosAranArticulo == idPosicionArancelaria)
						{
							resultadoTransporteAereo = transporteAereo_calcularCostoFinal(pArticulo, pPosicionArancelaria, pTransporteAereo);
							printf("\n > \x1b[43m \x1b[30m Costo final por Transporte Aereo: \x1b[0m \x1b[0m  USD %.2f \n", resultadoTransporteAereo);
							retorno = 0;
						}
					}
				}
				// ------------------------------------------------------------------------
			}
		}
	}
	return retorno;
}

/** \brief Listar Articulos con su costo final por Transporte Maritimo
 * \param listaArticulos LinkedList*
 * \param listaPosicionesArancelarias LinkedList*
 * \param pTransporteMaritimo TransporteMaritimo*
 * \return int 0 si ok, -1 error
 */
int informe_listarArticulosConCostoFinalTransporteMaritimo(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
		                                                   TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	Articulo* pArticulo;
	PosicionArancelaria* pPosicionArancelaria;
	if(listaArticulos != NULL && listaPosicionArancelaria != NULL && pTransporteMaritimo != NULL )
	{
		int i, k;
		int lenArticulos, lenPosicionArancelaria;
		float resultadoTransporteMaritimo;
		lenArticulos = ll_len(listaArticulos);
		lenPosicionArancelaria = ll_len(listaPosicionArancelaria);
		int idPosAranArticulo, idPosicionArancelaria, flagErrorA, flagErrorB;
	// ------------------------------------------------------------------------------------------------------
		for(i=0; i<lenArticulos; i++)
		{
			pArticulo = (Articulo*) ll_get(listaArticulos, i);
			if(pArticulo != NULL)
			{
				idPosAranArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagErrorA);
				articulo_imprimirUnArticulo(pArticulo); // Imprimo Articulo
				// ------------------------------------------------------------------------
				for(k=0; k<lenPosicionArancelaria; k++)
				{
					pPosicionArancelaria = (PosicionArancelaria*) ll_get(listaPosicionArancelaria, k);
					if(pPosicionArancelaria != NULL)
					{
						idPosicionArancelaria = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagErrorB);
						if(!flagErrorA && !flagErrorB &&
						   idPosAranArticulo == idPosicionArancelaria)
						{
							resultadoTransporteMaritimo = transporteMaritimo_calcularCostoFinal(pArticulo, pPosicionArancelaria, pTransporteMaritimo);
							printf("\n > \x1b[46m \x1b[30m Costo final por Transporte Maritimo: \x1b[0m \x1b[0m  USD %.2f \n", resultadoTransporteMaritimo);
							retorno = 0;
						}
					}
				}
				// ------------------------------------------------------------------------
			}
		}
  // ----------------------------------------------------------------------------------------------------
	}
	return retorno;
}
/** \brief Listar Articulos con su costo final por Transportes
 * \param listaArticulos LinkedList*
 * \param listaPosicionesArancelarias LinkedList*
 * \param pTransporteMaritimo TransporteMaritimo*
 * \param pTransporteAereo TransporteAereo*
 * \return int 0 si ok, -1 error
 */
int informe_listarArticulosConCostoFinalPorTransportes(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
                                                       TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	Articulo* pArticulo;
	PosicionArancelaria* pPosicionArancelaria;
	if(listaArticulos != NULL && listaPosicionArancelaria != NULL && pTransporteAereo != NULL && pTransporteMaritimo != NULL)
	{
		int i, k;
		int lenArticulos, lenPosicionArancelaria;
		//float resultadoTransporteAereo;
		lenArticulos = ll_len(listaArticulos);
		lenPosicionArancelaria = ll_len(listaPosicionArancelaria);
		int idPosAranArticulo, idPosicionArancelaria, flagErrorA, flagErrorB;

		float resultadoTransporteAereo, resultadoTransporteMaritimo;
	// ------------------------------------------------------------------------------------------------------
		for(i=0; i<lenArticulos; i++)
		{
			pArticulo = (Articulo*) ll_get(listaArticulos, i);
			if(pArticulo != NULL)
			{
				idPosAranArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagErrorA);
				articulo_imprimirUnArticulo(pArticulo); // Imprimo Articulo
				// ------------------------------------------------------------------------
				for(k=0; k<lenPosicionArancelaria; k++)
				{
					pPosicionArancelaria = (PosicionArancelaria*) ll_get(listaPosicionArancelaria, k);
					if(pPosicionArancelaria != NULL)
					{
						idPosicionArancelaria = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagErrorB);
						if(!flagErrorA && !flagErrorB &&
						   idPosAranArticulo == idPosicionArancelaria)
						{
							resultadoTransporteAereo = transporteAereo_calcularCostoFinal(pArticulo, pPosicionArancelaria, pTransporteAereo);
							resultadoTransporteMaritimo = transporteMaritimo_calcularCostoFinal(pArticulo, pPosicionArancelaria, pTransporteMaritimo);
							printf("\n > \x1b[43m \x1b[30m Costo final por Transporte Aereo: \x1b[0m \x1b[0m  USD %.2f", resultadoTransporteAereo);
							printf("\n > \x1b[46m \x1b[30m Costo final por Transporte Maritimo: \x1b[0m \x1b[0m  USD %.2f \n", resultadoTransporteMaritimo);
							retorno = 0;
						}
					}
				}
				// ------------------------------------------------------------------------
			}
		}
	}
	return retorno;
}

/** \brief Lista Posicion Arancelaria buscada por Nomenclador con sus Articulos
 * \param listaArticulos LinkedList*
 * \param listaPosicionArancelaria LinkedList*
 * \return int 0 si ok, -1 error
 */
int informe_listarPorBusquedaPorNomencladorPosAran(LinkedList* listaPosicionArancelaria, LinkedList* listaArticulos)
{
	int retorno = -1;
	void* pPosicionAranElement;
	void* pArticuloElement;

	if(listaPosicionArancelaria != NULL && listaArticulos != NULL )
	{
		// Pido que ingrese el Nomenclador, busco el elemento y lo retorno
		pPosicionAranElement = busquedaPorNomencladorPosicionArancelaria(listaPosicionArancelaria);

		// Verifico el elemento y imprimo
		if(pPosicionAranElement != NULL && !posicionArancelaria_imprimirUnaPosicionArancelaria(pPosicionAranElement))
		{
			pArticuloElement = ll_getNext(listaArticulos, 1);
			while(pArticuloElement != NULL)
			{
				if(sonIgualesIdPosicionArancelaria(pArticuloElement, pPosicionAranElement))
					articulo_imprimirUnArticulo(pArticuloElement);

				pArticuloElement = ll_getNext(listaArticulos, 0);
			}
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Pido que ingrese el Nomenclador, busca el elemento y lo retorna
 * \param listaArticulos LinkedList*
 * \param listaPosicionArancelaria LinkedList*
 * \return void* puntero al Elemento encontrado, NULL si no lo encontró
 */
void* busquedaPorNomencladorPosicionArancelaria(LinkedList* listaPosicionArancelaria)
{
	void* pRetornoElement = NULL;
	void* pPosicionArancelariaElem;
	char nomencladorAux[NOMENCLADOR_LEN];

	if(listaPosicionArancelaria != NULL &&
	  !utn_getTexto(nomencladorAux, NOMENCLADOR_LEN,"\n - POSICION ARANCELARIA -"
									                "\n > Ingrese nomenclador: ", "\n\x1b[31m * ERROR\x1b[0m", 3))
	{
		// Busco elemento
		pPosicionArancelariaElem = ll_buscarElement(listaPosicionArancelaria, funcionCriterio_buscarPorNomenclador, nomencladorAux);

		// Verifico el elemento y lo retorno
		if(pPosicionArancelariaElem != NULL)
			pRetornoElement = pPosicionArancelariaElem;
	}
	return pRetornoElement;
}

/** \brief Pide que ingrese el Codigo del Articulo, busca el elemento y lo retorna
 * \param listaArticulos LinkedList*
 * \return void* puntero al Elemento encontrado, NULL si no lo encontró
 */
void* busquedaPorCodigoArticulo(LinkedList* listaArticulos)
{
	void* pRetornoElement = NULL;
	void* pArticulo;
	char codigoAux[CODIGO_LEN];

	if(listaArticulos != NULL &&
	   !utn_getTexto(codigoAux, CODIGO_LEN,"\n - BUSCAR ARTICULO -"
							               "\n > Ingrese el codigo del Articulo: ", "\n\x1b[31m * ERROR\x1b[0m", 2))
	{
		// Busco elemento
		pArticulo = ll_buscarElement(listaArticulos, funcionCriterio_buscarPorCodigoArticulo, codigoAux);

		// Verifico el elemento y lo retorno
		if(pArticulo != NULL)
			pRetornoElement = pArticulo;
	}
	return pRetornoElement;
}
/** \brief Veerifica si los Ids de los parametros ingresados son iguales
 * \param void* pArticuloElement
 * \param pPosicionAranElement
 * \return int 1 si son IGUALES, 0 error o si NO son iguales
 */
int sonIgualesIdPosicionArancelaria(void* pArticuloElement, void* pPosicionAranElement)
{
	int retorno = 0;
	Articulo* pArticulo;
	PosicionArancelaria* pPosicionAran;
	int idPosAranArticulo, idPosAran,
	    flagErrorA, flagErrorB;

	if(pArticuloElement != NULL && pPosicionAranElement != NULL)
	{
		pArticulo = (Articulo*) pArticuloElement;
		pPosicionAran = (PosicionArancelaria*) pPosicionAranElement;
		//------------------------------------------------------------------------------------
		idPosAranArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagErrorA);
		idPosAran = posicionArancelaria_getIdPosicionArancelaria(pPosicionAran, &flagErrorB);
		//------------------------------------------------------------------------------------
		if(!flagErrorA && !flagErrorB &&
		  (idPosAranArticulo == idPosAran) )
		{
			retorno = 1;
		}
	}
	return retorno;
}
