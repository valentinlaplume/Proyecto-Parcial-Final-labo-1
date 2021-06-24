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

#include "TransporteMaritimo.h"
#include "TransporteAereo.h"

#include "Informe.h"

#include "eGeneral.h"

// Flags estaticos
static int flagCargueArticulo = 0;
static int flagCarguePosicionArancelaria = 0;
static int flagCargueTransporteMaritimo = 0;
static int flagCargueTransporteAereo = 0;
static int flagCargueDatosGenerales = 0;

// Contadores estaticos
static int staticIdArticulo = 0;
static int staticIdPosicionArancelaria = 0;

// Funciones estáticas
static int verificarIdPosicionArancelaria(Dictionary* posicionesArancelarias, int idPosicionArancelaria);
static int existeIdPosicionArancelariaEnArticulo(Dictionary* articulos, int idPosicionArancelaria);

// SubMenus edit
static Articulo* subMenuEditArticulo(void* pElement, Dictionary* posicionesArancelarias);
static PosicionArancelaria* subMenuEditPosicionArancelaria(void* pElement);
static int controller_subMenuEditTransporteAereo(TransporteAereo* pTransporteAereo);
static int controller_subMenuEditTransporteMaritimo(TransporteMaritimo* pTransporteMaritimo);

// Carga del datos del articulo
static Articulo* cargaDatosArticulo(Dictionary* articulos, int idPosArancelariaEnArticulo);

// nueva entidad
#include "eGeneral.h"



int controller_pruebasWhile(Dictionary* articulos, Dictionary* posicionesArancelarias,
		                    TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo,
							int (*pFuncion)(void*, void*))
{
	int retorno = -1;
	if(articulos != NULL && posicionesArancelarias != NULL && pTransporteAereo != NULL )
	{
		LinkedList* listaArticulos;
		LinkedList* listaPosicionArancelaria;
		//--------------------------- Obtengo listas
		listaArticulos = dict_getValues(articulos);
		listaPosicionArancelaria = dict_getValues(posicionesArancelarias);

		//-----------------------------------------
		if(listaArticulos != NULL && listaPosicionArancelaria != NULL &&
		  !informe_prueba(listaArticulos, listaPosicionArancelaria,
				          pTransporteAereo, pTransporteMaritimo,
						  pFuncion) &&
		  !ll_deleteLinkedList(listaArticulos) &&
		  !ll_deleteLinkedList(listaPosicionArancelaria))
		{
			retorno = 0;
		}
	}
	return retorno;
}

int funcionCriterio_sonIdsIgualesPosArancelaria(void* pElementArticulo, void* pElementPosAran)
{
	int retorno = 0;
	if(pElementArticulo != NULL && pElementPosAran != NULL)
	{
		int idPosAranArticulo, idPosicionArancelaria, flagErrorA, flagErrorB;
		//------------------------------------------------------------
		idPosAranArticulo = articulo_getIdPosicionArancelaria((Articulo*) pElementArticulo, &flagErrorA);
		idPosicionArancelaria = posicionArancelaria_getIdPosicionArancelaria((PosicionArancelaria*)pElementPosAran, &flagErrorB);
		//------------------------------------------------------------
		if(!flagErrorA && !flagErrorB &&
		   idPosAranArticulo == idPosicionArancelaria)
		{
			retorno = 1;
		}
	}
	return retorno;
}




//------------------------------------ INFORME PARCIAL ----------------------------------
/** \brief Carga los datos Generales desde el archivo datosGenerales.csv (modo texto).
 * \param (Dictionary* articulos,
 *  							Dictionary* posicionesArancelarias,
 *  							TransporteAereo* pTransporteAereo,
 *  							TransporteMaritimo* pTransporteMaritimo)
 * \return int [-1] si error, 0 si OK
 */
int controller_informeParcial(Dictionary* articulos, Dictionary* posicionesArancelarias,
		                      TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;

	if(articulos != NULL && posicionesArancelarias != NULL && pTransporteAereo != NULL )
	{
		LinkedList* listaArticulos;
		LinkedList* listaPosicionArancelaria;
		listaArticulos = dict_getValues(articulos);
		listaPosicionArancelaria = dict_getValues(posicionesArancelarias);
		//-----------------------------------------
		if(listaArticulos != NULL && listaPosicionArancelaria != NULL &&
		  !informe_calcularCostosFinalesParcial(listaArticulos, listaPosicionArancelaria, pTransporteAereo, pTransporteMaritimo,
				                                funcionCriterio_sonIdsIgualesPosArancelaria) &&
		  !ll_sort(listaArticulos, funcionCriterio_compararCostoMaritimo, 1) &&
		  !articulo_imprimirArticulosInformeParcial(listaArticulos) &&
		  !ll_deleteLinkedList(listaArticulos) &&
		  !ll_deleteLinkedList(listaPosicionArancelaria))
		{
			retorno = 0;
		}
	}
	return retorno;
}
//--------------------------------------------------------------------------------
/*int calcularCostosFinales(Dictionary* datosGenerales, Dictionary* articulos)
{
	int retorno = -1;
	LinkedList* listaGeneral;
	LinkedList* listaArticulos;
	if(datosGenerales != NULL && articulos != NULL)
	{
		listaGeneral = dict_getValues(datosGenerales);
		listaArticulos = dict_getValues(articulos);
		if(listaGeneral != NULL && listaArticulos != NULL)
		{
			//ll_map(listaGeneral, pFuncion);

			//------------------------------
			eGeneral* pGeneral;
			int i;
			for(i=0; i<ll_len(listaGeneral); i++)
			{
				pGeneral = (eGeneral*)ll_get(listaGeneral, i);
				printf("\n Precio final por Transporte Aereo: USD %.2f"
					   "\n Precio final por Transporte Maritimo: USD %.2f",pGeneral->costoTransporteAereo,
					                                                       pGeneral->costoTransporteMaritimo);
			}
			retorno = 0;
			ll_deleteLinkedList(listaGeneral);
			ll_deleteLinkedList(listaArticulos);
		}
	}
	return retorno;
}*/
//*********************************************************************************************
void controller_setearValorInicialDeIdArticulo(int id)
{
	staticIdArticulo = id;
}

int controller_generarIdArticulo(void)
{
	staticIdArticulo++;
	return staticIdArticulo;
}
//------------------------------------------------------------------------
void controller_setearValorInicialDeIdPosicionArancelaria(int IdPosicionArancelariaMax)
{
	staticIdPosicionArancelaria = IdPosicionArancelariaMax;
}

int controller_generarIdPosicionArancelaria(void)
{
	staticIdPosicionArancelaria++;
	return staticIdPosicionArancelaria;
}
//*********************************************************************************************
/** \brief Carga los datos Generales desde el archivo datosGenerales.csv (modo texto).
 * \param path char*
 * \param articulos Dictionary*
 * \return int [-1] si path == NULL o articulos == NULL, 0 si OK
 */
int controller_cargarDatosGenerales(char* path, Dictionary* datosGenerales)
{
	FILE* pFile;
	int retorno = -1;
	int cantidadCargados = -1;

	if(path != NULL && datosGenerales != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			cantidadCargados = parser_eGeneralFromText(pFile, datosGenerales);
			if(cantidadCargados > 0)
			{
				flagCargueDatosGenerales = 1;
				retorno = 0;
			}
			fclose(pFile);
		}
		printf("\n - Leiste del archivo %s [ %d Datos Generales]",path,cantidadCargados);
	}
	return retorno;
}
/** \brief Carga los datos de los Articulos desde el archivo articulos.csv (modo texto).
 * \param path char*
 * \param articulos Dictionary*
 * \return int [-1] si path == NULL o articulos == NULL, 0 si OK
 */
int controller_cargarArticulos(char* path, Dictionary* articulos)
{
	FILE* pFile;
	int retorno = -1;
	int cantidadCargados = -1;
	int idMaxEncontrado;

	if(path != NULL && articulos != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			cantidadCargados = parser_articulosFromText(pFile, articulos, &idMaxEncontrado);
			if(cantidadCargados > 0)
			{
				controller_setearValorInicialDeIdArticulo(idMaxEncontrado);
				flagCargueArticulo = 1;
				retorno = 0;
			}
			fclose(pFile);
		}
		printf("\n - Leiste del archivo %s [ %d articulos]",path,cantidadCargados);
	}
	return retorno;
}
/** \brief Carga los datos de lss Posiciones Arancelarias desde el archivo posicionesArancelarias.csv (modo texto).
 * \param path char*
 * \param articulos Dictionary*
 * \return int [-1] si path == NULL o posicionesArancelarias == NULL, 0 si OK
 */
int controller_cargarPosicionesArancelarias(char* path, Dictionary* posicionesArancelarias)
{
	FILE* pFile;
	int retorno = -1;
	int cantidadCargados = -1;
	int idMaxEncontrado;

	if(path != NULL && posicionesArancelarias != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			cantidadCargados = parser_posicionesArancelariasFromText(pFile, posicionesArancelarias, &idMaxEncontrado);
			if(cantidadCargados > 0)
			{
				controller_setearValorInicialDeIdPosicionArancelaria(idMaxEncontrado);
				flagCarguePosicionArancelaria = 1;
				retorno = 0;
			}
			fclose(pFile);
		}
		printf("\n - Leiste del archivo %s [ %d Posiciones Arancelarias]",path,cantidadCargados);
	}
	return retorno;
}
/** \brief Carga los datos del Transporte Maritimo desde el archivo transporteMaritimo.csv (modo texto).
 * \param path char*
 * \param articulos TransporteMaritimo*
 * \return int [-1] si path == NULL o pTransporteMaritimo == NULL, 0 si OK
 */
int controller_cargarTransporteMaritimo(char* path, TransporteMaritimo* pTransporteMaritimo)
{
	FILE* pFile;
	int retorno = -1;
	int cantidadCargados = -1;
	if(path != NULL && pTransporteMaritimo != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			cantidadCargados = parser_transporteMaritimoFromText(pFile, pTransporteMaritimo);
			if(cantidadCargados > 0)
			{
				flagCargueTransporteMaritimo = 1;
				retorno = 0;
			}
			fclose(pFile);
		}
		printf("\n - Leiste del archivo %s [ %d Transporte Maritimo]",path,cantidadCargados);
	}
	return retorno;
}
/** \brief Carga los datos del Transporte Aereo desde el archivo transporteAereo.csv (modo texto).
 * \param path char*
 * \param articulos TransporteAereo*
 * \return int [-1] si path == NULL o pTransporteAereo == NULL, 0 si OK
 */
int controller_cargarTransporteAereo(char* path, TransporteAereo* pTransporteAereo)
{
	FILE* pFile;
	int retorno = -1;
	int cantidadCargados = -1;
	if(path != NULL && pTransporteAereo != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			cantidadCargados = parser_transporteAereoFromText(pFile, pTransporteAereo);
			if(cantidadCargados > 0)
			{
				flagCargueTransporteAereo = 1;
				retorno = 0;
			}
			fclose(pFile);
		}
		printf("\n - Leiste del archivo %s [ %d Transporte Aereo]",path,cantidadCargados);
	}
	return retorno;
}

//----------------------------------------------------------------------------------
/** \brief Guarda los datos de los articulos en el archivo articulos.csv (modo texto).
 * \param path char*
 * \param articulos Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_guardarArticulos(char* path, Dictionary* articulos)
{
	int retorno = -1;
	FILE* pFile;
	if(path != NULL && articulos != NULL)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			if(!serializer_articulosFromText(pFile, articulos))
			{
				retorno = 0;
				printf("\n - GUARDE DATOS ARTICULOS EN %s",path);
			}
			fclose(pFile);
		}
	}
	return retorno;
}
/** \brief Guarda los datos de las posiciones Arancelarias en el archivo posicionesArancelarias.csv (modo texto).
 * \param path char*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_guardarPosicionesArancelarias(char* path, Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	FILE* pFile;
	if(path != NULL && posicionesArancelarias != NULL)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			if(!serializer_posicionesArancelariasFromText(pFile, posicionesArancelarias))
			{
				retorno = 0;
				printf("\n - GUARDE DATOS POSICIONES ARANCELIAS EN %s",path);
			}
			fclose(pFile);
		}
	}
	return retorno;
}
/** \brief Guarda los datos Generales en el archivo datosGenerales.csv (modo texto).
 * \param path char*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_guardarDatosGenerales(char* path, Dictionary* articulos, Dictionary* posicionesArancelarias,
		TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	FILE* pFile;
	if(path != NULL && articulos != NULL && posicionesArancelarias != NULL)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			if(!serializer_eGeneralFromText(pFile, articulos, posicionesArancelarias, pTransporteAereo, pTransporteMaritimo))
			{
				retorno = 0;
			}
			fclose(pFile);
		}
	}
	return retorno;
}

/** \brief Guarda los datos del Transporte Maritimo en el archivo transporteMaritimo.csv (modo texto).
 * \param path char*
 * \param pTransporteMaritimo TransporteMaritimo*
 * \return int 0 si ok, -1 error
 */
int controller_guardarTransporteMaritimo(char* path, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	FILE* pFile;
	if(path != NULL && pTransporteMaritimo != NULL)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			if(!serializer_transporteMaritimoFromText(pFile, pTransporteMaritimo))
			{
				retorno = 0;
				printf("\n - GUARDE DATOS TRANSPORTE MARITIMO EN %s",path);
			}
			fclose(pFile);
		}
	}
	return retorno;
}
/** \brief Guarda los datos del Transporte Aereo en el archivo transporteAereo.csv (modo texto).
 * \param path char*
 * \param pTransporteAereo TransporteAereo*
 * \return int 0 si ok, -1 error
 */
int controller_guardarTransporteAereo(char* path, TransporteAereo* pTransporteAereo)
{
	int retorno = -1;
	FILE* pFile;
	if(path != NULL && pTransporteAereo != NULL)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			if(!serializer_transporteAereoFromText(pFile, pTransporteAereo))
			{
				retorno = 0;
				printf("\n - GUARDE DATOS TRANSPORTE AEREO EN %s",path);
			}
			fclose(pFile);
		}
	}
	return retorno;
}

//********************************************************************************************* LISTAR
/** \brief Lista Articulos
 * \param articulos Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_listarArticulos(Dictionary* articulos)
{
	int retorno = -1;
	LinkedList* listaArticulos;
	if(articulos != NULL && flagCargueArticulo==1)
	{
		// Obtengo articulos del diccionario
		listaArticulos = dict_getValues(articulos);

		if(listaArticulos != NULL &&
		  !articulo_imprimirArticulos(listaArticulos))
		{
			/*printf("\n\n");
			ll_sort(listaArticulos, funcionCriterio_compararPorNombreArticulo, 1);
			articulo_imprimirArticulos(listaArticulos);
			printf("\n\n > Listado Articulos");*/
			ll_deleteLinkedList(listaArticulos);
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief Lista Posiciones Arancelarias
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_listarPosicionesArancelarias(Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	LinkedList* listaPosicionesArancelarias;
	if(posicionesArancelarias != NULL)
	{
		// Obtengo posicionesArancelarias del diccionario
		listaPosicionesArancelarias = dict_getValues(posicionesArancelarias);

		if(listaPosicionesArancelarias != NULL &&
		  !posicionArancelaria_imprimirPosicionesArancelarias(listaPosicionesArancelarias) &&
		  !ll_deleteLinkedList(listaPosicionesArancelarias))
		{
			printf("\n\n > Listado Posiciones Arancelarias");
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief Lista Posiciones Arancelarias con tipo de licencia NO AUTOMÁTICA
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_listarPosicionesArancelariasNoAutomatica(Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	LinkedList* listaPosicionesArancelarias;
	LinkedList* listaFiltradaNoAutomatica;
	if(posicionesArancelarias != NULL)
	{
		// Obtengo posicionesArancelarias del diccionario
		listaPosicionesArancelarias = dict_getValues(posicionesArancelarias);
		if(listaPosicionesArancelarias != NULL)
		{
			listaFiltradaNoAutomatica = ll_filter(listaPosicionesArancelarias,funcionCriterio_porTipoLicenciaNoAutomatica);
			if(listaFiltradaNoAutomatica != NULL &&
			  !posicionArancelaria_imprimirPosicionesArancelarias(listaFiltradaNoAutomatica) &&
			  !ll_deleteLinkedList(listaPosicionesArancelarias) &&
			  !ll_deleteLinkedList(listaFiltradaNoAutomatica))
			{
				printf("\n\n > Listado Posiciones Arancelarias con tipo de licencia NO AUTOMÁTICA");
				retorno = 0;
			}
		}
	}
	return retorno;
}
/** \brief Lista Posiciones Arancelarias con tipo de licencia AUTOMÁTICA
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_listarPosicionesArancelariasAutomatica(Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	LinkedList* listaPosicionesArancelarias;
	LinkedList* listaFiltradaAutomatica;
	if(posicionesArancelarias != NULL)
	{
		// Obtengo posicionesArancelarias del diccionario
		listaPosicionesArancelarias = dict_getValues(posicionesArancelarias);
		if(listaPosicionesArancelarias != NULL)
		{
			listaFiltradaAutomatica = ll_filter(listaPosicionesArancelarias,funcionCriterio_porTipoLicenciaAutomatica);
			if(listaFiltradaAutomatica != NULL &&
			  !posicionArancelaria_imprimirPosicionesArancelarias(listaFiltradaAutomatica) &&
			  !ll_deleteLinkedList(listaPosicionesArancelarias) &&
			  !ll_deleteLinkedList(listaFiltradaAutomatica))
			{
				printf("\n\n > Listado Posiciones Arancelarias con tipo de licencia NO AUTOMÁTICA");
				retorno = 0;
			}
		}
	}
	return retorno;
}
/** \brief Lista todas las Posiciones Arancelarias con sus Articulos correspondientes, incluye las que no poseen articulos
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_listarTotalPosicionesArancelariaConSusArticulos(Dictionary* articulos, Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	LinkedList* listaArticulos;
	LinkedList* listaPosicionesArancelarias;
	if(articulos != NULL && posicionesArancelarias != NULL)
	{
		// Obtengo articulos del diccionario
		listaArticulos = dict_getValues(articulos);

		listaPosicionesArancelarias = dict_getValues(posicionesArancelarias);

		if(listaArticulos != NULL && listaPosicionesArancelarias != NULL &&
		  !informe_listarTotalPosicionArancelariaConSusArticulos(listaArticulos, listaPosicionesArancelarias))
		{
			printf("\n\n > Listado de todas las Posiciones Arancelarias junto con sus Articulos "
					 "\n > [ Inclusive las que no poseen articulos ]");
			ll_deleteLinkedList(listaArticulos);
			ll_deleteLinkedList(listaPosicionesArancelarias);
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief Lista solamente Posiciones Arancelarias con Articulos
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_listarSoloPosicionesArancelariaConArticulos(Dictionary* articulos, Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	LinkedList* listaArticulos;
	LinkedList* listaPosicionesArancelarias;
	if(articulos != NULL && posicionesArancelarias != NULL)
	{
		// Obtengo articulos del diccionario
		listaArticulos = dict_getValues(articulos);

		listaPosicionesArancelarias = dict_getValues(posicionesArancelarias);

		if(listaArticulos != NULL && listaPosicionesArancelarias != NULL &&
		  !informe_listarSoloPosicionArancelariaConArticulos(listaArticulos, listaPosicionesArancelarias))
		{
			printf("\n\n > Listado de Posiciones Arancelarias con Articulos incluidos");
			ll_deleteLinkedList(listaArticulos);
			ll_deleteLinkedList(listaPosicionesArancelarias);
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief Lista Posicion Arancelaria buscada por Nomenclador y todos sus Articulos que correspondan
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_listarArticulosPorBusquedaPorNomenclador(Dictionary* articulos, Dictionary* posicionesArancelarias,
		                                               TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	LinkedList* listaPosicionArancelaria;
	LinkedList* listaArticulos;

	if(articulos != NULL && posicionesArancelarias != NULL && pTransporteAereo != NULL && pTransporteMaritimo != NULL)
	{
		listaPosicionArancelaria = dict_getValues(posicionesArancelarias);
		listaArticulos = dict_getValues(articulos);
		//--------------------------------------------------------------------------------
		if(listaPosicionArancelaria != NULL && listaArticulos != NULL &&
		   !informe_listarPorBusquedaPorNomencladorPosAran(listaPosicionArancelaria, listaArticulos, pTransporteAereo, pTransporteMaritimo))
		{
			ll_deleteLinkedList(listaArticulos);
			ll_deleteLinkedList(listaPosicionArancelaria);
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief Lista Articulo buscado por Codigo
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_listarUnArticuloPorBusquedaPorCodigo(Dictionary* articulos)
{
	int retorno = -1;
	LinkedList* listaArticulos;
	void* pArticulo;

	if(articulos != NULL)
	{
		listaArticulos = dict_getValues(articulos);
		if(listaArticulos != NULL )
		{
			// Busco elemento
			pArticulo = busquedaPorCodigoArticulo(listaArticulos);
			// Verifico y imprimo elemento
			if(pArticulo != NULL && !articulo_imprimirUnArticulo(pArticulo) &&
			  !ll_deleteLinkedList(listaArticulos))
				retorno = 0;
		}
	}
	return retorno;
}


//******************************************************************************* ABM
/** \brief Submenu: Alta, Baja, Modificacion - listar [Articulo]
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_ABMPosicionArancelaria(Dictionary* posicionesArancelarias, Dictionary* articulos)
{
	int retorno = -1;
	int opcion;
	int opcion_salir = 7;
	if(posicionesArancelarias != NULL && articulos != NULL)
	{
		do
		{
			if(!utn_getNumero(&opcion,
					            "\n\n * ============ \x1b[32m\x1b[40m MENU POSICION ARANCELARIA \x1b[0m\x1b[0m ============ *"
								"\n | =============================================== |"
								"\n | 1 -  Listar Posiciones Arancelarias             |"
								"\n | 2 -  Dar de alta una Posicion Arancelaria       |"
								"\n | 3 -  Dar de baja una Posicion Arancelaria       |"
								"\n | 4 -  Modificar una Posicion Arancelaria         |"
								"\n | 5 -  Listar los tipo de licencia NO AUTOMÁTICA  |"
								"\n | 6 -  Listar los tipo de licencia AUTOMÁTICA     |"
								"\n | 7 -  Volver al menu principal                   |"
								"\n * ----------------------------------------------- *"
								"\n > Eliga opcion: ",
								"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 1, opcion_salir, 2))
			{
				switch(opcion)
				{
					case 1: // Listar posiciones arancelarias
						controller_listarPosicionesArancelarias(posicionesArancelarias);
					break;
					case 2: // Dar de alta una Posicion Arancelaria
						controller_altaPosicionArancelaria(posicionesArancelarias);
					break;
					case 3: // Dar de baja una Posicion Arancelaria
						controller_bajaPosicionArancelaria(posicionesArancelarias, articulos);
					break;
					case 4: // Modificar una Posicion Arancelaria
						controller_modificarPosicionArancelaria(posicionesArancelarias);
					break;
					case 5: // Listar los tipo de licencia NO AUTOMÁTICA
						controller_listarPosicionesArancelariasNoAutomatica(posicionesArancelarias);
					break;
					case 6: // Listar los tipo de licencia AUTOMÁTICA
						controller_listarPosicionesArancelariasAutomatica(posicionesArancelarias);
					break;
				}
			}
			// acordarse de guardar en archivo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}while(opcion != opcion_salir);
		retorno = 0;
	}
	return retorno;
}

/** \brief Submenu: Alta, Baja, Modificacion - listar [Posiciones Arancelarias]
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_ABMArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	int opcion;
	int opcion_salir = 6;
	if(articulos != NULL && posicionesArancelarias != NULL)
	{
		do
		{
			if(!utn_getNumero(&opcion,
								"\n\n * \x1b[37m\x1b[40m===============  MENU ARTICULO  ===============\x1b[0m\x1b[0m *"
								"\n | =============================================== |"
								"\n | 1 -  Listar articulos                           |"
								"\n | 2 -  Dar de alta un Articulo                    |"
								"\n | 3 -  Dar de baja un Articulo                    |"
								"\n | 4 -  Modificar un Articulo                      |"
								"\n | 5 -  Buscar y listar Articulo por Codigo        |"
								"\n | 6 -  Volver al menu principal                   |"
								"\n * ----------------------------------------------- *"
								"\n > Eliga opcion: ",
								"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 1, opcion_salir, 2))
			{
				switch(opcion)
				{
					case 1: // Listar articulos
						controller_listarArticulos(articulos);
						break;
					case 2: // Dar de ALTA un articulo
						controller_altaArticulo(articulos, posicionesArancelarias);
						break;
					case 3: // Dar de BAJA un articulo
						controller_bajaArticulo(articulos);
						break;
					case 4: // Modificar un articulo
						controller_modificarArticulo(articulos, posicionesArancelarias);
						break;
					case 5: // Buscar y listar Articulo por Codigo
						controller_listarUnArticuloPorBusquedaPorCodigo(articulos);
					break;
				}
			}
			// acordarse de guardar en archivo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}while(opcion != opcion_salir);
		retorno = 0;
	}
	return retorno;
}

//********************************************************************************** SUB MENU INFORME
/** \brief Submenu: Informes
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \param TransporteAereo* pTransporteAereo
 * \param TransporteMaritimo* pTransporteMaritimo
 * \return int 0 si ok, -1 error
 */
int controller_subMenuInforme(Dictionary* articulos, Dictionary* posicionesArancelarias,
		                      TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	int opcion;
	int opcion_salir = 5;
	if(articulos != NULL && posicionesArancelarias != NULL && pTransporteAereo != NULL && pTransporteMaritimo != NULL)
	{
		do
		{
			if(!utn_getNumero(&opcion,
								"\n"
								"\n * \x1b[95m\x1b[40m=========================   MENU INFORME   ==========================\x1b[0m\x1b[0m *"
								"\n | ===================================================================== | "
								"\n |  1  - Calcular y ver costo final por Transporte Maritimo              |"
								"\n |  2  - Calcular y ver con costo final por Transporte Aereo             |"
								"\n |  3  - Calcular y ver costos finales por Transportes                   |"
								"\n |  4  - Informe Parcial 2:                                              |"
								"\n |  * Mostrar costos finales ordenados ascendentemente por Costo Maritimo|"
								"\n |                                                                       |"
								"\n |  5  - Volver al menu principal                                        |"
								"\n * ---------------------------------------------------------------------- *"
								"\n > Eliga opcion: ", "\n\x1b[31m * OPCION INVALIDA * \x1b[0m",1, opcion_salir, 2))
			{
				switch(opcion)
				{
					case 1:// Listar Articulos costo final por Transporte Maritimo
						controller_costoFinalTransporteMaritimo(articulos, posicionesArancelarias,pTransporteMaritimo);
					break;
					case 2: // Listar Articulos con costo final por Transporte Aereo
						controller_costoFinalTransporteAereo(articulos, posicionesArancelarias,pTransporteAereo);
					break;
					case 3: // Listar Articulos con costo final por Transporte
						controller_costoFinalPorTransportes(articulos, posicionesArancelarias,pTransporteAereo,pTransporteMaritimo);
					break;
					case 4: // Informe Parcial 2
						controller_informeParcial(articulos, posicionesArancelarias, pTransporteAereo, pTransporteMaritimo);
					break;
				}
			}
		}while(opcion != opcion_salir);
		retorno = 0;
	}
	return retorno;
}



//********************************************************************************** SUB MENU TRANSPORTES
/** \brief Submenu: Modificacion - listar [Transporte Aereo]
 * \param pTransporteAereo TransporteAereo*
 * \return int 0 si ok, -1 error
 */
int controller_subMenuTransporteAereo(TransporteAereo* pTransporteAereo)
{
	int retorno = -1;
	int opcion;
	int opcion_salir = 3;
	if(pTransporteAereo != NULL)
	{
		do
		{
			if(!utn_getNumero(&opcion,
					            "\n\n * ============== \x1b[30m\x1b[43m TRANSPORTE AEREO \x1b[0m\x1b[0m ============== *"
								"\n | ================================================ |"
								"\n | 1 -  Mostrar información Transporte Aereo        |"
								"\n | 2 -  Modificar información del Transporte Aereo  |"
								"\n | 3 -  Volver al menu principal                    |"
								"\n * ------------------------------------------------ *"
								"\n > Eliga opcion: ",
								"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 1, opcion_salir, 2))
			{
				switch(opcion)
				{
					case 1: // Mostrar información Transporte Aereo
						transporteAereo_imprimirTransporteAereo(pTransporteAereo);
					break;
					case 2: // Modificar información del Transporte Aereo
						controller_subMenuEditTransporteAereo(pTransporteAereo);
					break;
				}
			}
			// acordarse de guardar en archivo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}while(opcion != opcion_salir);
		retorno = 0;
	}
	return retorno;
}
/** \brief Submenu: Modificacion - listar [Transporte Maritimo]
 * \param pTransporteMaritimo TransporteMaritimo*
 * \return int 0 si ok, -1 error
 */
int controller_subMenuTransporteMaritimo(TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	int opcion;
	int opcion_salir = 3;
	if(pTransporteMaritimo != NULL)
	{
		do
		{
			if(!utn_getNumero(&opcion,
					            "\n\n * ============= \x1b[30m\x1b[46m MENU TRANSPORTE MARITIMO \x1b[0m\x1b[0m ============= *"
								"\n | ====================================================== |"
								"\n | 1 -  Mostrar información Transporte Maritimo           |"
								"\n | 2 -  Modificar información del Transporte Maritimo     |"
								"\n | 3 -  Volver al menu principal                          |"
								"\n * ------------------------------------------------------ *"
								"\n > Eliga opcion: ",
								"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 1, opcion_salir, 2))
			{
				switch(opcion)
				{
					case 1: // Mostrar información Transporte Maritimo
						transporteMaritimo_imprimirTransporteMaritimo(pTransporteMaritimo);
					break;
					case 2: // Modificar información del Transporte Maritimo
						controller_subMenuEditTransporteMaritimo(pTransporteMaritimo);
					break;
				}
			}
			// acordarse de guardar en archivo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}while(opcion != opcion_salir);
		retorno = 0;
	}
	return retorno;
}
//------------------------------------------------------------------------
/** \brief Lista Articulos con su costo final por Transportes - Maritimo y Aereo
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \param TransporteAereo* pTransporteAereo
 * \param TransporteMaritimo* pTransporteMaritimo
 * \return int 0 si ok, -1 error
 */
int controller_costoFinalPorTransportes(Dictionary* articulos, Dictionary* posicionesArancelarias, TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;

	if(articulos != NULL && posicionesArancelarias != NULL && pTransporteAereo != NULL )
	{
		LinkedList* listaArticulos;
		LinkedList* listaPosicionArancelaria;
		listaArticulos = dict_getValues(articulos);
		listaPosicionArancelaria = dict_getValues(posicionesArancelarias);
		//-----------------------------------------
		if(listaArticulos != NULL && listaPosicionArancelaria != NULL &&
		  !informe_listarArticulosConCostoFinalPorTransportes(listaArticulos, listaPosicionArancelaria,pTransporteAereo, pTransporteMaritimo) &&
		  !ll_deleteLinkedList(listaArticulos) && !ll_deleteLinkedList(listaPosicionArancelaria))
			retorno = 0;
	}
	return retorno;
}
/** \brief Lista Articulos con su costo final por Transporte Aereo
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \param TransporteAereo* pTransporteAereo
 * \return int 0 si ok, -1 error
 */
int controller_costoFinalTransporteAereo(Dictionary* articulos, Dictionary* posicionesArancelarias, TransporteAereo* pTransporteAereo)
{
	int retorno = -1;

	if(articulos != NULL && posicionesArancelarias != NULL && pTransporteAereo != NULL )
	{
		LinkedList* listaArticulos;
		LinkedList* listaPosicionArancelaria;
		listaArticulos = dict_getValues(articulos);
		listaPosicionArancelaria = dict_getValues(posicionesArancelarias);
		//-----------------------------------------
		if(listaArticulos != NULL && listaPosicionArancelaria != NULL &&
		  !informe_listarArticulosConCostoFinalTransporteAereo(listaArticulos, listaPosicionArancelaria, pTransporteAereo) &&
		  !ll_deleteLinkedList(listaArticulos) && !ll_deleteLinkedList(listaPosicionArancelaria))
			retorno = 0;
	}
	return retorno;
}
/** \brief Lista Articulos con su costo final por Transporte aerMaritimoeo
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \param TransporteAereo* pTransporteAereo
 * \return int 0 si ok, -1 error
 */
int controller_costoFinalTransporteMaritimo(Dictionary* articulos, Dictionary* posicionesArancelarias, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;

	if(articulos != NULL && posicionesArancelarias != NULL && pTransporteMaritimo != NULL )
	{
		LinkedList* listaArticulos;
		LinkedList* listaPosicionArancelaria;
		listaArticulos = dict_getValues(articulos);
		listaPosicionArancelaria = dict_getValues(posicionesArancelarias);
		//-----------------------------------------
		if(listaArticulos != NULL && listaPosicionArancelaria != NULL &&
		  !informe_listarArticulosConCostoFinalTransporteMaritimo(listaArticulos, listaPosicionArancelaria, pTransporteMaritimo) &&
		  !ll_deleteLinkedList(listaArticulos) && !ll_deleteLinkedList(listaPosicionArancelaria))
			retorno = 0;
	}
	return retorno;
}
//********************************************************************************************* ALTAS
/** \brief Alta del [Articulo]
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
/*int controller_altaArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	Articulo buffer;
	Articulo* pArticulo;
	char idArticuloSTR[10];

	if(articulos != NULL && posicionesArancelarias != NULL &&
	  !controller_listarPosicionesArancelarias(posicionesArancelarias) &&
	  !utn_getNumero(&buffer.idPosicionArancelaria, "\n\n > Ingrese ID de la Posicion Arancelaria que corresponda"
	  						                          "\n > De caso que no exista, ingrese [0] y se le pedira los datos para dar de alta a una nueva Posicion Arancelaria"
	  						                          "\n > ",  "\n\x1b[31m * ERROR \x1b[0m", 0, 99999999, 2))
	{
		// Si eliga la opcion [0], da de alta una posicion arancelaria
		if(buffer.idPosicionArancelaria == 0)
		   buffer.idPosicionArancelaria = controller_altaPosicionArancelaria(posicionesArancelarias);

		// Se verifica ID posicion arancelaria y se piden los datos del Articulo
		if(verificarIdPosicionArancelaria(posicionesArancelarias, buffer.idPosicionArancelaria) &&
		  !informe_pedirDatosArticulo(buffer.nombre, buffer.codigo, buffer.descripcion, buffer.paisDeFabricacion,
		                             &buffer.fob, &buffer.peso, &buffer.ancho, &buffer.altura, &buffer.profundidad))
		{

			buffer.idArticulo = controller_generarIdArticulo();
			// Creo el Articulo
			pArticulo = articulo_newParam(buffer.idArticulo, buffer.idPosicionArancelaria, buffer.nombre, buffer.codigo,
										  buffer.descripcion, buffer.paisDeFabricacion, buffer.fob, buffer.peso, buffer.ancho, buffer.altura, buffer.profundidad);
			if(pArticulo != NULL)
			{
				snprintf(idArticuloSTR, sizeof(idArticuloSTR), "%d", buffer.idArticulo);
				// Inserto Articulo en el diccionario
				if(!dict_insert(articulos, idArticuloSTR, pArticulo))
				{
					flagCargueArticulo = 1;
					retorno = 0;
				}
			}
		}

	}
	return retorno;
}*/

int controller_altaArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	Articulo bufferArticulo;
	Articulo* pArticulo;
	int flagDiAlta = 0;
	int opcion;
	//------------------ Variables para Posicion Arancelria
	char idPosAranArtSTR[ID_STR];
	PosicionArancelaria* pPosArancelariaElegida;
	//------------------------------------------------------------------------------
	if(articulos != NULL && posicionesArancelarias != NULL &&
	  !controller_listarPosicionesArancelarias(posicionesArancelarias) &&
	  !utn_getNumero(&opcion, "\n\n * =============== \x1b[30m\x1b[47m ALTA ARTICULO \x1b[0m\x1b[0m =============== *"
				              "\n | ================================================= |"
			                  "\n |  1 - Elegir una Posicion Arancelaria Existente    |"
	  				          "\n |  2 - Dar de alta a una nueva Posicion Arancelaria |"
	  				          "\n |  3 - Volver atras                                 |"
			  	  	  	  	  "\n > Opcion: ",
							  "\n\x1b[31m * ERROR \x1b[0m", 1, 3, 2))
	{
		switch(opcion)
		{
			case 1:
				if(!utn_getAlfanumerico(idPosAranArtSTR, 10,
				"\n > Ingrese ID de la [Posicion Arancelaria] existente: ", "\n\x1b[31m * ERROR \x1b[0m", 2))

				{
					pPosArancelariaElegida = (PosicionArancelaria*) dict_get(posicionesArancelarias, idPosAranArtSTR);
					if(pPosArancelariaElegida == NULL)
						printf("\n > ID de la Posicion Arancelaria no existe");
					else
					{
						posicionArancelaria_imprimirUnaPosicionArancelaria(pPosArancelariaElegida);
						bufferArticulo.idPosicionArancelaria = atoi(idPosAranArtSTR);
						pArticulo = cargaDatosArticulo(articulos, bufferArticulo.idPosicionArancelaria);
						if(pArticulo != NULL)
						{
							printf("\n > Articulo dado de alta con éxito\n");
							articulo_imprimirUnArticulo(pArticulo);
							flagDiAlta = 1;
						}
					}
				}
			break;
			case 2:
				bufferArticulo.idPosicionArancelaria = controller_altaPosicionArancelaria(posicionesArancelarias);
				if(bufferArticulo.idPosicionArancelaria > 0)
				{
					pArticulo = cargaDatosArticulo(articulos, bufferArticulo.idPosicionArancelaria);
					if(pArticulo != NULL)
					{
						printf("\n > Articulo dado de alta con éxito\n");
						articulo_imprimirUnArticulo(pArticulo);
						flagDiAlta = 1;
					}
				}
			break;
		}
		//---------------------- FIN SWITCH -----------------------------------------------
		if(flagDiAlta == 1 && !controller_guardarArticulos("articulos.csv", articulos))
			retorno = 0;
	}
	return retorno;
}

static Articulo* cargaDatosArticulo(Dictionary* articulos, int idPosArancelariaEnArticulo)
{
	Articulo* pArticulo;
	Articulo* pArticuloRetorno = NULL;
	Articulo bufferArticulo;
	char idArticuloStrAux[ID_STR];
	//------------------------------------------------------------------------------------------
	LinkedList* listaArticulo;
	listaArticulo = dict_getValues(articulos);
	if(articulos != NULL && listaArticulo != NULL &&
	  !informe_pedirDatosArticulo(listaArticulo, bufferArticulo.nombre, bufferArticulo.codigo, bufferArticulo.descripcion, bufferArticulo.paisDeFabricacion,
								 &bufferArticulo.fob, &bufferArticulo.peso, &bufferArticulo.ancho, &bufferArticulo.altura, &bufferArticulo.profundidad))
	{
		// Genero ID Articulo
		bufferArticulo.idArticulo = controller_generarIdArticulo();
		// Creo un nuevo Articulo
		pArticulo = articulo_newParam(bufferArticulo.idArticulo, idPosArancelariaEnArticulo, bufferArticulo.nombre, bufferArticulo.codigo,
									  bufferArticulo.descripcion, bufferArticulo.paisDeFabricacion, bufferArticulo.fob, bufferArticulo.peso, bufferArticulo.ancho,
									  bufferArticulo.altura, bufferArticulo.profundidad);
		if(pArticulo != NULL)
		{
			// Convierto ID para usarlo como Key e insertarlo en el Disccionario
			snprintf(idArticuloStrAux, sizeof(idArticuloStrAux), "%d", bufferArticulo.idArticulo);
			if(!dict_insert(articulos, idArticuloStrAux, pArticulo))
			{
				flagCargueArticulo = 1;
				pArticuloRetorno = pArticulo;
			}
		}
	}
	ll_deleteLinkedList(listaArticulo);
	return pArticuloRetorno;
}

/** \brief Alta de la [Posicion Arancelaria]
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int (ID > 0) si logró dar de ok,
 *             -1 error
 */
int controller_altaPosicionArancelaria(Dictionary* posicionesArancelarias)
{
	int IdRetorno = -1;
	PosicionArancelaria buffer;
	PosicionArancelaria* pPosicionArancelaria;
	char idPosicionArancelariaSTR[ID_STR];
	LinkedList* listaPosAran;

	listaPosAran = dict_getValues(posicionesArancelarias);
	if(listaPosAran != NULL && posicionesArancelarias != NULL && posicionesArancelarias != NULL &&
	  !informe_pedirDatosPosicionArancelaria(listaPosAran, buffer.nomenclador, &buffer.porcentajeSeguro, &buffer.porcentajeImportacion, &buffer.porcentajeTasaEstadistica, &buffer.tipoLicencia))
	{
		buffer.idPosicionArancelaria = controller_generarIdPosicionArancelaria();
		pPosicionArancelaria = posicionArancelaria_newParam(buffer.idPosicionArancelaria, buffer.nomenclador, buffer.porcentajeSeguro,
				                                            buffer.porcentajeImportacion, buffer.porcentajeTasaEstadistica, buffer.tipoLicencia);
		if(pPosicionArancelaria != NULL)
		{
			snprintf(idPosicionArancelariaSTR, sizeof(idPosicionArancelariaSTR), "%d", buffer.idPosicionArancelaria);
			if(!dict_insert(posicionesArancelarias, idPosicionArancelariaSTR, pPosicionArancelaria))
			{
				flagCarguePosicionArancelaria = 1;
				IdRetorno = buffer.idPosicionArancelaria;
				controller_guardarPosicionesArancelarias("posicionesArancelarias.csv", posicionesArancelarias);
				ll_deleteLinkedList(listaPosAran);
			}
		}
	}
	return IdRetorno;
}
//********************************************************************************************* BAJAS
/** \brief Baja de un [Articulo]
 * \param articulos Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_bajaArticulo(Dictionary* articulos)
{
	char idStr[ID_STR];
	int retorno = -1;
	Articulo* pArticulo;

	if(articulos != NULL && flagCargueArticulo == 1 && !controller_listarArticulos(articulos) &&
	  !utn_getTexto(idStr, ID_STR, "\n\n - BAJA DE ARTICULO -"
			                              "\n > Ingrese ID del [Articulo] a dar de baja: ", "\n\x1b[31m * ERROR \x1b[0m", 2))
	{
		pArticulo = (Articulo*) dict_get(articulos, idStr);
		if(pArticulo != NULL && !articulo_delete(pArticulo))
		{
			if(!dict_remove(articulos, idStr))
			{
				printf("\n > Articulo dado de baja");
				controller_guardarArticulos("articulos.csv", articulos);
				retorno = 0;
			}
		}

	}
	return retorno;
}
/* \brief Baja de una [Posicion Arancelaria]
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_bajaPosicionArancelaria(Dictionary* posicionesArancelarias, Dictionary* articulos)
{
	char idStr[10];
	int retorno = -1;
	int idPosAranAux, flagErrorA;
	int flagExisteEnArticulo = 0;
	PosicionArancelaria* pPosicionArancelaria;

	if(posicionesArancelarias != NULL && articulos != NULL && flagCarguePosicionArancelaria == 1 &&
	  !controller_listarPosicionesArancelarias(posicionesArancelarias) &&
	  !utn_getTexto(idStr, sizeof(idStr), "\n\n - BAJA DE POSICION ARANCELARIA -"
			                              "\n > Ingrese ID de la [Posicion Arancelaria] a dar de baja: ", "\n\x1b[31m * ERROR \x1b[0m", 2))
	{
		pPosicionArancelaria = (PosicionArancelaria*) dict_get(posicionesArancelarias, idStr);
		if(pPosicionArancelaria != NULL)
		{
			//-------- Verifico si esa Posicion Arancelaria pertenece a un Articulo ---------
			idPosAranAux = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagErrorA);
			if(!flagErrorA)
				flagExisteEnArticulo = existeIdPosicionArancelariaEnArticulo(articulos, idPosAranAux);
			if(flagExisteEnArticulo == 1)
				printf("\n > La Posicion Arancelaria no puede ser dada de baja ya que posee a un articulo existente");
			//-------- Si no pertenece entonces elimino -------------------------------------
			if(flagExisteEnArticulo == 0 && !posicionArancelaria_delete(pPosicionArancelaria)&&
			  !dict_remove(posicionesArancelarias, idStr))
			{
				printf("\n > Posicion Arancelaria dada de baja");
				controller_guardarPosicionesArancelarias("posicionesArancelarias.csv", posicionesArancelarias);
				retorno = 0;
			}
		}
	}
	return retorno;
}
//void* busquedaPorIdPosicionArancelaria(Dictionary* posicionesArancelarias, char* pId);
/*int controller_bajaPosicionArancelaria(Dictionary* posicionesArancelarias, Dictionary* articulos)
{
	char idStr[10];
	int retorno = -1;
	int idPosAranAux, flagErrorA;
	int flagExisteEnArticulo = 0;
	PosicionArancelaria* pPosicionArancelaria;

	if(posicionesArancelarias != NULL && articulos != NULL && flagCarguePosicionArancelaria == 1 &&
	  !controller_listarPosicionesArancelarias(posicionesArancelarias))
	{
		pPosicionArancelaria = (PosicionArancelaria*) busquedaPorIdPosicionArancelaria(posicionesArancelarias, idStr);
		if(pPosicionArancelaria != NULL)
		{
			//-------- Verifico si esa Posicion Arancelaria pertenece a un Articulo ---------
			idPosAranAux = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagErrorA);
			if(!flagErrorA)
				flagExisteEnArticulo = existeIdPosicionArancelariaEnArticulo(articulos, idPosAranAux);
			if(flagExisteEnArticulo == 1)
				printf("\n > La Posicion Arancelaria no puede ser dada de baja ya que posee a un articulo existente");
			//-------- Si no pertenece entonces elimino -------------------------------------
			if(flagExisteEnArticulo == 0 && !posicionArancelaria_delete(pPosicionArancelaria)&&
			  !dict_remove(posicionesArancelarias, idStr))
			{
				printf("\n > Posicion Arancelaria dada de baja");
				retorno = 0;
			}
		}
	}
	return retorno;
}*/
/** \brief Pide que ingrese el ID de la Posicion Arancelaria, busca el elemento y lo retorna
 * \param posicionesArancelarias Dictionary*
 * \param char* pId
 * \return void* puntero al Elemento encontrado, NULL si no lo encontró
 */
/*void* busquedaPorIdPosicionArancelaria(Dictionary* posicionesArancelarias, char* pId)
{
	void* pRetornoElement = NULL;
	void* pElementAuxiliar;
	if(posicionesArancelarias != NULL && !utn_getTexto(pId, sizeof(pId),
			"\n > Ingrese ID de la [Posicion Arancelaria]: ", "\n\x1b[31m * ERROR \x1b[0m", 2))
	{
		pElementAuxiliar =  dict_get(posicionesArancelarias, pId);
		if(pElementAuxiliar != NULL)
			pRetornoElement = pElementAuxiliar;
	}
	return pRetornoElement;
}*/
//******************************************************************************** MODIFICAR
/** \brief Modificacion de un [Articulo]
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_modificarArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias)
{
	char IdStr[ID_STR];
	int retorno = -1;
	void* pElemento;
	Articulo* pArticulo;

	if(articulos !=  NULL && posicionesArancelarias != NULL && flagCargueArticulo == 1 && !controller_listarArticulos(articulos) &&
	  !utn_getAlfanumerico(IdStr, sizeof(IdStr), "\n\n > Ingrese ID del articulo a modificar: ", "\n\x1b[31m * ERROR \x1b[0m", 2))
	{
		// Busco al pElement dandole su key (en este caso uso su id)
		pElemento = dict_get(articulos, IdStr);
		pArticulo = subMenuEditArticulo(pElemento, posicionesArancelarias);
		if(pArticulo != NULL)
		{
			articulo_imprimirUnArticulo(pArticulo);
			printf("\n\n > Modificacion con exito");
			if(!controller_guardarArticulos("articulos.csv", articulos))
					retorno = 0;
		}
	}
	return retorno;
}
/** \brief Modificacion de una [Posicion Arancelaria]
 * \param articulos Dictionary*
 * \param posicionesArancelarias Dictionary*
 * \return int 0 si ok, -1 error
 */
int controller_modificarPosicionArancelaria(Dictionary* posicionesArancelarias)
{
	char IdStr[ID_STR];
	int retorno = -1;
	void* pElemento;
	PosicionArancelaria* pPosicionArancelaria;

	if(posicionesArancelarias != NULL && flagCargueArticulo == 1 &&
	  !controller_listarPosicionesArancelarias(posicionesArancelarias) &&
	  !utn_getAlfanumerico(IdStr, sizeof(IdStr), "\n\n > Ingrese ID de la posicion arancelaria a modificar: ", "\n\x1b[31m * ERROR \x1b[0m", 2))
	{
		// Busco al pElement dandole su key (en este caso uso su id)
		pElemento = dict_get(posicionesArancelarias, IdStr);
		pPosicionArancelaria = subMenuEditPosicionArancelaria(pElemento);
		if(pPosicionArancelaria != NULL)
		{
			posicionArancelaria_imprimirUnaPosicionArancelaria(pPosicionArancelaria);
			printf("\n\n > Modificacion con exito");
			controller_guardarPosicionesArancelarias("posicionesArancelarias.csv", posicionesArancelarias);
			retorno = 0;
		}
	}
	return retorno;
}

//******************************************************************************************* FUNCIONES ESTÁTICAS
//******************************************************************************************* STATIC SUB MENUS MODIFICAR

/** \brief SubMenu statico de modificacion [Posicion Arancelaria]
 * \param pElement void*
 * \return int 0 si ok, -1 error
 */
static PosicionArancelaria* subMenuEditPosicionArancelaria(void* pElement)
{
	PosicionArancelaria* pRetorno = NULL;
	int opcion;
	int flagModificado = 0;

	if(pElement == NULL)
		printf("\n * No existe articulo con ese ID\n");
	else if(pElement != NULL)
	{
		PosicionArancelaria* pPosicionArancelaria = (PosicionArancelaria*) pElement;
		PosicionArancelaria buffer;
		int opcion_salir = 6;
		//articulo_mostrarArticulo(pArticulo);
		do
		{
			if(!utn_getNumero(&opcion,
								"\n\n * =============  \x1b[30m\x1b[46mSUBMENU MODIFICAR\x1b[0m\x1b[0m  ============= *"
								"\n | =============================================== |"
								"\n | 1 -  Modificar Nomenclador                      |"
								"\n | 2 -  Modificar porcentaje de seguro             |"
								"\n | 3 -  Modificar porcentaje de importacion        |"
					            "\n | 4 -  Modificar porcentaje de tasa estadística   |"
								"\n | 5 -  Modificar tipo de licencia                 |"
								"\n | 6 -  Salir                                      |"
								"\n * ----------------------------------------------- *"
								"\n > Eliga opcion: ",
								"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 1, opcion_salir, 2))
			{
				switch(opcion)
				{
					case 1: // Modificar Nomenclador
						printf("\n - MODIFICACION DEL NOMENCLADOR -");
						if(!utn_getTexto(buffer.nomenclador, NOMENCLADOR_LEN, "\n > Ingrese nomenclador: ", "\x1b[31m * ERROR \x1b[0m", 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!posicionArancelaria_setNomenclador(pPosicionArancelaria, buffer.nomenclador))
								flagModificado = 1;
						}
					break;
					case 2: // Modificar porcentaje de seguro
						printf("\n - MODIFICACION DEL PORCENTAJE DEL SEGURO -");
						if(!utn_getNumeroFloat(&buffer.porcentajeSeguro, " > Ingrese porcentaje de seguro: %", "\x1b[31m * ERROR \x1b[0m", 0.1, 100, 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!posicionArancelaria_setPorcentajeSeguro(pPosicionArancelaria, buffer.porcentajeSeguro))
								flagModificado = 1;
						}
					break;
					case 3: // Modificar porcentaje de importacion
						printf("\n - MODIFICACION DEL PORCENTAJE DE IMPORTACION -");
						if(!utn_getNumeroFloat(&buffer.porcentajeImportacion, " > Ingrese porcentaje de importacion: %", "\x1b[31m * ERROR \x1b[0m", 0.1, 100, 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!posicionArancelaria_setPorcentajeImportacion(pPosicionArancelaria, buffer.porcentajeImportacion))
								flagModificado = 1;
						}
					break;
					case 4: // Modificar porcentaje de tasa estadística
						printf("\n - MODIFICACION DEL PORCENTAJE DE TASA ESTADÍSTICA -");
						if(!utn_getNumeroFloat(&buffer.porcentajeTasaEstadistica, " > Ingrese porcentaje de tasa estadística: %", "\x1b[31m * ERROR \x1b[0m", 0.1, 100, 2) &&
					       !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!posicionArancelaria_setPorcentajeTasaEstadistica(pPosicionArancelaria, buffer.porcentajeTasaEstadistica))
								flagModificado = 1;
						}
					break;
					case 5: // Modificar tipo de licencia
						printf("\n - MODIFICACION TIPO DE LICENCIA -");
						if(!utn_getNumero(&buffer.tipoLicencia, " > Ingrese tipo de licencia [0]AUTOMATICA - [1]NO AUTOMATICA: ", "\x1b[31m * ERROR \x1b[0m", 0, 1, 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!posicionArancelaria_setTipoLicencia(pPosicionArancelaria, buffer.tipoLicencia))
								flagModificado = 1;
						}
					break;
				}
			}
		}while(opcion != opcion_salir);

		if(flagModificado == 1) // Se modificó el articulo, entonces lo retorno para imprimirlo modificado.
			pRetorno = pPosicionArancelaria;
	}
	return pRetorno;
}
/** \brief SubMenu statico de modificacion [Articulo]
 * \param pElement void*
 * \return int 0 si ok, -1 error
 */
static Articulo* subMenuEditArticulo(void* pElement, Dictionary* posicionesArancelarias)
{
	Articulo* pRetorno = NULL;
	int opcion;
	int flagModificado = 0;

	if(pElement == NULL)
		printf("\n * No existe articulo con ese ID\n");
	else if(pElement != NULL && posicionesArancelarias != NULL)
	{
		Articulo* pArticulo = (Articulo*) pElement;
		Articulo buffer;
		int opcion_salir = 10;
		//articulo_mostrararticulo(pArticulo);
		do
		{
			if(!utn_getNumero(&opcion,
								"\n\n * =============  \x1b[30m\x1b[46mSUBMENU MODIFICAR\x1b[0m\x1b[0m  ============= *"
								"\n | =============================================== |"
					            "\n | 0 -  Modificar Posicion Arancelaria             |"
								"\n | 1 -  Modificar Nombre                           |"
								"\n | 2 -  Modificar Codigo                           |"
								"\n | 3 -  Modificar Descripcion                      |"
					            "\n | 4 -  Modificar Pais de fabricacion              |"
								"\n | 5 -  Modificar valor Fob                        |"
								"\n | 6 -  Modificar peso                             |"
								"\n | 7 -  Modificar ancho[cm] del articulo           |"
								"\n | 8 -  Modificar altura[cm] del articulo          |"
								"\n | 9 -  Modificar profundidad[cm] del articulo     |"
								"\n |10 -  Salir                                      |"
								"\n * ----------------------------------------------- *"
								"\n > Eliga opcion: ",
								"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 0, opcion_salir, 2))
			{
				switch(opcion)
				{
					case 0:
						if(!controller_listarPosicionesArancelarias(posicionesArancelarias) &&
						   !utn_getNumero(&buffer.idPosicionArancelaria, "\n\n > Ingrese ID de la Posicion Arancelaria: ", "\n\x1b[31m * ERROR \x1b[0m", 0, 99999999, 2) &&
						    verificarIdPosicionArancelaria(posicionesArancelarias, buffer.idPosicionArancelaria) &&
							!laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!articulo_setIdPosicionArancelaria(pArticulo, buffer.idPosicionArancelaria))
								flagModificado = 1;
						}
					break;
					case 1: // Modificar Nombre
						printf("\n - MODIFICACION DEL NOMBRE -");
						if(!utn_getNombre(buffer.nombre, NOMBRE_LEN, "\n > Ingrese nombre del articulo: ", "\n\x1b[31m * ERROR \x1b[0m", 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!articulo_setNombre(pArticulo, buffer.nombre))
								flagModificado = 1;
						}
					break;
					case 2: // Modificar Codigo
						printf("\n - MODIFICACION DEL CODIGO -");
						if(!utn_getTexto(buffer.codigo, CODIGO_LEN, " > Ingrese el codigo del articulo: ", "\n\x1b[31m * ERROR \x1b[0m", 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!articulo_setCodigo(pArticulo, buffer.codigo))
								flagModificado = 1;
						}
					break;
					case 3: // Modificar Descripcion
						printf("\n - MODIFICACION DE LA DESCRIPCION -");
						if(!utn_getTexto(buffer.descripcion, DESCRIPCION_LEN, " > Ingrese descripcion del articulo: ", "\n\x1b[31m * ERROR \x1b[0m", 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!articulo_setDescripcion(pArticulo, buffer.descripcion))
								flagModificado = 1;
						}
					break;
					case 4: // Modificar Pais de fabricacion
						printf("\n - MODIFICACION PAIS DE FABRICACION -");
						if( !utn_getNombre(buffer.paisDeFabricacion, PAIS_LEN, " > Ingrese pais de fabricación del articulo: ", "\n\x1b[31m * ERROR \x1b[0m", 2) &&
					       !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!articulo_setPaisDeFabricacion(pArticulo, buffer.paisDeFabricacion))
								flagModificado = 1;
						}
					break;
					case 5: // Modificar valor Fob
					printf("\n - MODIFICACION VALOR FOB -");
					if(!utn_getNumeroFloat(&buffer.fob, " > Ingrese valor fob del articulo: USD ", "\n\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
					   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
					{
						if(!articulo_setFob(pArticulo, buffer.fob))
							flagModificado = 1;
					}
					break;
					case 6: // Modificar peso
					printf("\n - MODIFICACION DEL PESO -");
					if(!utn_getNumeroFloat(&buffer.peso, " > Ingrese peso en [kg] del articulo: ", "\n\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
					   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
					{
						if(!articulo_setPeso(pArticulo, buffer.peso))
							flagModificado = 1;
					}
					break;
					case 7: // Modificar ancho[cm] del articulo
					printf("\n - MODIFICACION ANCHO DEL ARTICULO -");
					if(!utn_getNumeroFloat(&buffer.ancho, "\n > Ingrese ancho[cm] del articulo: ", "\n\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
					   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
					{
						if(!articulo_setAncho(pArticulo, buffer.ancho))
							flagModificado = 1;
					}
					break;
					case 8: // Modificar altura[cm] del articulo
					printf("\n - MODIFICACION ALTURA DEL ARTICULO -");
					if(!utn_getNumeroFloat(&buffer.altura, " > Ingrese altura[cm] del articulo: ", "\n\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
					   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
					{
						if(!articulo_setAltura(pArticulo, buffer.altura))
							flagModificado = 1;
					}
					break;
					case 9: // Modificar profundidad[cm] del articulo
					printf("\n - MODIFICACION PROFUNDIDAD DEL ARTICULO -");
					if(!utn_getNumeroFloat(&buffer.profundidad, " > Ingrese profundidad[cm] del articulo: ", "\n\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
					   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
					{
						if(!articulo_setProfundidad(pArticulo, buffer.altura))
							flagModificado = 1;
					}
					break;
				}
			}
		}while(opcion != opcion_salir);

		if(flagModificado == 1) // Se modificó el articulo, entonces lo retorno para imprimirlo modificado.
			pRetorno = pArticulo;
	}

	return pRetorno;
}
/** \brief SubMenu statico de modificacion [TransporteMaritimo]
 * \param pTransporteMaritimo TransporteMaritimo*
 * \return int 0 si ok, -1 error
 */
static int controller_subMenuEditTransporteMaritimo(TransporteMaritimo* pTransporteMaritimo)
{
	int opcion;
	int retorno = -1;
	int flagModificado = 0;

	if(pTransporteMaritimo == NULL)
		printf("\n * ERROR\n");
	else if(pTransporteMaritimo != NULL)
	{
		TransporteMaritimo buffer;
		int opcion_salir = 3;
		do
		{
			if(!utn_getNumero(&opcion,
								"\n\n * =============  \x1b[30m\x1b[46mSUBMENU MODIFICAR\x1b[0m\x1b[0m  ============= *"
								"\n | =============================================== |"
								"\n | 1 -  Modificar metros Cubicos                   |"
								"\n | 2 -  Modificar precio Contenedor                |"
								"\n | 3 -  Salir                                      |"
								"\n * ----------------------------------------------- *"
								"\n > Eliga opcion: ",
								"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 1, opcion_salir, 2))
			{
				switch(opcion)
				{
					case 1: // Modificar metros Cubicos
						printf("\n - MODIFICACION METROS CUBICOS -");
						if(!utn_getNumeroFloat(&buffer.metrosCubicos, "\n > Ingrese metros cubicos: ", "\x1b[31m * ERROR \x1b[0m", 0.1, 9999, 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!transporteMaritimo_setMetrosCubicos(pTransporteMaritimo, buffer.metrosCubicos))
								flagModificado = 1;
						}
					break;
					case 2: // Modificar precio Contenedor
						printf("\n - MODIFICACION PRECIO DEL CONTENEDOR -");
						if(!utn_getNumeroFloat(&buffer.precioContenedor, "\n > Ingrese precio del Contenedor: ", "\x1b[31m * ERROR \x1b[0m", 0.1, 9999, 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!transporteMaritimo_setPrecioContenedor(pTransporteMaritimo, buffer.precioContenedor))
								flagModificado = 1;
						}
					break;
				}
			}
			controller_guardarTransporteMaritimo("transporteMaritimo.csv", pTransporteMaritimo);
		}while(opcion != opcion_salir);

		if(flagModificado == 1 &&
		  !transporteMaritimo_imprimirTransporteMaritimo(pTransporteMaritimo)) // Se modificó el articulo, entonces lo retorno para imprimirlo modificado.
		{
			printf("\n > Modificacion con éxito");
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief SubMenu statico de modificacion [Transporte Aereo]
 * \param pTransporteAereo TransporteAereo*
 * \return int 0 si ok, -1 error
 */
static int controller_subMenuEditTransporteAereo(TransporteAereo* pTransporteAereo)
{
	int opcion;
	int retorno = -1;
	int flagModificado = 0;

	if(pTransporteAereo == NULL)
		printf("\n * ERROR\n");
	else if(pTransporteAereo != NULL)
	{
		TransporteAereo buffer;
		int opcion_salir = 3;
		do
		{
			if(!utn_getNumero(&opcion,
								"\n\n * =============  \x1b[30m\x1b[46mSUBMENU MODIFICAR\x1b[0m\x1b[0m  ============= *"
								"\n | =============================================== |"
								"\n | 1 -  Modificar constante Volumetrica            |"
								"\n | 2 -  Modificar precio por Kg                    |"
								"\n | 3 -  Salir                                      |"
								"\n * ----------------------------------------------- *"
								"\n > Eliga opcion: ",
								"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 1, opcion_salir, 2))
			{
				switch(opcion)
				{
					case 1: // Modificar constante Volumetrica
						printf("\n - MODIFICACION DE LA CONSTANTE VOLUMETRICA -");
						if(!utn_getNumeroFloat(&buffer.constanteVolumetrica, "\n > Ingrese constante Volumetrica: ", "\x1b[31m * ERROR \x1b[0m", 0.1, 9999, 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!transporteAereo_setConstanteVolumetrica(pTransporteAereo, buffer.constanteVolumetrica))
								flagModificado = 1;
						}
					break;
					case 2: // Modificar precio por Kg
						printf("\n - MODIFICACION DEL PRECIO POR KG -");
						if(!utn_getNumeroFloat(&buffer.precioPorKg, "\n > Ingrese precio por Kg: USS", "\x1b[31m * ERROR \x1b[0m", 0.1, 9999, 2) &&
						   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
						{
							if(!transporteAereo_setPrecioPorKg(pTransporteAereo, buffer.precioPorKg))
								flagModificado = 1;
						}
					break;
				}
			}
			controller_guardarTransporteAereo("transporteAereo.csv", pTransporteAereo);
		}while(opcion != opcion_salir);

		if(flagModificado == 1 &&
		  !transporteAereo_imprimirTransporteAereo(pTransporteAereo)) // Se modificó el articulo, entonces lo retorno para imprimirlo modificado.
		{
			printf("\n > Modificacion con éxito");
			retorno = 0;
		}
	}
	return retorno;
}
//********************************************************************************************* VERIFICACIONES
/** \brief Verifica si el id ingresado de la Posicion Arancelaria
                             corresponde a alguna con el id de alguna Posicion Arancelaria.
                             (Sirve para cuando das de alta un Articulo y debe escoger la Posicion Arancelaria
                              mediante el ingreso de su ID)

 * \param posicionesArancelarias Dictionary*
 * \param idPosicionArancelaria int: ID ingresado de posicion arancelaria
 * \return int 0 si NO EXISTE,
 *                             1 si EXISTE
 */
static int verificarIdPosicionArancelaria(Dictionary* posicionesArancelarias, int idPosicionArancelaria)
{
	int retorno = 0;
	char idAux[ID_STR];
	void* pElement;
	if(posicionesArancelarias != NULL && idPosicionArancelaria >= 0)
	{
		// convierto id posicion arancelaria en cadena
		snprintf(idAux, sizeof(idAux), "%d", idPosicionArancelaria);
		// verifico si ese id existe
		pElement = dict_get(posicionesArancelarias, idAux);
		if(pElement != NULL)
		{
			retorno = 1; // existe
		}
		else
		{
			printf("\n > El ID de la Posicion Arancelaria no existe");
		}
	}
	return retorno;
}
/** \brief Verifica si existee id posicion arancelaria en articulo
 * \param Dictionary* articulos
 * \return int 0 si no existe, 1 si existe
 */
static int existeIdPosicionArancelariaEnArticulo(Dictionary* articulos, int idPosicionArancelaria)
{
	int lenArticulos, i;
	LinkedList* listaArticulos;
	Articulo* pArticulo;
	int flagExisteEnArticulo = 0;
	int idPosAranArticulo,flagError;

	listaArticulos = dict_getValues(articulos);
	if(listaArticulos != NULL && articulos != NULL)
	{
		lenArticulos = ll_len(listaArticulos);
		for(i=0; i<lenArticulos; i++)
		{
			pArticulo = (Articulo*) ll_get(listaArticulos, i);
			idPosAranArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagError);
			//------------------------------------------------------------
			if(pArticulo != NULL && !flagError &&
			   idPosicionArancelaria == idPosAranArticulo)
			{
				flagExisteEnArticulo = 1;
				break;
			}
		}
	}
	return flagExisteEnArticulo;
}

