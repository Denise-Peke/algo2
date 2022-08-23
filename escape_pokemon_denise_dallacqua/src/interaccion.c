#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_OBJETO 100
#define MAX_DESCRIPCION 124
#define MAX_MENSAJE 1000
#define MAX_ACCION 100

//Funcion de tipo bool que recibe una variable de tipo char.
//Devuelve true si la variable es la letra 'd','r','e' o 'm' . De lo contrario devuelce false
bool tipo_accion_valida(char tipo_accion)
{             
	return ((tipo_accion =='d') || (tipo_accion =='r') 
		|| (tipo_accion == 'e') || (tipo_accion == 'm')||(tipo_accion == 'g'));
}

//Procedimiento que recibe una variable de tipo char y un puntero a un struct interaccion.
//inicializa el campo "tipo" de la accion dentro del struct interaccion
void inicializar_tipo_accion(char tipo_accion,struct interaccion *interaccion)
{
	if(tipo_accion == 'd')
                interaccion->accion.tipo = DESCUBRIR_OBJETO;
        else if(tipo_accion == 'r')
                interaccion->accion.tipo = REEMPLAZAR_OBJETO;
        else if(tipo_accion == 'e')
                interaccion->accion.tipo = ELIMINAR_OBJETO;
        else if(tipo_accion == 'm')
                interaccion->accion.tipo = MOSTRAR_MENSAJE;
	else if(tipo_accion == 'g')
		interaccion->accion.tipo = ESCAPAR;
	
}

struct interaccion *inicializar_interaccion(char objeto_1[MAX_OBJETO], char verbo[MAX_VERBO], char objeto_2[MAX_OBJETO], char tipo_accion,
						char nombre_objeto[MAX_OBJETO],char mensaje[MAX_MENSAJE])
{

	struct interaccion *interaccion = malloc(sizeof(struct interaccion));
        if(!interaccion)
                return NULL;
	strcpy(interaccion->objeto,objeto_1);
	strcpy(interaccion->verbo,verbo);
	if(strcmp(objeto_2,"_")==0)
		strcpy(interaccion->objeto_parametro,"");
	else strcpy(interaccion->objeto_parametro,objeto_2);
	
	if((strcmp(nombre_objeto,"")==0)){
		free(interaccion);
		return NULL;
	}else if(strcmp(nombre_objeto,"_")==0){
	        strcpy(interaccion->accion.objeto,"");
	}else{
	        strcpy(interaccion->accion.objeto,nombre_objeto);
	}
	inicializar_tipo_accion(tipo_accion,interaccion);
        strcpy(interaccion->accion.mensaje,mensaje);
	return interaccion;
}

struct interaccion *interaccion_crear_desde_string(const char *string)
{
	if((string==NULL) || (strcmp(string,"")==0))
		return NULL;
	

	char objeto_1[MAX_OBJETO];
	char verbo[MAX_VERBO];
	char objeto_2[MAX_OBJETO];
	char accion[MAX_ACCION];
	char tipo_accion;
	char nombre_objeto[MAX_OBJETO];
	char mensaje[MAX_MENSAJE];
	int leidos = sscanf(string,"%[^;];%[^;];%[^;];%[^\n]",objeto_1,verbo,objeto_2,accion);	
	if((leidos != 4))
		return NULL;
	
	if(strcmp(objeto_1,"")==0)
              return NULL;
	
	int leidos_accion = sscanf(accion,"%c:%[^:]:%[^\n]",&tipo_accion,nombre_objeto,mensaje);
	if((leidos_accion != 3))
		return NULL;
	
	if(!tipo_accion_valida(tipo_accion))
		return NULL;

	return inicializar_interaccion(objeto_1, verbo, objeto_2, tipo_accion, nombre_objeto, mensaje);
}