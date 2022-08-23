
//bubble sort solo
void swap(char *a, char *b){
    char *aux = *a;
    *a = *b;
    *b = aux;
}

void bubble_sort(char vector_desordenado[MAX_VECTOR], char vector_ordenado[MAX_VECTOR], int tope, bool ascendente){
    if(ascendente){
        for(int i = 0; i < tope-1; i++){
            for(int j = 0 ; j < tope - i -1; j++){
                if(vector_desordenado[j] > vector_desordenado[j+1]){
                    swap(&vector_desordenado[j],&vector_desordenado[j+1]);
                }
            }
        }
    }else{
          for(int i = 0; i < tope-1; i++){
            for(int j = 0 ; j < tope - i -1; j++){
                if(vector_desordenado[j] < vector_desordenado[j+1]){
                    swap(&vector_desordenado[j],&vector_desordenado[j+1]);
                }
            }
        }
    }
    for(int i = 0; i<tope ; i++){
        vector_ordenado[i] = vector_desordenado[i];
    }
}


//bubble sort con stirngs


void bubble_sort(char string_desordenado[MAX_VECTOR], char string_ordenado[MAX_VECTOR], bool ascendente){
    int tope = strlen(string_desordenado);
     if(ascendente){
        for(int i = 0; i < tope-1; i++){
            for(int j = 0 ; j < tope - i -1; j++){
                if(string_desordenado[j] > string_desordenado[j+1]){
                    char aux = string_desordenado[j];
                    string_desordenado[j] = string_desordenado[j+1];
                    string_desordenado[j+1] = aux;
                }
            }
        }
    }else{
          for(int i = 0; i < tope-1; i++){
            for(int j = 0 ; j < tope - i -1; j++){
                if(string_desordenado[j] < string_desordenado[j+1]){
                    char aux = string_desordenado[j];
                    string_desordenado[j] = string_desordenado[j+1];
                    string_desordenado[j+1] = aux;
                }
            }
        }
    }
    for(int i = 0; i<tope ; i++){
        string_ordenado[i] = string_desordenado[i];
    }
}