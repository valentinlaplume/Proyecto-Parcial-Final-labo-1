
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dictionary.h"
#include "Articulo.h"
#include "PosicionArancelaria.h"
#include "Parser.h"
#include "utn.h"

/** \brief Parsea los datos los datos de los Articulos desde el archivo articulos.csv (modo texto).
 *
 * \param pFile FILE*
 * \param pArrayListArticulo LinkedList*
 * \return int
 *
 */
int parser_articuloFromText(FILE* pFile, Dictionary* articulos, int* pIdMaxEncontrado)
{
	char idArticuloStr[STR_LEN];
	char idPosicionArancelariaStr[STR_LEN];
	char nombre[STR_LEN];
	char codigo[STR_LEN];
	char descripcion[STR_LEN];
	char paisDeFabricacion[STR_LEN];
	char pesoStr[STR_LEN];
	char fobStr[STR_LEN];
	char alturaStr[STR_LEN];
	char anchoStr[STR_LEN];
	char profundidadStr[STR_LEN];
	//-----------------------------------
	int idArticulo;
	int idPosicionArancelaria;
	float peso;
	float fob;
	float altura;
	float ancho;
	float profundidad;
    //------------------------------------
	Articulo* pArticulo;
	int flagOnce = 0;
	int cantidadCargados = -1;
	int idMax;

	if(pFile != NULL && articulos != NULL && pIdMaxEncontrado != NULL)
	{
		cantidadCargados = 0;
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
					                          idArticuloStr, idPosicionArancelariaStr,
					                          nombre, codigo, descripcion, paisDeFabricacion,
											  fobStr, pesoStr, anchoStr, alturaStr, profundidadStr) == 11)
			{
				if(flagOnce != 0)
				{
					if(esNumerica(idArticuloStr, 10) && esNumerica(idPosicionArancelariaStr, 10) &&
					   esFlotante(pesoStr, 10) && esFlotante(alturaStr, 10) &&
					   esFlotante(anchoStr, 10) && esFlotante(profundidadStr, 10))
					{
						idArticulo = atoi(idArticuloStr);
						idPosicionArancelaria = atoi(idPosicionArancelariaStr);
						fob = atof(fobStr);
						peso = atof(pesoStr);
						ancho = atof(anchoStr);
						altura = atof(alturaStr);
						profundidad = atof(profundidadStr);

						pArticulo = articulo_newParam(idArticulo, idPosicionArancelaria,
								                      nombre, codigo, descripcion, paisDeFabricacion,
								                      fob, peso, ancho, altura, profundidad);

						// Guardo en diccionario el articulo construido
						if(pArticulo != NULL) // La clave(key) es el ID : de TIPO cadena
							dict_insert(articulos, idArticuloStr, pArticulo);

						// busco id maximo
						if(cantidadCargados == 0)
							idMax = idArticulo; // me guardo el 1ero como MAX
						else
						{
							if(idArticulo > idMax)
								idMax = idArticulo;
						}
						cantidadCargados++;
					}
				}
			}
			flagOnce = 1;
		}
		while(!feof(pFile));
		*pIdMaxEncontrado = idMax; // lo escribo en la var externa
	}
	return cantidadCargados; // devuelve cantidad leidos
}

/** \brief Parsea los datos los datos de las Posiciones Arancelarias desde el archivo posicionesArancelarias.csv (modo texto).
 *
 * \param pFile FILE*
 * \param pArrayListArticulo LinkedList*
 * \return int
 *
 */
int parser_posicionesArancelariasFromText(FILE* pFile, Dictionary* posicionesArancelarias, int* pIdMaxEncontrado)
{
	char idPosicionArancelariaStr[STR_LEN];
	char nomenclador[STR_LEN];
	char porcentajeSeguroStr[STR_LEN];
	char porcentajeImportacionStr[STR_LEN];
	char porcentajeTasaEstadisticaStr[STR_LEN];
	char tipoLicenciaStr[STR_LEN];
	//-----------------------------------
	int idPosicionArancelaria;
	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEstadistica;
	int tipoLicencia;
    //------------------------------------
    PosicionArancelaria* pPosicionArancelaria;
	int flagOnce = 0;
	int cantidadCargados = -1;
	int idMax;

	if(pFile != NULL && posicionesArancelarias != NULL && pIdMaxEncontrado != NULL)
	{
		cantidadCargados = 0;
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idPosicionArancelariaStr,
					                                                  nomenclador, porcentajeSeguroStr, porcentajeImportacionStr,
																	  porcentajeTasaEstadisticaStr, tipoLicenciaStr) == 6)
			{
				if(flagOnce != 0)
				{
					if(esNumerica(idPosicionArancelariaStr, 10) && esFlotante(porcentajeSeguroStr, 10) &&
					   esFlotante(porcentajeImportacionStr, 10) && esFlotante(porcentajeTasaEstadisticaStr, 10) &&
					   esNumerica(tipoLicenciaStr, 10))
					{
						idPosicionArancelaria = atoi(idPosicionArancelariaStr);
						porcentajeSeguro = atof(porcentajeSeguroStr);
						porcentajeImportacion = atof(porcentajeImportacionStr);
						porcentajeTasaEstadistica = atof(porcentajeTasaEstadisticaStr);
						tipoLicencia = atoi(tipoLicenciaStr);

						pPosicionArancelaria = posicionArancelaria_newParam(idPosicionArancelaria, nomenclador, porcentajeSeguro,
								                                            porcentajeImportacion, porcentajeTasaEstadistica, tipoLicencia);

						// Guardo en diccionario el articulo construido
						if(pPosicionArancelaria != NULL) // La clave(key) es el ID : de TIPO cadena
							dict_insert(posicionesArancelarias, idPosicionArancelariaStr, pPosicionArancelaria);

						// busco id maximo
						if(cantidadCargados == 0)
							idMax = idPosicionArancelaria; // me guardo el 1ero como MAX
						else
						{
							if(idPosicionArancelaria > idMax)
								idMax = idPosicionArancelaria;
						}
						cantidadCargados++;
					}
				}
			}
			flagOnce = 1;
		}
		while(!feof(pFile));
		*pIdMaxEncontrado = idMax; // lo escribo en la var externa
	}
	return cantidadCargados; // devuelve cantidad leidos
}


