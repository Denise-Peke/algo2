#include "cola.h"
#include "lista.h"

cola_t *cola_crear()
{
	return (cola_t*)lista_crear();
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	if(!cola){
		return NULL;
	}
	return (cola_t*)lista_insertar((lista_t*)cola,elemento);
}

void *cola_desencolar(cola_t *cola)
{
	if(!cola){
		return NULL;
	}
	return lista_quitar_de_posicion((lista_t*)cola,0);
}

void *cola_frente(cola_t *cola)
{
	if(!cola){
		return NULL;
	}
	void *elemento = lista_elemento_en_posicion((lista_t*)cola, 0);
	return elemento;
}

size_t cola_tamanio(cola_t *cola)
{
	if(!cola){
		return 0;
	}
	return lista_tamanio((lista_t*)cola);
}

bool cola_vacia(cola_t *cola)
{
	return lista_vacia((lista_t*)cola);
}

void cola_destruir(cola_t *cola)
{
	lista_destruir((lista_t*)cola);
}
