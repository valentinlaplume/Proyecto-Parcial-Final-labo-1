#ifndef TRANSPORTEMARITIMO_H_
#define TRANSPORTEMARITIMO_H_

typedef struct
{
	float metrosCubicos;
	float precioContenedor;
}TransporteMaritimo;

TransporteMaritimo* transporteMaritimo_newParam(TransporteMaritimo* pTransporteMaritimo,
		                                        float metrosCubicos, float precioContenedor);

//******************************************************************************** DESTRUCTOR
int transporteMaritimo_delete(TransporteMaritimo* this);

//******************************************************************************** SET - GET - IS VALID
int transporteMaritimo_setMetrosCubicos(TransporteMaritimo* this, float metrosCubicos);
float transporteMaritimo_getMetrosCubicos(TransporteMaritimo* this,int* flagError);
int isValidMetrosCubicos(float metrosCubicos);

int transporteMaritimo_setPrecioContenedor(TransporteMaritimo* this, float precioContenedor);
float transporteMaritimo_getPrecioContenedor(TransporteMaritimo* this,int* flagError);
int isValidPrecioContenedor(float precioContenedor);

// Encabezado
void transporteMaritimo_encabezado(void);
//******************************************************************************** LISTAR
int transporteMaritimo_imprimirTransporteMaritimo(TransporteMaritimo* pTransporteMaritimo);

#endif /* TRANSPORTEMARITIMO_H_ */
