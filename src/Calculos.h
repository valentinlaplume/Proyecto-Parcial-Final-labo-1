#ifndef CALCULOS_H_
#define CALCULOS_H_

#include "utn.h"
#include "laplume.h"
#include "Articulo.h"
#include "PosicionArancelaria.h"
#include "TransporteAereo.h"
#include "TransporteMaritimo.h"
#include "Calculos.h"

//******************************************************************************** Calculos Transporte Aereo
float transporteAereo_calcularCostoFinal(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,TransporteAereo* pTransporteAereo);

float transporteAereo_calcularBaseImponible(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria, TransporteAereo* pTransporteAereo);
float transporteAereo_calcularProporcionalFlete(Articulo* pArticulo, TransporteAereo* pTransporteAereo);

float transporteAereo_calcularPrecioPesoReal(Articulo* pArticulo, TransporteAereo* pTransporteAereo);

float transporteAereo_calcularPrecioPesoVolumetrico(Articulo* pArticulo, TransporteAereo* pTransporteAereo);
float transporteAereo_calcularVolumen(Articulo* pArticulo);
float transporteAereo_calcularKgVolumetrico(Articulo* pArticulo, TransporteAereo* pTransporteAereo);

float transporteAereo_calcularPorcentajeImportacion(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria, TransporteAereo* pTransporteAereo);
float transporteAereo_calcularPorcentajeTasaEstadistica(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,TransporteAereo* pTransporteAereo);
//******************************************************************************** Calculos Transporte Maritimo
float transporteMaritimo_calcularVolumenCubico(Articulo* pArticulo);
float transporteMaritimo_calcularPrecioPorMetroCubico(TransporteMaritimo* pTransporteMaritimo);
float transporteMaritimo_calcularProporcionalFlete(Articulo* pArticulo, TransporteMaritimo* pTransporteMaritimo);

float transporteMaritimo_calcularPorcentajeImportacion(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,TransporteMaritimo* pTransporteMaritimo);
float transporteMaritimo_calcularPorcentajeTasaEstadistica(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria, TransporteMaritimo* pTransporteMaritimo);

float transporteMaritimo_calcularBaseImponible(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,TransporteMaritimo* pTransporteMaritimo);
float transporteMaritimo_calcularCostoFinal(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,TransporteMaritimo* pTransporteMaritimo);

//******************************************************************************** Calculo Usado para los dos tipo de transportes
float calcularPorcentajeSeguro(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria);

#endif /* CALCULOS_H_ */
