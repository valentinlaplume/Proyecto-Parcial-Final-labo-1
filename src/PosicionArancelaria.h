#ifndef POSICIONARANCELARIA_H_
#define POSICIONARANCELARIA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "laplume.h"
#include "Parser.h"
#include "Serializer.h"
#include "PosicionArancelaria.h"

#define AUTOMATICA 0
#define NO_AUTOMATICA 1

#define NOMENCLADOR_LEN 40
#define TIPOLICENCIA_LEN 30

typedef struct
{
	int idPosicionArancelaria;

	char nomenclador[NOMENCLADOR_LEN];

	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEstadistica;

	int tipoLicencia; // [0] AUTOMATICA - [1] NO AUTOMATICA

}PosicionArancelaria;

// LISTAR
int posicionArancelaria_imprimirUnaPosicionArancelaria(void* pElement);
int posicionArancelaria_imprimirPosicionesArancelarias(LinkedList* posicionesArancelarias);

// OBTENER CADENA POR TIPO DE LICENCIA
int posicionArancelaria_obtenerCadenaPorTipoLicencia(int tipoLicencia, char opcionObtenida[]);

// ENCABEZADO AL LISTAR
void posicionArancelaria_encabezado(void);

// FUNCION CRITERIO BUSCAR POR NOMENCLATURA ARANCELARIA
int funcionCriterio_compararPorNomenclador(void* pElement, void* nomencladorIngresadoBuscado);

// FUN CRIT POR TIPO DE LICENCIA: NO AUTOMATICA
int funcionCriterio_porTipoLicenciaNoAutomatica(void* pElement);
// FUN CRIT POR TIPO DE LICENCIA: NO AUTOMATICA
int funcionCriterio_porTipoLicenciaAutomatica(void* pElement);

//------------------------------------------------------------------------------------------------------------------
// CONSTRUCTORES
PosicionArancelaria* posicionArancelaria_new(void);
PosicionArancelaria* posicionArancelaria_newParam(int idPosicionArancelaria, char* nomenclador, float porcentajeSeguro,
		                                          float porcentajeImportacion, float porcentajeTasaEstadistica, int tipoLicencia);
// DESTRUCTOR
int posicionArancelaria_delete(PosicionArancelaria* this);
//---------------------------------------------- SET - GET - IS VALID ----------------------------------------------

int posicionArancelaria_setIdPosicionArancelaria(PosicionArancelaria* this,int IdPosicionArancelaria);
int posicionArancelaria_getIdPosicionArancelaria(PosicionArancelaria* this,int* flagError);
int isValidIdPosicionArancelaria(int);

int posicionArancelaria_setNomenclador(PosicionArancelaria* this, char* nomenclador);
char* posicionArancelaria_getNomenclador(PosicionArancelaria* this,int* flagError);
int isValidNomenclador(char nomenclador[]);

int posicionArancelaria_setPorcentajeSeguro(PosicionArancelaria* this, float porcentajeSeguro);
float posicionArancelaria_getPorcentajeSeguro(PosicionArancelaria* this,int* flagError);
int isValidPorcentajeSeguro(float );

int posicionArancelaria_setPorcentajeImportacion(PosicionArancelaria* this, float porcentajeImportacion);
float posicionArancelaria_getPorcentajeImportacion(PosicionArancelaria* this,int* flagError);
int isValidPorcentajeImportacion(float );

int posicionArancelaria_setPorcentajeTasaEstadistica(PosicionArancelaria* this, float porcentajeTasaEstadistica);
float posicionArancelaria_getPorcentajeTasaEstadistica(PosicionArancelaria* this,int* flagError);
int isValidPorcentajeTasaEstadistica(float );

int posicionArancelaria_setIdPosicionArancelaria(PosicionArancelaria* this, int tipoLicencia);
int posicionArancelaria_getIdPosicionArancelaria(PosicionArancelaria* this,int* flagError);
int isValidTipoLicencia(int tipoLicencia);

int posicionArancelaria_setTipoLicencia(PosicionArancelaria* this, int tipoLicencia);
int posicionArancelaria_getTipoLicencia(PosicionArancelaria* this,int* flagError);
int isValidTipoLicencia(int tipoLicencia);
//-----------------------------------------------------------------------------------------------------------------

#endif /* POSICIONARANCELARIA_H_ */
