
#ifndef TRANSPORTEAEREO_H_
#define TRANSPORTEAEREO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"
#include "laplume.h"
#include "TransporteAereo.h"

typedef struct
{
	float constanteVolumetrica;
	float precioPorKg;
}TransporteAereo;

//TransporteAereo* TransporteAereo_new(void);
TransporteAereo* transporteAereo_newParam(TransporteAereo* pTransporteAereo,
		                                  float constanteVolumetrica, float precioPorKg);

//******************************************************************************** DESTRUCTOR
int transporteAereo_delete(TransporteAereo* this);

//******************************************************************************** SET - GET - IS VALID
int transporteAereo_setConstanteVolumetrica(TransporteAereo* this, float constanteVolumetrica);
float transporteAereo_getConstanteVolumetrica(TransporteAereo* this,int* flagError);
int isValidConstanteVolumetrica(float );

int transporteAereo_setPrecioPorKg(TransporteAereo* this, float precioPorKg);
float transporteAereo_getPrecioPorKg(TransporteAereo* this,int* flagError);
int isValidPrecioPorKg(float );

//******************************************************************************** LISTAR
int transporteAereo_imprimirTransporteAereo(TransporteAereo* pTransporteAereo);

#endif /* TRANSPORTEAEREO_H_ */
