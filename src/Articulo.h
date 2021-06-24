
#ifndef ARTICULO_H_
#define ARTICULO_H_

#include "Articulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "LinkedList.h"
#include "laplume.h"

#define NOMBRE_LEN 50
#define CODIGO_LEN 50
#define DESCRIPCION_LEN 100
#define PAIS_LEN 50

typedef struct
{
	int idArticulo;
	int idPosicionArancelaria;

	char nombre[NOMBRE_LEN];
	char codigo[CODIGO_LEN];
	char descripcion[DESCRIPCION_LEN];
	char paisDeFabricacion[PAIS_LEN];

	float fob;
	float peso;

	float ancho;
	float altura;
	float profundidad;

	//-----------------------------
	float costoTransporteAereo;
	float costoTransporteMaritimo;

}Articulo;

//------------------------------------ INFORME PARCIAL
void articulo_encabezadoParcial(void);
int articulo_imprimirArticulosInformeParcial(LinkedList* listaArticulos);
int articulo_imprimirUnArticuloInformeParcial(void* pElement);

// Comparar costos final argentino por transportes
int funcionCriterio_compararCostoMaritimo(void* this1, void* this2);
int funcionCriterio_compararCostoAereo(void* this1, void* this2);

// LISTAR
int articulo_imprimirUnArticulo(void* pElement);
int articulo_imprimirArticulos(LinkedList* listaArticulos);

// ENCABEZADO AL LISTAR ARTICULO
void articulo_encabezado(void);

//int articulo_pedirIdPosicionArancelaria(int* idPosicionArancelaria);
int funcionCriterio_compararPorNombreArticulo(void* thisUno, void* thisDos);

// FUNCION CRITERIO BUSCAR POR CODIGO
int funcionCriterio_compararPorCodigoArticulo(void* pElement, void* codigoIngresadoBuscado);

// FUNCION CRITERIO BUSCAR POR DESCRIPCION
int funcionCriterio_compararPorDescripcionArticulo(void* pElement, void* descripcionIngresadaBuscado);

//------------------------------------------------------------------------------------------------------------------
// CONSTRUCTORES
Articulo* articulo_new(void);
Articulo* articulo_newParam(int idArticulo, int IdPosicionArancelaria,
		                    char* nombre, char* codigo,char* descripcion,char* paisDeFabricacion,
		                    float fob, float peso, float ancho, float altura, float profundidad);
// DESTRUCTOR
int articulo_delete(Articulo* this);
//---------------------------------------------- SET - GET - IS VALID ----------------------------------------------
int articulo_setCostoTransporteMaritimo(Articulo* this, float costoTransporteMaritimo);
float articulo_getCostoTransporteMaritimo(Articulo* this,int* flagError);

int articulo_setCostoTransporteAereo(Articulo* this, float costoTransporteAereo);
float articulo_getCostoTransporteAereo(Articulo* this,int* flagError);
//----------------------------------------------------------
int articulo_setIdArticulo(Articulo* this,int idArticulo);
int articulo_getIdArticulo(Articulo* this,int* flagError);
int isValidId(int);

int articulo_setIdPosicionArancelaria(Articulo* this, int id);
int articulo_getIdPosicionArancelaria(Articulo* this,int* flagError);

int articulo_setNombre(Articulo* this,char* nombre);
char* articulo_getNombre(Articulo* this,int* flagError);
int isValidNombre(char* nombre);

int articulo_setCodigo(Articulo* this, char* Codigo);
char* articulo_getCodigo(Articulo* this,int* flagError);
int isValidCodigo(char*);

int articulo_setDescripcion(Articulo* this,char* Descripcion);
char* articulo_getDescripcion(Articulo* this,int* flagError);
int isValidDescripcion(char*);

int articulo_setPaisDeFabricacion(Articulo* this, char* paisDeFabricacion);
char* articulo_getPaisDeFabricacion(Articulo* this,int* flagError);
int isValidPaisDeFabricacion(char* paisDeFabricacion);

int articulo_setFob(Articulo* this, float fob);
float articulo_getFob(Articulo* this,int* flagError);
int isValidFob(float fob);

int articulo_setPeso(Articulo* this, float peso);
float articulo_getPeso(Articulo* this,int* flagError);
int isValidPeso(float peso);

int articulo_setAncho(Articulo* this, float ancho);
float articulo_getAncho(Articulo* this,int* flagError);
int isValidAncho(float ancho);

int articulo_setAltura(Articulo* this, float altura);
float articulo_getAltura(Articulo* this,int* flagError);
int isValidAltura(float);

int articulo_setProfundidad(Articulo* this, float profundidad);
float articulo_getProfundidad(Articulo* this,int* flagError);
int isValidProfundidad(float profundidad);
//-----------------------------------------------------------------------------------------------------------------

#endif /* ARTICULO_H_ */
