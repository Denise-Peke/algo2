#include "src/hash.h"
#include "pa2m.h"
#include <stdlib.h>
#include <stdbool.h>

void creo_un_hash_valido_pasandole_la_cantidad_correcta_me_debe_devolver_el_hash_creado_correctamente_con_la_cantidad_asignada()
{
	size_t cantidad = 20;
	hash_t *hash = hash_crear(cantidad);
	pa2m_afirmar(hash != NULL,"hash con mas de la cantidad correcta: se ha creado correctamente");
	pa2m_afirmar(hash_cantidad(hash)==0,"hash vacio: no tiene elementos al inicializarse");
	hash_destruir(hash);
}

void creo_un_hash_valido_pasandole_menos_de_la_cantidad_minima_me_debe_devolver_un_hash_con_la_cantidad_de_espacios_3()
{
	size_t cantidad = 1;
	hash_t *hash = hash_crear(cantidad);
	pa2m_afirmar(hash != NULL,"hash con menos de la cantidad minima: se ha creado correctamente");
	pa2m_afirmar(hash_cantidad(hash)==0,"hash vacio: no tiene elementos al inicializarse");
	hash_destruir(hash);
}
void quiero_insertar_un_par_valor_clave_en_un_hash_null_me_debe_devolver_null()
{
	char clave = 'S';
	int valor = 10;
	void *anterior = NULL;
	pa2m_afirmar(hash_insertar(NULL, &clave, &valor,anterior)==NULL,"hash null: al querer insertar se devolvio null");
}
void quiero_insertar_un_par_valor_clave_con_clave_nula_en_un_hash_me_debe_devolver_null()
{
	size_t cantidad = 20;
	int valor = 10;
	void *anterior = NULL;
	hash_t *hash = hash_crear(cantidad);
	pa2m_afirmar(hash_insertar(hash, NULL, &valor,&anterior)==NULL,"CLAVE NULL: al querer insertar se devolvio null");
	hash_destruir(hash);
}

void quiero_insertar_en_un_hash_vacio_me_debe_insertar_el_Elemento_correctamente()
{
	size_t cantidad = 20;
	int valor = 10;
	char *clave = "si";
	void *anterior = NULL;
	hash_t *hash = hash_crear(cantidad);
	pa2m_afirmar(hash_insertar(hash, clave, &valor,&anterior)!=NULL,"hash vacio: se inserto correctamente un elemento");
	pa2m_afirmar(hash_cantidad(hash)==1,"hash con un elemento: contiene un elemento");
	pa2m_afirmar(hash_obtener(hash,clave) == &valor,"se ha encontrado el elemento insertado");
	char valor2 = 9;
	hash_insertar(hash, clave, &valor2,&anterior);
	pa2m_afirmar(anterior == &valor,"se ha reemplazado el valor que antes tenia la clave");
	pa2m_afirmar(hash_obtener(hash, clave) == &valor2,"se ha encontrado el elemento insertado y reemplazado");
	pa2m_afirmar(hash_contiene(hash, clave)==true, "hash con elementos: se ha encontrado correctamente la clave insertada");
	hash_destruir(hash);
	
}


void quiero_quitar_un_elemento_mediante_su_clave_de_un_hash_null_me_tiene_que_devolver_null()
{
	char *clave = "si";
	pa2m_afirmar(hash_quitar(NULL,clave)==NULL,"hash nulo: no se pudo quitar de un hash nulo");
}


void quiero_quitar_un_elemento_mediate_una_clave_null_de_un_hash_valido_me_tiene_que_devolver_null()
{
	
	size_t cantidad = 20;
	hash_t *hash = hash_crear(cantidad);
	pa2m_afirmar(hash_quitar(hash,NULL)==NULL,"hash valido: no se pudo quitar con una clave null");
	hash_destruir(hash);

}

void quiero_quitar_un_elemento_mediante_su_clave_de_un_hash_valido_me_debe_devolver_el_elemento_extraido()
{
	size_t cantidad = 20;
	hash_t *hash = hash_crear(cantidad);
	char *clave_1 = "si";
	char *clave_2 = "no";
	char *clave_3 = "fua";
	int elemento_1 = 9;
	int elemento_2 = 10;
	char *hola = "hola";
	void *anterior = NULL;
	hash_insertar(hash,clave_1,&elemento_1,&anterior);
	hash_insertar(hash,clave_2,&elemento_2,&anterior);
	hash_insertar(hash,clave_3,hola,&anterior);
	pa2m_afirmar(hash_cantidad(hash)==3,"se ha insertado correctamente los tres elementos");
	pa2m_afirmar(hash_quitar(hash,clave_2)==&elemento_2,"hash valido: se ha eleminado el elemento correcto");
	pa2m_afirmar(hash_cantidad(hash)==2,"quedaron la cantidad de elementos correctos despues de la extraccion");
	pa2m_afirmar(hash_quitar(hash,clave_3)==hola,"hash valido: se ha eleminado el elemento correcto");
	pa2m_afirmar(hash_cantidad(hash)==1,"quedaron la cantidad de elementos correctos despues de la extraccion");
	pa2m_afirmar(hash_quitar(hash,clave_1)==&elemento_1,"hash valido: se ha eleminado el elemento correcto");
	pa2m_afirmar(hash_cantidad(hash)==0,"quedaron la cantidad de elementos correctos despues de la extraccion");

	
	hash_destruir(hash);

}

void quiero_quitar_un_elemento_mediante_una_clave_que_no_existe_me_debe_devolver_null()
{
	size_t cantidad = 20;
	hash_t *hash = hash_crear(cantidad);
	char *clave_1 = "si";
	char *clave_2 = "no";
	char *clave_3 = "fua";
	int elemento_1 = 9;
	int elemento_2 = 10;
	char *hola = "hola";
	char *clave_4 = "jiji";
	void *anterior = NULL;
	hash_insertar(hash,clave_1,&elemento_1,&anterior);
	hash_insertar(hash,clave_2,&elemento_2,&anterior);
	hash_insertar(hash,clave_3,hola,&anterior);
	pa2m_afirmar(hash_quitar(hash,clave_4)==NULL,"hash con elementos: no se pudo eliminar mediante una clave que no existe");
	hash_destruir(hash);

}

void quiero_quitar_un_elemento_mediante_su_clave_de_un_hash_vacio_me_debe_devolver_false()
{
	size_t cantidad = 20;
	char* clave = "hola";
	hash_t *hash = hash_crear(cantidad);
	pa2m_afirmar(hash_quitar(hash,clave)==false,"hash vacio: no se pudo quitar con una clave que no existe");
	hash_destruir(hash);
}

bool funcion(const char* clave, void* elemento, void* aux)
{
	if(elemento==aux){
		return false;
	}
	return true;
}

void quiero_iterar_en_un_hash_nulo_me_debe_devolver_cero()
{
	int aux = 10;
	pa2m_afirmar(hash_con_cada_clave(NULL,funcion,&aux)==0,"hash nulo: ha devuelto null");
}

void quiero_iterar_en_un_hash_valido_con_una_funcion_nula_me_debe_devolver_cero()
{
	size_t cantidad = 20;
	hash_t *hash = hash_crear(cantidad);
	char *clave_1 = "si";
	char *clave_2 = "no";
	char *clave_3 = "fua";
	int elemento_1 = 9;
	int elemento_2 = 10;
	char *hola = "hola";
	void *anterior = NULL;
	hash_insertar(hash,clave_1,&elemento_1,&anterior);
	hash_insertar(hash,clave_2,&elemento_2,&anterior);
	hash_insertar(hash,clave_3,hola,&anterior);
	int aux = 80;
	pa2m_afirmar(hash_con_cada_clave(hash,NULL,&aux)==0,"hash con elementos y funcion nula: ha devuelto cero, no pudo iterar");
	hash_destruir(hash);
}

void quiero_iterar_en_un_hash_valido_y_me_debe_devolver_la_cantidad_de_veces_que_recorrio_para_haber_cumplido_la_condicion_de_corte()
{
	size_t cantidad = 40;
	hash_t *hash = hash_crear(cantidad);
	char *clave_1 = "si"; //3
	char *clave_2 = "no"; //4
	char *clave_3 = "fua";//1
	int elemento_1 = 9;
	int elemento_2 = 10;
	char *hola = "hola";
	void *anterior = NULL;
	int elemento_4 = 60;//1
	char *clave_4 = "jeje";
	int aux = 109;
	hash_insertar(hash,clave_1,&elemento_1,&anterior);
	hash_insertar(hash,clave_2,&elemento_2,&anterior);
	hash_insertar(hash,clave_3,hola,&anterior);
	hash_insertar(hash,clave_4,&elemento_4,&anterior);
	pa2m_afirmar(hash_con_cada_clave(hash,funcion,&aux)==4,"ha recorrido correctamente");
	hash_destruir(hash);
}


void agrego_mucha_cantidad_de_pares_en_un_hash_valido_debe_insertar_correctamento_todos_los_pares()
{
	printf("20 INSERCIONES EN UN HASH DE CAPACIDAD 5\n");
	size_t capacidad = 5;
	hash_t *hash = hash_crear(capacidad);
	void *anterior = NULL;
	for (int i = 0; i < 20; i++){
		char clave = 'A'+(char)i;
		printf("clave: %c, valor: %i\n",clave,i);
		pa2m_afirmar(hash_insertar(hash,&clave,&i,&anterior)!=NULL,"hash con elementos: Se ha insertado la clave y elemento");
		pa2m_afirmar(hash_obtener(hash, &clave)==&i,"hash con elementos: se ha encontrado el elemento con su respect. clave");
		pa2m_afirmar(hash_cantidad(hash)==i+1,"hash con elementos: la cantidad es la correcta");
		printf("\n");
	}
	pa2m_afirmar(hash_cantidad(hash)==20,"hash rehasheado: el tamanio es el correcto");

	hash_destruir(hash);
}



int main()
{
	pa2m_nuevo_grupo("PRUEBAS DE HASH");
	printf("\n");
	pa2m_nuevo_grupo("INICIALIZACION");
	creo_un_hash_valido_pasandole_la_cantidad_correcta_me_debe_devolver_el_hash_creado_correctamente_con_la_cantidad_asignada();
	creo_un_hash_valido_pasandole_menos_de_la_cantidad_minima_me_debe_devolver_un_hash_con_la_cantidad_de_espacios_3();
	pa2m_nuevo_grupo("INSERTAR");
	quiero_insertar_un_par_valor_clave_en_un_hash_null_me_debe_devolver_null();
	quiero_insertar_un_par_valor_clave_con_clave_nula_en_un_hash_me_debe_devolver_null();
	quiero_insertar_en_un_hash_vacio_me_debe_insertar_el_Elemento_correctamente();
	pa2m_nuevo_grupo("QUITAR");
	quiero_quitar_un_elemento_mediante_su_clave_de_un_hash_null_me_tiene_que_devolver_null();
	quiero_quitar_un_elemento_mediate_una_clave_null_de_un_hash_valido_me_tiene_que_devolver_null();
	quiero_quitar_un_elemento_mediante_su_clave_de_un_hash_vacio_me_debe_devolver_false();
	quiero_quitar_un_elemento_mediante_su_clave_de_un_hash_valido_me_debe_devolver_el_elemento_extraido();
	quiero_quitar_un_elemento_mediante_una_clave_que_no_existe_me_debe_devolver_null();
	pa2m_nuevo_grupo("HASH CON CADA ELEMENTO");
	quiero_iterar_en_un_hash_nulo_me_debe_devolver_cero();
	quiero_iterar_en_un_hash_valido_con_una_funcion_nula_me_debe_devolver_cero();
	quiero_iterar_en_un_hash_valido_y_me_debe_devolver_la_cantidad_de_veces_que_recorrio_para_haber_cumplido_la_condicion_de_corte();
	pa2m_nuevo_grupo("REHASH");
	agrego_mucha_cantidad_de_pares_en_un_hash_valido_debe_insertar_correctamento_todos_los_pares();

	return pa2m_mostrar_reporte();
}
