#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

void creo_una_lista_correctamente_verifico_lista_vacia_si_sus_nodos_son_NULL()
{
        lista_t *lista = lista_crear();
        pa2m_afirmar((lista_vacia(lista)==true),"la lista esta vacia");
        pa2m_afirmar((lista_tamanio(lista)==0),"la lista tiene cantidad cero");
        pa2m_afirmar(lista->nodo_inicio==NULL,"el nodo_inicio es igual a NULL");
        pa2m_afirmar(lista->nodo_fin==NULL,"el nodo_fin es igual a NULL");
        free(lista);
}
void verifico_si_le_paso_una_lista_null_y_elemento_null_a_insertar_lista()
{
        int elemento = 9;
        pa2m_afirmar(lista_insertar(NULL,&elemento)==NULL,"Le paso una lista NULL");
        lista_t *lista_2 = lista_crear();
        int *elemento_2 = NULL;
        lista_insertar(lista_2,elemento_2);
        pa2m_afirmar(lista_elemento_en_posicion(lista_2,0)== NULL,"Le paso un elemento NULL");
        lista_destruir(lista_2);
}
void liberar_elementos(void *elemento)
{
        free(elemento);
}
void le_paso_tres_elementos_a_la_lista_correctamente()
{
        lista_t *lista = lista_crear();
        int elemento = 2;
        int elemento1 = 3;
        lista_insertar(lista,&elemento);
        pa2m_afirmar(lista->cantidad == 1,"Se aniadio la cantidad correcta de elementos");
        pa2m_afirmar(lista->nodo_inicio->elemento == &elemento,"Se aniadio el elemento 1 correctamente");
        lista_insertar(lista,&elemento1);
        pa2m_afirmar(lista->cantidad == 2, "Se aniadio el segundo elemento correctamente");
        pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == &elemento1,"elemento 3 a la segunda posicion");
        pa2m_afirmar(lista->nodo_fin->elemento == &elemento1,"elemento 3 en el nodo final");
        int elemento2 =4;
        lista_insertar(lista,&elemento2);
        pa2m_afirmar(lista->cantidad == 3, "cantidad de elementos igual a 3");
        pa2m_afirmar(lista->nodo_fin->elemento==&elemento2,"El ultimo elemento es el correcto");
        int elemento_3 = 10;
        int elemento_4 = 9;
        lista_insertar_en_posicion(lista,&elemento_3,2);
        pa2m_afirmar(lista->nodo_inicio->siguiente->siguiente->elemento==&elemento_3,"Se posiciono correctamente en la posicion 2 el elemento");
        lista_insertar_en_posicion(lista,&elemento_4,0);
        pa2m_afirmar(lista->nodo_inicio->elemento == &elemento_4, "Se posiciono correctamente en la posicion 0");
        lista_destruir_todo(lista,NULL);
}

void le_paso_una_lista_nula_un_elemento_nulo_a_lista_quitar()
{
        lista_t *lista = NULL;
        pa2m_afirmar(lista_quitar(lista)==NULL,"Le paso una lista NULL");
}
void elimino_el_ulitmo_elemento_de_una_lista()
{
        lista_t *lista = lista_crear();
        int elemento = 9;
        lista_insertar(lista,&elemento);
        pa2m_afirmar(lista_quitar(lista)==&elemento,"SE ELIMINO CORRECTAMENTE");
        pa2m_afirmar(lista->cantidad == 0, "al eliminarse el unico elemento, esa quedo vacia");
        lista_destruir(lista);
}
void elimino_de_una_lista_con_mas_de_un_elemento()
{
        lista_t *lista = lista_crear();
        if(!lista)
                return;
        int elemento_1 = elemento_1 = 1;
        int elemento_2 = 2;
        char elemento_3 = 3;
        lista_insertar(lista,&elemento_1);
        lista_insertar(lista,&elemento_2);
        lista_insertar(lista,&elemento_3);
        pa2m_afirmar(lista->cantidad == 3,"cantidad correcta");
        pa2m_afirmar(lista_quitar_de_posicion(lista,1)==&elemento_2,"Se ha eliminado el elemento de la posicion 2 correctamente");
        pa2m_afirmar(lista_quitar(lista)==&elemento_3,"Se eliminado correctamente de la ultima posicion");
        pa2m_afirmar(lista_tamanio(lista)==1,"Se han eliminado correctamente 2 elementos");
        lista_destruir(lista);
}

void le_paso_una_lista_null_a_las_funciones_restantes_que_me_faltaron_probar()
{
        lista_t *lista = NULL;
        pa2m_afirmar(lista_primero(lista)==NULL,"pasarle una lista null a lista primero");
        pa2m_afirmar(lista_ultimo(lista)==NULL,"pasarle una lista null a lista ultimo");
        pa2m_afirmar(lista_vacia(lista)==true,"le paso una lista null a lista_vacia");
        pa2m_afirmar(lista_tamanio(lista)==0,"se paso una lista null a lista_tamania");
}

int comparar_elemento(void *elemento1, void *elemento2)
{
        if((*((int*)elemento1)) == (*((int*)elemento2)))
                return 0;
        
        return 1;
}

void pruebo_elemento_en_posicion()
{
        lista_t *lista = lista_crear();
        int elemento_1 = 2;
        int elemento_2 = 4;
        int elemento_3 = 5;
        lista_insertar(lista,&elemento_1);
        lista_insertar(lista,&elemento_2);
        lista_insertar(lista,&elemento_3);
        int elemento_4 = 6;
        pa2m_afirmar(lista_buscar_elemento(lista,comparar_elemento,&elemento_2)==&elemento_2,"El elemento buscado es el correcto");
        pa2m_afirmar(lista_buscar_elemento(NULL,comparar_elemento,&elemento_2)==NULL,"Pasar lista null");
        pa2m_afirmar(lista_buscar_elemento(lista,comparar_elemento,&elemento_4)==NULL,"Buscar en una posicion no existente");
        lista_destruir(lista);
}

void inicializo_el_iterador()
{       
        lista_t *lista = lista_crear();
        lista_iterador_t *iterador = lista_iterador_crear(lista);
        pa2m_afirmar(iterador->corriente == NULL,"El corriente de iterador es igual a NULL al inicializarse");
        pa2m_afirmar(iterador->lista == lista,"esta apuntando a la lista correcta");
        pa2m_afirmar(lista_iterador_crear(NULL)== NULL, "no se puede crear un iterador a partir de una lista NULL");
        lista_iterador_destruir(iterador);
        lista_destruir(lista);
}

void itero_en_una_lista_con_elementos_pruebo_las_funciones_booleanas_y_el_elemento_del_corriente()
{
        char elemento_1 = 'g';
        char elemento_2 = 'a';
        char elemento_3 = 'b';
        char elemento_4 = 'c';
        lista_t *lista = lista_crear();
        lista_insertar(lista,&elemento_1);
        lista_insertar(lista,&elemento_2);
        lista_insertar(lista,&elemento_3);
        lista_insertar(lista,&elemento_4);
        lista_iterador_t *iterador = lista_iterador_crear(lista);
        pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==true,"el corriente tiene siguiente");
        pa2m_afirmar(lista_iterador_elemento_actual(iterador)==&elemento_1,"el elemento del corriente en la posicion 0 es g");
        pa2m_afirmar(lista_iterador_avanzar(iterador)==true,"se pudo avanzar");
        pa2m_afirmar(lista_iterador_elemento_actual(iterador)==&elemento_2,"al avanzar ahora el elemento de corriente es a");
        pa2m_afirmar(lista_iterador_avanzar(iterador)==true,"se pudo avanzar al elemento 3");
        pa2m_afirmar(lista_iterador_elemento_actual(iterador)==&elemento_3,"al avanzar ahora el elemento de corriente es b");
        pa2m_afirmar(lista_iterador_avanzar(iterador)==true,"se pudo avanzar al alemento 4");
        pa2m_afirmar(lista_iterador_elemento_actual(iterador)==&elemento_4,"al avanzar ahora el elemento de corriente es c");
        pa2m_afirmar(lista_iterador_avanzar(iterador)==false,"no pudo avanzar mas, no hay mas elemento en la lista");
        lista_iterador_destruir(iterador);
        lista_destruir(lista);
}

void mostrar_pruebas_lista()
{
        pa2m_nuevo_grupo("INCIALIZAR UNA LISTA");
        creo_una_lista_correctamente_verifico_lista_vacia_si_sus_nodos_son_NULL();
        printf("\n");
        pa2m_nuevo_grupo("LISTA INSERTAR");
        verifico_si_le_paso_una_lista_null_y_elemento_null_a_insertar_lista();
        le_paso_tres_elementos_a_la_lista_correctamente();
        printf("\n");
        pa2m_nuevo_grupo("LISTA BORRAR");
        le_paso_una_lista_nula_un_elemento_nulo_a_lista_quitar();
        elimino_el_ulitmo_elemento_de_una_lista();
        elimino_de_una_lista_con_mas_de_un_elemento();
        printf("\n");
        pa2m_nuevo_grupo("LISTA ELEMENTO EN POSICION");
        pruebo_elemento_en_posicion();
        printf("\n");
        pa2m_nuevo_grupo("LISTA BOOLEANOS Y OTRAS FUNCIONES");
        le_paso_una_lista_null_a_las_funciones_restantes_que_me_faltaron_probar();
        printf("\n");
        pa2m_nuevo_grupo("ITERADORES");
        inicializo_el_iterador();
        itero_en_una_lista_con_elementos_pruebo_las_funciones_booleanas_y_el_elemento_del_corriente();

}

void inicializacion_de_la_cola()
{
        cola_t *cola = cola_crear();
        pa2m_nuevo_grupo("COLA INICIALIZACION");
        pa2m_afirmar((cola_vacia(cola)==true),"la cola esta vacia");
        pa2m_afirmar((cola_tamanio(cola)==0),"la cola tiene cantidad cero");
        pa2m_afirmar(cola_frente(cola)==NULL,"el primero de la cola es igual a NULL");
        cola_destruir(cola);
        
}

void funciones_con_una_cola_NULL()
{
        int elemento = 2;
        pa2m_nuevo_grupo("Funciones de cola con una cola NULL y elemento NULL");
        pa2m_afirmar(cola_encolar(NULL,&elemento)==NULL,"No se pudo encolar en una cola NULL");
        pa2m_afirmar(cola_desencolar(NULL)==NULL,"No se pude desencolar en una cola NULL");
        pa2m_afirmar(cola_frente(NULL)==NULL,"no se pudo extraer el primer elemento de una cola null");
        pa2m_afirmar(cola_tamanio(NULL)==0,"No existe el tamanio de una cola NULL");
        pa2m_afirmar(cola_vacia(NULL)==true,"claramente no hay elemento en una cola null");
        cola_t *cola = cola_crear();
        cola_encolar(cola,NULL);
        pa2m_afirmar(cola_frente(cola)==NULL,"el elemento NULL se aniadio correctamente");
        cola_destruir(cola);

}
void funciones_encolar_descolar_de_una_cola_valida()
{
        pa2m_nuevo_grupo("Funciones de encolar y desencolar");
        cola_t *cola = cola_crear();
        int elemento_1 = 3;
        char elemento_2 = 'a';
        char *elemento_3="hola";
        cola_encolar(cola,&elemento_1);
        cola_encolar(cola,&elemento_2);
        cola_encolar(cola,elemento_3);
        printf("se inserto en la cola : 3, a , hola\n");
        pa2m_afirmar(cola_tamanio(cola)==3,"cantidad correcta de elementos al insertar tres elementos de diferentes tipos de dato");
        cola_desencolar(cola);
        pa2m_afirmar(cola_frente(cola)==&elemento_2,"El elemento [3] se desencolo correctamente quedando el de la segunda posicion primero");
        cola_desencolar(cola);
        pa2m_afirmar(cola_frente(cola)==elemento_3,"El elemento 'a' elemento se desencolo correctamente quedando el de la segunda posicion [hola]");
        cola_destruir(cola);

}

void mostrar_pruebas_cola()
{
        inicializacion_de_la_cola();
        funciones_con_una_cola_NULL();
        funciones_encolar_descolar_de_una_cola_valida();

}

void pila_inicializacion()
{
        pila_t *pila = pila_crear();
        pa2m_nuevo_grupo("Pila inicializacion");
        pa2m_afirmar((pila_vacia(pila)==true),"la pila esta vacia");
        pa2m_afirmar((pila_tamanio(pila)==0),"la pila tiene cantidad cero");
        pa2m_afirmar(pila_tope(pila)==NULL,"el tope de la pila es igual a NULL");
        pila_destruir(pila);

}


void funciones_con_una_pila_NULL()
{
        char elemento = 'a';
        pa2m_nuevo_grupo("Funciones de pila con una pila NULL y elemento NULL");
        pa2m_afirmar(pila_apilar(NULL,&elemento)==NULL,"No se pudo apilar en una pila NULL");
        pa2m_afirmar(pila_desapilar(NULL)==NULL,"No se pude desapilar en una pila NULL");
        pa2m_afirmar(pila_tope(NULL)==NULL,"no se pudo extraer el primer elemento de una pila null");
        pa2m_afirmar(pila_tamanio(NULL)==0,"No existe el tamanio de una pila NULL");
        pa2m_afirmar(pila_vacia(NULL)==true,"claramente no hay elemento en una pila null");
        pila_t *pila = pila_crear();
        pila_apilar(pila,NULL);
        pa2m_afirmar(pila_tope(pila)==NULL,"el elemento NULL se aniadio correctamente");
        pila_destruir(pila);

}

void funciones_con_una_pila_valida()
{
        pa2m_nuevo_grupo("Funciones de apilar y desapilar");
        pila_t *pila = pila_crear();
        int elemento_1 = 24;
        char elemento_2 = 'f';
        char *elemento_3="bueno";
        pila_apilar(pila,&elemento_1);
        pila_apilar(pila,&elemento_2);
        pila_apilar(pila,elemento_3);
        printf("se inserto en la cola : 24, f , bueno\n");
        pa2m_afirmar(pila_tamanio(pila)==3,"cantidad correcta de elementos al insertar tres elementos de diferentes tipos de dato");
        pa2m_afirmar(pila_tope(pila)==elemento_3,"el tope es el elemento que se aniadio ultimo, en este caso el string [bueno]");
        pila_desapilar(pila);
        pa2m_afirmar(pila_tope(pila)==&elemento_2,"El elemento [hola] se desapilo correctamente quedando como tope 'f'");
        pila_desapilar(pila);
        pa2m_afirmar(pila_tope(pila)==&elemento_1,"El elemento 'f' elemento se desencolo correctamente quedando como tope [24]");
        pila_destruir(pila);

}
void mostrar_pruebas_pila()
{
        pila_inicializacion();
        funciones_con_una_pila_NULL();
        funciones_con_una_pila_valida();
}

int main(){
        mostrar_pruebas_lista();
        printf("\n");
        mostrar_pruebas_cola();
        printf("\n");
        mostrar_pruebas_pila();
        return pa2m_mostrar_reporte();
}
