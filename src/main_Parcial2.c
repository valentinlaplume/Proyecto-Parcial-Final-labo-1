#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "Dictionary.h"

#include "utn.h"
#include "Controller.h"

#define OPCION_SALIR 15

int main(void)
{
	int opcion;
	Dictionary* articulos;
	Dictionary* posicionesArancelarias;
	TransporteMaritimo transporteMaritimo;
	TransporteAereo transporteAereo;

	articulos = dict_new(0);
	posicionesArancelarias = dict_new(0);

	if(articulos != NULL && posicionesArancelarias != NULL)
	{
		controller_cargarArticulos("articulos.csv", articulos);
		controller_cargarPosicionesArancelarias("posicionesArancelarias.csv", posicionesArancelarias);
		//-------------------------------------------------------------------------------
		controller_cargarTransporteMaritimo("transporteMaritimo.csv", &transporteMaritimo);
		controller_cargarTransporteAereo("transporteAereo.csv", &transporteAereo);
		do{
			if(!utn_getNumero(&opcion,
					"\n"
					"\n * ========================= \x1b[93m\x1b[44m MENU PRINCIPAL \x1b[0m\x1b[0m ========================= *"
					"\n | ==================================================================== |"
					"\n |  1  - Listar Articulos                                               |"
					"\n |  2  - Listar Posiciones Arancelarias                                 |"
					"\n |  3  - Submenu: Alta, Baja, Modificacion [Articulo]                   |"
					"\n |  4  - Submenu: Alta, Baja, Modificacion [Posicion Arancelaria]       |"
					"\n |  5  - Ver información - Modificar información [Transporte Aereo]     |"
					"\n |  6  - Ver información - Modificar información [Transporte Maritimo]  |"
					"\n |  7  - Listar Posicion Arancelaria con sus Articulos                  |"
					"\n |  8  - Listar Articulos y costo final por Transporte Maritimo         |"
					"\n |  9  - |"
					"\n | 10  - |"
					"\n | 11  -  Guardar Transporte Aereo                                      |"
					"\n | 12  -  Guardar Transporte Maritimo                                   |"
					"\n | 13  -  Guardar Articulos                                             |"
					"\n | 14  -  Guardar Posiciones Arancelarias                               |"
					"\n | 15  -  Salir                                                         |"
					"\n * -------------------------------------------------------------------- *"
					"\n > Eliga opcion: ",
					"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 1, OPCION_SALIR, 9999))
			{
				switch(opcion)
				{
					case 1: // Listar articulos
						controller_imprimirArticulos(articulos);
					break;
					case 2: // Listar posiciones arancelarias
						controller_imprimirPosicionesArancelarias(posicionesArancelarias);
					break;
					case 3: // Alta - Baja - Modificacion [Articulo]
						controller_ABMArticulo(articulos, posicionesArancelarias);
					break;
					case 4: // Alta - Baja - Modificacion [Posicion Arancelaria]
						controller_ABMPosicionArancelaria(posicionesArancelarias, articulos);
					break;
					case 5: // Ver información - Modificar información [Transporte Aereo]
						controller_subMenuTransporteAereo(&transporteAereo);
					break;
					case 6: // Ver información - Modificar información [Transporte Maritimo]
						controller_subMenuTransporteMaritimo(&transporteMaritimo);
					break;
					case 7: // Listar Posicion Arancelaria con sus Articulos
						controller_imprimirPosicionArancelariaConSusArticulo(articulos, posicionesArancelarias);
					break;
					case 8: // Listar Articulos y costo final por Transporte Maritimo
						controller_precioMaritimoArticulo(articulos, posicionesArancelarias,&transporteMaritimo);
					break;
					case 9:
					break;
					case 10:
					break;
					case 11:
						controller_guardarTransporteAereo("transporteAereo.csv", &transporteAereo);
					break;
					case 12:
						controller_guardarTransporteMaritimo("transporteMaritimo.csv", &transporteMaritimo);
					break;
					case 13:
						controller_guardarArticulos("articulos.csv", articulos);
					break;
					case 14:
						controller_guardarPosicionesArancelarias("posicionesArancelarias.csv", posicionesArancelarias);
					break;
				} // fin switch
			}// fin if opcion
		}while(opcion != OPCION_SALIR);
	}// fin if
	return EXIT_SUCCESS;
}
