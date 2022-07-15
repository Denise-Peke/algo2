#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


#define VACIO 0
#define ERROR 0
#define ERROR_1 NULL

lista_t *lista_crear()
{
	return calloc(1,sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{	
        if(!lista)
		return NULL;
	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo){
		return ERROR_1;
	}
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = NULL;
	if(lista_tamanio(lista)!=VACIO){
		lista->nodo_fin->siguiente = nuevo_nodo;
	}else{
		lista->nodo_inicio = nuevo_nodo;	
	}
	lista->nodo_fin = nuevo_nodo;
	(lista->cantidad)++;
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if(!lista)
		return ERROR_1;
	if((lista_tamanio(lista)==VACIO)||(posicion>(lista_tamanio(lista))-1))
		return lista_insertar(lista, elemento);
	nodo_t *nodo_agregado = malloc(sizeof(struct nodo));
	if(!nodo_agregado)
		return ERROR_1;
	nodo_agregado->elemento = elemento;
	if(posicion == 0){
		nodo_agregado->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_agregado;
		(lista->cantidad)++;
		return lista;
	}
	nodo_t *auxiliar = lista->nodo_inicio;
	size_t i = 0;
	while(i<(posicion-1)){
		auxiliar = auxiliar->siguiente;
		i++;
	}
	nodo_t *auxiliar_2 = auxiliar;
	auxiliar = (auxiliar->siguiente);
	(auxiliar_2->siguiente) = nodo_agregado;
	nodo_agregado->siguiente = auxiliar;
	(lista->cantidad)++;
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if((!lista)||(lista->cantidad)==0)
		return ERROR_1;
	void *elemento = lista->nodo_fin->elemento;
	if(lista_tamanio(lista) == 1){
		free(lista->nodo_inicio);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		(lista->cantidad)--;
		return elemento;
	}
	nodo_t *auxiliar = lista->nodo_inicio;
	int i = 0;
	while(i<(lista_tamanio(lista)-2)){
		auxiliar = auxiliar->siguiente;
		i++;
	}
	free(lista->nodo_fin);
	lista->nodo_fin = auxiliar;
	auxiliar->siguiente = NULL;
	(lista->cantidad)--;
	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if((!lista)||(lista_tamanio(lista) == VACIO))
		return ERROR_1;
	nodo_t *auxiliar = lista->nodo_inicio;
	if(posicion >= (lista_tamanio(lista))-1)
		return lista_quitar(lista);
	if(posicion==0){
		void *elemento = auxiliar->elemento;
		lista->nodo_inicio = auxiliar->siguiente;
		free(auxiliar);
		(lista->cantidad)--;
		return elemento;
	}
	int i = 1;
	while(i<(posicion)){
		auxiliar = auxiliar->siguiente;
		i++;
	}
	nodo_t *auxiliar_2 = auxiliar->siguiente;
	void *elemento = auxiliar_2->elemento;
	auxiliar->siguiente = auxiliar_2->siguiente;
	free(auxiliar_2);
	(lista->cantidad)--;
	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if((!lista)||(posicion>=(lista_tamanio(lista))))
		return ERROR_1;
	nodo_t *auxiliar = lista->nodo_inicio;
	int i = 0;
	while (i<posicion){
		auxiliar = auxiliar->siguiente;
		i++;
	}
	return (auxiliar->elemento);
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if((!lista)||(!comparador))
		return ERROR_1;
	struct nodo *auxiliar = lista->nodo_inicio;
	while(auxiliar){
		if(comparador(auxiliar->elemento,contexto)==0){
			return auxiliar->elemento;
	        }
		auxiliar=auxiliar->siguiente;
	}
	return ERROR_1;
}

void *lista_primero(lista_t *lista)
{
	if((!lista)||(lista_tamanio(lista)==VACIO)){
		return ERROR_1;
	}
	return lista->nodo_inicio->elemento;	
}

void *lista_ultimo(lista_t *lista)
{
	if((!lista)||(lista_tamanio(lista)==VACIO)){
		return ERROR_1;
	}
	return lista->nodo_fin->elemento;	
}

bool lista_vacia(lista_t *lista)
{
	return ((!lista)||(lista_tamanio(lista) == VACIO));
}

size_t lista_tamanio(lista_t *lista)
{
	if(!lista){
		return (size_t)ERROR;
	}
	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista,NULL);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if(!lista){
		return;
	}
	if(lista_tamanio(lista)==VACIO){
		free(lista);
		return;
	}	
	while(lista->nodo_inicio){
	        struct nodo *auxiliar=lista->nodo_inicio->siguiente;
		if(funcion)
			funcion(lista->nodo_inicio->elemento); 
		free(lista->nodo_inicio);
		lista->nodo_inicio = auxiliar;
		lista->cantidad--;
	}
	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if(!lista)
		return ERROR_1;

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador)
		return NULL;
	iterador->corriente = lista->nodo_inicio;
	iterador->lista = lista;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if(!iterador){
		return false;
	}
	return (iterador->corriente);
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if((!iterador) || (!iterador->corriente))
		return false;
	iterador->corriente = iterador->corriente->siguiente;
	return (iterador->corriente);
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if((!iterador)||(!iterador->corriente))
		return ERROR_1;
	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
    if((!lista)||(!funcion)||(lista_tamanio(lista)==VACIO))
		return ERROR;
	int contador = 0;
	nodo_t *auxiliar = lista->nodo_inicio;
	bool avanzar = true;
	while(auxiliar && avanzar){
		avanzar = funcion(auxiliar->elemento, contexto);
		contador++;
		auxiliar = auxiliar->siguiente;
	}
	return (size_t)contador;
}
