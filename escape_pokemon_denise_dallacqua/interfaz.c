#include "interfaz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEIDOS "%[^;];%[^;];%[^\n]"
#define MAX_LEN 2000
#define MAX_PALABRA 150
#define IGUALES 0
#define CANCELADO 'n'

/*
* 
* post -> imprimir el archivo con el path pasado por parametro
*/
void print_image(const char *path)
{
	FILE* f_archivo = fopen(path, "r");
        if(!f_archivo)  return;
    	char read_string[MAX_LEN];
 
    	while(fgets(read_string,sizeof(read_string),f_archivo) != NULL)
        	printf("%s",read_string);
	fclose(f_archivo);
}

/*
*
* post-> imprime el archivo "pikachu_salir.txt" de la carpeta archivos
*/
int salir_juego()
{
	print_image("archivos/pikachu_salir.txt");
	printf("\n");
	return 0;
}

/*
* pre -> sala se tiene en cuenta que es diferenta a NULL
* post -> devuelve e impirmir dos vectores que contiene los nombres de los objetos conocidos
*  y poseidos
*/
void mostrar_vector_conocidos(sala_t *sala)
{
	int cantidad = 0;
	char** conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	print_image("archivos/conocidos.txt");
	for (int i = 0; i < cantidad; i++){
		printf("| %s |",conocidos[i]);
	}
	printf("\n");
	printf("\n");
	int cant = 0;
	char**poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cant);
	print_image("archivos/poseidos.txt");
	printf("\n");
	if(cant > 0){
		for (int i = 0; i < cant; i++)
			printf("| %s |",poseidos[i]);
	}
	printf("\n");
	free(conocidos);
	free(poseidos);
}

/*
* funcion para la funcion ejecutar_interacciones que se encuentra en sala.h
*/
void mostrar_mensaje(const char *mensaje, enum tipo_accion accion,void *aux)
{
	printf("mensaje %i: %s\n",accion, mensaje);
	printf("\n");
}


/*
* pre -> todos los punteros se tienen en cuenta que son diferentes a null
* post -> se encanga de la impresion de las interacciones dependiendo de los paremetros 
*/
void cargar_interaccion(char* palabra1,char* palabra2,char* palabra3, sala_t *sala, bool *juego_terminado)
{
	
	if(strcmp(palabra1,"agarrar")==IGUALES){
		if(!sala_agarrar_objeto(sala, (const char*)palabra2))
			printf("%s no se puede agarrar :(\n",palabra2);
		print_image("archivos/pokebola.txt");
		printf("\n");
		return;
	}
	else if(strcmp(palabra1,"describir")==IGUALES){
		char *descripcion = sala_describir_objeto(sala, (const char*)palabra2); 
		if(!descripcion){
			printf("no conocemos este objeto......\n");
			return;
		}
		print_image("archivos/pikachu_describir.txt");
		printf("DESCRIPCION: %s\n",descripcion);
		return;	
	}
	else if(strcmp(palabra1,"salir")==IGUALES&&(strcmp(palabra2,"juego")==IGUALES)){
		*juego_terminado = true;
		salir_juego();
		return;
	}
	else if(strcmp(palabra1,"ayuda")==IGUALES && strcmp(palabra2,"pika")==IGUALES){
		print_image("archivos/pikachu2.txt");
		return;
	}
	if(strcmp(palabra3,"pika")==IGUALES)
		strcpy(palabra3,"");

	if(sala_ejecutar_interaccion(sala, palabra1, palabra2, palabra3, mostrar_mensaje, NULL)==0){
		print_image("archivos/pikachu_advertencia.txt");
		printf("\n");
	}else{
		print_image("archivos/ejecutar.txt");
		printf("\n");
	}
}

/*
* imprime el titulo del juego
*/

void imprimir_titulo()
{
	system("clear");
	printf("\
		########  ######   ######     ###    ########  ######## \n \
                ##       ##    ## ##    ##   ## ##   ##     ## ##       \n \
                ##       ##       ##        ##   ##  ##     ## ##       \n \
                ######    ######  ##       ##     ## ########  ######   \n \
                ##             ## ##       ######### ##        ##       \n \
                ##       ##    ## ##    ## ##     ## ##        ##       \n \
                ########  ######   ######  ##     ## ##        ######## \n");
	printf("\n");
	printf("\
		########   #######  ##    ## ######## ##     ##  #######  ##    ## \n \
		##     ## ##     ## ##   ##  ##       ###   ### ##     ## ###   ## \n \
		##     ## ##     ## ##  ##   ##       #### #### ##     ## ####  ## \n \
		########  ##     ## #####    ######   ## ### ## ##     ## ## ## ## \n \
		##        ##     ## ##  ##   ##       ##     ## ##     ## ##  #### \n \
		##        ##     ## ##   ##  ##       ##     ## ##     ## ##   ### \n \
		##         #######  ##    ## ######## ##     ##  #######  ##    ## \n ");
		printf("\n");
	printf("                       APRETA CUALQUIER LETRA PARA CONTINUAR\n");

}



int mostrar_instrucciones_inicio()
{
	imprimir_titulo();
	char inicio;
	scanf(" %c",&inicio);
	getchar();
	system("clear");
	print_image("archivos/pikachu.txt");	
	printf("continuar? s/n: ");
	scanf(" %c",&inicio);
	getchar();
	system("clear");
	if(inicio == CANCELADO)
		return salir_juego();
	printf("\n");
	print_image("archivos/pikachu2.txt");	
	printf("continuar? s/n: ");
	scanf(" %c",&inicio);
	getchar();
	system("clear");
	if(inicio == CANCELADO)
		return salir_juego();
	system("clear");
	print_image("archivos/instrucciones.txt");
	printf("continuar? s/n: ");
	scanf(" %c",&inicio);
	getchar();
	if(inicio == CANCELADO)
		return salir_juego();
	system("clear");
	print_image("archivos/PIKACHU3.TXT");
	scanf(" %c",&inicio);
	getchar();
	if(inicio == CANCELADO)
		return salir_juego();
	printf("\n");
	return 1;
}

/*
* 
* valida si la linea pasada por el usuario es la correcta
*/
void validar_leidos(int leidos, char *linea, char *palabra1, char* palabra2, char* palabra3)
{
	while(leidos != 3){
		print_image("archivos/pikachu_advertencia.txt");
		printf("\n");
		printf("PON UN COMANDO: ");
		fgets(linea, 300, stdin);
		leidos = sscanf(linea,"%[^ ] %[^ ] %[^\n]\n",palabra1,palabra2,palabra3);
		system("clear");
	}
}


void realizar_juego(sala_t *sala)
{
	bool salir_juego = false;
	char linea[MAX_LEN];
	char palabra1[MAX_PALABRA];
	char palabra2[MAX_PALABRA];
	char palabra3[MAX_PALABRA];

	while(!salir_juego && !sala_escape_exitoso(sala)){
		mostrar_vector_conocidos(sala);
		printf("PON UN COMANDO: ");
		fgets(linea, 300, stdin);
		int leidos = sscanf(linea,"%[^ ] %[^ ] %[^\n]\n",palabra1,palabra2,palabra3);
		system("clear");
		validar_leidos(leidos, linea, palabra1,palabra2,palabra3);
		cargar_interaccion(palabra1,palabra2,palabra3,sala,&salir_juego);
		if(sala_escape_exitoso(sala)){
			system("clear");
			print_image("archivos/pikachu_ganar.txt");
			printf("\n");
		}
	}
}