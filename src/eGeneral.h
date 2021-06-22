
#ifndef EGENERAL_H_
#define EGENERAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Dictionary.h"
#include "eGeneral.h"
#include "eGeneral.h"

#include "eGeneral.h"

typedef struct
{
	//------------------------------- Campos eGeneral
	float costoTransporteAereo;
	float costoTransporteMaritimo;
	//------------------------------------------------------------ Campos Articulo
	int idArticuloGeneral; // Uso el ID del Articulo como key eGeneral, y como Id de eGeneral

	float fob;
	float peso;

	float ancho;
	float altura;
	float profundidad;
	//--------------------------------------- Campos Posicion Arancelaria
	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEstadistica;

}eGeneral;

eGeneral* eGeneral_new(void);
eGeneral* eGeneral_newParam(int idArticuloGeneral, float fob, float peso, float ancho, float altura, float profundidad,
							float porcentajeSeguro, float porcentajeImportacion, float porcentajeTasaEstadistica);


int eGeneral_delete(eGeneral* this);


int eGeneral_setCostoTransporteMaritimo(eGeneral* this, float costoTransporteMaritimo);
float eGeneral_getCostoTransporteMaritimo(eGeneral* this,int* flagError);

int eGeneral_setCostoTransporteAereo(eGeneral* this, float costoTransporteAereo);
float eGeneral_getCostoTransporteAereo(eGeneral* this,int* flagError);
//---------------------------------------------- SET - GET - IS VALID ----------------------------------------------
int eGeneral_setIdArticuloGeneral(eGeneral* this, int idArticuloGeneral);
int eGeneral_getIdArticuloGeneral(eGeneral* this,int* flagError);

int eGeneral_setFob(eGeneral* this, float fob);
float eGeneral_getFob(eGeneral* this,int* flagError);
int isValidFob(float fob);

int eGeneral_setPeso(eGeneral* this, float peso);
float eGeneral_getPeso(eGeneral* this,int* flagError);

int eGeneral_setAncho(eGeneral* this, float ancho);
float eGeneral_getAncho(eGeneral* this,int* flagError);

int eGeneral_setAltura(eGeneral* this, float altura);
float eGeneral_getAltura(eGeneral* this,int* flagError);

int eGeneral_setProfundidad(eGeneral* this, float profundidad);
float eGeneral_getProfundidad(eGeneral* this,int* flagError);
//-----------------------------------------------------------------------------------------------------------------
int eGeneral_setPorcentajeSeguro(eGeneral* this, float porcentajeSeguro);
float eGeneral_getPorcentajeSeguro(eGeneral* this,int* flagError);
int isValidPorcentajeSeguro(float );

int eGeneral_setPorcentajeImportacion(eGeneral* this, float porcentajeImportacion);
float eGeneral_getPorcentajeImportacion(eGeneral* this,int* flagError);
int isValidPorcentajeImportacion(float );

int eGeneral_setPorcentajeTasaEstadistica(eGeneral* this, float porcentajeTasaEstadistica);
float eGeneral_getPorcentajeTasaEstadistica(eGeneral* this,int* flagError);
int isValidPorcentajeTasaEstadistica(float );


#endif /* EGENERAL_H_ */
