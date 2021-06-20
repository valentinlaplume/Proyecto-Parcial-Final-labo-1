
#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dictionary.h"
#include "LinkedList.h"

#include "Serializer.h"
#include "Articulo.h"
#include "Controller.h"

#include "TransporteMaritimo.h"
#include "TransporteAereo.h"

int serializer_articulosFromText(FILE* pFile, Dictionary* articulos);
int serializer_posicionesArancelariasFromText(FILE* pFile, Dictionary* posicionesArancelarias);
int serializer_transporteMaritimoFromText(FILE* pFile, TransporteMaritimo* pTransporteMaritimo);
int serializer_transporteAereoFromText(FILE* pFile, TransporteAereo* pTransporteAereo);

#endif /* SERIALIZER_H_ */
