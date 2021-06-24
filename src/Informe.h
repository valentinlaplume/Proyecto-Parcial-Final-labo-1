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
int informe_pedirDatosArticulo(LinkedList* listaArticulos,char* nombre, char* codigo, char* descripcion, char* paisDeFabricacion,
		                       float* fob, float* peso, float* ancho, float* altura, float* profundidad);
// Pedir los datos de la Posicion Arancelaria
int informe_pedirDatosPosicionArancelaria(LinkedList* listaPosAran, char* nomenclador, float* porcentajeSeguro, float* porcentajeImportacion,
		                                  float* porcentajeTasaEstadistica, int* tipoLicencia);
//-----------------------------------------------------------------------------------------------------------------------
// generico - probando

int informe_prueba(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
                   TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo,
				   int (*pFuncion)(void*, void*));





//-----------------------------------------------------------------------------------------------------------------------
int informe_calcularCostosFinalesParcial(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
                                 TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo,
								 int (*pFuncion)(void*, void*));
// Calcula el costo de un articulo por transportes
int calcularUnCostoFinalEnArgentina(Articulo* pArticulo, PosicionArancelaria* pPosicionArancelaria,
		                             TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo);
//-------------------------------------------------------------------------------------------------------------------------------------------------
// Listar todas las Posicion Arancelaria con sus Articulos [Inclusive las que no poseen articulos]
int informe_listarTotalPosicionArancelariaConSusArticulos(LinkedList* listaArticulos, LinkedList* listaPosicionesArancelarias,
														  int (*pFuncion)(void*, void*));
// Listar Articulos con costo final por Transporte Maritimo
int informe_listarArticulosConCostoFinalTransporteMaritimo(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,TransporteMaritimo* pTransporteMaritimo,
														   int (*pFuncion)(void*, void*));
// Listar Articulos con costo final por Transporte Aereo
int informe_listarArticulosConCostoFinalTransporteAereo(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,TransporteAereo* pTransporteAereo,
		                                                int (*pFuncion)(void*, void*));
// Listar Articulos con costo final por Transportes
int informe_listarArticulosConCostoFinalPorTransportes(LinkedList* listaArticulos, LinkedList* listaPosicionArancelaria,
		                                               TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo,
													   int (*pFuncion)(void*, void*));

// Listar Articulos por Busqueda nomenclador
int informe_listarPorBusquedaPorNomencladorPosAran(LinkedList* listaPosicionArancelaria, LinkedList* listaArticulos,
		                                           TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo,
												   int (*pFuncion)(void*, void*));

//-------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCION CRITERIO, SON IDS IGUALES
int funcionCriterio_sonIdsIgualesPosArancelaria(void* pElementArticulo, void* pElementPosAran);


// Busqueda Posicion Arancelaria por nomenclador
void* buscarPorNomencladorPosicionArancelaria(LinkedList* listaPosicionArancelaria);
// Busqueda Articulo por codigo
void* buscarPorCodigoArticulo(LinkedList* listaArticulos);

//Busca si existe nomenclatura ingresada
int buscarSiExisteNomenclatura(LinkedList* listaPosAran, char* nomenclador);
//Busca si existe codigo ingresado
int buscarSiExisteCodigo(LinkedList* listaArticulos, char* codigo);
////Busca si existe descripcion ingresado
int buscarSiExisteDescripcion(LinkedList* listaArticulos, char* descripcion);

// Listar solo las Posicion Arancelaria con Articulos
//int informe_listarSoloPosicionArancelariaConArticulos(LinkedList* listaArticulos, LinkedList* listaPosicionesArancelarias); // no usada

#endif /* INFORME_H_ */
