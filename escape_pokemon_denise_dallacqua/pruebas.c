#include "pa2mm.h"
#include "src/estructuras.h"
#include "src/sala.h"
#include "src/objeto.h"
#include "src/interaccion.h"
#include "src/lista.h"
#include "src/hash.h"
#include "string.h"
#include <stdbool.h>



struct  sala
{
	hash_t *objetos;
	lista_t *interacciones;
	lista_t *objetos_conocidos;
	lista_t *objetos_poseidos;
};

void pruebasCrearObjeto()
{
	pa2m_afirmar(objeto_crear_desde_string(NULL) == NULL,
		     "No puedo crear un objeto a partir de un string NULL");
	pa2m_afirmar(objeto_crear_desde_string("") == NULL,
		     "No puedo crear un objeto a partir de un string vacío");
	pa2m_afirmar(objeto_crear_desde_string("a;b") == NULL,
		     "\"a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;b") == NULL,
		     "\"a;;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;b") == NULL,
		     "\";a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;b;c") == NULL,
		     "\"a;b;c\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;true") == NULL,
		     "\"a;;true\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;false") == NULL,
		     "\";a;false\" no es un string objeto válido");

	struct objeto *objeto1 = objeto_crear_desde_string("nombre;desc;true");
	pa2m_afirmar(objeto1, "\"nombre;desc;true\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto1->nombre, "nombre") == 0, "El nombre del objeto es \"nombre\"");
	pa2m_afirmar(strcmp(objeto1->descripcion, "desc") == 0,
		     "La descripcion del objeto es \"desc\"");
	pa2m_afirmar(objeto1->es_asible == true, "El objeto es asible");

	struct objeto *objeto2 = objeto_crear_desde_string("A;Be;false\n");
	pa2m_afirmar(objeto2, "\"A;Be;false\\n\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto2->nombre, "A") == 0, "El nombre del objeto es \"A\"");
	pa2m_afirmar(strcmp(objeto2->descripcion, "Be") == 0,
		     "La descripcion del objeto es \"Be\"");
	pa2m_afirmar(objeto2->es_asible == false, "El objeto no es asible");

	free(objeto1);
	free(objeto2);
}

void pruebasCrearInteracciones()
{
	pa2m_afirmar(interaccion_crear_desde_string(NULL) == NULL,
		     "No puedo crear una interacción a partir de un string NULL");
	pa2m_afirmar(interaccion_crear_desde_string("") == NULL,
		     "No puedo crear una interacción a partir de un string vacío");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c:d:e") == NULL,
		     "\"a;b;c:d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d") == NULL,
		     "\"a;b;c;d\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d:e") == NULL,
		     "\"a;b;c;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;d:e") == NULL,
		     "\"a;b;_;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;de:f:g") == NULL,
		     "\"a;b;_;de:f:g\" no es un string interacción válido");

	struct interaccion *inter1 = interaccion_crear_desde_string("a;b;c;d:e:f");
	pa2m_afirmar(inter1, "\"a;b;c;d:e:f\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter1->objeto, "a") == 0, "El nombre del objeto es \"a\"");
	pa2m_afirmar(strcmp(inter1->verbo, "b") == 0, "El verbo es \"b\"");
	pa2m_afirmar(strcmp(inter1->objeto_parametro, "c") == 0, "El segundo objeto es \"c\"");
	pa2m_afirmar(inter1->accion.tipo == DESCUBRIR_OBJETO,
		     "El tipo de acción es DESCUBRIR_OBJETO");
	pa2m_afirmar(strcmp(inter1->accion.objeto, "e") == 0, "El objeto de la acción es \"e\"");
	pa2m_afirmar(strcmp(inter1->accion.mensaje, "f") == 0, "El mensaje de la acción es \"f\"");

	struct interaccion *inter2 = interaccion_crear_desde_string("OB;VER;_;m:_:MSG");
	pa2m_afirmar(inter1, "\"OB;VER;_;m:_:MSG\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter2->objeto, "OB") == 0, "El nombre del objeto es \"OB\"");
	pa2m_afirmar(strcmp(inter2->verbo, "VER") == 0, "El verbo es \"VER\"");
	pa2m_afirmar(strcmp(inter2->objeto_parametro, "") == 0, "El segundo objeto es vacío");
	pa2m_afirmar(inter2->accion.tipo == MOSTRAR_MENSAJE,
		     "El tipo de acción es MOSTRAR_MENSAJE");
	pa2m_afirmar(strcmp(inter2->accion.objeto, "") == 0, "El objeto de la acción es vacío");
	pa2m_afirmar(strcmp(inter2->accion.mensaje, "MSG") == 0,
		     "El mensaje de la acción es \"MSG\"");
	
	
	free(inter1);
	free(inter2);
}


void pruebas_crear_sala()
{
	pa2m_afirmar(sala_crear_desde_archivos("/ASD/ASD/", "dasD/sa2asdd") == NULL,
		     "No puedo crear la sala a partír de archivos inexistentes");

	pa2m_afirmar(sala_crear_desde_archivos("", "chanu/int.csv") == NULL,
			     "No puedo crear la sala sin objetos");

	pa2m_afirmar(sala_crear_desde_archivos("chanu/obj.dat", "chanu/vacio.txt") == NULL,
		     "No puedo crear la sala sin interacciones");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");
	size_t cantidad = 9;
	pa2m_afirmar(sala != NULL, "Puedo crear la sala a partir de archivos no vacíos");
	pa2m_afirmar(hash_cantidad(sala->objetos) == cantidad, "Se leyeron 9 objetos");
	pa2m_afirmar(lista_tamanio(sala->interacciones) == cantidad, "Se leyeron 9 interacciones");

	sala_destruir(sala);
}


void pruebas_nombre_objetos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos(NULL, &cantidad) == NULL,
		     "No puedo obtener los nombres de objetos de una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir la lista de nombres a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir la lista de nombres a la sala pasando cantidad no NULL");
	int cantidad_1 = 9;
	pa2m_afirmar(cantidad == cantidad_1, "La cantidad de elementos de la lista coincide con lo esperado");
	
	const char *esperados[] = { "habitacion",    "mesa",  "interruptor", "pokebola", "cajon",
				    "cajon-abierto", "llave", "anillo",	     "puerta" };
	int comparaciones_exitosas = 0;
	int vueltas = 0;
	int i = 0, j=0;
	while(i < cantidad && vueltas < 2){
		if(j > cantidad-1){
			j = 0;
			vueltas++;
		}
		if(strcmp(objetos2[j], esperados[i])==0){
			comparaciones_exitosas++;
			j = 0;
			vueltas = 0;
			i++;
		}
		j++;
	}
	pa2m_afirmar(comparaciones_exitosas == cantidad,
		     "Todos los nombres de objeto son los esperados");
	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}


void pruebas_interacciones()
{
	pa2m_afirmar(sala_es_interaccion_valida(NULL, "hacer", NULL, NULL) == false,
		     "No es válido pedir interacciones de una sala NULL");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala_es_interaccion_valida(sala, NULL, "", "") == false, "No es válida una intearcción con verbo NULL");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "hacer", NULL, "") == false, "No es válida una intearcción con objeto NULL");

	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == true, "Puedo examinar la habitación");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "usar", "llave", "cajon") == true, "Puedo usar la llave en el cajón");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "pokebola", "") == true, "Puedo abrir la pokebola");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "cajon-abierto", "") == true, "Puedo examinar el cajón abierto");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "romper", "todo", "") == false, "No puedo romper todo");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "mesa", "") == false, "No puedo abrir la mesa");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "techo", "") == false, "No puedo examinar el techo");

	sala_destruir(sala);
}

void obtener_objetos_conocidos_de_una_sala_null_y_devuelve_null()
{
	int cantidad =0;
	pa2m_afirmar(sala_obtener_nombre_objetos_conocidos(NULL,&cantidad)==NULL,"no se puede obtener los objetos de una sala nula");
}

void obtener_objetos_conocidos_de_una_sala_valida_y_cantidad_null_me_devuelve_el_vector()
{
	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");
	char** objetos_conocidos = sala_obtener_nombre_objetos_conocidos(sala,NULL);
	pa2m_afirmar(objetos_conocidos!=NULL,"no se puede obtener los objetos de una sala nula");
	free(objetos_conocidos);
	sala_destruir(sala);

}

void obtener_objetos_conocidos_de_una_sala_valida_y_cantidad_valida_me_devuelve_el_vector()
{
	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");
	int cantidad = 0;
	char** objetos_conocidos = sala_obtener_nombre_objetos_conocidos(sala,&cantidad);
	pa2m_afirmar(cantidad == 1 && objetos_conocidos,"se conoce un elemento al iniciar el juego");
	pa2m_afirmar(strcmp(objetos_conocidos[0],"habitacion")==0,"es el objeto correcto");
	free(objetos_conocidos);
	sala_destruir(sala);
}

void prueba_nombre_objetos_conocidos()
{
	obtener_objetos_conocidos_de_una_sala_null_y_devuelve_null();
	obtener_objetos_conocidos_de_una_sala_valida_y_cantidad_null_me_devuelve_el_vector();
	obtener_objetos_conocidos_de_una_sala_valida_y_cantidad_valida_me_devuelve_el_vector();
	
}

void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void* aux)
{
	printf("mensaje de: %s\n",mensaje);
}
void mostrar_mensaje1(const char *mensaje, enum tipo_accion accion, void* aux)
{
	char *hola = aux;
	printf("mensaje de %s: %s\n",hola, mensaje);
}

void prueba_de_interacciones_invalidas()
{
	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "golpear","habitacion","",mostrar_mensaje,NULL)==0,"no se puede golpear una habitacion");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "comer","pokebola","",mostrar_mensaje,NULL)==0,"no se puede comer una pokebola");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir","puerta","",mostrar_mensaje,NULL)==0,"no puedo abrir la puerta");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "usar","llave","puerta",mostrar_mensaje,NULL)==0,"no puedo usar la llave con la puerta que no conozco");
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "transportar","habitacion","",mostrar_mensaje,NULL)==0,"no puedo transportar una habitacion");
	
	sala_destruir(sala);
}

void prueba_de_interacciones_validas()
{
	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");
	int cantidad = 0;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar","habitacion","",mostrar_mensaje1,"habitacion")==2,"se puede examinar una habitacion");
	char **objetos_conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	pa2m_afirmar(cantidad == 3,"vector conocidos: esta la cantidad correcta de cosas conocidas");
	free(objetos_conocidos);
	
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar","mesa","",mostrar_mensaje1,"mesa")==2,"se puede examinar una mesa");
	
	char **objetos_conocidos1 = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	pa2m_afirmar(cantidad == 5,"vector conocidos: esta la cantidad correcta de cosas conocidas");
	free(objetos_conocidos1);
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "cajon","",mostrar_mensaje1,"cajon")==1, "no se pudo abrir cajon sin llave");

	sala_destruir(sala);
}
int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de objetos");
	pruebasCrearObjeto();

	pa2m_nuevo_grupo("Pruebas de creación de interacciones");
	pruebasCrearInteracciones();

	pa2m_nuevo_grupo("Pruebas de creación de sala");
	pruebas_crear_sala();
	
	pa2m_nuevo_grupo("Pruebas del vector de nombres");
	pruebas_nombre_objetos();
	
	pa2m_nuevo_grupo("Pruebas de interacciones");
	pruebas_interacciones();

	pa2m_nuevo_grupo("Pruebas de objetos conocidos");
	prueba_nombre_objetos_conocidos();

	pa2m_nuevo_grupo("pruebas de ejecutar interacciones");
	prueba_de_interacciones_invalidas();
	printf("\n");
	prueba_de_interacciones_validas();
	
	return pa2m_mostrar_reporte();
}
