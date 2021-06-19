

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

#define STR_LEN 1024

int parser_articuloFromText(FILE* pFile, Dictionary* articulos, int* pIdMaxEncontrado);
int parser_posicionesArancelariasFromText(FILE* pFile, Dictionary* posicionesArancelarias, int* pIdMaxEncontrado);

#endif /* PARSER_H_ */
