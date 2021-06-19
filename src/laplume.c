/*
 * laplume.c
 *
 *  Created on: 1 may. 2021
 *      Author: valentinlaplume
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "laplume.h"

//-----------------------------------Obtener respuesta. si o no
/*
*\brief Muestra un mensaje con dos opciones(si o no), y obtiene respuesta
*\return Retorna un numero entero, opciones: 0 si [SI], 1 si [NO], -1 Error.
*/
int laplume_deseaConfirmar_SioNo()
{
	int retorno = -1;
	int respuesta;
	if(utn_getNumero(&respuesta, "\n * Desea confirmar? [0]Si - [1]NO >  ",
								 "\n- OPCION INVALIDA -\n", 0, 1, 2)==0)
	{  if(respuesta == OPCION_SI)
	   {
			retorno = respuesta;
	   }
	   else
	   {
		   if(respuesta == OPCION_NO)
		   {
			   retorno = respuesta;
		   }
	   }
	}
	return retorno;
}
//-----------------------------------Obtener respuesta. si o no
/*
*\brief Muestra un mensaje con dos opciones(si o no), y obtiene respuesta
*\return Retorna un numero entero, opciones: 0 si [SI], 1 si [NO], -1 Error.
*/
int laplume_SioNo()
{
	int retorno = -1;
	int respuesta;
	if(utn_getNumero(&respuesta, "\n   \x1b[92m[0]SI\x1b[0m - \x1b[91m[1]NO\x1b[0m >  ",
								 "\n- OPCION INVALIDA -\n", 0, 1, 2)==0)
	{  if(respuesta == OPCION_SI)
	   {
			retorno = respuesta;
	   }
	   else
	   {
		   if(respuesta == OPCION_NO)
		   {
			   retorno = respuesta;
		   }
	   }
	}
	return retorno;
}
//-----------------------------------Obtener respuesta. si o no
/*
*\brief Muestra un mensaje y dos opciones(si o no), y obtiene respuesta
*\param mensaje char* mensaje a ser mostrado al usuario
*\return Retorna un numero entero, opciones: 0 si [SI], 1 si [NO], -1 Error.
*/
int laplume_confirmarAccion(char* mensaje)
{
	int retorno = -1;
	int respuesta;

	printf("%s", mensaje);
	if(!utn_getNumero(&respuesta, "\n \x1b[92m  [0]SI\x1b[0m - \x1b[91m[1]NO: \x1b[0m",
								 "\n- OPCION INVALIDA -\n", 0, 1, 2))
	{
		retorno = respuesta;
	}
	return retorno;
}
