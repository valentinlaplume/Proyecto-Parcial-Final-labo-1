#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Dictionary.h"
#include "Controller.h"
#include "Articulo.h"
#include "PosicionArancelaria.h"
#include "TransporteMaritimo.h"
#include "TransporteAereo.h"

#define ID_STR 10



// generico - pruebas
int controller_pruebasWhile(Dictionary* articulos, Dictionary* posicionesArancelarias,
		                    TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo);
//*************************************************************************************************************************

int controller_informeParcial(Dictionary* articulos, Dictionary* posicionesArancelarias, TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo);

// BUSCA POSICION ARANCELARIA POR NOMENCLADOR Y LISTAR SUS ARTICULOS CON SUS COSTOS DE TRANSPORTE
int controller_listarArticulosPorBusquedaPorNomenclador(Dictionary* articulos, Dictionary* posicionesArancelarias,
		                                               TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo);
// BUSCAR ARTICULO POR CODIGO
int controller_listarUnArticuloPorBusquedaPorCodigo(Dictionary* articulos);

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// SUB MENU INFORME
int controller_subMenuInforme(Dictionary* articulos, Dictionary* posicionesArancelarias, TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo);

//Costo final por Transportes
int controller_costoFinalPorTransportes(Dictionary* articulos, Dictionary* posicionesArancelarias, TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo);
// Costo final por Transporte Maritimo
int controller_costoFinalTransporteMaritimo(Dictionary* articulos,Dictionary* posicionesArancelarias, TransporteMaritimo* pTransporteMaritimo);
// Costo final por Transporte Aereo
int controller_costoFinalTransporteAereo(Dictionary* articulos, Dictionary* posicionesArancelarias,TransporteAereo* pTransporteAereo);
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// GENERAR ID - INCREMENTAR
int controller_generarIdArticulo(void);
int controller_generarIdPosicionArancelaria(void);

// SETER ID
void controller_setearValorInicialDeIdArticulo(int);
void controller_setearValorInicialDeIdPosicionArancelaria(int );

// CARGAR DATOS DESDE EL ARCHIVO
int controller_cargarDatosGenerales(char* path, Dictionary* datosGenerales); // Carga datos generales
int controller_cargarArticulos(char* path, Dictionary* articulos);
int controller_cargarPosicionesArancelarias(char* path, Dictionary* posicionesArancelarias);
int controller_cargarTransporteMaritimo(char* path, TransporteMaritimo* pTransporteMaritimo);
int controller_cargarTransporteAereo(char* path, TransporteAereo* pTransporteAereo);

// VOLCAR DATOS AL ARCHIVO
int controller_guardarDatosGenerales(char* path, Dictionary* articulos, Dictionary* posicionesArancelarias,
		TransporteAereo* pTransporteAereo, TransporteMaritimo* pTransporteMaritimo); // Guarda datos generales
int controller_guardarArticulos(char* path, Dictionary* articulos);
int controller_guardarPosicionesArancelarias(char* path, Dictionary* posicionesArancelarias);
int controller_guardarTransporteMaritimo(char* path, TransporteMaritimo* pTransporteMaritimo);
int controller_guardarTransporteAereo(char* path, TransporteAereo* pTransporteAereo);

//ABM - submenu
int controller_ABMArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias);
int controller_ABMPosicionArancelaria(Dictionary* posicionesArancelarias, Dictionary* articulos);

//SUB MENU TRANSPORTES
int controller_subMenuTransporteAereo(TransporteAereo* pTransporteAereo);
int controller_subMenuTransporteMaritimo(TransporteMaritimo* pTransporteMaritimo);

// LISTAR
int controller_listarArticulos(Dictionary* articulos);
int controller_listarPosicionesArancelarias(Dictionary* posicionesArancelarias);

// Listar todas las Posicion Arancelaria con sus Articulos [Inclusive las que no poseen articulos]
int controller_listarTotalPosicionesArancelariaConSusArticulos(Dictionary* articulos, Dictionary* posicionesArancelarias);
// Listar solo las Posicion Arancelaria con Articulos
//int controller_listarSoloPosicionesArancelariaConArticulos(Dictionary* articulos, Dictionary* posicionesArancelarias); no usada

// Lista Posiciones Arancelarias con tipo de licencia NO AUTOMÁTICA
int controller_listarPosicionesArancelariasNoAutomatica(Dictionary* posicionesArancelarias);
// Lista Posiciones Arancelarias con tipo de licencia AUTOMÁTICA
int controller_listarPosicionesArancelariasAutomatica(Dictionary* posicionesArancelarias);

// ALTAS
int controller_altaArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias);
int controller_altaPosicionArancelaria(Dictionary* posicionesArancelarias);

//BAJAS
int controller_bajaArticulo(Dictionary* articulos);
int controller_bajaPosicionArancelaria(Dictionary* posicionesArancelarias, Dictionary* articulos);

//MODIFICAR
int controller_modificarArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias);
int controller_modificarPosicionArancelaria( Dictionary* posicionesArancelarias);


#endif /* CONTROLLER_H_ */
