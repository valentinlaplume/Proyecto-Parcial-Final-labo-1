/*
 * utn.c
 *
 *  Created on: 13 abr. 2021
 *      Author: valentinlaplume
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

// FUNCIONES STATIC:
static int getInt(int* pResultado);
static int getFloat(float* resultado);

static int getTexto(char resultado[], int limite);
static int getNombre(char resultado[], int limite);
static int getSexo(char resultado[], int limite);
static int getOpciones(char resultado[], int limite);
static int getAlfanumerico(char resultado[], int limite);
//static int getDescripcion(char* pResultado, int longitud);
static int getTelefono(char resultado[], int limite);
static int getCuit(char resultado[], int limite);
static int getEmail(char resultado[], int limite);
static int getFecha(char resultado[], int limite);

/*
\brief obtiene la cadena de forma segura utilizando la funcion 'fgets' y elimina el 'ENTER' de su ultimo indice.
\param char cadena[] es el puntero al array
\param longitud es la longitud hasta donde escribe el array.
\return 0 si obtuvo correctamente la cadena, -1 si no lo obtuvo.
*/
int myGets(char cadena[], int longitud) //
{
	int retorno = -1;
	char bufferString[4096]; // esto es un mamarracho

	if(cadena != NULL && longitud > 0)
	{
		fpurge(stdin);
		if(fgets(bufferString, sizeof(bufferString), stdin) != NULL) // lee hasta lo que es buffer
		{
			if(bufferString[ strnlen(bufferString,sizeof(bufferString)) - 1 ] == '\n')
				bufferString[ strnlen(bufferString,sizeof(bufferString)) - 1] = '\0';

			if(strnlen(bufferString,sizeof(bufferString)) <= longitud)
			{
				strncpy(cadena,bufferString, longitud);
				retorno = 0;
			}
		}
	}
	return retorno;
}
//------------------------------------------------------------
int esDireccion(char str[])
{
	int retorno = 1;
	int i=0;
	if(str != NULL)
	{
		while(str[i] != '\0')
		{
			if((str[i] != ' ') &&
			   (str[i] < 'a' || str[i] > 'z') &&
			   (str[i] < 'A' || str[i] > 'Z') &&
			   (str[i] < '0' || str [i] > '9'))
			{
				retorno = 0;
			}
			i++;
		}
	}
	return retorno;
}
//-----------------------------------------------------------------------ES FECHA
/*
\brief verifica si el valor recibido contiene 1 @ y minimo 1 punto
\param char str[] array con la cadena a ser analizada.
\return 1 si son num o ' ' o un 2 guiones, 0 si no lo son.
*/
int esFecha(char* cadena)
{
    int retorno = 0;
    int i;
    int contadorBarra = 0;
    int contadorGuion = 0;

    if (cadena != NULL)
    {
        for (i= 0; cadena [i] != '\0'; i++){

            if ((cadena [i] < '0' || cadena [i]> '9') &&
				(cadena [i] != '/' || cadena [i] != '-') )
            {
                retorno = 0;
            }
            if (cadena[i]== '-')
            {
            	contadorGuion++;
            }
            if (cadena[i]== '/')
			{
            	contadorBarra++;
			}
            if (contadorGuion==2 || contadorBarra==2 )
            {
                retorno = 1;
            }
        }
    }
    return retorno;
}
/*
\brief De una cadena obtiene el texto de forma seguro
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena
\return Retorna 0 si OK, -1 ERROR.
*/

static int getFecha(char resultado[], int limite)
{
	int retorno = -1;
	char bufferString[4096];

	if(myGets(bufferString, sizeof(bufferString) )==0)
	{
		if( (esFecha(bufferString) == 1) )
		{
			strncpy(resultado, bufferString, limite);
			retorno = 0;
		}
	}

	return retorno;
}
/*\brief Solicita Una fecha al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del texto
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un texto valido
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getFecha(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos)
{
	int retorno = -1;
	char bufferString[4096];
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getFecha(bufferString, longitud)==0) &&
			(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
			(reintentos >= 0) &&
			longitud > 0)
		{
			strncpy(pResultado,bufferString, longitud);
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
//---------------------------------------------------------------------- ES EMAIL
/*
\brief verifica si el valor recibido contiene 1 @ y minimo 1 punto
\param char str[] array con la cadena a ser analizada.
\return 1 si son num o ' ' o un 2 guiones, 0 si no lo son.
*/
int esEmail(char* cadena)
{
    int retorno = 1;
    int i;
    int contadorArroba = 0;
    int contadorPunto = 0;

    if (cadena != NULL){
        for (i= 0; cadena [i] != '\0'; i++){

            if ((cadena [i] < 'a' || cadena [i]> 'z') &&
            	(cadena [i]< 'A' || cadena [i]> 'Z') &&
                (cadena[i]< '0' || cadena[i]>'9') &&
				(cadena [i] != '@') &&
				(cadena[i] != '.'))
            {
                retorno = 0;
            }
            if (cadena[i]== '@')
            {
                contadorArroba++;
            }
            if (cadena[i]== '.')
			{
				contadorPunto++;
			}
            if (contadorArroba!=1 || contadorPunto<1 )
            {
                retorno =0;
            }
        }
    }
    return retorno;
}
/*
\brief De una cadena obtiene el texto de forma seguro
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena
\return Retorna 0 si OK, -1 ERROR.
*/

static int getEmail(char resultado[], int limite)
{
	int retorno = -1;
	char bufferString[4096];

	if(myGets(bufferString, sizeof(bufferString) )==0)
	{
		if( (esEmail(bufferString) == 1) )
		{
			strncpy(resultado, bufferString, limite);
			retorno = 0;
		}
	}

	return retorno;
}
/*\brief Solicita Un email al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del texto
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un texto valido
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getEmail(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos)
{
	int retorno = -1;
	char bufferString[4096];
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getEmail(bufferString, longitud)==0) &&
			(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
			(reintentos >= 0) &&
			longitud > 0)
		{
			strncpy(pResultado,bufferString, longitud);
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
/////////------------------------------------------------------------------------ ES CUIT
/*
\brief verifica si el valor recibido contiene ' ', numeros y 2 guiones '-'.
\param char str[] array con la cadena a ser analizada.
\return 1 si son num o ' ' o un 2 guiones, 0 si no lo son.
*/
int esCuit(char str[])
{
	int retorno = 1;
	int contadorDeGuiones=0;
	int i=0;
	if(str != NULL)
	{
		while(str[i] != 0) // 30-58541245-3
		{
			if((str[2] != '-') && (str[i]<'0' || str[i]>'9') && (str[i] != '-'))
			{
				retorno = 0;
				break;
			}
			if(str[i] == '-')
			{
				contadorDeGuiones++;
			}

			i++;
		}
		if(contadorDeGuiones != 2)
			retorno = 0;
	}
	return retorno;
}
/*
\brief De una cadena obtiene el texto de forma seguro
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena
\return Retorna 0 si OK, -1 ERROR.
*/

static int getCuit(char resultado[], int limite)
{
	int retorno = -1;
	char bufferString[4096];

	if(myGets(bufferString, sizeof(bufferString) )==0)
	{
		if( (esCuit(bufferString) == 1) )
		{
			strncpy(resultado, bufferString, limite);
			retorno = 0;
		}
	}

	return retorno;
}
/*\brief Solicita Un cuit al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del texto
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un texto valido
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getCuit(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos)
{
	int retorno = -1;
	char bufferString[4096];
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getCuit(bufferString, longitud)==0) &&
			(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
			(reintentos >= 0) &&
			longitud > 0)
		{
			strncpy(pResultado,bufferString, longitud);
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief De una cadena obtiene alguna de las opciones pactadas en utn_getCadenaGerenica validandolo
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena
\return Retorna 0 si OK, -1 ERROR.
*/
static int getOpciones(char resultado[], int limite)
{
	int retorno = -1;
	char bufferString[4096];

	if(myGets(bufferString, sizeof(bufferString))==0)
	{
		if( (esOpciones(bufferString) == 1) )
		{
			strncpy(resultado, bufferString, limite);
			retorno = 0;
		}
	}
	return retorno;
}
/*
\brief Verifica si el valor recibido es igual a la cadena generica cargado
\param char str[] array con la cadena a ser analizada.
\return 1 si es igual a alguna de las cadenas, 0 si no es igual.
*/
int esOpciones(char str[])
{
	int retorno = 0;
	char bufferGenerico[10][50] = {"gato", "perro", "raro", "escribi la palabra que vas a validar aca"};
	int i;
	if(str != NULL)
	{
		for(i=0; str[i] != '\0'; i++)
		{
			if(strncmp(&str[i], bufferGenerico[0], sizeof(bufferGenerico)) == 0 ||
			   strncmp(&str[i], bufferGenerico[1], sizeof(bufferGenerico)) == 0	||
			   strncmp(&str[i], bufferGenerico[2], sizeof(bufferGenerico)) == 0 ||
			   strncmp(&str[i], bufferGenerico[3], sizeof(bufferGenerico)) == 0)
			{
				retorno = 1;
			}
		}
	}
	return retorno;
}
/*\brief Solicita que escriba una de las opciones en 'mensaje' al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud de la cadena
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser una cadena valida
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getOpciones(char pResultado[], int longitud, char* mensaje, char* mensajeError, int reintentos)
{
	int retorno = -1;
	char bufferString[4096];
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getOpciones(bufferString, longitud)==0) &&
			(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
			(reintentos >= 0) &&
			longitud > 0 && longitud <= 50) // que el nombre sea menor o igual a 50 caracteres
		{
			strncpy(pResultado,bufferString, longitud);
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief De una cadena obtiene un nombre validandolo
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena
\return Retorna 0 si OK, -1 ERROR.
*/

static int getNombre(char resultado[], int limite)
{
	int retorno = -1;
	char bufferString[4096];

	if(myGets(bufferString, sizeof(bufferString))==0)
	{
		if( (esNombre(bufferString) == 1) )
		{
			strncpy(resultado, bufferString, limite);
			retorno = 0;
		}
	}

	return retorno;
}
/*
\brief verifica si el valor recibido contiene letras,espacios ' ', y si la primer letra es mayuscula.
\param char str[] array con la cadena a ser analizada.
\return 1 si son letras, ' ' o la primer letra de la palabra es mayuscula, 0 si no lo son.
*/
int esNombre(char str[])
{
	int retorno = 1;
	int i;
	if(str != NULL)
	{
		for(i=0; str[i] != '\0'; i++)
		{
			if(i==0 && (str[0] >= 'A' && str[0] <= 'Z'))
				continue;
			if((str[i] != ' ') && (str[i] < 'a' || str[i] > 'z'))
				retorno = 0;
		}
	}
	return retorno;
}
/*\brief Solicita Un nombre al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del nombre
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un texto valido
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getNombre(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos)
{
	int retorno = -1;
	char bufferString[4096];
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getNombre(bufferString, longitud)==0) &&
			(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
			(reintentos >= 0) &&
			longitud > 0) // que el nombre sea menor o igual a 50 caracteres
		{
			strncpy(pResultado,bufferString, longitud);
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief De una cadena obtiene un char validandolo
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena
\return Retorna 0 si OK, -1 ERROR.
*/

static int getSexo(char resultado[], int limite)
{
	int retorno = -1;
	char bufferSexo[2];

	if(myGets(bufferSexo, sizeof(bufferSexo))==0)
	{
		if( (esSexo(bufferSexo) == 1) )
		{
			strncpy(resultado, bufferSexo, limite);
			retorno = 0;
		}
	}

	return retorno;
}
/*
\brief verifica si el valor recibido contiene los char 'f', 'm', 'F' y 'M' de femenino y maculino
\param char str[] array con la cadena a ser analizada.
\return 1 si son 'f', 'm', 'F' o 'M', 0 si no lo son.
*/
int esSexo(char str[])
{
	int retorno = 1;
	int i;
	if(str != NULL)
	{
		for(i=0; str[i] != '\0'; i++)
		{
			if(str[i] != 'f' && str[i] != 'm' && str[i] != 'F' && str[i] != 'M' )
				retorno = 0;
		}
	}
	return retorno;
}
/*\brief Solicita un SEXO al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del char nombre
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un SEXO valido
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getSexo(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos)
{
	int retorno = -1;
	char bufferString[4096];
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getSexo(bufferString, longitud)==0) &&
			(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
			(reintentos >= 0) &&
			longitud > 0 && longitud <= 2) // que el char no sea mayor a 2
		{
			strncpy(pResultado,bufferString, longitud);
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Obtiene un string valido como descripcion
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
/*
static int getDescripcion(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getDescripcion(buffer,sizeof(buffer))==0 &&
    		esDescripcion(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}
*/
/*
 * \brief Verifica si la cadena ingresada es una descripcion valida
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
/*
int esDescripcion(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != '.' && cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ) && (cadena[i] < '0' || cadena[i] > '9' ) )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
*/
/**
 * \brief Solicita una descripcion al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el numero flotante y -1 si no
 *
 */
/*
int utn_getDescripcion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getDescripcion(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief verifica si el valor recibido contiene letras, ' ', y numeros.
\param char str[] array con la cadena a ser analizada.
\return 1 si son letras, ' ' o numeros, 0 si no lo son.
*/
int esAlfanumerico(char str[])
{
	int retorno = 1;
	int i=0;
	if(str != NULL)
	{
		while(str[i] != '\0')
		{
			if((str[i] != ' ') &&
			   (str[i] < 'a' || str[i] > 'z') &&
			   (str[i] < 'A' || str[i] > 'Z') &&
			   (str[i] < '0' || str [i] > '9'))
			{
				retorno = 0;
			}
			i++;
		}
	}
	return retorno;
}
/*
\brief De una cadena obtiene el texto de forma seguro
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena
\return Retorna 0 si OK, -1 ERROR.
*/

static int getAlfanumerico(char resultado[], int limite)
{
	int retorno = -1;
	char bufferString[4096];

	if(myGets(bufferString, sizeof(bufferString) )==0)
	{
		if( (esAlfanumerico(bufferString) == 1) )
		{
			strncpy(resultado, bufferString, limite);
			retorno = 0;
		}
	}

	return retorno;
}
/*\brief Solicita Un texto alfanumerico(ej: un domicilio) al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del texto
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un texto valido
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getAlfanumerico(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos)
{
	int retorno = -1;
	char bufferString[4096];
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getAlfanumerico(bufferString, longitud)==0) &&
			(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
			(reintentos >= 0) &&
			 longitud   > 0)
		{
			strncpy(pResultado, bufferString, longitud);
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief verifica si el valor recibido contiene ' ', numeros y un solo guion '-'.
\param char str[] array con la cadena a ser analizada.
\return 1 si son num o ' ' o un solo guion, 0 si no lo son.
*/
int esTelefono(char str[])
{
	int retorno = 1;
	int contadorDeGuiones=0;
	int i=0;
	if(str != NULL)
	{
		while(str[i] != 0)
		{
			if((str[i] != ' ') && (str[i]<'0' || str[i]>'9') && (str[i] != '-'))
			{
				retorno = 0;
				break;
			}
			if(str[i] == '-')
				contadorDeGuiones++;

			i++;
		}
		if(contadorDeGuiones > 1)
			retorno = 0;
	}
	return retorno;
}
/*
\brief De una cadena obtiene el texto de forma seguro
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena
\return Retorna 0 si OK, -1 ERROR.
*/
static int getTelefono(char resultado[], int limite)
{
	int retorno = -1;
	char bufferString[4096];

	if(myGets(bufferString, sizeof(bufferString) )==0)
	{
		if( (esTelefono(bufferString) == 1) )
		{
			strncpy(resultado, bufferString, limite);
			retorno = 0;
		}
	}

	return retorno;
}
/*\brief Solicita Un numero dee telefono al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del texto
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un texto valido
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getTelefono(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos)
{
	int retorno = -1;
	char bufferString[4096];
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getTelefono(bufferString, longitud)==0) &&
			(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
			(reintentos >= 0) &&
			longitud > 0)
		{
			strncpy(pResultado,bufferString, longitud);
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief verifica si el valor recibido es un texto.
\param char str[] array con la cadena a ser analizada.
\return 1 si ok, 0 si no es texto valido.
*/
int esTexto(char str[])
{
	int retorno = 1;
	int i=0;
	if(str != NULL)
	{
		for(i=0; (str[i] != '\0'); i++)
		{
			if((str[i] != ' ') && (str[i] < '!' || str[i] > '~'))
				retorno = 0;
		}
	}
	return retorno;
}

/*
\brief De una cadena obtiene el texto de forma seguro
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena
\return Retorna 0 si OK, -1 ERROR.
*/

static int getTexto(char resultado[], int limite)
{
	int retorno = -1;
	char bufferString[4096];

	if(myGets(bufferString, sizeof(bufferString) )==0)
	{
		if( (esTexto(bufferString) == 1) )
		{
			strncpy(resultado, bufferString, limite);
			retorno = 0;
		}
	}

	return retorno;
}
/*\brief Solicita Un texto al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del texto
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un texto valido
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getTexto(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos)
{
	int retorno = -1;
	char bufferString[4096];
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getTexto(bufferString, longitud)==0) &&
			(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
			(reintentos >= 0) &&
			longitud > 0)
		{
			strncpy(pResultado,bufferString, longitud);
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief de una cadena verifica si es flotante
\param char str[] cadena a ser verificada
\return Retorna 1 si esflotante, 0 si no lo es.
*/
int esFlotante(char str[], int limite)
{
	int retorno = 1;
	int i = 0;
	int contadorPuntos = 0;

	if(str != NULL)
	{
		for( ; (str[i] < limite) && (str[i] != '\0'); i++)
		{
			if(i==0 && (str[i] == '-' || str[i] == '+') )
				continue;

			if(str[i] < '0' || str [i] > '9' )
			{
				if(str[i] == '.' && contadorPuntos == 0)
					contadorPuntos++;
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}
/*
 * \brief de la una cadena obtiene un flotante. Utiliza la funcion 'atof'
 * \param resultado Puntero al espacio de memoria donde se dejara el flotante
 * \return Retorna 0 si ok, -1 si no pudo transformar la cadena a flotante
 */
static int getFloat(float* resultado) // obtengo el int
{
	int retorno = -1;
	char bufferString[4096];

	if(myGets(bufferString, sizeof(bufferString))==0)
	{
		if( (esFlotante(bufferString, sizeof(bufferString)) == 1) )
		{
			*resultado = atof(bufferString);
			retorno = 0;
		}
	}

	return retorno;
}
/*\brief Solicita un numero flotante al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un operando valido
 * \param reintentos Es la cantidad de reintentos
 * \return Retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError, float minimo, float maximo, int reintentos)
{
	int retorno = -1;
	float bufferFloat;
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getFloat(&bufferFloat)==0) &&
				(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
				(minimo <= maximo) &&
				(reintentos >= 0) &&
				(bufferFloat >= minimo) && (bufferFloat <= maximo))
		{
			*pResultado = bufferFloat;
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief De una cadena transforma a un numero entero con la funcion 'atoi'
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena ya tranformada a entero
\return Retorna 0 si OK, -1 ERROR.
*/
static int getInt(int* pResultado) // obtengo el int
{
	int retorno = -1;
	char bufferString[50];

	if( (pResultado != NULL &&
		myGets(bufferString, sizeof(bufferString))==0) && // acabo de obtener un string
		(esNumerica(bufferString, sizeof(bufferString)) == 1) ) // nos dicee si es numerica, 1 true
	{
		retorno = 0;
		*pResultado = atoi(bufferString);
	}


	return retorno;
}
/*
\brief Verifica si el valor recibido es numerico.
\param Char str[] array con la cadena a ser analizada.
\return Retorna 1 si es numerico, 0 si no lo es.
*/
int esNumerica(char str[], int limite)
{
	int retorno = 1; // es numerica
	int i = 0;

	if(str != NULL && limite > 0)
	{
		for(i=0; (str[i]<limite) && (str[i] != '\0'); i++)
		{
			if((i==0) && (str[i] == '+' || str[i] == '-'))
				continue; // se saltea el if y vuelve a iterar
			if(str[i] < '0' || str [i] > '9' )
			{
				retorno = 0; // no es numerica
				break;
			}
		}
	}
	return retorno;
}
/*\brief Solicita Un numero entero al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser una opcion valida
 * \param reintentos Es la cantidad de reintentos
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getNumero(int* pResultado,char* mensaje,char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getInt(&bufferInt)==0) &&
			(pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) &&
			(minimo <= maximo) &&
			(reintentos >= 0) &&
			(bufferInt >= minimo) && (bufferInt <= maximo))// Una vez que obtuvo el numero entero, me pregunto si está en el rango.
		{
			*pResultado = bufferInt;
			retorno = 0;
			break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief verifica si el valor recibido contiene letras y ' '.
\param char str[] array con la cadena a ser analizada.
\return 1 si son letras o ' ', 0 si no lo son.
*/
int esSoloLetras(char str[])
{
	int retorno = 1;
	int i=0;
	if(str != NULL)
	{
		while(str[i] != '\0')
		{
			if((str[i] != ' ') && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
				retorno = 0;
			i++;
		}
	}
	return retorno;
}
/*
\brief verifica si el valor recibido contiene numeros y '.'.
\param char str[] array con la cadena a ser analizada.
\return 1 si son letras o ' ', 0 si no lo son.
*/
int esDni(char str[])
{
    int retorno=1;
    int i;
    for(i=0; str[i]!='\0';i++)
    {
        if((str[i]<'0' || str[i]>'9') && (str[i]!='.'))
        {
            retorno=0;
            break;
        }
    }
    return retorno;
}
////////////////////////////////////////////////////////////////////////////////////////////
// No está terminada
int utn_getChar(char * pResultado,char* pTexto,char* ptextoError, char min, char max, int reintentos)
{
	int retorno = -1;
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",pTexto);
		fpurge(stdin);
		if(scanf("%c",pResultado) > 0 && pResultado != NULL && pTexto != NULL && ptextoError != NULL && min <= max && reintentos >= 0)
		{
			if((*pResultado) >= min && (*pResultado) <= max)
				{
					retorno = 0;
					break;
				}
				else
				{
					printf("%s",ptextoError);
				} // fin validacion rango de numeros.
		}
	} // fin ciclo for.

	return retorno;
}
/*
void esTarjetaDeCredito(char numeros[])
{
  int n = 0;
  int suma = 0;
  //Ciclo para ir sumando los numeros ya sea multiplicados x2 o con su valor original segun
  //dice el algoritmo de Luhn
  for(int i = 0; i < 16; i++)
  {
    if(i%2 == 0)
    {
      n = (numeros[i] - '0') * 2;
      if(n >= 10)
        n = (n - 10) + 1;
    }
    else
    {
      n = numeros[i]-'0';
    }
    suma = suma + n;
  }
  //Si el resultado es multiplo de 10 entonces la sumatoria es correcta
  if(suma%10 == 0)
  {
    printf("Tarjeta valida %d\n", suma);
  }//%d la usamos para verificar que sean correctos las sumatorias
  else
  {
    printf("Tarjeta invalida %d\n", suma);
  }
}
*/
