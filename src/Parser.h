
#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dictionary.h"
#include "Articulo.h"
#include "PosicionArancelaria.h"
#include "Parser.h"
#include "utn.h"
#include "TransporteMaritimo.h"
#include "TransporteAereo.h"

#define STR_LEN 1024

int parser_articulosFromText(FILE* pFile, Dictionary* articulos, int* pIdMaxEncontrado);
int parser_posicionesArancelariasFromText(FILE* pFile, Dictionary* posicionesArancelarias, int* pIdMaxEncontrado);

// PARSER TRANSPORTE MARITIMO
int parser_transporteMaritimoFromText(FILE* pFile, TransporteMaritimo* pTransporteMaritimo);

// PARSER TRANSPORTE AEREO
int parser_transporteAereoFromText(FILE* pFile, TransporteAereo* pTransporteAereo);

#endif /* PARSER_H_ */
