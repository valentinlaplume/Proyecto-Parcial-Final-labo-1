#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "Dictionary.h"

#include "utn.h"
#include "Controller.h"

#define OPCION_SALIR 10

int main(void)
{
	int opcion;
	Dictionary* articulos;
	Dictionary* posicionesArancelarias;

	articulos = dict_new(0);
	posicionesArancelarias = dict_new(0);

	if(articulos != NULL && posicionesArancelarias != NULL)
	{
		controller_cargarArticulos("articulos.csv", articulos);
		controller_cargarPosicionesArancelarias("posicionesArancelarias.csv", posicionesArancelarias);
		do{
			if(!utn_getNumero(&opcion,
					"\n"
					"\n * ====================== \x1b[93m\x1b[44m MENU PRINCIPAL \x1b[0m\x1b[0m ====================== *"
					"\n | ============================================================== |"
					"\n |  1  - Listar articulos                                         |"
					"\n |  2  - Listar posiciones arancelarias                           |"
					"\n |  3  - Dar de ALTA un articulo                                  |"
					"\n |  4  - Dar de ALTA una posicion arancelaria                     |"
					"\n |  5  - Dar de BAJA un articulo                                  |"
					"\n |  6  - Dar de BAJA una posicion arancelaria                     |"
					"\n |  7  -  guardar articulos |"
					"\n |  8  -  guardar posiciones arancelarias|"
					"\n |  9  -  |"
					"\n | 10  -  Salir                                                   |"
					"\n * -------------------------------------------------------------- *"
					"\n > Eliga opcion: ",
					"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 1, OPCION_SALIR, 9999))
			{
				switch(opcion)
				{
					case 1:
						controller_imprimirArticulos(articulos);
					break;
					case 2:
						controller_imprimirPosicionesArancelarias(posicionesArancelarias);
					break;
					case 3:
						controller_altaArticulo(articulos, posicionesArancelarias);
					break;
					case 4:
						controller_altaPosicionArancelaria(posicionesArancelarias);
					break;
					case 5:
						controller_bajaArticulo(articulos);
					break;
					case 6:
						controller_bajaPosicionArancelaria(posicionesArancelarias, articulos);
					break;
					case 7:
						//controller_modificarArticulo(articulos, posicionesArancelarias);
						controller_guardarArticulos("articulos.csv", articulos);
					break;
					case 8:
						controller_guardarPosicionesArancelarias("posicionesArancelarias.csv", posicionesArancelarias);
					break;
					case 9:
					break;
				} // fin switch
			}// fin if opcion
		}while(opcion != OPCION_SALIR);
	}// fin if
	return EXIT_SUCCESS;
}
