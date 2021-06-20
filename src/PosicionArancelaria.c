#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "laplume.h"

#include "Parser.h"
#include "Serializer.h"

#include "PosicionArancelaria.h"

PosicionArancelaria* posicionArancelaria_new(void)
{
	return (PosicionArancelaria*)malloc(sizeof(PosicionArancelaria));
}

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

int isValidNomenclador(char nomenclador[])
{
	int retorno = 0;
	//int i = 0;
	if(nomenclador != NULL)
	{
		/*while(nomenclador[i] != '\0')
		{

			if((nomenclador[i] != ' ') && (nomenclador[i] != '.') &&
			   (nomenclador[i] < 'a' || nomenclador[i] > 'z') &&
			   (nomenclador[i] < 'A' || nomenclador[i] > 'Z') &&
			   (nomenclador[i] < '0' || nomenclador [i] > '9'))
			{
				retorno = 0;
			}
			i++;
		}*/
		retorno =1;
	}
	return retorno;
}
//-----------------------------------------------------------------------------
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

int isValidPorcentajeSeguro(float porcentajeSeguro)
{
	int retorno = 0;
	if(porcentajeSeguro > 0 && porcentajeSeguro < 101)
	{
		retorno = 1;
	}
	return retorno;
}
//-----------------------------------------------------------------------------
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

int isValidPorcentajeImportacion(float porcentajeImportacion)
{
	int retorno = 0;
	if(porcentajeImportacion > 0 && porcentajeImportacion < 101)
	{
		retorno = 1;
	}
	return retorno;
}
//-----------------------------------------------------------------------------
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

int isValidPorcentajeTasaEstadistica(float porcentajeTasaEstadistica)
{
	int retorno = 0;
	if(porcentajeTasaEstadistica > 0 && porcentajeTasaEstadistica < 101)
	{
		retorno = 1;
	}
	return retorno;
}
//-----------------------------------------------------------------------------
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
			posicionArancelaria_encabezado();
			printf("\n %-10d %-20s %-20.2f %-20.2f %-25.2f %-25s",idPosicionArancelaria, nomenclador, porcentajeSeguro,
					                                 porcentajeImportacion, porcentajeTasaEstadistica, tipoDeLicenciaStr);
			//printf("\n\x1b[34m ----------------------------------------------------------------------------------------------------------------------------------  \x1b[0m");
			retorno = 0;
		}

	}
	return retorno;
}

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







int posicionArancelaria_imprimirPosicionesArancelarias(LinkedList* ListaPosicionesArancelarias)
{
	int retorno = -1;
	int i, lenListaPosArancelarias;
	void* pPosicionArancelaria;

	if(ListaPosicionesArancelarias != NULL)
	{
		lenListaPosArancelarias = ll_len(ListaPosicionesArancelarias);
		for(i=0; i<lenListaPosArancelarias; i++)
		{
			pPosicionArancelaria = ll_get(ListaPosicionesArancelarias, i);
			if(pPosicionArancelaria != NULL &&
			  !posicionArancelaria_imprimirUnaPosicionArancelaria(pPosicionArancelaria) )
				retorno = 0;
		}
	}
	return retorno;
}

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
