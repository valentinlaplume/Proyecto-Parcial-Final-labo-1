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
					"\n |  7  - Listar Posiciones Arancelarias con sus Articulos               |"
					"\n |  8  - Informe costo final por Transportes                            |"
					"\n |  9  - Buscar Posicion Arancelaria por Nomenclador y listar Articulos |"
					"\n | 10  - Buscar Articulo por Codigo                                     |"
					"\n | 11  -  |"
					"\n | 12  -  |"
					"\n | 13  -  |"
					"\n | 14  -  Guardar todo (SE SACA ESTA OPCION)                            |"
					"\n | 15  -  Salir                                                         |"
					"\n * -------------------------------------------------------------------- *"
					"\n > Eliga opcion: ",
					"\n\x1b[31m * OPCION INVALIDA * \x1b[0m", 1, OPCION_SALIR, 9999))
			{
				switch(opcion)
				{
					case 1: // Listar articulos
						controller_listarArticulos(articulos);
					break;
					case 2: // Listar posiciones arancelarias
						controller_listarPosicionesArancelarias(posicionesArancelarias);
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
						controller_listarPosicionArancelariaConSusArticulo(articulos, posicionesArancelarias);
					break;
					case 8: // Informe costo final por Transportes
						controller_subMenuInforme(articulos, posicionesArancelarias, &transporteAereo, &transporteMaritimo);
					break;
					case 9: // Buscar Posicion Arancelaria por Nomenclador y listar Articulos
						controller_listarArticulosPorBusquedaNomenclador(articulos, posicionesArancelarias);
					break;
					case 10: // Buscar Articulo por Codigo
						controller_listarArticuloPorBusquedaCodigo(articulos);
					break;
					case 11:

					break;
					case 12:

					break;
					case 13:

					break;
					case 14:
						controller_guardarTransporteAereo("transporteAereo.csv", &transporteAereo);
						controller_guardarTransporteMaritimo("transporteMaritimo.csv", &transporteMaritimo);
						controller_guardarArticulos("articulos.csv", articulos);
						controller_guardarPosicionesArancelarias("posicionesArancelarias.csv", posicionesArancelarias);
					break;
				} // fin switch
			}// fin if opcion
		}while(opcion != OPCION_SALIR);
	}// fin if
	return EXIT_SUCCESS;
}
