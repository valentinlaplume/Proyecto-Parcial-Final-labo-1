/*
 * utn.h
 *
 *  Created on: 13 abr. 2021
 *      Author: valentinlaplume
 */

#ifndef UTN_H_
#define UTN_H_

int myGets(char cadena[], int longitud); // obtener cadena

int utn_getNumero(int* pResultado,char* mensaje,char* mensajeError, int minimo, int maximo, int reintentos); // int
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError, float minimo, float maximo, int reintentos); //float

int utn_getOpciones(char pResultado[], int longitud, char* mensaje, char* mensajeError, int reintentos);// validar opciones
int utn_getTexto(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos);// texto
int utn_getNombre(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos); //nombre
//int utn_getDescripcion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos); // descrip
int utn_getSexo(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos); //---------sexo
int utn_getAlfanumerico(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos);//-------alfa num
int utn_getTelefono(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos);//---------------telefono
int utn_getCuit(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos);//-------cuit
int utn_getEmail(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos);//--emial
int utn_getFecha(char pResultado[],int longitud,char* mensaje,char* mensajeError,int reintentos);//--fecha


int utn_getChar(char* pResultado,char* pTexto,char* ptextoError, char min, char max, int reintentos); // no terminada

int esNumerica(char str[], int limite);
int esFlotante(char str[], int limite);

int esSoloLetras(char str[]);
int esAlfanumerico(char str[]);
int esTelefono(char str[]);

int esTexto(char str[]);
int esNombre(char str[]);
int esSexo(char str[]);
//int esDescripcion(char* cadena,int longitud);
int esOpciones(char str[]);
int esAlfanumerico(char str[]);
int esCuit(char str[]);
int esEmail(char* cadena);
int esFecha(char* cadena);
int esDni(char str[]);





#endif /* UTN_H_ */
