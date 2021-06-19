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
#include "Informe.h"

// Flags estaticos
static int flagCargueArticulo = 0;
static int flagCarguePosicionArancelaria = 0;

// Contadores estaticos
static int staticIdArticulo = 0;
static int staticIdPosicionArancelaria = 0;

// Funciones estáticas
static int verificarIdPosicionArancelaria(Dictionary* posicionesArancelarias, int idPosicionArancelaria);
static int existeIdPosicionArancelariaEnArticulo(Dictionary* articulos, int idPosicionArancelaria);
static Articulo* subMenuEditArticulo(void* pElement, Dictionary* posicionesArancelarias);
//static PosicionArancelaria* buscarPorPosicionArancelariaPorId(LinkedList* listaPosicionArancelaria,int idABuscar);
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
			cantidadCargados = parser_articuloFromText(pFile, articulos, &idMaxEncontrado);
			if(cantidadCargados > 0)
			{
				controller_setearValorInicialDeIdArticulo(idMaxEncontrado);
				flagCargueArticulo = 1;
				retorno = 0;
			}
		}
		printf("\n - Leiste del archivo %s [ %d articulos]",path,cantidadCargados);
	}
	return retorno;
}

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
		}
		printf("\n\n - Leiste del archivo %s [ %d Posiciones Arancelarias]\n",path,cantidadCargados);
	}
	return retorno;
}
//------------------------------------------------------------------------
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
				printf("\n - GUARDE ARTICULOS EN %s",path);
			}
			fclose(pFile);
		}
	}
	return retorno;
}

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
				printf("\n - GUARDE POSICIONES ARANCELIAS EN %s",path);
			}
			fclose(pFile);
		}
	}
	return retorno;
}
//********************************************************************************************* LISTAR
int controller_imprimirArticulos(Dictionary* articulos)
{
	int retorno = -1;
	LinkedList* listaArticulos;
	if(articulos != NULL)
	{
		// Obtengo articulos del diccionario
		listaArticulos = dict_getValues(articulos);

		if(listaArticulos != NULL &&
		  !articulo_imprimirArticulos(listaArticulos) &&
		  !ll_deleteLinkedList(listaArticulos))
		{
			retorno = 0;
		}
	}
	return retorno;
}

int controller_imprimirPosicionesArancelarias(Dictionary* posicionesArancelarias)
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
			retorno = 0;
		}
	}
	return retorno;
}

//********************************************************************************************* ALTAS
int controller_altaArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	Articulo buffer;
	Articulo* pArticulo;
	char idArticuloSTR[10];

	if(articulos != NULL && posicionesArancelarias != NULL &&
	  !controller_imprimirPosicionesArancelarias(posicionesArancelarias) &&
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
}

// retorna Id dado de alta;
int controller_altaPosicionArancelaria(Dictionary* posicionesArancelarias)
{
	int IdRetorno = -1;
	PosicionArancelaria buffer;
	PosicionArancelaria* pPosicionArancelaria;
	char idPosicionArancelariaSTR[10];

	if(posicionesArancelarias != NULL && posicionesArancelarias != NULL &&
	  !informe_pedirDatosPosicionArancelaria(buffer.nomenclador, &buffer.porcentajeSeguro, &buffer.porcentajeImportacion, &buffer.porcentajeTasaEstadistica, &buffer.tipoLicencia))
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
			}
		}
	}
	return IdRetorno;
}
//********************************************************************************************* BAJAS
int controller_bajaArticulo(Dictionary* articulos)
{
	char idStr[10];
	int retorno = -1;
	Articulo* pArticulo;

	if(articulos != NULL && flagCargueArticulo == 1 && !controller_imprimirArticulos(articulos) &&
	  !utn_getTexto(idStr, sizeof(idStr), "\n\n > Ingrese Id del articulo dar de baja: ", "\n\x1b[31m * ERROR \x1b[0m", 2))
	{
		pArticulo = (Articulo*) dict_get(articulos, idStr);
		if(pArticulo != NULL && !articulo_delete(pArticulo))
		{
			if(!dict_remove(articulos, idStr))
			{
				printf("\n > Articulo dado de baja");
				retorno = 0;
			}
		}

	}
	return retorno;
}

int controller_bajaPosicionArancelaria(Dictionary* posicionesArancelarias, Dictionary* articulos)
{
	char idStr[10];
	int retorno = -1;
	int idPosAranAux, flagErrorA;
	int flagExisteEnArticulo = 0;
	PosicionArancelaria* pPosicionArancelaria;

	if(posicionesArancelarias != NULL && articulos != NULL && flagCarguePosicionArancelaria == 1 &&
	  !controller_imprimirPosicionesArancelarias(posicionesArancelarias) &&
	  !utn_getTexto(idStr, sizeof(idStr), "\n\n > Ingrese Id de la Posicion Arancelaria dar de baja: ", "\n\x1b[31m * ERROR \x1b[0m", 2))
	{
		pPosicionArancelaria = (PosicionArancelaria*) dict_get(posicionesArancelarias, idStr);
		if(pPosicionArancelaria != NULL)
		{
			//---------------------------------------------------------- VERIFICO SI ESA POS POSEE A UN ARTICULO
			idPosAranAux = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagErrorA);
			if(!flagErrorA)
				flagExisteEnArticulo = existeIdPosicionArancelariaEnArticulo(articulos, idPosAranAux);
			//----------------------------------------------------------
			if(flagExisteEnArticulo == 0 && !posicionArancelaria_delete(pPosicionArancelaria)&&
			  !dict_remove(posicionesArancelarias, idStr))
			{
				printf("\n > Posicion Arancelaria dada de baja");
				retorno = 0;
			}
		}
	}
	return retorno;
}

int controller_modificarArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias)
{
	char IdStr[10];
	int retorno = -1;
	void* pElemento;
	Articulo* pArticulo = NULL;

	if(articulos !=  NULL && posicionesArancelarias != NULL && flagCargueArticulo == 1 && !controller_imprimirArticulos(articulos) &&
	  !utn_getAlfanumerico(IdStr, sizeof(IdStr), "\n\n > Ingrese ID del articulo a modificar: ", "\n\x1b[31m * ERROR \x1b[0m", 2))
	{
		// Busco al pElement dandole su key (en este caso uso su id)
		pElemento = dict_get(articulos, IdStr);
		pArticulo = subMenuEditArticulo(pElemento, posicionesArancelarias);
		if(pArticulo != NULL)
		{
			articulo_imprimirUnArticulo(pArticulo);
			printf("\n\n > Modificacion con exito");
			retorno = 0;
		}
	}
	return retorno;
}

//****************************** SUB MENU MODIFICACION *****************************************

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
						if(!controller_imprimirPosicionesArancelarias(posicionesArancelarias) &&
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
						if(!utn_getAlfanumerico(buffer.codigo, CODIGO_LEN, " > Ingrese el codigo del articulo: ", "\n\x1b[31m * ERROR \x1b[0m", 2) &&
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
					if(!utn_getNumeroFloat(&buffer.fob, " > Ingrese valor fob del articulo: USS ", "\n\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
					   !laplume_confirmarAccion("\n > Desea confimar la modificacion?"))
					{
						if(!articulo_setFob(pArticulo, buffer.fob))
							flagModificado = 1;
					}
					break;
					case 6: // Modificar peso
					printf("\n - MODIFICACION DEL PESO -");
					if(!utn_getNumeroFloat(&buffer.peso, " > Ingrese peso [kg] del articulo: ", "\n\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
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



/*
static PosicionArancelaria* buscarPorPosicionArancelariaPorId(LinkedList* listaPosicionArancelaria,int idABuscar)
{
	PosicionArancelaria* pPosicionArancelaria;
	PosicionArancelaria* pRetorno = NULL;
	int i, lenLinkedList, idEncontrado, flagError;

	lenLinkedList = ll_len(listaPosicionArancelaria);
	if(listaPosicionArancelaria != NULL && idABuscar >= 0 && lenLinkedList > 0)
	{
		for(i=0; i<lenLinkedList; i++)
		{
			pPosicionArancelaria = (PosicionArancelaria*)ll_get(listaPosicionArancelaria, i);
			if(pPosicionArancelaria != NULL)
			{
				idEncontrado = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagError);
				if(!flagError &&
				   idABuscar == idEncontrado)
				{
					pRetorno = pPosicionArancelaria;
					break;
				}
			}
		}
	}
	return pRetorno;
}
*/
//********************************************************************************************* FUNCIONES ESTÁTICAS
static int verificarIdPosicionArancelaria(Dictionary* posicionesArancelarias, int idPosicionArancelaria)
{
	int retorno = 0;
	char idAux[10];
	void* pElement;
	if(posicionesArancelarias != NULL && idPosicionArancelaria >= 0)
	{
		// convierto id posicion arancelaria en cadena
		snprintf(idAux, sizeof(idAux), "%d", idPosicionArancelaria);
		// verifico si ese id existe
		pElement = dict_get(posicionesArancelarias, idAux);
		if(pElement != NULL)
		{
			retorno = 1;
		}
		else
		{
			printf("\n > El ID de la posicion arancelaria no existe");
		}
	}
	return retorno;
}

static int existeIdPosicionArancelariaEnArticulo(Dictionary* articulos, int idPosicionArancelaria)
{
	int lenArticulos, i;
	LinkedList* listaArticulos;
	Articulo* pArticulo;
	int flagExisteEnArticulo = 0;
	int idArticuloAux,flagError;

	listaArticulos = dict_getValues(articulos);
	if(listaArticulos != NULL && articulos != NULL)
	{
		lenArticulos = ll_len(listaArticulos);
		for(i=0; i<lenArticulos; i++)
		{
			pArticulo = (Articulo*) ll_get(listaArticulos, i);
			idArticuloAux = articulo_getIdArticulo(pArticulo, &flagError);
			if(pArticulo != NULL && !flagError &&
			   idPosicionArancelaria == idArticuloAux)
			{
				flagExisteEnArticulo = 1;
				printf("\n > La Posicion Arancelaria no puede ser dada de baja ya que posee a un articulo existente");
				break;
			}
		}
	}
	return flagExisteEnArticulo;
}
