/*
    Copyright (C) <2021>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __LINKEDLIST
#define __LINKEDLIST
struct Node
{
    void* pElement;
    struct Node* pNextNode;
}typedef Node;

struct LinkedList
{
    Node* pFirstNode;
    int size;
}typedef LinkedList;
#endif

typedef int(*Function)(void*);
typedef float(*FunctionReduceFloat)(void*);
typedef int (*FunctionFilter)(void*, void*);

// ************************************** Funciones agregadas **************************************

// Buscar element por funcion criterio
void* ll_buscarElement_VL(LinkedList* lista, int(*pFuncionCriterio)(void*, void*), void* datoIngresadoBuscado);

// Filter
LinkedList* ll_filter(LinkedList* pListaOriginal, int(*pFuncionCriterio)(void*));

int ll_map(LinkedList* plistaFiltrada, int (*pFuncion)(void*));

// Get mas optimo
void* ll_getNext(LinkedList* this, int isFirst);
//-----------------------------------------------------------------------------------------------------------
int ll_map2(LinkedList* this, Function pFunc);
int ll_filter3(LinkedList * this, Function pFunc);
int ll_reduceInt(LinkedList* this, Function pFunc);
float ll_reduceFloat(LinkedList* this, FunctionReduceFloat pFunc);
int ll_filter2(LinkedList * this, FunctionFilter pFunc, void* arg);
int ll_reduceInt2(LinkedList* this,int (*pFunc)(void*,void*),void* arg);

//Publicas
LinkedList* ll_newLinkedList(void);
int ll_len(LinkedList* this);
Node* test_getNode(LinkedList* this, int nodeIndex);
int test_addNode(LinkedList* this, int nodeIndex,void* pElement);
int ll_add(LinkedList* this, void* pElement);
void* ll_get(LinkedList* this, int index);
int ll_set(LinkedList* this, int index,void* pElement);
int ll_remove(LinkedList* this,int index);
int ll_clear(LinkedList* this);
int ll_deleteLinkedList(LinkedList* this);
int ll_indexOf(LinkedList* this, void* pElement);
int ll_isEmpty(LinkedList* this);
int ll_push(LinkedList* this, int index, void* pElement);
void* ll_pop(LinkedList* this,int index);                           //elimina un elemento (los enlaces a ese elemento) y devuelve un puntero a ese elemento
int ll_contains(LinkedList* this, void* pElement);
int ll_containsAll(LinkedList* this,LinkedList* this2);
LinkedList* ll_subList(LinkedList* this,int from,int to);
LinkedList* ll_clone(LinkedList* this);
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order);
