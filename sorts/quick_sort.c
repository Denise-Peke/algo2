
void swap(int *vector, int a , int b)
{
    int aux = vector[a];
    vector[a] = vector[b];
    vector[b] = aux;
}


int pivotear(int *vector, int tamanio, bool ascendente){

    int pos_pivote = tamanio -1;
    int pos_final_pivote = 0;

    for(int i = 0; i < pos_pivote; i++){
        if(ascendente){
            if(vector[i] < vector[pos_pivote]){
                swap(vector, i, pos_final_pivote);
                pos_final_pivote++;
            }
        }else{
            if(vector[i] > vector[pos_pivote]){
                swap(vector, i, pos_final_pivote);
                pos_final_pivote++;
            }
        }
    }
    swap(vector, pos_pivote, pos_final_pivote);
    return pos_final_pivote;
}




void quick_sort(int* numeros, int tope, bool ascendente){
    
    if( tope <= 1){
        return;
    }
    int pos_pivote = pivotear(numeros, tope,ascendente);

    quick_sort(numeros, pos_pivote,ascendente);
    quick_sort(numeros + pos_pivote + 1, tope - pos_pivote -1,ascendente);
}