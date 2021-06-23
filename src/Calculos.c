#include "utn.h"
#include "laplume.h"
#include "Articulo.h"
#include "PosicionArancelaria.h"
#include "TransporteAereo.h"
#include "TransporteMaritimo.h"
#include "Calculos.h"

//******************************************************************************************** CALCULOS
//  TRANSPORTE AEREO
//  Costo final - Base imponible - Porcentajes

/** \brief Calcula costo final del Transporte Aereo
 * \param path (Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
        												TransporteAereo* pTransporteAereo)
 * \return int [-1] error, resultado final si ok
 */
float transporteAereo_calcularCostoFinal(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                 TransporteAereo* pTransporteAereo)
{
	float retornoResultado = -1;
	float resulBaseImponible, resulImportacion, resultTasaEstadistica;
	if(pArticulo != NULL && pPosicionArancelaria != NULL && pTransporteAereo != NULL)
	{
		resulBaseImponible = transporteAereo_calcularBaseImponible(pArticulo, pPosicionArancelaria, pTransporteAereo);

		resulImportacion = transporteAereo_calcularPorcentajeImportacion(pArticulo, pPosicionArancelaria, pTransporteAereo);
		resultTasaEstadistica = transporteAereo_calcularPorcentajeTasaEstadistica(pArticulo, pPosicionArancelaria, pTransporteAereo);

		//if(resulBaseImponible > 0 && resulImportacion > 0 && resultTasaEstadistica > 0)
			retornoResultado = (resulBaseImponible + resulImportacion + resultTasaEstadistica);
			// Seteo el campo costo Transporte Aereo
			articulo_setCostoTransporteAereo(pArticulo, retornoResultado);
	}
	return retornoResultado;
}
/** \brief Calcula porcentaje Tasa Estadistica del Transporte Aereo
 * \param (Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
        												TransporteAereo* pTransporteAereo)
 * \return int [-1] error, resultado final si ok
 */
float transporteAereo_calcularPorcentajeTasaEstadistica(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
        												TransporteAereo* pTransporteAereo)
{
	float retornoResultado = -1;
	float porcentajeTasaEstadistica, resulBaseImponible;
	int flagErrorA;
	if(pArticulo != NULL && pPosicionArancelaria != NULL && pTransporteAereo != NULL)
	{
		porcentajeTasaEstadistica = posicionArancelaria_getPorcentajeTasaEstadistica(pPosicionArancelaria, &flagErrorA);
		resulBaseImponible = transporteAereo_calcularBaseImponible(pArticulo, pPosicionArancelaria, pTransporteAereo);

		if(!flagErrorA)
			retornoResultado = ((porcentajeTasaEstadistica * resulBaseImponible) / 100);
	}
	return retornoResultado;
}
/** \brief Calcula porcentaje Importacion del Transporte Aereo
 * \param (Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
        												TransporteAereo* pTransporteAereo)
 * \return int [-1] error, resultado final si ok
 */
float transporteAereo_calcularPorcentajeImportacion(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                            TransporteAereo* pTransporteAereo)
{
	float retornoResultado = -1;
	float porcentajeImportacion, resulBaseImponible;
	int flagErrorA;
	if(pArticulo != NULL && pPosicionArancelaria != NULL && pTransporteAereo != NULL)
	{
		porcentajeImportacion = posicionArancelaria_getPorcentajeImportacion(pPosicionArancelaria, &flagErrorA);
		resulBaseImponible = transporteAereo_calcularBaseImponible(pArticulo, pPosicionArancelaria, pTransporteAereo);

		if(!flagErrorA)
			retornoResultado = ((porcentajeImportacion * resulBaseImponible) / 100);
	}
	return retornoResultado;
}
/** \brief Calcula porcentaje BaseI mponible del Transporte Aereo
 * \param (Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
        												TransporteAereo* pTransporteAereo)
 * \return int [-1] error, resultado final si ok
 */
float transporteAereo_calcularBaseImponible(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                    TransporteAereo* pTransporteAereo)
{
	float retornoResultado = -1;
	float resultadoFlete, resulPorcentajeSeguro;
	float fob;
	int flagErrorA;
	if(pArticulo != NULL && pPosicionArancelaria != NULL && pTransporteAereo != NULL)
	{
		// Calculo proporcional Maritimo
		resultadoFlete = transporteAereo_calcularProporcionalFlete(pArticulo, pTransporteAereo);
		// Calculo Porcentaje del Seguro
		resulPorcentajeSeguro = calcularPorcentajeSeguro(pArticulo, pPosicionArancelaria);

		fob = articulo_getFob(pArticulo, &flagErrorA); // Obtengo valor fob
		if(!flagErrorA)
			retornoResultado = (fob + resulPorcentajeSeguro + resultadoFlete);
	}
	return retornoResultado;
}
//---------------------------------------------------------------- Flete Aereo
/*
 * Volumen nose que: (ancho x alto x profundidad) - funcion
 * precio por volumen: ( Volumen  / LA CONSTANTEE VOLUMETRICA) - funcion
 * precio peso Volumetrico: (precio por volumen * precioPorKg)
 *
 * (precioReal > precioVolumetrico) veo cual es mayor - de aca saco el proporcional de flete aereo
 * */
float transporteAereo_calcularProporcionalFlete(Articulo* pArticulo, TransporteAereo* pTransporteAereo)
{
	float retornoResultado = -1;
	float resultPrecioPesoReal, resulPrecioVolumetrico;
	if(pArticulo != NULL && pTransporteAereo != NULL)
	{
		resultPrecioPesoReal = transporteAereo_calcularPrecioPesoReal(pArticulo, pTransporteAereo);
		resulPrecioVolumetrico = transporteAereo_calcularPrecioPesoVolumetrico(pArticulo, pTransporteAereo);

		if(resultPrecioPesoReal > resulPrecioVolumetrico)
		{
			retornoResultado = resultPrecioPesoReal;
		}
		else
		{
			retornoResultado = resulPrecioVolumetrico;
		}
	}
	return retornoResultado;
}
/** \brief Calcula Precio Peso Volumetrico del Transporte Aereo
 * \param path (Articulo* pArticulo,
        							TransporteAereo* pTransporteAereo)
 * \return int [-1] error, resultado final si ok
 */
float transporteAereo_calcularPrecioPesoVolumetrico(Articulo* pArticulo, TransporteAereo* pTransporteAereo)
{
	float retornoResultado = -1;
	int flagErrorA;
	float precioPorKg, resultKgVolumetrico;
	if(pArticulo != NULL)
	{
		precioPorKg = transporteAereo_getPrecioPorKg(pTransporteAereo, &flagErrorA);
		resultKgVolumetrico = transporteAereo_calcularKgVolumetrico(pArticulo, pTransporteAereo);

		if(!flagErrorA)
			retornoResultado = (resultKgVolumetrico * precioPorKg);
	}
	return retornoResultado;
}

/** \brief Calcula volumen en centimetros cubicos del Transporte Aereo
 * \param path (Articulo* pArticulo,
        						TransporteAereo* pTransporteAereo)
 * \return int [-1] error, resultado final si ok
 */
float transporteAereo_calcularKgVolumetrico(Articulo* pArticulo, TransporteAereo* pTransporteAereo)
{
	float retornoResultado = -1;
	int flagErrorA;
	float constanteVolumetrica, resultVolumen;
	if(pArticulo != NULL)
	{
		constanteVolumetrica = transporteAereo_getConstanteVolumetrica(pTransporteAereo, &flagErrorA);
		resultVolumen = transporteAereo_calcularVolumen(pArticulo);
		if(!flagErrorA)
			retornoResultado = (resultVolumen / constanteVolumetrica);
	}
	return retornoResultado;
}
float transporteAereo_calcularVolumen(Articulo* pArticulo)
{
	float retornoResultado = -1;
	float ancho, altura, profundidad;
	int flagErrorA, flagErrorB, flagErrorC;
	if(pArticulo != NULL)
	{
		ancho = articulo_getAncho(pArticulo, &flagErrorA);
		altura = articulo_getAltura(pArticulo, &flagErrorB);
		profundidad = articulo_getProfundidad(pArticulo, &flagErrorC);

		if(!flagErrorA && !flagErrorB && !flagErrorC)
			retornoResultado = ((ancho*altura)*profundidad);
	}
	return retornoResultado;
}

/** \brief Calcula Precio Peso Real del Transporte Aereo
 * \param path (Articulo* pArticulo,
        							TransporteAereo* pTransporteAereo)
 * \return int [-1] error, resultado final si ok
 */
float transporteAereo_calcularPrecioPesoReal(Articulo* pArticulo, TransporteAereo* pTransporteAereo)
{
	float retornoResultado = -1;
	float pesoArticulo, precioPorKg;
	int flagErrorA,flagErrorB;
	if(pArticulo != NULL && pTransporteAereo != NULL)
	{
		pesoArticulo = articulo_getPeso(pArticulo, &flagErrorA);
		precioPorKg = transporteAereo_getPrecioPorKg(pTransporteAereo, &flagErrorB);

		if(!flagErrorA && !flagErrorB)
			retornoResultado = (pesoArticulo*precioPorKg);
	}
	return retornoResultado;
}

//******************************************************************************************** CALCULOS
//******************************************************************************************** TRANSPORTE MARITIMO
/** \brief Calcula costo final del Transporte Maritimo
 * \param path (Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
        												TransporteMaritimo* pTransporteMaritimo)
 * \return int [-1] error, resultado final si ok
 */
float transporteMaritimo_calcularCostoFinal(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
                                            TransporteMaritimo* pTransporteMaritimo)
{
	float retornoResultado = -1;
	float resulBaseImponible, resulImportacion, resultTasaEstadistica;
	if(pArticulo != NULL && pPosicionArancelaria != NULL && pTransporteMaritimo != NULL)
	{
		resulBaseImponible = transporteMaritimo_calcularBaseImponible(pArticulo, pPosicionArancelaria, pTransporteMaritimo);
		resulImportacion = transporteMaritimo_calcularPorcentajeImportacion(pArticulo, pPosicionArancelaria, pTransporteMaritimo);
		resultTasaEstadistica = transporteMaritimo_calcularPorcentajeTasaEstadistica(pArticulo, pPosicionArancelaria, pTransporteMaritimo);

		//if(resulBaseImponible > 0 && resulImportacion > 0 && resultTasaEstadistica > 0)
			retornoResultado = (resulBaseImponible + resulImportacion + resultTasaEstadistica);
			articulo_setCostoTransporteMaritimo(pArticulo, retornoResultado);
	}
	return retornoResultado;
}
/** \brief Calcula Porcentaje Tasa Estadistica Transporte Maritimo
 * \param path (Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
        												TransporteMaritimo* pTransporteMaritimo)
 * \return int [-1] error, resultado final si ok
 */
float transporteMaritimo_calcularPorcentajeTasaEstadistica(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
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
			retornoResultado = ((porcentajeTasaEstadistica * resulBaseImponible) / 100);
	}
	return retornoResultado;
}
/** \brief Calcula Porcentaje Importacion Transporte Maritimo
 * \param path (Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
        												TransporteMaritimo* pTransporteMaritimo)
 * \return int [-1] error, resultado final si ok
 */
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

		if(!flagErrorA)
			retornoResultado = ((porcentajeImportacion * resulBaseImponible) / 100);


	}
	return retornoResultado;
}

/** \brief Calcula Base Imponible Transporte Maritimo
 * \param path (Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
        												TransporteMaritimo* pTransporteMaritimo)
 * \return int [-1] error, resultado final si ok
 */
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
		resultadoFlete = transporteMaritimo_calcularProporcionalFlete(pArticulo, pTransporteMaritimo);
		// Calculo Porcentaje del Seguro
		resulPorcentajeSeguro = calcularPorcentajeSeguro(pArticulo, pPosicionArancelaria);

		fob = articulo_getFob(pArticulo, &flagErrorA); // Obtengo valor fob
		if(!flagErrorA)
			retornoResultado = (fob + resulPorcentajeSeguro + resultadoFlete);

	}
	return retornoResultado;
}
/** \brief Calcula porcentaje Seguro  Transporte Maritimo
 * \param path (Articulo* pArticulo,
        							TransporteMaritimo* pTransporteMaritimo)
 * \return int [-1] error, resultado final si ok
 */
float calcularPorcentajeSeguro(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria)
{
	float retornoResultado = -1;
	float porcentajeSeguro, fob;
	int flagErrorA, flagErrorB;
	if(pArticulo != NULL && pPosicionArancelaria != NULL)
	{
		porcentajeSeguro = posicionArancelaria_getPorcentajeSeguro(pPosicionArancelaria, &flagErrorB);
		fob = articulo_getFob(pArticulo, &flagErrorA);

		if(!flagErrorA && !flagErrorB)
			retornoResultado = ((porcentajeSeguro * fob) / 100);
	}
	return retornoResultado;
}
//---------------------------------------------------------------Proporcional Flete
/** \brief Calcula Volumen Cubico Transporte Maritimo
 * \param path (Articulo* pArticulo,
 * \return int [-1] error, resultado final si ok
 */
float transporteMaritimo_calcularVolumenCubico(Articulo* pArticulo) // Calcula volumen en metros cubicos 1)
{
	float retornoResultado = -1;
	float ancho, altura, profundidad;
	int flagErrorA, flagErrorB, flagErrorC;

	if(pArticulo != NULL)
	{
		ancho = articulo_getAncho(pArticulo, &flagErrorA);
		altura = articulo_getAltura(pArticulo, &flagErrorB);
		profundidad = articulo_getProfundidad(pArticulo, &flagErrorC);

		// (ancho / 100) *********** [ Paso de centimetros a metro]
		retornoResultado = ( (ancho / 100) * (altura / 100) * (profundidad / 100) );
	}
	return retornoResultado;
}
/** \brief Calcula Precio Por Metro Cubico Transporte Maritimo
 * \param path (TransporteMaritimo* pTransporteMaritimo,
 * \return int [-1] error, resultado final si ok
 */
float transporteMaritimo_calcularPrecioPorMetroCubico(TransporteMaritimo* pTransporteMaritimo) // 2)
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
			retornoResultado = (precioContenedor / metrosCubicos);
	}
	return retornoResultado;
}
/** \brief Calcula Proporcional Flete Transporte Maritimo
 * \param path (TransporteMaritimo* pTransporteMaritimo,
 * \return int [-1] error, resultado final si ok
 */
float transporteMaritimo_calcularProporcionalFlete(Articulo* pArticulo, TransporteMaritimo* pTransporteMaritimo) // 3)
{
	float retornoResultado = -1;
	float resultadoVolumenCubico;
	float resulPrecioPorMetroCubico;

	if(pArticulo != NULL && pTransporteMaritimo != NULL)
	{
		resultadoVolumenCubico = transporteMaritimo_calcularVolumenCubico(pArticulo);
		resulPrecioPorMetroCubico = transporteMaritimo_calcularPrecioPorMetroCubico(pTransporteMaritimo);

		retornoResultado = ( resultadoVolumenCubico * resulPrecioPorMetroCubico );
	}
	return retornoResultado;
}
