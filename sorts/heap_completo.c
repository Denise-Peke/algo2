void swap(int *vector, int pos1, int pos2){
    int aux = vector[pos1];
    vector[pos1] = vector[pos2];
    vector[pos2] = aux;    
}

int padre_de(int n)
{
    return (n-1)/2;
}

void sift_up(int* vector, int pos_actual){
    if(pos_actual==0)
        return;
    
    int padre = padre_de(pos_actual);
    if(vector[pos_actual]>vector[padre]){
        swap(vector, pos_actual, padre);
        sift_up(vector, padre);
    }
}

void sift_down(int* vector, int tope, int pos_actual){
    int hijo_izq = 2*pos_actual+1;
    int hijo_der = 2*pos_actual+2;

    if(hijo_izq >= tope)
        return;

    int hijo_mas_grande = hijo_izq;

    if(hijo_der < tope){
        if(vector[hijo_der] > vector[hijo_izq])
            hijo_mas_grande = hijo_der;
    }

    if(vector[pos_actual] < vector[hijo_mas_grande])
        swap(vector, pos_actual, hijo_mas_grande);
        sift_down(vector, tope, hijo_mas_grande);
}

void heap_insertar(int* vector, int* tope, int elemento){
    vector[*tope]=elemento;
    sift_up(vector, *tope);
    (*tope)++;
}

int heap_extraer_raiz(int* vector, int* tope){
    int extraido = vector[0];
    if(*tope == 0)
        return 0;
    swap(vector, 0, (*tope-1));
    (*tope)--;
    sift_down(vector, (*tope),0);
    return extraido;
}