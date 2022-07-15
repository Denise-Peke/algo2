#include "estructuras.h"
#include "sala.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "objeto.h"
#include "interaccion.h"
#include "lista.h"
#include "hash.h"

#define ELEMENTO_GANADOR "puerta-abierta"
#define MAX_LINEA 1024
#define CANTIDAD_HASH 10

struct  sala
{
	hash_t *objetos;
	lista_t *interacciones;
	hash_t *objetos_conocidos;
	hash_t *objetos_poseidos;
        bool pudo_escapar;
};

struct vector
{
        char **objetos;
        int tamanio;
};



//procedimiento que recibe el archivo que contiene los objetos y un puntero de tipo sala_t.
//devuelve el vector objetos de la sala inicializado con la informacion que hay dentro de archivo. Si este no cumple con el formato de lectura 
//la funcion devuelve NULL
void *leer_archivo_objetos(FILE* f_objetos, sala_t* sala, struct objeto** primer_conocido)
{                  
        char linea[MAX_LINEA];
        int primero = 0;
        char *linea_leida_objetos = fgets(linea,MAX_LINEA,f_objetos);
        while (linea_leida_objetos){
                struct objeto *objeto = objeto_crear_desde_string(linea); 
                if(primero == 0){
                        (*primer_conocido) = objeto;
                } 
                char* clave = objeto->nombre;
                hash_insertar(sala->objetos,clave, objeto, NULL);
                linea_leida_objetos = fgets(linea,MAX_LINEA,f_objetos);
                primero++;
        }
        fclose(f_objetos);
        return (sala->objetos);       
}


//procedimiento que recibe el archivo que contiene las interacciones y un puntero de tipo sala_t.
//devuelve el vector interacciones de la sala inicializado con la informacion que hay dentro de archivo. Si este no cumple con el formato de lectura 
//la funcion devuelve NULL
lista_t *leer_archivo_interacciones(FILE* f_interacciones, lista_t* interacciones)
{
        char linea[MAX_LINEA];
        char *linea_leida_interacciones = fgets(linea,MAX_LINEA,f_interacciones);
        while (linea_leida_interacciones){
                struct interaccion *interaccion = interaccion_crear_desde_string(linea);  
                lista_insertar(interacciones,interaccion);   
                linea_leida_interacciones = fgets(linea,MAX_LINEA,f_interacciones);
        }
	
        fclose(f_interacciones);
        return (interacciones);
}


/*
* pre: Ingresa un puntero de tipo sala_t no nula y un puntero de tipo FILE tambien no nulo
* post: devuelve los campos "objetos", "objetos_conocidos" inicializados del putero sala, retorna la sala si no hubo 
* ningun fallo
*/ 
sala_t *inicializar_hash_objetos(sala_t* sala, FILE* f_objetos)
{
        sala->objetos_conocidos = hash_crear(CANTIDAD_HASH);
        sala->objetos_poseidos = hash_crear(CANTIDAD_HASH);
        sala->objetos = hash_crear(CANTIDAD_HASH);

        if((!sala->objetos_conocidos) || (!sala->objetos_poseidos) || (!sala->objetos)){
                sala_destruir(sala);
                return NULL;
        }

        struct objeto *primer_conocido = NULL;
        sala->objetos = leer_archivo_objetos(f_objetos,sala,&primer_conocido);
        if(primer_conocido)
                if(!hash_insertar(sala->objetos_conocidos, primer_conocido->nombre, primer_conocido,NULL))
                        return NULL;

        if ((!sala->objetos) || (hash_cantidad(sala->objetos)==0)){
                sala_destruir(sala);
                return NULL;
        }
        return sala;
}


/*
* pre: ingresa un puntero de tipo sala_t no nula y un puntero de tipo FILE tambien no nulo
* post: devuelve el campo "interacciones" inicializado del putero sala, retorna la sala si no hubo 
* ningun fallo
*/ 
sala_t *inicializar_lista_interacciones(sala_t* sala, FILE* f_interacciones)
{
        sala->interacciones = lista_crear();
        sala->interacciones = leer_archivo_interacciones(f_interacciones,sala->interacciones);

        if (!sala->interacciones || lista_vacia(sala->interacciones)){
                sala_destruir(sala);
                return NULL;
        }
        return sala;
}


sala_t *sala_crear_desde_archivos(const char* objetos, const char* interacciones)
{
	FILE* f_objetos = fopen(objetos,"r");
        if (!f_objetos) return NULL;

        FILE* f_interacciones = fopen(interacciones,"r");
        if (!f_interacciones){
                fclose(f_objetos);
                return NULL;
        } 
        sala_t *sala = calloc(1,sizeof(sala_t));
        if (!sala) return NULL;
        sala->pudo_escapar = false;
        
        if(!inicializar_hash_objetos(sala, f_objetos) || !inicializar_lista_interacciones(sala, f_interacciones))
                return NULL;
	return sala;
}


/*
* pre: se toma en cuenta que los parametros no van a ser NULL
* post: devuelve true las dos interacciones son iguales, false si son diferentes
*/
bool comparadora(struct interaccion* interaccion_1, struct interaccion* interaccion_2 )
{
        return (strcmp(interaccion_1->verbo,interaccion_2->verbo)==0) &&
        (strcmp(interaccion_1->objeto,interaccion_2->objeto)==0) &&
        (strcmp(interaccion_1->objeto_parametro,interaccion_2->objeto_parametro)==0);
}



bool sala_es_interaccion_valida(sala_t* sala, const char* verbo, const char* objeto1, const char* objeto2)
{

        if ((!sala) || (!verbo) || (!objeto1) || (!objeto2)) return NULL;
        
        struct interaccion auxiliar;
        strcpy(auxiliar.verbo,verbo);
        strcpy(auxiliar.objeto,objeto1);
        strcpy(auxiliar.objeto_parametro,objeto2);

        lista_iterador_t *iterador = lista_iterador_crear(sala->interacciones);
        for(;lista_iterador_tiene_siguiente(iterador);lista_iterador_avanzar(iterador)){
                struct interaccion *obj_iterador = lista_iterador_elemento_actual(iterador);
                if(comparadora(obj_iterador, &auxiliar)){
                        lista_iterador_destruir(iterador);
                        return true;
                }
        }

        lista_iterador_destruir(iterador);
        return false;
}


/*
* pre: la clave ya se tiene en cuenta que es diferente a NULL
* post: devuelve true realizando la insercion de un elemento al vector 
*/
bool insertar_en_vector(const char *clave, void* elem1, void* elem2)
{
        struct objeto *objeto = elem1;
        struct vector *vector = elem2;
        vector->objetos[(vector->tamanio)] = objeto->nombre;
        (vector->tamanio)++;
        return true; 
}


/*
* pre: los parametros se tiene en cuenta que son diferentes a NULL
* post: si no hubo errores (retorna NULL) , va a devolver un vector con los nombres de los elementos
* del hash que se pasa por parametro
*/
char **inicializacion_vector(hash_t *objetos, int *cantidad)
{
        size_t tamanio = hash_cantidad(objetos);
        char **nombres = malloc(sizeof(char*)*((unsigned)tamanio));
        if(tamanio == 0){
                if(cantidad) *cantidad = 0;
                return nombres;
        }
        if(!nombres){
               if(cantidad) (*cantidad) = -1;
                return NULL;
        }
        struct vector vector;
        vector.objetos = nombres;
        vector.tamanio = 0;
        hash_con_cada_clave(objetos,insertar_en_vector,&vector);
        if(cantidad) (*cantidad) = vector.tamanio;
        return vector.objetos;
}

/*
* 
* post: devuelve un vector con los nombres del campo "objetos" de la sala, de lo contrario devuelve NULL
*/
char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
        if (!sala){
                if(!cantidad)
                        return NULL;
                (*cantidad) = -1;
                return NULL;   
        }
        return inicializacion_vector(sala->objetos, cantidad);
}


/*
*  
* post: devuelve un vector con los nombres del campo "objetos_conocidos" de la sala, de lo contrario devuelve NULL
*/
char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
        if(!sala)
                return NULL;
        return inicializacion_vector(sala->objetos_conocidos, cantidad);
}


/*
*  
* post: devuelve un vector con los nombres del campo "objetos_poseidos" de la sala, de lo contrario devuelve NULL
*/
char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
        if(!sala)
                return NULL;
        return inicializacion_vector(sala->objetos_poseidos, cantidad);
}


bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
        if((!sala) || (!nombre_objeto))
                return false;
        struct objeto *objeto = hash_obtener(sala->objetos_conocidos,nombre_objeto);

        if((!objeto)|| (!objeto->es_asible) || (hash_contiene(sala->objetos_poseidos,nombre_objeto)))
                return false;
                
        hash_quitar(sala->objetos_conocidos,nombre_objeto);
        hash_insertar(sala->objetos_poseidos,nombre_objeto, objeto, NULL);

        return true;
}


char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{
        if(!sala || !nombre_objeto) return NULL;

        struct objeto *objeto_conocido = hash_obtener(sala->objetos_conocidos,nombre_objeto);
        if(objeto_conocido) return objeto_conocido->descripcion;
                
        struct objeto *objeto_poseido = hash_obtener(sala->objetos_poseidos,nombre_objeto);
        if(objeto_poseido) return objeto_poseido->descripcion;
        
        return NULL;
}


/*
* pre: los parametros se tiene en cuenta que se pasan diferentes a NULL
* post: devuelve uno si se pudo realizar la eliminacion, cero si hubo algun error
*/
int eliminar_objeto(sala_t *sala, struct interaccion *interaccion)
{
        
        hash_quitar(sala->objetos_conocidos,interaccion->objeto);
        hash_quitar(sala->objetos_poseidos, interaccion->objeto);
        struct objeto *eliminar = hash_quitar(sala->objetos, interaccion->objeto); 
        if(!eliminar) return 0;
        if(eliminar) free(eliminar);
        return 1;
}


/*
* pre: los parametros se tiene en cuenta que se pasan diferentes a NULL
* post: devuelve uno si se pudo realizar el reemplazo, cero si hubo algun error
*/
int reemplazar_objeto(sala_t *sala, struct interaccion *interaccion)
{
        if(hash_contiene(sala->objetos_poseidos,interaccion->objeto) && (hash_contiene(sala->objetos_conocidos,interaccion->objeto_parametro))){
                struct objeto *reemplazo = hash_obtener(sala->objetos, interaccion->accion.objeto);
                if(reemplazo){
                        hash_quitar(sala->objetos_conocidos,interaccion->objeto_parametro);
                        struct objeto* objeto = hash_quitar(sala->objetos, interaccion->objeto_parametro);
                        if(objeto) free(objeto);
                        hash_insertar(sala->objetos_conocidos,interaccion->accion.objeto, reemplazo, NULL);
                }else return 0;
        }else return 0;
        return 1;
}


/*
* pre: los parametros se tiene en cuenta que se pasan diferentes a NULL
* post: devuelve uno si se pudo ejecutar la interaccion dependiendo del tipo de accion o cero si hubo algun error
*/
int ejecutar_interacciones(sala_t *sala, struct interaccion *interaccion, 
                        void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion, void*aux ), void* aux)
{
        if(interaccion->accion.tipo == MOSTRAR_MENSAJE)
                mostrar_mensaje(interaccion->accion.mensaje,MOSTRAR_MENSAJE, aux);

        if(interaccion->accion.tipo == ELIMINAR_OBJETO){    
                if(eliminar_objeto(sala, interaccion)==0) return 0;
                mostrar_mensaje(interaccion->accion.mensaje, ELIMINAR_OBJETO, aux);
        }

        if(interaccion->accion.tipo == DESCUBRIR_OBJETO){     
                struct objeto *objeto = hash_obtener(sala->objetos,interaccion->accion.objeto);
                if(objeto && (!hash_contiene(sala->objetos_conocidos, interaccion->accion.objeto)&&!hash_contiene(sala->objetos_poseidos,interaccion->accion.objeto))){
                        hash_insertar(sala->objetos_conocidos,interaccion->accion.objeto,objeto,NULL);
                        mostrar_mensaje(interaccion->accion.mensaje, DESCUBRIR_OBJETO, aux);
                }else return 0;
        }

        if(interaccion->accion.tipo == REEMPLAZAR_OBJETO){
                if(reemplazar_objeto(sala, interaccion)==0) return 0;
                mostrar_mensaje(interaccion->accion.mensaje, REEMPLAZAR_OBJETO, aux);
        }

        if(interaccion->accion.tipo == ESCAPAR){
                char *clave = ELEMENTO_GANADOR;
                if(hash_contiene(sala->objetos_conocidos,clave)) sala->pudo_escapar = true;
                mostrar_mensaje(interaccion->accion.mensaje, ESCAPAR,aux);
        }
        return 1;
}


/*
* pre: los parametros se tiene en cuenta que se pasan diferentes a NULL
* post: devuelve true si cada campo de la interaccion coicide con los punteros verbo, objeto1 y objeto2; y
* si esta en el campo "objetos_conocidos" o "objetos_poseidos" de la sala
*/
bool coincide_interaccion(sala_t *sala, const char* verbo, const char* objeto1, const char* objeto2, 
                          struct interaccion *interaccion)
{
        return (strcmp(objeto1,interaccion->objeto)==0) &&
        (strcmp(objeto2, interaccion->objeto_parametro)==0) &&
        (strcmp(verbo, interaccion->verbo)==0) && ((hash_contiene(sala->objetos_conocidos,interaccion->objeto)
         )||(hash_contiene(sala->objetos_poseidos,interaccion->objeto)));
}


int sala_ejecutar_interaccion(sala_t* sala, const char* verbo,const char* objeto1, const char* objeto2,
			      void (*mostrar_mensaje)(const char* mensaje, enum tipo_accion accion, void* aux), void* aux)
{
        if((!sala) || (!mostrar_mensaje )) return 0;
        int ejecutadas = 0;
        lista_iterador_t *iterador = lista_iterador_crear(sala->interacciones);

        for (;lista_iterador_tiene_siguiente(iterador); lista_iterador_avanzar(iterador)){
                struct interaccion *interaccion = lista_iterador_elemento_actual(iterador);
                if(coincide_interaccion(sala, verbo, objeto1, objeto2, interaccion)){
                        ejecutadas += ejecutar_interacciones(sala, interaccion, mostrar_mensaje, aux);
                }
        }

        lista_iterador_destruir(iterador);
        return ejecutadas;
}


bool sala_escape_exitoso(sala_t* sala)
{
        if(!sala) return false;
        return sala->pudo_escapar;
}

/*
* pre: El parametro se tiene en cuenta que se pasa diferente a NULL
* post: libera el espacio de memoria del puntero de tipo void pasado por parametro
*/
void destructora(void* elem)
{
	free(elem);
}


void sala_destruir(sala_t* sala)
{

	hash_destruir_todo(sala->objetos, destructora);
	lista_destruir_todo(sala->interacciones, destructora);
	hash_destruir(sala->objetos_poseidos);
	hash_destruir(sala->objetos_conocidos);
	free(sala);	
}
