#ifndef INTERFAZ_H_
#define INTERFAZ_H_
#include "src/sala.h"


/*
*
* realiza la impresion y ejecucion del instructivo que se da antes de jugar 
*/
int mostrar_instrucciones_inicio();


/*
* pre-> se tiene en cuenta que el puntero sala no es NULL
* post -> realiza las jugadas del usuario hasta que haya ganado o salido del juego.
*/
void realizar_juego(sala_t *sala);


#endif // INTERFAZ_H_