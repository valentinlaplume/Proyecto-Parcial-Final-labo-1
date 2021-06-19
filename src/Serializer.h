
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

int serializer_articulosFromText(FILE* pFile, Dictionary* articulos);
int serializer_posicionesArancelariasFromText(FILE* pFile, Dictionary* posicionesArancelarias);
#endif /* SERIALIZER_H_ */
