#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utn.h"
#include "Articulo.h"
#include "laplume.h"

//******************************************************************************* CONSTRUCTORES
Articulo* articulo_new(void)
{
	return (Articulo*) malloc(sizeof(Articulo));
}

Articulo* articulo_newParam(int idArticulo, int IdPosicionArancelaria,
		                    char* nombre, char* codigo,char* descripcion,char* paisDeFabricacion,
		                    float fob, float peso, float ancho, float altura, float profundidad)
{
	Articulo* pArticulo = articulo_new();
	if(pArticulo != NULL && codigo != NULL && descripcion != NULL && paisDeFabricacion != NULL)
	{
		if( articulo_setIdArticulo(pArticulo, idArticulo)                          < 0 ||
			articulo_setIdPosicionArancelaria(pArticulo, IdPosicionArancelaria)    < 0 ||
			articulo_setNombre(pArticulo, nombre)                                  < 0 ||
			articulo_setCodigo(pArticulo, codigo)                                  < 0 ||
			articulo_setDescripcion(pArticulo, descripcion)                        < 0 ||
			articulo_setPaisDeFabricacion(pArticulo, paisDeFabricacion)            < 0 ||
			articulo_setFob(pArticulo, fob)                                        < 0 ||
			articulo_setPeso(pArticulo, peso)                                      < 0 ||
			articulo_setAncho(pArticulo, ancho)                                    < 0 ||
			articulo_setAltura(pArticulo, altura)                                  < 0 ||
			articulo_setProfundidad(pArticulo, profundidad)                        < 0)
		{
			printf("\n * Articulo no valido cargado de articulos.csv");
			articulo_delete(pArticulo);
			pArticulo = NULL;
		}
		//	FLAG_CARGUE_ARTICULO = 1;
	}
	return pArticulo;
}

//******************************************************************************** DESTRUCTOR
int articulo_delete(Articulo* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}
//******************************************************************************** GET - SET - IS VALID
int articulo_setIdArticulo(Articulo* this, int idarticulo)
{
	int retorno = -1;
	if(this != NULL && isValidId(idarticulo) )
	{
		this->idArticulo = idarticulo;
		retorno = 0;
	}
	return retorno;
}

int articulo_getIdArticulo(Articulo* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->idArticulo;
		*flagError = 0;
	}
	return auxId;
}
//---------------------------------------------------
int articulo_setIdPosicionArancelaria(Articulo* this, int id)
{
	int retorno = -1;
	if(this != NULL && isValidId(id))
	{
		this->idPosicionArancelaria = id;
		retorno = 0;
	}
	return retorno;
}

int articulo_getIdPosicionArancelaria(Articulo* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId = this->idPosicionArancelaria;
		*flagError = 0;
	}
	return auxId;
}

int isValidId(int id)
{
	int retorno = 0;
	if(id >= 0)
	{
		retorno = 1;
	}
	return retorno;
}
//---------------------------------------------------
int articulo_setNombre(Articulo* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL && isValidNombre(nombre))
	{
		strncpy(this->nombre,nombre,NOMBRE_LEN);
		retorno = 0;
	}
	return retorno;
}

char* articulo_getNombre(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* auxNombre = NULL;
	if(this != NULL && flagError != NULL)
	{
		auxNombre = this->nombre;
		*flagError = 0;
	}
	return auxNombre;
}

int isValidNombre(char* nombre)
{
	int retorno = 0;
	if(nombre != NULL && esNombre(nombre) )
	{
		retorno = 1;
	}
	return retorno;
}

int articulo_setCodigo(Articulo* this, char* Codigo)
{
	int retorno = -1;
	if(this != NULL && Codigo != NULL && isValidCodigo(Codigo) )
	{
		strcpy(this->codigo,Codigo);
		retorno = 0;
	}
	return retorno;
}

char* articulo_getCodigo(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* auxCodigo= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxCodigo = this->codigo;
		*flagError = 0;
	}
	return auxCodigo;
}

int isValidCodigo(char* codigo)
{
	int retorno = 0;
	if(codigo != NULL)
		retorno = esAlfanumerico(codigo);

	return retorno;
}
//---------------------------------------------------
int articulo_setDescripcion(Articulo* this, char* descripcion)
{
	int retorno = -1;
	if(this != NULL && descripcion != NULL && isValidDescripcion(descripcion) )
	{
		strcpy(this->descripcion,descripcion);
		retorno = 0;
	}
	return retorno;
}

char* articulo_getDescripcion(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->descripcion;
		*flagError = 0;
	}
	return aux;
}

int isValidDescripcion(char* descripcion)
{
	int retorno = 0;
	if(descripcion != NULL)
		retorno = esTexto(descripcion);
	return retorno;
}
//---------------------------------------------------
int articulo_setPaisDeFabricacion(Articulo* this, char* paisDeFabricacion)
{
	int retorno = -1;
	if(this != NULL && paisDeFabricacion != NULL && isValidPaisDeFabricacion(paisDeFabricacion) )
	{
		strcpy(this->paisDeFabricacion,paisDeFabricacion);
		retorno = 0;
	}
	return retorno;
}

char* articulo_getPaisDeFabricacion(Articulo* this,int* flagError)
{
	*flagError = -1;
	char* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->paisDeFabricacion;
		*flagError = 0;
	}
	return aux;
}

int isValidPaisDeFabricacion(char* paisDeFabricacion)
{
	int retorno = 0;
	if(paisDeFabricacion != NULL)
		retorno = esNombre(paisDeFabricacion);
	return retorno;
}
//---------------------------------------------------
int articulo_setFob(Articulo* this, float fob)
{
    int retorno = -1;
    if(this != NULL && isValidFob(fob))
    {
        this->fob = fob;
        retorno = 0;
    }
    return retorno;
}

float articulo_getFob(Articulo* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->fob;
        *flagError = 0;
    }
    return aux;
}

int isValidFob(float fob)
{
	int retorno = 0;
	if(fob > 0)
	{
		retorno = 1;
	}
	return retorno;
}
//---------------------------------------------------
int articulo_setPeso(Articulo* this, float peso)
{
    int retorno = -1;
    if(this != NULL && isValidPeso(peso))
    {
        this->peso = peso;
        retorno = 0;
    }
    return retorno;
}

float articulo_getPeso(Articulo* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->peso;
        *flagError = 0;
    }
    return aux;
}

int isValidPeso(float peso)
{
	int retorno = 0;
	if(peso > 0)
	{
		retorno = 1;
	}
	return retorno;
}
//---------------------------------------------------
int articulo_setAltura(Articulo* this, float altura)
{
    int retorno = -1;
    if(this != NULL && isValidAltura(altura))
    {
        this->altura = altura;
        retorno = 0;
    }
    return retorno;
}

float articulo_getAltura(Articulo* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->altura;
        *flagError = 0;
    }
    return aux;
}

int isValidAltura(float altura)
{
	int retorno = 0;
	if(altura > 0)
	{
		retorno = 1;
	}
	return retorno;
}
//---------------------------------------------------
int articulo_setAncho(Articulo* this, float ancho)
{
    int retorno = -1;
    if(this != NULL && isValidAncho(ancho))
    {
        this->ancho = ancho;
        retorno = 0;
    }
    return retorno;
}

float articulo_getAncho(Articulo* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->ancho;
        *flagError = 0;
    }
    return aux;
}

int isValidAncho(float ancho)
{
	int retorno = 0;
	if(ancho > 0)
	{
		retorno = 1;
	}
	return retorno;
}
//---------------------------------------------------
int articulo_setProfundidad(Articulo* this, float profundidad)
{
    int retorno = -1;
    if(this != NULL && isValidProfundidad(profundidad))
    {
        this->profundidad = profundidad;
        retorno = 0;
    }
    return retorno;
}

float articulo_getProfundidad(Articulo* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->profundidad;
        *flagError = 0;
    }
    return aux;
}

int isValidProfundidad(float profundidad)
{
	int retorno = 0;
	if(profundidad > 0)
	{
		retorno = 1;
	}
	return retorno;
}
//---------------------------------------------------

/* \brief Pide id PosicionArancelaria articulo al usuarios
 * \param int* idPosicionArancelaria
 * \return -1 ERROR, 0 si ok
 */
/*int articulo_pedirIdPosicionArancelaria(int* idPosicionArancelaria)
{
	int retorno = -1;
	if(idPosicionArancelaria != NULL )
	{
		if(!utn_getNumero(idPosicionArancelaria,  "\n > Ingrese ID de la Posicion Arancelaria que corresponda"
				                                  "\n > De caso que no exista, ingrese [0] y se le pedira los datos para dar de alta a una nueva Posicion Arancelaria"
				                                  "\n > ",  "\x1b[31m * ERROR \x1b[0m", 0, 99999999, 2))
		{

			retorno = 0;
		}
	}
	return retorno;
}*/


//******************************************************************************** LISTAR
/** \brief Lista un Articulo
 * \param pElement void*
 * \return int 0 si ok, -1 error
 */
int articulo_imprimirUnArticulo(void* pElement)
{
	int retorno = -1;
	if(pElement != NULL)
	{
		Articulo* pArticulo = (Articulo*)pElement;
		int idArticulo;
		int idPosicionArancelaria;
		char* nombre;
		char* codigo;
		char* descripcion;
		char* paisDeFabricacion;
		float peso;
		float fob;
		float altura;
		float ancho;
		float profundidad;
		int flagErrorA, flagErrorB, flagErrorC, flagErrorD, flagErrorE, flagErrorF, flagErrorG,
			flagErrorH, flagErrorI, flagErrorJ, flagErrorK;

		// Obtengo cada campo
		idArticulo = articulo_getIdArticulo(pArticulo, &flagErrorA);
		idPosicionArancelaria = articulo_getIdPosicionArancelaria(pArticulo, &flagErrorB);

		nombre = articulo_getNombre(pArticulo, &flagErrorC);
		codigo = articulo_getCodigo(pArticulo, &flagErrorD);
		descripcion = articulo_getDescripcion(pArticulo, &flagErrorE);
		paisDeFabricacion = articulo_getPaisDeFabricacion(pArticulo, &flagErrorF);

		fob = articulo_getFob(pArticulo, &flagErrorG);
		peso = articulo_getPeso(pArticulo, &flagErrorH);
		ancho = articulo_getAncho(pArticulo, &flagErrorI);
		altura = articulo_getAltura(pArticulo, &flagErrorJ);
		profundidad = articulo_getProfundidad(pArticulo, &flagErrorK);

		if(!flagErrorA && !flagErrorB && !flagErrorC && !flagErrorD && !flagErrorE && !flagErrorF &&
		   !flagErrorG && !flagErrorH && !flagErrorI && !flagErrorJ && !flagErrorK)
		{
			//printf("\n\x1b[34m --------------------------------------------------------------------------------------------------------------------------------------------------------------  \x1b[0m");
			articulo_encabezado();
			printf("\n %-10d %-13d %-15s %-15s %-20s %-15s %-15.2f %-12.2f %-12.2f %-12.2f %-12.2f",idArticulo,idPosicionArancelaria,
																                             nombre,codigo,descripcion,paisDeFabricacion,
																                             fob,peso,ancho,altura,profundidad);
			retorno = 0;
		}

	}
	return retorno;
}
/** \brief print encabezado al listar
 * \param void
 * \return void
 */
void articulo_encabezado(void)
{
	char idArticulo[] = {"ID [A]"};
	char idPosicionArancelaria[] = {"ID [P.A]"};
	char nombre[] = {"NOMBRE"};
	char codigo[] = {"CODIGO"};
	char descripcion[] = {"DESCRIPCIÓN"};
	char paisDeFabricacion[] = {"ORIGEN"};
	char peso[] = {"PESO KG"};
	char fob[] = {"V.FOB [USD]"};
	char altura[] = {"ALTURA"};
	char ancho[] = {"ANCHO"};
	char profundidad[] = {"PROFUNDIDAD"};

	printf("\n \x1b[40m\x1b[37m%-10s %-13s %-15s %-15s %-20s %-15s %-15s %-12s %-12s %-12s %-12s \x1b[0m\x1b[0m ",   idArticulo,idPosicionArancelaria,
																													nombre,codigo,descripcion,paisDeFabricacion,
																													fob,peso,ancho,altura,profundidad);
}
/** \brief Lista todos los Articulos
 * \param listaArticulos LinkedList*
 * \return int 0 si ok, -1 error
 */
int articulo_imprimirArticulos(LinkedList* listaArticulos)
{
	int retorno = -1;
	int i, lenListaArticulos;
	void* pArticulo;

	if(listaArticulos != NULL)
	{
		lenListaArticulos = ll_len(listaArticulos);
		for(i=0; i<lenListaArticulos; i++)
		{
			pArticulo = ll_get(listaArticulos, i);
			if(pArticulo != NULL && !articulo_imprimirUnArticulo(pArticulo))
				retorno = 0;
		}
	}
	return retorno;
}
/* \brief Compara el codigo ingresado con el de todos los elementos
 * \param pElement void*
 * \param codigoIngresadoBuscado void*
 * \return int: 0 si no encontró
 	 	 	    1 si encontró
 */
int funcionCriterio_buscarPorCodigoArticulo(void* pElement, void* codigoIngresadoBuscado)
{
	int retorno = 0;
	char* codigoAux;
	int flagError;
	if(pElement != NULL && codigoIngresadoBuscado != NULL)
	{
		Articulo* pArticulo = (Articulo*)pElement;
		codigoAux = articulo_getCodigo(pArticulo, &flagError);

		if(!flagError && (strcmp(codigoAux, codigoIngresadoBuscado) == 0) )
			retorno = 1;
	}
	return retorno;
}

/* \brief Compara dos Nombres
 * \param this1 void*
 * \param this2 void*
 * \return int -2 ERROR,
 	 	 	 	 	 	  0 si los this son iguales
 	 	 	 	 	 	  1 si thisUno es mayor a thisDos
 	 	 	 	 	 	 -1 si thisUno es menor a thisDos
 */
int funcionCriterio_compararPorNombreArticulo(void* thisUno, void* thisDos)
{
    int retorno= -2;
    char* bufferNombreUno;
    char* bufferNombreDos;
    int flagErrorUno, flagErrorDos;

    if(thisUno != NULL && thisDos != NULL)
    {
    	bufferNombreUno = articulo_getNombre((Articulo*)thisUno, &flagErrorUno);
    	bufferNombreDos = articulo_getNombre((Articulo*)thisDos, &flagErrorDos);

    	if(!flagErrorUno && !flagErrorDos)
    	{
    		if(strcmp(bufferNombreUno, bufferNombreDos) > 0)
    		{
    			retorno = 1;
    		}
    		else
    		{
				if(strcmp(bufferNombreUno, bufferNombreDos) < 0)
				{
					retorno = -1;
				}
    			else
    			{
    				if(strcmp(bufferNombreUno, bufferNombreDos) == 0)
    				{
    					retorno = 0;
    				}
    			}
    		}
    	}
    }
    return retorno;
}
