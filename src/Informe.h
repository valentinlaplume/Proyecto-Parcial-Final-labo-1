#ifndef INFORME_H_
#define INFORME_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Dictionary.h"
#include "Controller.h"
#include "utn.h"
#include "laplume.h"
#include "Articulo.h"
#include "PosicionArancelaria.h"
#include "Informe.h"
#include "TransporteAereo.h"
#include "TransporteMaritimo.h"

int informe_pedirDatosArticulo(char* nombre, char* codigo, char* descripcion, char* paisDeFabricacion,
		                       float* fob, float* peso, float* ancho, float* altura, float* profundidad);

int informe_pedirDatosPosicionArancelaria(char* nomenclador, float* porcentajeSeguro, float* porcentajeImportacion,
		                                  float* porcentajeTasaEstadistica, int* tipoLicencia);

// Listar Posicion Arancelaria con sus Articulos
int informe_listarPosicionArancelariaConSusArticulo(LinkedList* listaArticulos, LinkedList* listaPosicionesArancelarias);

// Listar Articulos y costo final por Transporte Maritimo
int informe_listarArticulosConCostoFinalTransporteMaritimo(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
		                                                   TransporteMaritimo* pTransporteMaritimo);
//******************************************************************************** Calculos
// Transporte Maritimo
float transporteMaritimo_obtenerVolumenCubico(Articulo* pArticulo);
float transporteMaritimo_obtenerPrecioPorMetroCubico(TransporteMaritimo* pTransporteMaritimo);
float transporteMaritimo_calcularFlete(Articulo* pArticulo, TransporteMaritimo* pTransporteMaritimo);
/*
  (seguro*fob) / 100 -------- OK
  base imponible maritimo: fob + seguro + proporcional flete = la base imponible maritima ----- OK

 PORCENTAJE DE IMPORTACION = (% importacion * base imponible) / 100        - OK
 PORCENTAJE DE TASA ESTADISTICA = (% tasa estad * base imponible) / 100    - OK

 COSTO final !!!!!
 import final maritima = basee impon + porcentaje de importortacion + porcentaje tasa estadis */
float transporteMaritimo_calcularCostoFinal(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                    TransporteMaritimo* pTransporteMaritimo);
float transporteMaritimo_calcularBaseImponible(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
											   TransporteMaritimo* pTransporteMaritimo);
float transporteMaritimo_calcularPorcentajeImportacion(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                               TransporteMaritimo* pTransporteMaritimo);
float transporteMaritimo_calcularPorcentajeeTasaEstadistica(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                                                    TransporteMaritimo* pTransporteMaritimo);
float transporteMaritimo_calcularPorcentajeSeguro(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria);

#endif /* INFORME_H_ */
