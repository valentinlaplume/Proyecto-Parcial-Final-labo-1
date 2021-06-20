
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

#include "TransporteAereo.h"
#include "TransporteMaritimo.h"


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
		   !utn_getNumeroFloat(peso, " > Ingrese peso [kg] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
		   !utn_getNumeroFloat(ancho, "\n > DIMENSIONES:\n > Ingrese ancho[cm] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
		   !utn_getNumeroFloat(altura, " > Ingrese altura[cm] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2) &&
		   !utn_getNumeroFloat(profundidad, " > Ingrese profundidad[cm] del articulo: ", "\x1b[31m * ERROR \x1b[0m", 0, 99999, 2))
		{
			retorno = 0;
		}
	}
	return retorno;
}

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
					printf("\n");
				}
				// ------------------------------------
			}
		}
		// ---------------------------------------------------------------------
		retorno = 0;
	}
	return retorno;
}
// Listar Articulos y costo final por Transporte Maritimo
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
	// ---------------------------------------------------------------------
		for(i=0; i<lenArticulos; i++)
		{
			pArticulo = (Articulo*) ll_get(listaArticulos, i);
			// Imprimo Articulo
			articulo_imprimirUnArticulo(pArticulo);
		//-----------------------------------------
			for(k=0; k<lenPosicionArancelaria; k++)
			{
				pPosicionArancelaria = (PosicionArancelaria*) ll_get(listaPosicionArancelaria, k);
				if(pPosicionArancelaria->idPosicionArancelaria == pArticulo->idPosicionArancelaria)
				{
					resultadoTransporteMaritimo = transporteMaritimo_calcularCostoFinal(pArticulo, pPosicionArancelaria, pTransporteMaritimo);
					printf("\n > Costo final por Transporte Maritimo:  usd %f\n", resultadoTransporteMaritimo);
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}
//******************************************************************************** CALCULOS
//Proporcional Flete
float transporteMaritimo_obtenerVolumenCubico(Articulo* pArticulo) // 1)
{
	float retornoResultado = -1;
	float ancho, altura, profundidad;
	int flagErrorA, flagErrorB, flagErrorC;

	if(pArticulo != NULL)
	{
		ancho = articulo_getAncho(pArticulo, &flagErrorA);
		altura = articulo_getAltura(pArticulo, &flagErrorB);
		profundidad = articulo_getProfundidad(pArticulo, &flagErrorC);
		//----------------------------------------------------------------------------
		// (ancho / 100) *********** [ Paso de centimetros a metro]
		retornoResultado = ( (ancho / 100) * (altura / 100) * (profundidad / 100) );
	}
	return retornoResultado;
}

float transporteMaritimo_obtenerPrecioPorMetroCubico(TransporteMaritimo* pTransporteMaritimo) // 2)
{
	float retornoResultado = -1;
	int flagErrorA, flagErrorB;
	float metrosCubicos;
	float precioContenedor;

	if(pTransporteMaritimo != NULL)
	{
		metrosCubicos = transporteMaritimo_getMetrosCubicos(pTransporteMaritimo, &flagErrorA);
		precioContenedor = transporteMaritimo_getPrecioContenedor(pTransporteMaritimo, &flagErrorB);

		if(!flagErrorA && !flagErrorB)
			retornoResultado = (metrosCubicos / precioContenedor);
	}
	return retornoResultado;
}
// creo que es flete
float transporteMaritimo_calcularFlete(Articulo* pArticulo, TransporteMaritimo* pTransporteMaritimo) // 3)
{
	float retornoResultado = -1;
	float resultadoVolumenCubico;
	float resulPrecioPorMetroCubico;

	if(pArticulo != NULL && pTransporteMaritimo != NULL)
	{
		resultadoVolumenCubico = transporteMaritimo_obtenerVolumenCubico(pArticulo);
		resulPrecioPorMetroCubico = transporteMaritimo_obtenerPrecioPorMetroCubico(pTransporteMaritimo);

		retornoResultado = ( resultadoVolumenCubico * resulPrecioPorMetroCubico );
	}
	return retornoResultado;
}
//--------------------------------------------------------------------------
float transporteMaritimo_calcularCostoFinal(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
                                            TransporteMaritimo* pTransporteMaritimo)
{
	float retornoResultado = -1;
	float resulBaseImponible, resulImportacion, resultTasaEstadistica;
	if(pArticulo != NULL && pPosicionArancelaria != NULL && pTransporteMaritimo != NULL)
	{
		resulBaseImponible = transporteMaritimo_calcularBaseImponible(pArticulo, pPosicionArancelaria, pTransporteMaritimo);
		resulImportacion = transporteMaritimo_calcularPorcentajeImportacion(pArticulo, pPosicionArancelaria, pTransporteMaritimo);
		resultTasaEstadistica = transporteMaritimo_calcularPorcentajeeTasaEstadistica(pArticulo, pPosicionArancelaria, pTransporteMaritimo);
		if(resulBaseImponible > 0 && resulImportacion > 0 && resultTasaEstadistica > 0)
		{
			retornoResultado = (resulBaseImponible + resulImportacion + resultTasaEstadistica);
		}
	}
	return retornoResultado;
}

float transporteMaritimo_calcularPorcentajeeTasaEstadistica(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                                    TransporteMaritimo* pTransporteMaritimo)
{
	float retornoResultado = -1;
	float porcentajeTasaEstadistica, resulBaseImponible;
	int flagErrorA;
	if(pArticulo != NULL && pPosicionArancelaria != NULL && pTransporteMaritimo != NULL)
	{
		porcentajeTasaEstadistica = posicionArancelaria_getPorcentajeTasaEstadistica(pPosicionArancelaria, &flagErrorA);
		resulBaseImponible = transporteMaritimo_calcularBaseImponible(pArticulo, pPosicionArancelaria, pTransporteMaritimo);
		if(!flagErrorA && resulBaseImponible > 0)
		{
			retornoResultado = ((porcentajeTasaEstadistica * resulBaseImponible) / 100);
		}
	}
	return retornoResultado;
}

float transporteMaritimo_calcularPorcentajeImportacion(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                               TransporteMaritimo* pTransporteMaritimo)
{
	float retornoResultado = -1;
	float porcentajeImportacion, resulBaseImponible;
	int flagErrorA;
	if(pArticulo != NULL && pPosicionArancelaria != NULL && pTransporteMaritimo != NULL)
	{
		porcentajeImportacion = posicionArancelaria_getPorcentajeImportacion(pPosicionArancelaria, &flagErrorA);
		resulBaseImponible = transporteMaritimo_calcularBaseImponible(pArticulo, pPosicionArancelaria, pTransporteMaritimo);
		if(!flagErrorA && resulBaseImponible > 0)
		{
			retornoResultado = ((porcentajeImportacion * resulBaseImponible) / 100);
		}
	}
	return retornoResultado;
}


float transporteMaritimo_calcularBaseImponible(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
											   TransporteMaritimo* pTransporteMaritimo)
{
	float retornoResultado = -1;
	float resultadoFlete, resulPorcentajeSeguro;
	float fob;
	int flagErrorA;
	if(pArticulo != NULL && pPosicionArancelaria != NULL && pTransporteMaritimo != NULL)
	{
		// Calculo proporcional Maritimo
		resultadoFlete = transporteMaritimo_calcularFlete(pArticulo, pTransporteMaritimo);
		// Calculo Porcentaje del Seguro
		resulPorcentajeSeguro = transporteMaritimo_calcularPorcentajeSeguro(pArticulo, pPosicionArancelaria);

		fob = articulo_getFob(pArticulo, &flagErrorA); // Obtengo valor fob
		if(!flagErrorA)
			retornoResultado = (fob + resulPorcentajeSeguro + resultadoFlete);
	}
	return retornoResultado;
}

float transporteMaritimo_calcularPorcentajeSeguro(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria)
{
	float retornoResultado = -1;
	float porcentajeSeguro, fob;
	int flagErrorA, flagErrorB;
	if(pArticulo != NULL && pPosicionArancelaria != NULL)
	{
		porcentajeSeguro = posicionArancelaria_getPorcentajeSeguro(pPosicionArancelaria, &flagErrorB);
		fob = articulo_getFob(pArticulo, &flagErrorA);
		if(!flagErrorA && !flagErrorB)
		{
			retornoResultado = ((porcentajeSeguro * fob) / 100);
		}
	}
	return retornoResultado;
}








