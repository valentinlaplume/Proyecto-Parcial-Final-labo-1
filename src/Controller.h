#ifndef CONTROLLER_H_
#define CONTROLLER_H_

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

int controller_generarIdArticulo(void);
void controller_setearValorInicialDeIdArticulo(int);
void controller_setearValorInicialDeIdPosicionArancelaria(int );
int controller_generarIdPosicionArancelaria(void);

int controller_cargarArticulos(char* path, Dictionary* articulos);
int controller_cargarPosicionesArancelarias(char* path, Dictionary* posicionesArancelarias);

int controller_guardarArticulos(char* path, Dictionary* articulos);
int controller_guardarPosicionesArancelarias(char* path, Dictionary* posicionesArancelarias);

int controller_modificar(Dictionary* articulos);
int controller_borrar(Dictionary* articulos);

// LISTAR
int controller_imprimirArticulos(Dictionary* articulos);
int controller_imprimirPosicionesArancelarias(Dictionary* posicionesArancelarias);

// ALTAS
int controller_altaArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias);
int controller_altaPosicionArancelaria(Dictionary* posicionesArancelarias);

//BAJAS
int controller_bajaArticulo(Dictionary* articulos);
int controller_bajaPosicionArancelaria(Dictionary* posicionesArancelarias, Dictionary* articulos);

//MODIFICAR
int controller_modificarArticulo(Dictionary* articulos, Dictionary* posicionesArancelarias);

#endif /* CONTROLLER_H_ */
