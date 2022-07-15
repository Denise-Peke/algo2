#include "objeto.h"
#include "estructuras.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LEIDOS "%[^;];%[^;];%[^\n]"
#define MAX_DESCRIPCION 1024
#define MAX_FLAG 20
#define CANT_LEIDOS 3
#define IGUALES 0


bool informacion_valida(char flag[MAX_FLAG], char nombre[MAX_NOMBRE], char descripcion[MAX_DESCRIPCION])
{
        return ((strcmp(flag,"true")==0)||(strcmp(flag,"false")==0))&&(strcmp(nombre,"")!=0)
                &&(strcmp(descripcion,"")!=0)&&(strcmp(flag,"")!=0);
}

struct objeto *inicializar_objetos(char nombre[MAX_NOMBRE], char descripcion[MAX_DESCRIPCION],char flag[MAX_FLAG])
{
        struct objeto *objeto = malloc(sizeof(struct objeto));
        if(!objeto)  return NULL;
                
        if(!informacion_valida(flag, nombre, descripcion)){
                free(objeto);
                return NULL;
        }
        strcpy(objeto->nombre,nombre);
        strcpy(objeto->descripcion,descripcion);
        if(strcmp(flag,"true")==IGUALES)
                objeto->es_asible = true;
        else    objeto->es_asible = false;

        return objeto;
}


struct objeto *objeto_crear_desde_string(const char *string)
{
        if((string == NULL)||(strcmp(string,"")==0)){
                return NULL;
        }

	char nombre[MAX_NOMBRE];
        char descripcion[MAX_DESCRIPCION];   
        char flag[MAX_FLAG];
        int leidos = sscanf(string,LEIDOS,nombre,descripcion,flag);       
        if((leidos != CANT_LEIDOS)){
                return NULL;
        }  
        return inicializar_objetos(nombre, descripcion, flag);
}
