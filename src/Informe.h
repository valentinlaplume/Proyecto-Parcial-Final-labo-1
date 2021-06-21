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

int informe_pedirDatosArticulo(char* nombre, char* codigo, char* descripcion, char* paisDeFabricacion,
		                       float* fob, float* peso, float* ancho, float* altura, float* profundidad);

int informe_pedirDatosPosicionArancelaria(char* nomenclador, float* porcentajeSeguro, float* porcentajeImportacion,
		                                  float* porcentajeTasaEstadistica, int* tipoLicencia);

// Listar Posicion Arancelaria con sus Articulos
int informe_listarPosicionArancelariaConSusArticulo(LinkedList* listaArticulos, LinkedList* listaPosicionesArancelarias);
// Listar Articulos con costo final por Transporte Maritimo
int informe_listarArticulosConCostoFinalTransporteMaritimo(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,TransporteMaritimo* pTransporteMaritimo);
// Listar Articulos con costo final por Transporte Aereo
int informe_listarArticulosConCostoFinalTransporteAereo(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,TransporteAereo* pTransporteAereo);
// Listar Articulos con costo final por Transportes
int informe_listarArticulosConCostoFinalPorTransportes(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria, TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo);



// Listar Articulos por Busqueda nomenclador
int informe_listarPorBusquedaPorNomencladorPosAran(LinkedList* listaPosicionArancelaria, LinkedList* listaArticulos);
int sonIgualesIdPosicionArancelaria(void* pArticuloElement, void* pPosicionAranElement);






#endif /* INFORME_H_ */
