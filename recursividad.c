/*
El Profesor Samuel Oak se puso a estudiar la genética de los pokemones para saber si era posible crear nuevas especies.
 Para esto se compró un termociclador de PCR (REACCIÓN EN CADENA DE LA POLIMERASA), pero le vino fallada y no sabe como 
 calcular cuántas especies puede crear con las muestras que tiene. Entonces, como sabe que sos muy bueno programando, te
  pide ayuda para que realices un algoritmo que dado un número de muestras genéticas le devuelva el número de combinaciones posibles.
*/
int calcular_combinaciones_posibles(int muestras_ADN){
    if(muestras_ADN <= 1)
        return 1;
    return (muestras_ADN)*(calcular_combinaciones_posibles(muestras_ADN-1));
}

/*

Misty, fascinada con la belleza de la naturaleza de pueblo Paleta, se puso a observar detalladamente el patrón de las semillas dentro 
de la cabeza de un girasol y noto algo muy interesante, que la secuencia crece en espirales desde el centro hacia afuera. Cada número 
de la secuencia es la suma de los dos anteriores, Misty desea contar sin tener en cuenta esta secuencia y te pide que realices un algoritmo 
que dado un número devuelva la suma de sus anteriores
*/
int calcular_fibonacci(int numero_semillas_girasol){
    if((numero_semillas_girasol == 0)||(numero_semillas_girasol==1))
        return numero_semillas_girasol;

    return (calcular_fibonacci(numero_semillas_girasol -1)+ (calcular_fibonacci(numero_semillas_girasol -2)));
}

/*
Zangoose y Seviper quieren saber quién es más amenazante a la hora de enfrentar a sus enemigos, 
pues la rivalidad que existe entre ellos es bastante chispeante. Por eso, decidieron empezar a llevar 
la cuenta de cuánto daño puede infligir cada uno y comparar sus resultados.

Luego de varias batallas, tienen anotado cuántos golpes dio cada uno en su turno, y cuántos minutos 
tardaron en dar esos golpes. Ahora, sólo les queda averiguar quién logró golpear más veces por minuto al otro, 
para definir de una vez por todas quién es mejor.

Es por esto que te piden un programa que, sabiendo la cantidad de golpes que el rival actual dio y la cantidad de 
minutos que tardó en darlos, devuelva cuánto daño hizo ese rival por minuto.
*/
int calcular_division_sucesiva(int golpes, int minutos){
    if (golpes < minutos)
        return 0;
    return 1 + calcular_division_sucesiva(golpes - minutos, minutos);
}

/*
Brock es muy conocido en Ciudad Plateada y sus alrededores por ser muy enamoradizo. Pero un día, 
luego de conocer a Olivia, decide enviarle un poema de amor. Pero como desea que ella sea la única que lo lea, 
pues no confía en los carteros. Entonces decide escribirlo con todas las palabras al revés.

Ejemplo: HOLA lo escribe ALOH.

Ayuda a la joven Olivia, creando un programa que recibe palabras y las devuelve en el orden correcto. 
Apresúrate, Olivia está ansiosa por leer el poema de Brock.
*/

void invertidor_de_poema_rec(char* poema, char* auxiliar, int posicion_poema, int posicion_aux)
{
    if(posicion_poema == -1){
        auxiliar[posicion_aux]='\0';
        strcpy(poema, auxiliar);
        return;
    }
    auxiliar[posicion_aux]=poema[posicion_poema];
    return invertidor_de_poema_rec(poema, auxiliar, posicion_poema-1, posicion_aux+1);
}

void invertidor_de_poema(char* poema){
    char* auxiliar = malloc(strlen(poema)+1);
    int tope = (int)strlen(poema)-1;
    invertidor_de_poema_rec(poema, auxiliar,tope,0);
}



/*
Ash Ketchum quiere convertirse en Maestro Pokémon, el más alto grado de entrenamiento Pokémon, para lograrlo necesita entrenar a 
sus pokémones en batallas y estar también físicamente en forma, para lograrlo decide seguir el consejo del doctor Proctor, 
hacer sentadillas y la cantidad que debe hacer tiene que ser un números primo. Como a veces se olvida si un número es primo o no, 
te pide ayuda, para que crees un programa en el cual, le diga a Ash si la cantidad de sentadillas que desea realizar es un número primo 
en ese caso la función devolverá cero, y si no lo es, el próximo primo de la cantidad ingresada.
*/

bool es_primo_aux(size_t n, size_t m){
    if(m<2)
        return true;
    if(n%m==0)
        return false;
    return es_primo_aux(n,m-1);
}

bool es_primo(size_t n){
    if(n<2)
        return false;
    return es_primo_aux(n, n-1);
}

int devuelve_siempre_numero_primo_rec(size_t cantidad_ingresada){
    if(es_primo(cantidad_ingresada))
        return (int)cantidad_ingresada;
    return devuelve_siempre_numero_primo_rec(cantidad_ingresada+1);
}

int devuelve_siempre_numero_primo(size_t cantidad_ingresada) {
    if(es_primo(cantidad_ingresada)||cantidad_ingresada<=1)
        return 0;
    return devuelve_siempre_numero_primo_rec(cantidad_ingresada+1);
}

/*

Meowth, que es un Pokémon muy inteligente, se dio cuenta, mientras aprendía a leer, 
que hay palabras que leyéndolas de izquierda a derecha o derecha a izquierda tienen 
el mismo significado y se leen igual. Las tiene escritas en una libreta, pero como no confía qué tan 
bien escribe, te pide que confecciones una función para que le diga si es una palabra palíndromo o no.
*/


bool buscar_polindromo(const char *cadena, size_t inicio, size_t fin){

    if(!cadena)
        return false;
    //Aquí va su código.
    if (inicio >= fin) 
        return true;
    if (cadena[inicio] == cadena[fin])
        return buscar_polindromo(cadena, inicio + 1, fin -1);
    return false;
}


/*
Brock piensa que los músculos impresionan a las chicas, con la excusa de que quiere cuidar su salud, 
además de estar con una figura envidiable para el verano, sigue el consejo de la doctora Joy, anotar todas 
las calorías que ingiere en un casillero que corresponde a la hora y tipo de comida. Pero en los fines de semana… Se 
da sus buenos permitidos y no quiere ponerse a sumar.

Ayúdale haciendo una función que recibe la matriz que contiene los valores de las calorías que consumió 
cada día y devuelva el total de calorías
*/

int sumar_calorias_rec(int matriz[MAX_TAM][MAX_TAM],int tope_fil, int tope_col, int pos_fil, int pos_col, int contador)
{
    if((pos_fil >= tope_fil)&&(pos_col>=tope_col))
        return contador;

    if((pos_fil < tope_fil)&&(pos_col == tope_col-1)){
        contador += matriz[pos_fil][pos_col];
        return sumar_calorias_rec(matriz, tope_fil, tope_col, pos_fil+1, 0, contador);
    }

    if((pos_fil < tope_fil)&&(pos_col < tope_col)){
        contador += matriz[pos_fil][pos_col];
    }
    return sumar_calorias_rec(matriz, tope_fil, tope_col, pos_fil, pos_col+1, contador);
}

int sumar_calorias(int cantidad_filas, int cantidad_columnas, int matriz[MAX_TAM][MAX_TAM]){
        return sumar_calorias_rec(matriz, cantidad_filas+1, cantidad_columnas+1, 0,0,0);
    
}