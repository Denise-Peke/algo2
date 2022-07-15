
//semi generico
void sort_semi_generico(void** vector, int cant_elementos, int (*comparador) (void*, void*)){

    if(!vector || !comparador)
        return;
    
    for(int j = 0; j < cant_elementos; j++){
        for(int i = 0; i < cant_elementos-j-1; i++){
            if(comparador(vector[i], vector[i+1]) > 0){
                void *aux = vector[i];
                vector[i] = vector[i+1];
                vector[i+1] = aux;
            }
        }
    }
}

//generico

void sort_generico(void *vector, int cant_elementos, int tamanio_un_elemento, int (*comparador)(const void *, const void*)){
    
    if(!vector || !comparador)
        return;

      for(int j = 0; j < cant_elementos; j++){
        for(int i = 0; i < cant_elementos-j-1; i++){
            if(comparador(vector+(i*tamanio_un_elemento), vector+((i+1)*tamanio_un_elemento)) > 0){
                char aux[tamanio_un_elemento];
                memcpy(aux, vector+(i*tamanio_un_elemento), tamanio_un_elemento);
                memcpy(vector+(i*tamanio_un_elemento),vector+((i+1)*tamanio_un_elemento), tamanio_un_elemento);
                memcpy(vector+((i+1)*tamanio_un_elemento),aux, tamanio_un_elemento);

            }
        }
    }
}