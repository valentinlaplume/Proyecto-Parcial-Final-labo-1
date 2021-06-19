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

#define NOMENCLADOR_LEN 20

typedef struct
{
	int idPosicionArancelaria;

	char nomenclador[NOMENCLADOR_LEN];

	float porcentajeSeguro;
	float porcentajeImportacion;
	float porcentajeTasaEstadistica;

	int tipoLicencia; // [0] AUTOMATICA - [1] NO AUTOMATICA
}PosicionArancelaria;

PosicionArancelaria* posicionArancelaria_new(void);
PosicionArancelaria* posicionArancelaria_newParam(int idPosicionArancelaria, char* nomenclador, float porcentajeSeguro,
		                                          float porcentajeImportacion, float porcentajeTasaEstadistica, int tipoLicencia);

int posicionArancelaria_delete(PosicionArancelaria* this);

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

//******************************************************************************** LISTAR
int posicionArancelaria_imprimirUnaPosicionArancelaria(void* pElement);
int posicionArancelaria_imprimirPosicionesArancelarias(LinkedList* posicionesArancelarias);

#endif /* POSICIONARANCELARIA_H_ */
