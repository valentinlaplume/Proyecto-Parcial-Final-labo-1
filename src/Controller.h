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

int controller_precioMaritimoArticulo(Dictionary* articulos,Dictionary* posicionesArancelarias,
		                              TransporteMaritimo* pTransporteMaritimo);

int controller_generarIdArticulo(void);
void controller_setearValorInicialDeIdArticulo(int);
void controller_setearValorInicialDeIdPosicionArancelaria(int );
int controller_generarIdPosicionArancelaria(void);

int controller_cargarArticulos(char* path, Dictionary* articulos);
int controller_cargarPosicionesArancelarias(char* path, Dictionary* posicionesArancelarias);
int controller_cargarTransporteMaritimo(char* path, TransporteMaritimo* pTransporteMaritimo);
int controller_cargarTransporteAereo(char* path, TransporteAereo* pTransporteAereo);

int controller_guardarArticulos(char* path, Dictionary* articulos);
int controller_guardarPosicionesArancelarias(char* path, Dictionary* posicionesArancelarias);
int controller_guardarTransporteMaritimo(char* path, TransporteMaritimo* pTransporteMaritimo);
int controller_guardarTransporteAereo(char* path, TransporteAereo* pTransporteAereo);

int controller_modificar(Dictionary* articulos);
int controller_borrar(Dictionary* articulos);

//ABM
int controller_ABMArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias);
int controller_ABMPosicionArancelaria(Dictionary* posicionesArancelarias, Dictionary* articulos);

//SUB MENU TRANSPORTES
int controller_subMenuTransporteAereo(TransporteAereo* pTransporteAereo);
int controller_subMenuTransporteMaritimo(TransporteMaritimo* pTransporteMaritimo);

// LISTAR
int controller_imprimirArticulos(Dictionary* articulos);
int controller_imprimirPosicionesArancelarias(Dictionary* posicionesArancelarias);

int controller_imprimirPosicionArancelariaConSusArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias);

// ALTAS
int controller_altaArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias);
int controller_altaPosicionArancelaria(Dictionary* posicionesArancelarias);

//BAJAS
int controller_bajaArticulo(Dictionary* articulos);
int controller_bajaPosicionArancelaria(Dictionary* posicionesArancelarias, Dictionary* articulos);

//MODIFICAR
int controller_modificarArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias);
int controller_modificarPosicionArancelaria( Dictionary* posicionesArancelarias);
int controller_modificarTransporteMaritimo(TransporteMaritimo* pTransporteMaritimo);
int controller_modificarTransporteAereo(TransporteAereo* pTransporteAereo);

#endif /* CONTROLLER_H_ */
