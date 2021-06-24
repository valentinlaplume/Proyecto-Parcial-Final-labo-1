#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "laplume.h"

#include "Parser.h"
#include "Serializer.h"

#include "PosicionArancelaria.h"

// CONSTRUCTORES

/* \brief Reserva espacio en memoria para una Posicion Arancelaria
 * \param void
 * \return PosicionArancelaria* [direccion de memoria] si obtuvo memoria, [NULL] si no hay mas memoria
 */
PosicionArancelaria* posicionArancelaria_new(void)
{
	return (PosicionArancelaria*)malloc(sizeof(PosicionArancelaria));
}
/* \brief Valida los campos y convierte al tipo de dato que corresponda en cada campo, y los carga en una variable PosicionArancelaria
 * \param (int idPosicionArancelaria, char* nomenclador, float porcentajeSeguro,
		  float porcentajeImportacion, float porcentajeTasaEstadistica, int tipoLicencia)
 * \return PosicionArancelaria* Retorna puntero a la PosicionArancelaria cargado
 */
PosicionArancelaria* posicionArancelaria_newParam(int idPosicionArancelaria, char* nomenclador, float porcentajeSeguro,
		                                          float porcentajeImportacion, float porcentajeTasaEstadistica, int tipoLicencia)
{
	PosicionArancelaria* pPosicionArancelaria = posicionArancelaria_new();
	if(pPosicionArancelaria != NULL && nomenclador != NULL )
	{
		if(posicionArancelaria_setIdPosicionArancelaria(pPosicionArancelaria, idPosicionArancelaria)         < 0 ||
		   posicionArancelaria_setNomenclador(pPosicionArancelaria, nomenclador)                             < 0 ||
		   posicionArancelaria_setPorcentajeSeguro(pPosicionArancelaria, porcentajeSeguro)                   < 0 ||
		   posicionArancelaria_setPorcentajeImportacion(pPosicionArancelaria, porcentajeImportacion)         < 0 ||
		   posicionArancelaria_setPorcentajeTasaEstadistica(pPosicionArancelaria, porcentajeTasaEstadistica) < 0 ||
		   posicionArancelaria_setTipoLicencia(pPosicionArancelaria, tipoLicencia)                           < 0 ) // aca van los set
		{
			posicionArancelaria_delete(pPosicionArancelaria);
			pPosicionArancelaria = NULL;
		}
	}
	return pPosicionArancelaria;
}

//******************************************************************************** DESTRUCTOR
/* \brief Libera el espacio reservado en memoria para una Posicion Arancelaria
 * \param this PosicionArancelaria*
 * \return void
 */
int posicionArancelaria_delete(PosicionArancelaria* this)
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
/** \brief Valida un ID y lo carga en la variable PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param idPosicionArancelaria int
 * \return int  -1 error, 0 si ok
 */
int posicionArancelaria_setIdPosicionArancelaria(PosicionArancelaria* this, int idPosicionArancelaria)
{
	int retorno = -1;
	if(this != NULL && isValidIdPosicionArancelaria(idPosicionArancelaria) )
	{
		this->idPosicionArancelaria = idPosicionArancelaria;
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene Id PosicionArancelaria del PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna Id PosicionArancelaria si ok
 */
int posicionArancelaria_getIdPosicionArancelaria(PosicionArancelaria* this,int* flagError)
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
/** \brief Valida un id
 * \param int id)
 * \return int retorna 1 si es valido, 0 no es valido
 */
int isValidIdPosicionArancelaria(int idPosicionArancelaria)
{
	int retorno = 0;
	if(idPosicionArancelaria >= 0 )
	{
		retorno = 1;
	}
	return retorno;
}
//-----------------------------------------------------------------------------
/** \brief Valida un nomenclador y lo carga en la variable PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param nomenclador char*
 * \return int  -1 error, 0 si ok
 */
int posicionArancelaria_setNomenclador(PosicionArancelaria* this, char* nomenclador)
{
	int retorno = -1;
	if(this != NULL && nomenclador != NULL && isValidNomenclador(nomenclador) )
	{
		strcpy(this->nomenclador,nomenclador);
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene nomenclador del PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna Nombre si ok
 */
char* posicionArancelaria_getNomenclador(PosicionArancelaria* this,int* flagError)
{
	*flagError = -1;
	char* auxNomenclador= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxNomenclador = this->nomenclador;
		*flagError = 0;
	}
	return auxNomenclador;
}
/** \brief Valida un nomenclador
 * \param nombre char*
 * \return int retorna 1 si es valido, 0 no es valido
 */
int isValidNomenclador(char nomenclador[])
{
	int retorno = 0;
	//int i = 0;
	if(nomenclador != NULL && esTexto(nomenclador))
	{
		retorno = 1;
	}
	return retorno;
}
//-----------------------------------------------------------------------------
/** \brief Valida un porcentajeSeguro y lo carga en la variable PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param porcentajeSeguro float
 * \return int  -1 error, 0 si ok
 */
int posicionArancelaria_setPorcentajeSeguro(PosicionArancelaria* this, float porcentajeSeguro)
{
    int retorno = -1;
    if(this != NULL && isValidPorcentajeSeguro(porcentajeSeguro))
    {
        this->porcentajeSeguro = porcentajeSeguro;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene porcentajeSeguro del PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param flagError int*
 * \return float retorna -1 ERROR, retorna porcentajeSeguro si ok
 */
float posicionArancelaria_getPorcentajeSeguro(PosicionArancelaria* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->porcentajeSeguro;
        *flagError = 0;
    }
    return aux;
}
/** \brief Valida un porcentajeSeguro
 * \param porcentajeSeguro float
 * \return int retorna 1 si es valido, 0 no es valido
 */
int isValidPorcentajeSeguro(float porcentajeSeguro)
{
	int retorno = 0;
	if(porcentajeSeguro >= 0 && porcentajeSeguro < 101)
	{
		retorno = 1;
	}
	return retorno;
}
//-----------------------------------------------------------------------------
/** \brief Valida un porcentajeImportacion y lo carga en la variable PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param porcentajeImportacion float
 * \return int  -1 error, 0 si ok
 */
int posicionArancelaria_setPorcentajeImportacion(PosicionArancelaria* this, float porcentajeImportacion)
{
    int retorno = -1;
    if(this != NULL && isValidPorcentajeImportacion(porcentajeImportacion))
    {
        this->porcentajeImportacion = porcentajeImportacion;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene porcentajeImportacion del PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param flagError int*
 * \return float retorna -1 ERROR, retorna porcentajeImportacion si ok
 */
float posicionArancelaria_getPorcentajeImportacion(PosicionArancelaria* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->porcentajeImportacion;
        *flagError = 0;
    }
    return aux;
}
/** \brief Valida un porcentajeImportacion
 * \param porcentajeImportacion float
 * \return int retorna 1 si es valido, 0 no es valido
 */
int isValidPorcentajeImportacion(float porcentajeImportacion)
{
	int retorno = 0;
	if(porcentajeImportacion >= 0 && porcentajeImportacion < 101)
	{
		retorno = 1;
	}
	return retorno;
}
//-----------------------------------------------------------------------------
/** \brief Valida un porcentajeTasaEstadistica y lo carga en la variable PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param porcentajeTasaEstadistica float
 * \return int  -1 error, 0 si ok
 */
int posicionArancelaria_setPorcentajeTasaEstadistica(PosicionArancelaria* this, float porcentajeTasaEstadistica)
{
    int retorno = -1;
    if(this != NULL && isValidPorcentajeTasaEstadistica(porcentajeTasaEstadistica))
    {
        this->porcentajeTasaEstadistica = porcentajeTasaEstadistica;
        retorno = 0;
    }
    return retorno;
}
/** \brief Obtiene porcentajeTasaEstadistica del PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param flagError int*
 * \return float retorna -1 ERROR, retorna porcentajeTasaEstadistica si ok
 */
float posicionArancelaria_getPorcentajeTasaEstadistica(PosicionArancelaria* this,int* flagError)
{
    *flagError = -1;
    float aux = -1;
    if(this != NULL && flagError != NULL )
    {
    	aux = this->porcentajeTasaEstadistica;
        *flagError = 0;
    }
    return aux;
}
/** \brief Valida un porcentajeTasaEstadistica
 * \param porcentajeTasaEstadistica float
 * \return int retorna 1 si es valido, 0 no es valido
 */
int isValidPorcentajeTasaEstadistica(float porcentajeTasaEstadistica)
{
	int retorno = 0;
	if(porcentajeTasaEstadistica >= 0 && porcentajeTasaEstadistica < 101)
	{
		retorno = 1;
	}
	return retorno;
}
//-----------------------------------------------------------------------------
/** \brief Valida un tipoLicencia y lo carga en la variable PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param tipoLicencia int
 * \return int  -1 error, 0 si ok
 */
int posicionArancelaria_setTipoLicencia(PosicionArancelaria* this, int tipoLicencia)
{
	int retorno = -1;
	if(this != NULL && isValidTipoLicencia(tipoLicencia) )
	{
		this->tipoLicencia = tipoLicencia;
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene tipoLicencia del PosicionArancelaria
 * \param this PosicionArancelaria*
 * \param flagError int*
 * \return int retorna -1 ERROR, retorna porcentajeTasaEstadistica si ok
 */
int posicionArancelaria_getTipoLicencia(PosicionArancelaria* this,int* flagError)
{
	*flagError = -1;
	int auxtipoLicencia = -1;
	if(this != NULL && flagError != NULL )
	{
		auxtipoLicencia = this->tipoLicencia;
		*flagError = 0;
	}
	return auxtipoLicencia;
}
/** \brief Valida un tipoLicencia
 * \param tipoLicencia int
 * \return int retorna 1 si es valido, 0 no es valido
 */
int isValidTipoLicencia(int tipoLicencia)
{
	int retorno = 0;
	if(tipoLicencia == AUTOMATICA || tipoLicencia == NO_AUTOMATICA)
	{
		retorno = 1;
	}
	return retorno;
}
//******************************************************************************** LISTAR
/** \brief Lista una Posicion Arancelaria
 * \param pElement void*
 * \return int 0 si ok, -1 error
 */
int posicionArancelaria_imprimirUnaPosicionArancelaria(void* pElement)
{
	int retorno = -1;
	if(pElement != NULL)
	{
		PosicionArancelaria* pPosicionArancelaria = (PosicionArancelaria*)pElement;

		int idPosicionArancelaria;
		char* nomenclador;
		float porcentajeSeguro;
		float porcentajeImportacion;
		float porcentajeTasaEstadistica;
		int tipoLicencia;
		char tipoDeLicenciaStr[TIPOLICENCIA_LEN];
		int flagErrorA, flagErrorB, flagErrorC, flagErrorD, flagErrorE, flagErrorF;

		// ----------------------------------- Obtengo cada campo -----------------------------------------------
		idPosicionArancelaria = posicionArancelaria_getIdPosicionArancelaria(pPosicionArancelaria, &flagErrorA);
		nomenclador = posicionArancelaria_getNomenclador(pPosicionArancelaria, &flagErrorB);
		porcentajeSeguro = posicionArancelaria_getPorcentajeSeguro(pPosicionArancelaria, &flagErrorC);
		porcentajeImportacion = posicionArancelaria_getPorcentajeImportacion(pPosicionArancelaria, &flagErrorD);
		porcentajeTasaEstadistica = posicionArancelaria_getPorcentajeTasaEstadistica(pPosicionArancelaria, &flagErrorE);
		tipoLicencia = posicionArancelaria_getTipoLicencia(pPosicionArancelaria, &flagErrorF);
		// ------------------------------------------------------------------------------------------------------
		if(!flagErrorA && !flagErrorB && !flagErrorC && !flagErrorD && !flagErrorE && !flagErrorF &&
		   !posicionArancelaria_obtenerCadenaPorTipoLicencia(tipoLicencia, tipoDeLicenciaStr))
		{
			posicionArancelaria_encabezado(); // Imprimo encabezado
			printf("\n %-10d %-20s %-20.2f %-20.2f %-25.2f %-25s",idPosicionArancelaria,nomenclador,porcentajeSeguro,
					                                porcentajeImportacion,porcentajeTasaEstadistica,tipoDeLicenciaStr);
			retorno = 0;
		}

	}
	return retorno;
}

/** \brief print encabezado al listar
 * \param void
 * \return void
 */
void posicionArancelaria_encabezado(void)
{
	char idPosicionArancelaria[] = {"ID [P.A]"};
	char nomenclador[] = {"NOMENCLADOR"};
	char porcentajeSeguro[] = {"% SEGURO"};
	char porcentajeImportacion[] = {"% IMPORTACION"};
	char porcentajeTasaEstadistica[] = {"% TASA ESTADISTICA"};
	char tipoLicencia[] = {"TIPO DE LICENCIA"};

	//printf("\n\x1b[34m ----------------------------------------------------------------------------------------------------------------------------------  \x1b[0m");
	printf("\n \x1b[40m\x1b[32m%-10s %-20s %-20s %-20s %-25s %-25s\x1b[0m\x1b[0m ", idPosicionArancelaria,
																							nomenclador,
																							porcentajeSeguro,
																							porcentajeImportacion,
																							porcentajeTasaEstadistica,
																							tipoLicencia);
}
/** \brief Lista todos las Posiciones Arancelarias
 * \param ListaPosicionesArancelarias LinkedList*
 * \return int 0 si ok, -1 error
 */
int posicionArancelaria_imprimirPosicionesArancelarias(LinkedList* ListaPosicionesArancelarias)
{
	int retorno = -1;
	void* pPosicionArancelaria;

	if(ListaPosicionesArancelarias != NULL)
	{
		pPosicionArancelaria = (PosicionArancelaria*)ll_getNext(ListaPosicionesArancelarias, 1);
		while(pPosicionArancelaria != NULL)
		{
			if(!posicionArancelaria_imprimirUnaPosicionArancelaria(pPosicionArancelaria))
				pPosicionArancelaria = (PosicionArancelaria*)ll_getNext(ListaPosicionesArancelarias, 0);
		}
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene Cadena Por TipoLicencia AUTOMATICA [0] NO_AUTOMATICA[1]
 * \param tipoLicencia int
 * \param opcionObtenida char*
 * \return int 0 si ok, -1 error
 */
int posicionArancelaria_obtenerCadenaPorTipoLicencia(int tipoLicencia, char opcionObtenida[])
{
	int retorno = -1;
	if(opcionObtenida != NULL && (tipoLicencia == AUTOMATICA || tipoLicencia == NO_AUTOMATICA))
	{
		switch(tipoLicencia)
		{
			case AUTOMATICA:
				strncpy(opcionObtenida, "AUTOMÁTICA", TIPOLICENCIA_LEN);
			break;
			case NO_AUTOMATICA:
				strncpy(opcionObtenida, "NO AUTOMÁTICA", TIPOLICENCIA_LEN);
			break;
		}
		retorno = 0;
	}

	return retorno;
}

/* \brief Compara el Nomenclador ingresado con el de todos los elementos
 * \param pElement void*
 * \param codigoIngresadoBuscado void*
 * \return int: 0 si no encontró
 	 	 	    1 si encontró
 */
int funcionCriterio_buscarPorNomenclador(void* pElement, void* nomencladorIngresadoBuscado)
{
	int retorno = 0;
	char* nomencladorAux;
	int flagError;
	if(pElement != NULL && nomencladorIngresadoBuscado != NULL)
	{
		PosicionArancelaria* pPosicionArancelaria = (PosicionArancelaria*)pElement;
		nomencladorAux = posicionArancelaria_getNomenclador(pPosicionArancelaria, &flagError);

		if(!flagError && (strcmp(nomencladorIngresadoBuscado, nomencladorAux) == 0) )
			retorno = 1;
	}
	return retorno;
}
//---------------------------------------------------------------
/* \brief Compara el Tipo Licencia con que sea NO_AUTOMATICA
 * \param pElement void*
 * \return int: 0 si no es NO_AUTOMATICA
 	 	 	    1 si es NO_AUTOMATICA
 */
int funcionCriterio_porTipoLicenciaNoAutomatica(void* pElement)
 {
	 int flagError, tipoLicencia;
	 int retorno = 0;

	 if(pElement != NULL)
	 {
		 tipoLicencia = posicionArancelaria_getTipoLicencia( (PosicionArancelaria*)pElement, &flagError);

		if(!flagError &&
		   tipoLicencia == NO_AUTOMATICA)
		{
			retorno = 1; // TRUE
		}
	 }
	 return retorno;
 }
/* \brief Compara el Tipo Licencia con que sea AUTOMATICA
 * \param pElement void*
 * \return int: 0 si no es AUTOMATICA
 	 	 	    1 si es AUTOMATICA
 */
int funcionCriterio_porTipoLicenciaAutomatica(void* pElement)
 {
	 int flagError, tipoLicencia;
	 int retorno = 0;

	 if(pElement != NULL)
	 {
		 tipoLicencia = posicionArancelaria_getTipoLicencia( (PosicionArancelaria*)pElement, &flagError);

		if(!flagError &&
		   tipoLicencia == AUTOMATICA)
		{
			retorno = 1; // TRUE
		}
	 }
	 return retorno;
 }




