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
		listaPosicionArancelaria = dict_getValues(posicionesArancelarias); // Obtengo articulos del diccionario
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
