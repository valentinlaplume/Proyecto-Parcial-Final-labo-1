#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dictionary.h"
#include "LinkedList.h"

#include "Serializer.h"
#include "Articulo.h"
#include "Controller.h"
#include "TransporteMaritimo.h"
#include "TransporteAereo.h"

#include "eGeneral.h"

/** \brief Escribe los datos de los articulos al archivo articulos.csv (modo texto).
 * \param pFile FILE*
 * \param articulos Dictionary*
 * \return int
 */
int serializer_articulosFromText(FILE* pFile, Dictionary* articulos)
{
	int retorno = -1;
	//------------------------------------
	int idArticulo;
	int idPosicionArancelaria;
	char* nombre;
	char* codigo;
	char* descripcion;
	char* paisDeFabricacion;
	float peso;
	float fob;
	float altura;
	float ancho;
	float profundidad;
	//------------------------------------
	int flagErrorA, flagErrorB, flagErrorC, flagErrorD, flagErrorE, flagErrorF, flagErrorG,
	    flagErrorH, flagErrorI, flagErrorJ, flagErrorK;

	int i,lenListaArticulos;
	int flagGuarde = 0;
	LinkedList* listaArticulos;
	Articulo* pArticulo;

	if(pFile != NULL && articulos != NULL)
	{
		listaArticulos = dict_getValues(articulos); // Obtengo articulos del diccionario
		if(listaArticulos != NULL)
		{
			fprintf(pFile,"idArticulo,idPosicionArancelaria,nombre,codigo,descripcion,paisDeFabricacion,fob,peso,ancho,altura,profundidad\n");
			lenListaArticulos = ll_len(listaArticulos);
			for(i=0; i<lenListaArticulos; i++)
			{
				pArticulo = (Articulo*) ll_get(listaArticulos, i);

				// obtengo cada campo
				idArticulo = articulo_getIdArticulo(pArticulo, &flagErrorA);
				idPosicionArancelaria = articulo_getIdPosicionArancelaria(pArticulo, &flagErrorB);

				nombre = articulo_getNombre(pArticulo, &flagErrorC);
				codigo = articulo_getCodigo(pArticulo, &flagErrorD);
				descripcion = articulo_getDescripcion(pArticulo, &flagErrorE);
				paisDeFabricacion = articulo_getPaisDeFabricacion(pArticulo, &flagErrorF);

				fob = articulo_getFob(pArticulo, &flagErrorG);
				peso = articulo_getPeso(pArticulo, &flagErrorH);
				ancho = articulo_getAncho(pArticulo, &flagErrorI);
				altura = articulo_getAltura(pArticulo, &flagErrorJ);
				profundidad = articulo_getProfundidad(pArticulo, &flagErrorK);

				// Escribo cada articulo en una linea del archivo
				if(!flagErrorA && !flagErrorB && !flagErrorC && !flagErrorD && !flagErrorE && !flagErrorF &&
				   !flagErrorG && !flagErrorH && !flagErrorI && !flagErrorJ && !flagErrorK)
				{
					fprintf(pFile,"%d,%d,%s,%s,%s,%s,%.3f,%.3f,%.3f,%.3f,%.3f\n",idArticulo,idPosicionArancelaria,
																	             nombre,codigo,descripcion,paisDeFabricacion,
																	             fob,peso,ancho,altura,profundidad);
					flagGuarde = 1;
				}
			}
			if(flagGuarde == 1 && !ll_deleteLinkedList(listaArticulos))
				retorno = 0;
		}
	}
	return retorno;
}
/** \brief Escribe los datos de los articulos al archivo articulos.csv (modo texto).
 * \param pFile FILE*
 * \param articulos Dictionary*
 * \return int
 */
int serializer_eGeneralFromText(FILE* pFile, Dictionary* articulos, Dictionary* posicionesArancelarias,
		                        TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	int idArticuloGeneral;
	//----------------------------------- Variables Articulo
	int idPosicionArancelariaArticulo;
	LinkedList* listaArticulos;
	Articulo* pArticulo;
	float peso;
	float fob;
	float altura;
	float ancho;
	float profundidad;
	//------------------------------------------ Variables Posicion Arancelaria
	LinkedList* listaPosicionArancelaria;
	PosicionArancelaria* pPosicionArancelaria;
	int idPosicionArancelaria;
	float porcentajeSeguro, porcentajeImportacion, porcentajeTasaEstadistica;
	//------------------------------------ Variables Transporte Aereo
	float constanteVolumetrica;
	float precioPorKg;
	//------------------------------------ Variables Transporte Maritimo
	float metrosCubicos;
	float precioContenedor;
	//------------------------------------
	int flagErrorA, flagErrorB, flagErrorC, flagErrorD, flagErrorE, flagErrorF, flagErrorG,
	    flagErrorH, flagErrorI, flagErrorJ, flagErrorK,
		flagErrorL, flagErrorM, flagErrorN, flagErrorO;

	int i, k, lenListaArticulos, lenListaPosicionArancelaria;
	int flagGuarde = 0;

	int contadorCargados = 0;

	if(pFile != NULL && articulos != NULL && posicionesArancelarias != NULL && pTransporteAereo != NULL && pTransporteMaritimo != NULL)
	{
		listaArticulos = dict_getValues(articulos); // Obtengo articulos del diccionario
		listaPosicionArancelaria = dict_getValues(posicionesArancelarias); // Obtengo pos aran del diccionario
		if(listaArticulos != NULL)
		{
			fprintf(pFile,  "idArticuloGeneral,fob,peso,ancho,altura,profundidad," // articulo
							"porcentajeSeguro,porcentajeImportacion,porcentajeTasaEstadistica," // pos aran
							"constanteVolumetrica,precioPorKg," // trans aereo
							"metrosCubicos,precioContenedor\n"); // trans maritimo
			lenListaArticulos = ll_len(listaArticulos);
			lenListaPosicionArancelaria = ll_len(listaPosicionArancelaria);


			// obtengo datos de transporte Aereo
			constanteVolumetrica = transporteAereo_getConstanteVolumetrica(pTransporteAereo, &flagErrorL);
			precioPorKg = transporteAereo_getPrecioPorKg(pTransporteAereo, &flagErrorM);
			// obtengo datos de transporte Maritimo
			metrosCubicos = transporteMaritimo_getMetrosCubicos(pTransporteMaritimo, &flagErrorN);
			precioContenedor = transporteMaritimo_getPrecioContenedor(pTransporteMaritimo, &flagErrorO);
			for(i=0; i<lenListaArticulos; i++)
			{
				pArticulo = (Articulo*) ll_get(listaArticulos, i);

				// Obtengo el Id que vincula a la Posicion Arancelaria para asi compararlo
				idPosicionArancelariaArticulo = articulo_getIdPosicionArancelaria(pArticulo, &flagErrorK);

				for(k=0; k<lenListaPosicionArancelaria; k++)
				{
					pPosicionArancelaria = (PosicionArancelaria*) ll_get(listaPosicionArancelaria, k);
					// Obtengo su Id
					idPosicionArancelaria = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagErrorG);

					// Si los Ids son iguales entonces que cargue sus datos al ARCHIVO
					if(idPosicionArancelaria == idPosicionArancelariaArticulo)
					{
						// Obtengo Id Articulo que va a ser usado como [ ID de eGeneral ]
						idArticuloGeneral = articulo_getIdArticulo(pArticulo, &flagErrorA);

						// obtengo cada campo Articulo
						fob = articulo_getFob(pArticulo, &flagErrorB);
						peso = articulo_getPeso(pArticulo, &flagErrorC);
						ancho = articulo_getAncho(pArticulo, &flagErrorD);
						altura = articulo_getAltura(pArticulo, &flagErrorE);
						profundidad = articulo_getProfundidad(pArticulo, &flagErrorF);

						// obtengo campos Posicion Arancelaria
						porcentajeSeguro = posicionArancelaria_getPorcentajeSeguro(pPosicionArancelaria, &flagErrorH);
						porcentajeImportacion = posicionArancelaria_getPorcentajeImportacion(pPosicionArancelaria, &flagErrorI);
						porcentajeTasaEstadistica = posicionArancelaria_getPorcentajeTasaEstadistica(pPosicionArancelaria, &flagErrorJ);

						// Escribo cada articulo en una linea del archivo
						if(!flagErrorA && !flagErrorB && !flagErrorC && !flagErrorD && !flagErrorE && !flagErrorF &&
						   !flagErrorG && !flagErrorH && !flagErrorI && !flagErrorJ && !flagErrorK &&
						   !flagErrorL && !flagErrorM && !flagErrorN && !flagErrorO)
						{
							fprintf(pFile,"%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",idArticuloGeneral,
																						 fob,peso,ancho,altura,profundidad,
														  porcentajeSeguro,porcentajeImportacion,porcentajeTasaEstadistica,
														  constanteVolumetrica, precioPorKg,
														  metrosCubicos,precioContenedor);
							flagGuarde = 1;
							contadorCargados++;
						}
					}
				}
			}
			if(flagGuarde == 1 && !ll_deleteLinkedList(listaArticulos) && !ll_deleteLinkedList(listaPosicionArancelaria))
			{
				printf("\n eGeneral: guardados en el archivo la cantidad de: %d", contadorCargados);
				retorno = 0;
			}
		}
	}
	return retorno;
}

/** \brief Escribe los datos de las Posiciones Arancelarias al archivo posicionesArancelarias.csv (modo texto).
 * \param pFile FILE*
 * \param articulos Dictionary*
 * \return int
 */
int serializer_posicionesArancelariasFromText(FILE* pFile, Dictionary* posicionesArancelarias)
{
	int retorno = -1;
	//------------------------------------
	int idPosicionArancelaria;
	char* nomenclador;
	float porcentajeSeguro, porcentajeImportacion, porcentajeTasaEstadistica;
	int tipoLicencia;
	//------------------------------------
	int flagErrorA, flagErrorB, flagErrorC, flagErrorD, flagErrorE, flagErrorF;

	int i,lenListaPosArancelaria;
	int flagGuarde = 0;
	LinkedList* listaPosicionArancelaria;
	PosicionArancelaria* pPosicionArancelaria;

	if(pFile != NULL && posicionesArancelarias != NULL)
	{
		listaPosicionArancelaria = dict_getValues(posicionesArancelarias); // Obtengo pos aran del diccionario
		if(listaPosicionArancelaria != NULL)
		{
			fprintf(pFile,"idPosicionArancelaria,nomenclador,porcentajeSeguro,porcentajeImportacion,porcentajeTasaEstadistica,tipoLicencia\n");
			lenListaPosArancelaria = ll_len(listaPosicionArancelaria);
			for(i=0; i<lenListaPosArancelaria; i++)
			{
				pPosicionArancelaria = (PosicionArancelaria*) ll_get(listaPosicionArancelaria, i);
				//---------------------------- OBTENGO CAMPOS -------------------------------------------------------------
				idPosicionArancelaria = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagErrorA);
				nomenclador = posicionArancelaria_getNomenclador(pPosicionArancelaria, &flagErrorB);
				porcentajeSeguro = posicionArancelaria_getPorcentajeSeguro(pPosicionArancelaria, &flagErrorC);
				porcentajeImportacion = posicionArancelaria_getPorcentajeImportacion(pPosicionArancelaria, &flagErrorD);
				porcentajeTasaEstadistica = posicionArancelaria_getPorcentajeTasaEstadistica(pPosicionArancelaria, &flagErrorE);
				tipoLicencia = posicionArancelaria_getTipoLicencia(pPosicionArancelaria, &flagErrorF);
				//---------------------------- OBTENGO CAMPOS -------------------------------------------------------------
				if(!flagErrorA && !flagErrorB && !flagErrorC && !flagErrorD && !flagErrorE && !flagErrorF)
				{
					fprintf(pFile,"%d,%s,%.2f,%.2f,%.2f,%d\n",idPosicionArancelaria, nomenclador, porcentajeSeguro,
										                porcentajeImportacion, porcentajeTasaEstadistica, tipoLicencia);
					flagGuarde = 1;
				}
			}
			if(flagGuarde == 1 && !ll_deleteLinkedList(listaPosicionArancelaria))
				retorno = 0;
		}
	}
	return retorno;
}

/** \brief Escribe los datos del TransporteMaritimo al archivo transporteMaritimo.csv (modo texto).
 * \param pFile FILE*
 * \param pTransporteMaritimo TransporteMaritimo*
 * \return int
 */
int serializer_transporteMaritimoFromText(FILE* pFile, TransporteMaritimo* pTransporteMaritimo)
{
	int retorno = -1;
	//------------------------------------
	float metrosCubicos;
	float precioContenedor;
	int flagErrorA, flagErrorB;

	if(pFile != NULL && pTransporteMaritimo != NULL)
	{
		fprintf(pFile,"metrosCubicos,precioContenedor\n");
		//---------------------------- OBTENGO CAMPOS -------------------------------------------------------------
		metrosCubicos = transporteMaritimo_getMetrosCubicos(pTransporteMaritimo, &flagErrorA);
		precioContenedor = transporteMaritimo_getPrecioContenedor(pTransporteMaritimo, &flagErrorB);
		if(!flagErrorA && !flagErrorB)
		{
			fprintf(pFile,"%.2f,%.2f\n",metrosCubicos, precioContenedor);
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Escribe los datos del Transporte Aereo al archivo transporteAereo.csv (modo texto).
 * \param pFile FILE*
 * \param pTransporteMaritimo TransporteMaritimo*
 * \return int
 */
int serializer_transporteAereoFromText(FILE* pFile, TransporteAereo* pTransporteAereo)
{
	int retorno = -1;
	//------------------------------------
	float constanteVolumetrica;
	float precioPorKg;
	int flagErrorA, flagErrorB;

	if(pFile != NULL && pTransporteAereo != NULL)
	{
		fprintf(pFile,"constanteVolumetrica,precioPorKg\n");
		//---------------------------- OBTENGO CAMPOS -------------------------------------------------------------
		constanteVolumetrica = transporteAereo_getConstanteVolumetrica(pTransporteAereo, &flagErrorA);
		precioPorKg = transporteAereo_getPrecioPorKg(pTransporteAereo, &flagErrorB);
		if(!flagErrorA && !flagErrorB)
		{
			fprintf(pFile,"%.2f,%.2f\n",constanteVolumetrica, precioPorKg);
			retorno = 0;
		}
	}
	return retorno;
}
