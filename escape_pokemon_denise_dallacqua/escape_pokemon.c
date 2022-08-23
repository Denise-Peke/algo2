#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaz.h"



int main(int argc, char *argv[])
{
	
	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	if (!sala) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}
	if(mostrar_instrucciones_inicio()==0)
		return 0;
	realizar_juego(sala);
	sala_destruir(sala);

	return 0;
}
