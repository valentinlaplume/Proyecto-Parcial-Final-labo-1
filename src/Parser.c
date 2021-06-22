
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dictionary.h"
#include "Articulo.h"
#include "PosicionArancelaria.h"
#include "Parser.h"
#include "utn.h"

#include "TransporteMaritimo.h"
#include "TransporteAereo.h"

#include "eGeneral.h"

/** \brief Parsea los datos los datos de los Articulos desde el archivo articulos.csv (modo texto).
 * \param pFile FILE*
 * \param articulos Dictionary*
 * \return int
 *
 */
int parser_articulosFromText(FILE* pFile, Dictionary* articulos, int* pIdMaxEncontrado)
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
					if(esNumerica(idArticuloStr, ID_STR) && esNumerica(idPosicionArancelariaStr, ID_STR) &&
					   esFlotante(fobStr, 10) && esFlotante(pesoStr, 10) && esFlotante(alturaStr, 10) &&
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
						if(pArticulo != NULL &&
						  !dict_insert(articulos, idArticuloStr, pArticulo)) // La clave(key) es el ID : de TIPO cadena
						{
							// busco id maximo
							if(cantidadCargados == 0 || idArticulo > idMax)
								idMax = idArticulo; // me guardo el 1ero como MAX

							cantidadCargados++;
						}
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
/** \brief Parsea los datos los datos de los Datos Generales desde el archivo datosGenerales.csv (modo texto).
 * \param pFile FILE*
 * \param datosGenerales Dictionary*
 * \return int
 *
 */
int parser_eGeneralFromText(FILE* pFile, Dictionary* datosGenerales)
{
	char idArticuloGeneralStr[STR_LEN];
	char pesoStr[STR_LEN];
	char fobStr[STR_LEN];
	char alturaStr[STR_LEN];
	char anchoStr[STR_LEN];
	char profundidadStr[STR_LEN];
	//-------------
	int idArticuloGeneral;
	float peso;
	float fob;
	float altura;
	float ancho;
	float profundidad;
    //------------------------------------
	char porcentajeSeguroStr[STR_LEN];
	char porcentajeImportacionStr[STR_LEN];
	char porcentajeTasaEstadisticaStr[STR_LEN];
	//-------------
	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEstadistica;
	//------------------------------------
	eGeneral* pGeneral;
	int flagOnce = 0;
	int cantidadCargados = -1;

	if(pFile != NULL && datosGenerales != NULL)
	{
		cantidadCargados = 0;
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
					                          idArticuloGeneralStr,
			                          fobStr, pesoStr, anchoStr, alturaStr, profundidadStr,
		                              porcentajeSeguroStr, porcentajeImportacionStr,porcentajeTasaEstadisticaStr) == 9)
			{
				if(flagOnce != 0)
				{
					if(esNumerica(idArticuloGeneralStr, ID_STR) &&
					   esFlotante(fobStr, 10) && esFlotante(pesoStr, 10) && esFlotante(alturaStr, 10) &&
					   esFlotante(anchoStr, 10) && esFlotante(profundidadStr, 10) &&
					   esFlotante(porcentajeSeguroStr, 10) && esFlotante(porcentajeImportacionStr, 10) && esFlotante(porcentajeTasaEstadisticaStr, 10))
					{
						// Convierto los datos de Articulo
						idArticuloGeneral = atoi(idArticuloGeneralStr);
						fob = atof(fobStr);
						peso = atof(pesoStr);
						ancho = atof(anchoStr);
						altura = atof(alturaStr);
						profundidad = atof(profundidadStr);

						// Convierto los datos de Posicion Arancelaria
						porcentajeSeguro = atof(porcentajeSeguroStr);
						porcentajeImportacion = atof(porcentajeImportacionStr);
						porcentajeTasaEstadistica = atof(porcentajeTasaEstadisticaStr);

						pGeneral = eGeneral_newParam(idArticuloGeneral, fob, peso, ancho, altura, profundidad,
								                     porcentajeSeguro, porcentajeImportacion, porcentajeTasaEstadistica);

						// Guardo en diccionario el articulo construido
						if(pGeneral != NULL &&
						  !dict_insert(datosGenerales, idArticuloGeneralStr, pGeneral)) // La clave(key) es el ID : de TIPO cadena
						{
							cantidadCargados++;
						}
					}
				}
			}
			flagOnce = 1;
		}
		while(!feof(pFile));
	}
	return cantidadCargados; // devuelve cantidad leidos
}
//---------------------------------------------------------------------------------------------------------------
/** \brief Parsea los datos los datos de las Posiciones Arancelarias desde el archivo posicionesArancelarias.csv (modo texto).
 * \param pFile FILE*
 * \param posicionesArancelarias Dictionary*
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
					if(esNumerica(idPosicionArancelariaStr, ID_STR) && esFlotante(porcentajeSeguroStr, 10) &&
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
						{
							dict_insert(posicionesArancelarias, idPosicionArancelariaStr, pPosicionArancelaria);
							// busco id maximo
							if(cantidadCargados == 0 || idPosicionArancelaria > idMax)
								idMax = idPosicionArancelaria; // me guardo el 1ero como MAX

							cantidadCargados++;
						}
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

/** \brief Parsea .
 * \param pFile FILE*
 * \param pTransporteMaritimo TransporteMaritimo*
 * \return int
 */
int parser_transporteMaritimoFromText(FILE* pFile, TransporteMaritimo* pTransporteMaritimo)
{
	char metrosCubicosStr[STR_LEN];
	char precioContenedorStr[STR_LEN];
	//-----------------------------------
	float metrosCubicos;
	float precioContenedor;
    //------------------------------------
	int flagOnce = 0;
	int cantidadCargados = -1;

	if(pFile != NULL && pTransporteMaritimo)
	{
		cantidadCargados = 0;
		do
		{
			if(fscanf(pFile,"%[^,],%[^\n]\n", metrosCubicosStr,precioContenedorStr) == 2)
			{
				if(flagOnce != 0)
				{
					if(esFlotante(metrosCubicosStr, 10) && esFlotante(precioContenedorStr, 10))
					{
						metrosCubicos = atof(metrosCubicosStr);
						precioContenedor = atof(precioContenedorStr);

						transporteMaritimo_newParam(pTransporteMaritimo, metrosCubicos, precioContenedor);

						if(pTransporteMaritimo != NULL)
							cantidadCargados++;
					}
				}
			}
			flagOnce = 1;
		}
		while(!feof(pFile));
	}
	return cantidadCargados; // devuelve cantidad leidos
}

/** \brief Parsea .
 * \param pFile FILE*
 * \param pTransporteAereo TransporteAereo*
 * \return int
 */
int parser_transporteAereoFromText(FILE* pFile, TransporteAereo* pTransporteAereo)
{
	char constanteVolumetricaStr[STR_LEN];
	char precioPorKgStr[STR_LEN];
	//-----------------------------------
	float constanteVolumetrica;
	float precioPorKg;
    //------------------------------------
	int flagOnce = 0;
	int cantidadCargados = -1;

	if(pFile != NULL && pTransporteAereo)
	{
		cantidadCargados = 0;
		do
		{
			if(fscanf(pFile,"%[^,],%[^\n]\n", constanteVolumetricaStr, precioPorKgStr) == 2)
			{
				if(flagOnce != 0)
				{
					if(esFlotante(constanteVolumetricaStr, 10) && esFlotante(precioPorKgStr, 10))
					{
						constanteVolumetrica = atof(constanteVolumetricaStr);
						precioPorKg = atof(precioPorKgStr);

						transporteAereo_newParam(pTransporteAereo, constanteVolumetrica, precioPorKg);

						if(pTransporteAereo != NULL)
							cantidadCargados++;
					}
				}
			}
			flagOnce = 1;
		}
		while(!feof(pFile));
	}
	return cantidadCargados; // devuelve cantidad leidos
}


