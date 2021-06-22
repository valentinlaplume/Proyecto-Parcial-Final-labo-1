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

	//Dictionary* datosGenerales;
	//datosGenerales = dict_new(0); // Fue una idea, no hubo tiempo de plasmar

	articulos = dict_new(0);
	posicionesArancelarias = dict_new(0);

	if(articulos != NULL && posicionesArancelarias != NULL)
	{
		//controller_cargarDatosGenerales("datosGenerales.csv", datosGenerales); // Fue una idea, no hubo tiempo de plasmar
		//-------------------------------------------------------------------------------
		controller_cargarArticulos("articulos.csv", articulos);
		controller_cargarPosicionesArancelarias("posicionesArancelarias.csv", posicionesArancelarias);
		controller_cargarTransporteMaritimo("transporteMaritimo.csv", &transporteMaritimo);
		controller_cargarTransporteAereo("transporteAereo.csv", &transporteAereo);
		//-------------------------------------------------------------------------------
		do{
			if(!utn_getNumero(&opcion,
					"\n"
					"\n * \x1b[93m\x1b[44m=========================  MENU PRINCIPAL  =========================\x1b[0m\x1b[0m *"
					"\n | ==================================================================== |"
					"\n |  1  - Listar Articulos                                               |"
					"\n |                                                                      |"
					"\n |  2  - Listar Posiciones Arancelarias                                 |"
					"\n |                                                                      |"
					"\n |  3  - Listar todas las Posiciones Arancelarias con sus Articulos     |"
					"\n |                                                                      |"
					"\n |  4  - Submenu: Alta, Baja, Modificacion [Articulo]                   |"
					"\n |              * Buscar Articulo por codigo                            |"
					"\n |                                                                      |"
					"\n |  5  - Submenu: Alta, Baja, Modificacion [Posicion Arancelaria]       |"
					"\n |              * Listas Filtradas [AUTOMÁTICA - NO AUTOMÁTICA]         |"
					"\n |                                                                      |"
					"\n |  6  - Ver información - Modificar información [Transporte Aereo]     |"
					"\n |                                                                      |"
					"\n |  7  - Ver información - Modificar información [Transporte Maritimo]  |"
					"\n |                                                                      |"
					"\n |  8  - Submenu: Informes, calcular costos final por Transportes       |"
					"\n |                                                                      |"
					"\n |  9  - Buscar Posicion Arancelaria por Nomenclador:                   |"
					"\n |                        * Listar Articulos y su costo por Transportes |"
					"\n |                                                                      |"
				  /*"\n | 10  -  |"
					"\n | 11  -  |"
					"\n | 12  -  |"
					"\n | 13  -  |"
					"\n | 14  -  |"*/
					"\n | 15  - Salir y cerrar programa                                        |"
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
					case 3: // Listar todas las Posicion Arancelaria con sus Articulos
						controller_listarTotalPosicionesArancelariaConSusArticulos(articulos, posicionesArancelarias);
					break;
					case 4: // Alta - Baja - Modificacion [Articulo]
						controller_ABMArticulo(articulos, posicionesArancelarias);
					break;
					case 5: // Alta - Baja - Modificacion [Posicion Arancelaria]
						controller_ABMPosicionArancelaria(posicionesArancelarias, articulos);
					break;
					case 6: // Ver información - Modificar información [Transporte Aereo]
						controller_subMenuTransporteAereo(&transporteAereo);
					break;
					case 7: // Ver información - Modificar información [Transporte Maritimo]
						controller_subMenuTransporteMaritimo(&transporteMaritimo);
					break;
					case 8: // Informe costo final por Transportes
						controller_subMenuInforme(articulos, posicionesArancelarias, &transporteAereo, &transporteMaritimo);
					break;
					case 9: // Buscar Posicion Arancelaria por Nomenclador y Listar Articulos
						controller_listarArticulosPorBusquedaPorNomenclador(articulos, posicionesArancelarias, &transporteAereo, &transporteMaritimo);
					break;
					case 10:
					break;
					case 11:
					break;
					case 12:
					break;
					case 13:
					break;
					case 14:
					break;
				}
			}
		}while(opcion != OPCION_SALIR);
	}
	return EXIT_SUCCESS;
}
