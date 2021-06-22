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
#include "Calculos.h"

// Pedir los datos del Articulo
int informe_pedirDatosArticulo(char* nombre, char* codigo, char* descripcion, char* paisDeFabricacion,
		                       float* fob, float* peso, float* ancho, float* altura, float* profundidad);
// Pedir los datos de la Posicion Arancelaria
int informe_pedirDatosPosicionArancelaria(char* nomenclador, float* porcentajeSeguro, float* porcentajeImportacion,
		                                  float* porcentajeTasaEstadistica, int* tipoLicencia);
//-------------------------------------------------------------------------------------------------------------------------------------------------
// Listar solo las Posicion Arancelaria con Articulos
int informe_listarSoloPosicionArancelariaConArticulos(LinkedList* listaArticulos, LinkedList* listaPosicionesArancelarias);
// Listar todas las Posicion Arancelaria con sus Articulos [Inclusive las que no poseen articulos]
int informe_listarTotalPosicionArancelariaConSusArticulos(LinkedList* listaArticulos, LinkedList* listaPosicionesArancelarias);
// Listar Articulos con costo final por Transporte Maritimo
int informe_listarArticulosConCostoFinalTransporteMaritimo(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,TransporteMaritimo* pTransporteMaritimo);
// Listar Articulos con costo final por Transporte Aereo
int informe_listarArticulosConCostoFinalTransporteAereo(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,TransporteAereo* pTransporteAereo);
// Listar Articulos con costo final por Transportes
int informe_listarArticulosConCostoFinalPorTransportes(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria, TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo);

// Listar Articulos por Busqueda nomenclador
int informe_listarPorBusquedaPorNomencladorPosAran(LinkedList* listaPosicionArancelaria, LinkedList* listaArticulos,
		                                           TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo);
int sonIgualesIdPosicionArancelaria(void* pArticuloElement, void* pPosicionAranElement);

//-------------------------------------------------------------------------------------------------------------------------------------------------
// Busqueda Posicion Arancelaria por nomenclador
void* busquedaPorNomencladorPosicionArancelaria(LinkedList* listaPosicionArancelaria);
// Busqueda Articulo por codigo
void* busquedaPorCodigoArticulo(LinkedList* listaArticulos);


#endif /* INFORME_H_ */
