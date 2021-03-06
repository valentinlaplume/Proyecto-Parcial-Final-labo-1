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

//-------------------------------------------------------------------------------Funciones estaticas:
// Print costos finales por Transporte maritimo o aereo
static int printCostosFinalesTransportes(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                 TransporteAereo* pTransporteAereo,TransporteMaritimo* pTransporteMaritimo);
// Print costos finales por Transporte Aereo
static int printCostoFinalTransporteAereo(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                  TransporteAereo* pTransporteAereo);
// Print costos finales por Transporte Maritimo
static int printCostoFinalTransporteMaritimo(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                     TransporteMaritimo* pTransporteMaritimo);
//*************************************************************************************************************


int informe_prueba(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
                   TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo,
				   int (*pFuncion)(void*, void*))
{
	int retorno = -1;
	if(listaArticulos != NULL && listaPosicionArancelaria != NULL && pTransporteAereo != NULL && pTransporteMaritimo != NULL)
	{
		Articulo* pArticulo;
		PosicionArancelaria* pPosicionArancelaria;
		//----------------------------------------------------
		pPosicionArancelaria =ll_getNext(listaPosicionArancelaria, 1);
		while(pPosicionArancelaria != NULL)
		{
			pArticulo =  ll_getNext(listaArticulos, 1);
			while(pArticulo != NULL)
			{
				if(pFuncion(pArticulo, pPosicionArancelaria))
				{
					posicionArancelaria_imprimirUnaPosicionArancelaria(pPosicionArancelaria);
					articulo_imprimirUnArticulo(pArticulo);
					printCostosFinalesTransportes(pArticulo, pPosicionArancelaria, pTransporteAereo, pTransporteMaritimo);
				}
				pArticulo =  ll_getNext(listaArticulos, 0);
			}
			pPosicionArancelaria = ll_getNext(listaPosicionArancelaria, 0);
			posicionArancelaria_imprimirUnaPosicionArancelaria(pPosicionArancelaria);
		}

		/*for(k=0; k<lenArticulos; k++)
		{
			pArticulo = (Articulo*)ll_get(listaArticulos, k);
			// ------------------------------------
			if(pFuncion(pArticulo, pPosicionArancelaria))
			{
				articulo_imprimirUnArticulo(pArticulo);
			}
			// ------------------------------------
		}*/
	}
	return retorno;
}

/*
int informe_generico(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
                   TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo,
				   int (*pFuncion)(void*, void*))
{
	int retorno = -1;
	Articulo* pArticulo;
	PosicionArancelaria* pPosicionArancelaria;
	if(listaArticulos != NULL && listaPosicionArancelaria != NULL && pTransporteAereo != NULL && pTransporteMaritimo != NULL)
	{
		//-----------------------------------------------------------------------------
		pArticulo = (Articulo*) ll_getNext(listaArticulos, 1);
		while(pArticulo != NULL)
		{
			pPosicionArancelaria = (PosicionArancelaria*)ll_getNext(listaPosicionArancelaria, 1);
			while(pPosicionArancelaria != NULL)
			{
				if(pFuncion(pArticulo, pPosicionArancelaria))
				{

				}
				pPosicionArancelaria = (PosicionArancelaria*)ll_getNext(listaPosicionArancelaria, 0);
			}
			pArticulo = (Articulo*) ll_getNext(listaArticulos, 0);
		}
		//------------------------------------------------------------------------------------------------------
	}
	return retorno;
}*/


//-------------------------------------------------------------- INFORME PARCIAL
/** \brief Calcula los costos Finales en Argentina por transportes
 * \param (Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		  TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo)
	punteros a las variables a ser escritas.
 * \return int 0 si ok, -1 error
 */
int informe_calcularCostosFinalesParcial(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
                                         TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo,
										 int (*pFuncion)(void*, void*))
{
	int retorno = -1;
	Articulo* pArticulo;
	PosicionArancelaria* pPosicionArancelaria;
	if(listaArticulos != NULL && listaPosicionArancelaria != NULL && pTransporteAereo != NULL && pTransporteMaritimo != NULL && pFuncion != NULL)
	{
		int i, lenPosicionArancelaria;
		lenPosicionArancelaria = ll_len(listaPosicionArancelaria);

		pArticulo = (Articulo*) ll_getNext(listaArticulos, 1);
		while(pArticulo != NULL)
		{
			for(i=0; i<lenPosicionArancelaria; i++)
			{
				pPosicionArancelaria = (PosicionArancelaria*) ll_get(listaPosicionArancelaria, i);
				if(pPosicionArancelaria != NULL &&
				   pFuncion(pArticulo, pPosicionArancelaria) &&
				  !calcularUnCostoFinalEnArgentina(pArticulo, pPosicionArancelaria, pTransporteAereo, pTransporteMaritimo))
				{
					retorno = 0;
				}
			}
			pArticulo = (Articulo*) ll_getNext(listaArticulos, 0);
		}
	}
	return retorno;
}

/** \brief Calcula el costo Final dee un Articulo por transportes en Argentina
 * \param (Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		  TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo)
	punteros a las variables a ser escritas.
 * \return int 0 si ok, -1 error
 */
int calcularUnCostoFinalEnArgentina(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                             TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	if(pArticulo != NULL && pPosicionArancelaria != NULL  && pTransporteAereo != NULL)
	{
		if(transporteAereo_calcularCostoFinal(pArticulo, pPosicionArancelaria, pTransporteAereo) > -1 &&
		   transporteMaritimo_calcularCostoFinal(pArticulo, pPosicionArancelaria, pTransporteMaritimo)> -1)
		{
			retorno = 0;
		}
	}
	return retorno;
}
//*******************************************************************************************
/** \brief Pide los datos del Articulo para a ser dada de Alta
 * \param (char* nombre, char* codigo, char* descripcion, char* paisDeFabricacion,
		  float* fob, float* peso, float* ancho, float* altura, float* profundidad)
	punteros a las variables a ser escritas.

 * \return int 0 si ok, -1 error
 */
int informe_pedirDatosArticulo(LinkedList* listaArticulos,char* nombre, char* codigo, char* descripcion, char* paisDeFabricacion,
		                       float* fob, float* peso, float* ancho, float* altura, float* profundidad)
{
	int retorno = -1;
	if(nombre != NULL && codigo != NULL && descripcion != NULL &&
	   paisDeFabricacion != NULL && fob  != NULL && peso != NULL && ancho != NULL && altura != NULL && profundidad != NULL )
	{
		if(!utn_getTexto(codigo, CODIGO_LEN, "\n > Ingrese el codigo del articulo: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
		   !buscarSiExisteCodigo(listaArticulos, codigo))
		{
			if(!utn_getTexto(descripcion, DESCRIPCION_LEN, " > Ingrese descripcion del articulo: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
			   !buscarSiExisteDescripcion(listaArticulos, descripcion))
			{
				if(!utn_getNombre(nombre, NOMBRE_LEN, " > Ingrese nombre del articulo: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
				   !utn_getNombre(paisDeFabricacion, PAIS_LEN, " > Ingrese pais de fabricaci??n del articulo: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
				   !utn_getNumeroFloat(fob, " > Ingrese valor fob del articulo: USS ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
				   !utn_getNumeroFloat(peso, " > Ingrese peso en [kg] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
				   !utn_getNumeroFloat(ancho, "\n > DIMENSIONES:\n > Ingrese ancho[cm] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
				   !utn_getNumeroFloat(altura, " > Ingrese altura[cm] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
				   !utn_getNumeroFloat(profundidad, " > Ingrese profundidad[cm] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2))
				{
					retorno = 0;
				}
			}
			else
				printf("\n > La Descripcion ingresada ya correspone a un Articulo, por lo tanto, no se puede dar de alta.");
		}
		else
			printf("\n > El Codigo ingresado ya correspone a un Articulo, por lo tanto, no se puede dar de alta.");
	}
	return retorno;
}
/** \brief Busca si existe el Codigo ingresado por el usuario en Articulos
 * \param listaArticulos LinkedList*
 * \param codigo char* puntero al codigo ingresado
 * \return int: retorna 1 si existe, 0 si no existe
 */
int buscarSiExisteCodigo(LinkedList* listaArticulos, char* codigo)
{
	int retorno = 0;
	if(listaArticulos != NULL && codigo != NULL)
	{
		void* pElement;
		//----------------------------------------- // busca el elemento depende la funcion criterio pasada
		pElement = ll_buscarElement_VL(listaArticulos, funcionCriterio_compararPorCodigoArticulo, codigo);
		if(pElement != NULL)
		{
			// significa que existe
			retorno = 1;
		}
	}
	return retorno;
}
/** \brief Busca si existe la descripcion ingresada por el usuario en Articulos
 * \param listaArticulos LinkedList*
 * \param codigo char* puntero al codigo ingresado
 * \return int: retorna 1 si existe, 0 si no existe
 */
int buscarSiExisteDescripcion(LinkedList* listaArticulos, char* descripcion)
{
	int retorno = 0;
	if(listaArticulos != NULL && descripcion != NULL)
	{
		void* pElement;
		//----------------------------------------- // busca el elemento depende la funcion criterio pasada
		pElement = ll_buscarElement_VL(listaArticulos, funcionCriterio_compararPorDescripcionArticulo, descripcion);
		if(pElement != NULL)
		{
			// significa que existe
			retorno = 1;
		}
	}
	return retorno;
}
//----------------------------------------------------------------------------------------------------------
/** \brief Pide los datos de la Posicion Arancelaria a ser dada de Alta
 * \param (char* nomenclador, float* porcentajeSeguro, float* porcentajeImportacion,
		   float* porcentajeTasaEstadistica, int* tipoLicencia)
	punteros a las variables a ser escritas.

 * \return int 0 si ok, -1 error
 */
int informe_pedirDatosPosicionArancelaria(LinkedList* listaPosAran, char* nomenclador, float* porcentajeSeguro, float* porcentajeImportacion,
		                                  float* porcentajeTasaEstadistica, int* tipoLicencia)
{
	int retorno = -1;
	if(listaPosAran != NULL && nomenclador != NULL && porcentajeSeguro != NULL && porcentajeImportacion != NULL && porcentajeTasaEstadistica != NULL && tipoLicencia != NULL)
	{
		if(!utn_getTexto(nomenclador, NOMENCLADOR_LEN, "\n > Ingrese nomenclador: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
		   !buscarSiExisteNomenclatura(listaPosAran, nomenclador))
		{
			if(!utn_getNumeroFloat(porcentajeSeguro, " > Ingrese porcentaje de seguro: %", "\x1b[31m * ERROR \x1b[0m", 0.1, 100, 2) &&
			   !utn_getNumeroFloat(porcentajeImportacion, " > Ingrese porcentaje de importacion: %", "\x1b[31m * ERROR \x1b[0m", 0.1, 100, 2) &&
			   !utn_getNumeroFloat(porcentajeTasaEstadistica, " > Ingrese porcentaje de tasa estad??stica: %", "\x1b[31m * ERROR \x1b[0m", 0.1, 100, 2) &&
			   !utn_getNumero(tipoLicencia, " > Ingrese tipo de licencia [0]AUTOMATICA - [1]NO AUTOMATICA: ", "\x1b[31m * ERROR \x1b[0m", 0, 1, 2))
			{
				retorno = 0;
			}
		}
		else
			printf("\n > La Nomenclatura ingresada ya correspone a una Posicion Arancelaria, por lo tanto, no se puede dar de alta.");
	}
	return retorno;
}
/** \brief Busca si existe la Nomenclatura ingresado por el usuario en las Posiciones Arancelarias
 * \param listaPosAran LinkedList*
 * \param nomenclador char* puntero al nomenclador ingresado
 * \return int: retorna 1 si existe, 0 si no existe
 */
int buscarSiExisteNomenclatura(LinkedList* listaPosAran, char* nomenclador)
{
	int retorno = 0;
	if(listaPosAran != NULL && nomenclador != NULL)
	{
		void* pElement;
		//-----------------------------------------
		pElement = ll_buscarElement_VL(listaPosAran, funcionCriterio_compararPorNomenclador, nomenclador);
		if(pElement != NULL)
		{
			// significa que existe
			retorno = 1;
		}
	}
	return retorno;
}


/** \brief Lista Todas las Posiciones Arancelarias Con Sus Articulos [inclusive las que no poseen articulos]
 * \param listaArticulos LinkedList*
 * \param listaPosicionesArancelarias LinkedList*
 * \return int 0 si ok, -1 error
 */
int informe_listarTotalPosicionArancelariaConSusArticulos(LinkedList* listaArticulos, LinkedList* listaPosicionesArancelarias,
		                                                  int (*pFuncion)(void*, void*))
{
	int retorno = -1;
	if(listaArticulos != NULL && listaPosicionesArancelarias != NULL && pFuncion != NULL)
	{
		int i, lenArticulos;
		lenArticulos = ll_len(listaArticulos);
		Articulo* pArticulo;
		PosicionArancelaria* pPosicionArancelaria;
		// ---------------------------------------------------------------------
		pPosicionArancelaria = (PosicionArancelaria*) ll_getNext(listaPosicionesArancelarias, 1);
		while(pPosicionArancelaria != NULL)
		{
			printf("\n");
			posicionArancelaria_imprimirUnaPosicionArancelaria(pPosicionArancelaria);
			for(i=0; i<lenArticulos; i++)
			{
				pArticulo = (Articulo*) ll_get(listaArticulos, i);
				if(pArticulo != NULL &&
				   pFuncion(pArticulo, pPosicionArancelaria) &&
				  !articulo_imprimirUnArticulo(pArticulo))
				{
					retorno = 0;
				}
			}
			pPosicionArancelaria = (PosicionArancelaria*) ll_getNext(listaPosicionesArancelarias, 0);
		}
	}
	return retorno;
}

/** \brief Lista solo las Posiciones Arancelarias Con Articulos
 * \param listaArticulos LinkedList*
 * \param listaPosicionesArancelarias LinkedList*
 * \return int 0 si ok, -1 error
 */
/*int informe_listarSoloPosicionArancelariaConArticulos(LinkedList* listaArticulos, LinkedList* listaPosicionesArancelarias)
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
			for(k=0; k<lenArticulos; k++)
			{
				pArticulo = (Articulo*)ll_get(listaArticulos, k);
				idPosAranArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagErrorA);
				// ------------------------------------
				if(!flagErrorA && !flagErrorPA &&
				   idPosAranArticulo == idPosAran)
				{
					posicionArancelaria_imprimirUnaPosicionArancelaria(pPosicionArancelaria);
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
*/
/** \brief Listar Articulos con su costo final por Transporte Aereo
 * \param listaArticulos LinkedList*
 * \param listaPosicionesArancelarias LinkedList*
 * \param pTransporteAereo TransporteAereo*
 * \return int 0 si ok, -1 error
 */
int informe_listarArticulosConCostoFinalTransporteAereo(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
                                                        TransporteAereo* pTransporteAereo, int (*pFuncion)(void*, void*))
{
	int retorno = -1;
	Articulo* pArticulo;
	PosicionArancelaria* pPosicionArancelaria;
	if(listaArticulos != NULL && listaPosicionArancelaria != NULL && pTransporteAereo != NULL && pFuncion != NULL)
	{
		int i, k;
		int lenArticulos, lenPosicionArancelaria;
		lenArticulos = ll_len(listaArticulos);
		lenPosicionArancelaria = ll_len(listaPosicionArancelaria);
// ------------------------------------------------------------------------------------------------------
		for(i=0; i<lenArticulos; i++)
		{
			pArticulo = (Articulo*) ll_get(listaArticulos, i);
			if(pArticulo != NULL && !articulo_imprimirUnArticulo(pArticulo)) // Imprimo Articulo
			{
				for(k=0; k<lenPosicionArancelaria; k++)
				{
					pPosicionArancelaria = (PosicionArancelaria*) ll_get(listaPosicionArancelaria, k);
					if(pPosicionArancelaria != NULL && pFuncion(pArticulo, pPosicionArancelaria))
					{
						if(!printCostoFinalTransporteAereo(pArticulo, pPosicionArancelaria, pTransporteAereo))
						{
							printf("\n");
							retorno = 0;
						}
					}
				}
			}
		}
// -------------------------------------------------------------------------------------------------------------
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
		                                                   TransporteMaritimo* pTransporteMaritimo, int (*pFuncion)(void*, void*))
{
	int retorno = -1;
	Articulo* pArticulo;
	PosicionArancelaria* pPosicionArancelaria;
	if(listaArticulos != NULL && listaPosicionArancelaria != NULL && pTransporteMaritimo != NULL && pFuncion != NULL)
	{
		int i, k;
		int lenArticulos, lenPosicionArancelaria;
		lenArticulos = ll_len(listaArticulos);
		lenPosicionArancelaria = ll_len(listaPosicionArancelaria);
// ----------------------------------------------------------------------------------------------------
		for(i=0; i<lenArticulos; i++)
		{
			pArticulo = (Articulo*) ll_get(listaArticulos, i);
			if(pArticulo != NULL && !articulo_imprimirUnArticulo(pArticulo))  // Imprimo Articulo
			{
				for(k=0; k<lenPosicionArancelaria; k++)
				{
					pPosicionArancelaria = (PosicionArancelaria*) ll_get(listaPosicionArancelaria, k);
					if(pPosicionArancelaria != NULL && pFuncion(pArticulo, pPosicionArancelaria))
					{
						if(!printCostoFinalTransporteMaritimo(pArticulo, pPosicionArancelaria, pTransporteMaritimo))
						{
							printf("\n");
							retorno = 0;
						}
					}
				}
			}
		}
// ------------------------------------------------------------------------------------------------------
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
                                                       TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo,
													   int (*pFuncion)(void*, void*))
{
	int retorno = -1;
	Articulo* pArticulo;
	PosicionArancelaria* pPosicionArancelaria;
	if(listaArticulos != NULL && listaPosicionArancelaria != NULL && pTransporteAereo != NULL && pTransporteMaritimo != NULL && pFuncion != NULL)
	{
		int i, k;
		int lenArticulos, lenPosicionArancelaria;
		lenArticulos = ll_len(listaArticulos);
		lenPosicionArancelaria = ll_len(listaPosicionArancelaria);
//------------------------------------------------------------------------------------------------------
		for(i=0; i<lenArticulos; i++)
		{
			pArticulo = (Articulo*) ll_get(listaArticulos, i);
			if(pArticulo != NULL)
			{
				articulo_imprimirUnArticulo(pArticulo); // Imprimo Articulo
				for(k=0; k<lenPosicionArancelaria; k++)
				{
					pPosicionArancelaria = (PosicionArancelaria*) ll_get(listaPosicionArancelaria, k);
					if(pPosicionArancelaria != NULL && pFuncion(pArticulo, pPosicionArancelaria))
					{
						printCostosFinalesTransportes(pArticulo,pPosicionArancelaria,pTransporteAereo,pTransporteMaritimo);
						retorno = 0;
					}
				}
//-------------------------------------------------------------------------------------------------------------------
			}
		}
	}
	return retorno;
}

/** \brief Lista Posicion Arancelaria buscada por Nomenclador con sus Articulos y sus costos por Transporte
 * \param listaArticulos LinkedList*
 * \param listaPosicionArancelaria LinkedList*
 * \return int 0 si ok, -1 error
 */
int informe_listarPorBusquedaPorNomencladorPosAran(LinkedList* listaPosicionArancelaria, LinkedList* listaArticulos,
		                                           TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo,
												   int (*pFuncion)(void*, void*))
{
	int retorno = -1;
	void* pPosicionAranElement;
	void* pArticuloElement;

	if(listaPosicionArancelaria != NULL && listaArticulos != NULL  && pTransporteAereo != NULL && pTransporteMaritimo != NULL)
	{
		// Pido que ingrese el Nomenclador, busco el elemento y lo retorno
		pPosicionAranElement = buscarPorNomencladorPosicionArancelaria(listaPosicionArancelaria);

		// Verifico el elemento y imprimo
		if(pPosicionAranElement != NULL && !posicionArancelaria_imprimirUnaPosicionArancelaria(pPosicionAranElement))
		{
			pArticuloElement = ll_getNext(listaArticulos, 1);
			while(pArticuloElement != NULL)
			{
				if(pFuncion(pArticuloElement, pPosicionAranElement))
				{
					articulo_imprimirUnArticulo(pArticuloElement);
					printCostosFinalesTransportes((Articulo*)pArticuloElement,(PosicionArancelaria*)pPosicionAranElement,pTransporteAereo,pTransporteMaritimo);
				}
				pArticuloElement = ll_getNext(listaArticulos, 0);
			}
			retorno = 0;
		}
	}
	return retorno;
}
//------------------------------------------------------------------------------------------ PRINT COSTO FINAL TRANSPORTES
/** \brief Llama a las funciones print costo final ARG por Transporte Aereo y Maritimo
  	  	  	  	  	  las cuales esas mismas calculas y imprimen su resultado por consola
 * \param pArticulo Articulo*
 * \param pPosicionArancelaria PosicionArancelaria*
 * \param pTransporteAereo TransporteAereo*
 * \param pTransporteMaritimo TransporteMaritimo*
 * \return int -1 error, 0 si ok
 */
static int printCostosFinalesTransportes(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                 TransporteAereo* pTransporteAereo,TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	if(pArticulo != NULL && pPosicionArancelaria != NULL  && pTransporteAereo != NULL && pTransporteMaritimo != NULL &&
	  !printCostoFinalTransporteAereo(pArticulo, pPosicionArancelaria, pTransporteAereo) &&
	  !printCostoFinalTransporteMaritimo(pArticulo, pPosicionArancelaria, pTransporteMaritimo))
	{
		retorno = 0;
	}
	return retorno;
}


/** \brief Llama a la funcion calcular costo final Transporte Aereo y imprimet por consola el resultado
 * \param pArticulo Articulo*
 * \param pPosicionArancelaria PosicionArancelaria*
 * \param pTransporteAereo TransporteAereo*
 * \return int -1 error, 0 si ok
 */
static int printCostoFinalTransporteAereo(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                  TransporteAereo* pTransporteAereo)
{
	int retorno = -1;
    float costoTransporteAereo;;
	int flagError;
	if(pArticulo != NULL && pPosicionArancelaria != NULL  && pTransporteAereo != NULL)
	{
		if(transporteAereo_calcularCostoFinal(pArticulo, pPosicionArancelaria, pTransporteAereo) > -1)
		{
			//costoTransporteAereo = transporteAereo_calcularCostoFinal(pArticulo, pPosicionArancelaria, pTransporteAereo)
			costoTransporteAereo = articulo_getCostoTransporteAereo(pArticulo, &flagError);
			if(!flagError)
			{
				printf("\n > \x1b[43m \x1b[30m Costo final por Transporte Aereo: \x1b[0m \x1b[0m  USD %.2f", costoTransporteAereo);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/** \brief Llama a la funcion calcular costo final Transporte Maritimo y imprime por consola el resultado
 * \param pArticulo Articulo*
 * \param pPosicionArancelaria PosicionArancelaria*
 * \param pTransporteMaritimo TransporteMaritimo*
 * \return int -1 error, 0 si ok
 */
static int printCostoFinalTransporteMaritimo(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                     TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
    float costoTransporteMaritimo;
	int flagError;
	if(pArticulo != NULL && pPosicionArancelaria != NULL  && pTransporteMaritimo != NULL)
	{
		if(transporteMaritimo_calcularCostoFinal(pArticulo, pPosicionArancelaria, pTransporteMaritimo)>-1)
		{
			costoTransporteMaritimo = articulo_getCostoTransporteMaritimo(pArticulo, &flagError);
			if(!flagError)
			{
				printf("\n > \x1b[46m \x1b[30m Costo final por Transporte Maritimo: \x1b[0m \x1b[0m  USD %.2f \n", costoTransporteMaritimo);
				retorno = 0;
			}
		}
	}
	return retorno;
}
//------------------------------------------------------------------------------------------- Funciones de Busqueda
/** \brief Pido que ingrese el Nomenclador, busca el elemento y lo retorna
 * \param listaArticulos LinkedList*
 * \param listaPosicionArancelaria LinkedList*
 * \return void* puntero al Elemento encontrado, NULL si no lo encontr??
 */
void* buscarPorNomencladorPosicionArancelaria(LinkedList* listaPosicionArancelaria)
{
	void* pRetornoElement = NULL;
	void* pPosicionArancelariaElem;
	char nomencladorAux[NOMENCLADOR_LEN];

	if(listaPosicionArancelaria != NULL &&
	  !utn_getTexto(nomencladorAux, NOMENCLADOR_LEN,"\n - POSICION ARANCELARIA -"
									                "\n > Ingrese nomenclador: ", "\n\x1b[31m * ERROR\x1b[0m", 3))
	{
		// Busco elemento
		pPosicionArancelariaElem = ll_buscarElement_VL(listaPosicionArancelaria, funcionCriterio_compararPorNomenclador, nomencladorAux);

		// Verifico el elemento y lo retorno
		if(pPosicionArancelariaElem != NULL)
			pRetornoElement = pPosicionArancelariaElem;
	}
	return pRetornoElement;
}

/** \brief Pide que ingrese el Codigo del Articulo, busca el elemento y lo retorna
 * \param listaArticulos LinkedList*
 * \return void* puntero al Elemento encontrado, NULL si no lo encontr??
 */
void* buscarPorCodigoArticulo(LinkedList* listaArticulos)
{
	void* pRetornoElement = NULL;
	void* pArticulo;
	char codigoAux[CODIGO_LEN];

	if(listaArticulos != NULL &&
	   !utn_getTexto(codigoAux, CODIGO_LEN,"\n - BUSCAR ARTICULO -"
							               "\n > Ingrese el codigo del Articulo: ", "\n\x1b[31m * ERROR\x1b[0m", 2))
	{
		// Busco elemento
		pArticulo = ll_buscarElement_VL(listaArticulos, funcionCriterio_compararPorCodigoArticulo, codigoAux);

		// Verifico el elemento y lo retorno
		if(pArticulo != NULL)
			pRetornoElement = pArticulo;
	}
	return pRetornoElement;
}
//-----------------------------------------------------------------------------------------------------

/** \brief Veerifica si los Ids de los parametros ingresados son iguales
 * \param void* pArticuloElement
 * \param pPosicionAranElement
 * \return int 1 si son IGUALES, 0 error o si NO son iguales
 */
int funcionCriterio_sonIdsIgualesPosArancelaria(void* pElementArticulo, void* pElementPosAran)
{
	int retorno = 0;
	if(pElementArticulo != NULL && pElementPosAran != NULL)
	{
		int idPosAranArticulo, idPosicionArancelaria, flagErrorA, flagErrorB;
		//------------------------------------------------------------------------------------
		idPosAranArticulo = articulo_getIdPosicionArancelaria((Articulo*) pElementArticulo, &flagErrorA);
		idPosicionArancelaria = posicionArancelaria_getIdPosicionArancelaria((PosicionArancelaria*)pElementPosAran, &flagErrorB);
		//------------------------------------------------------------------------------------
		if(!flagErrorA && !flagErrorB &&
		   idPosAranArticulo == idPosicionArancelaria)
		{
			retorno = 1;
		}
	}
	return retorno;
}
