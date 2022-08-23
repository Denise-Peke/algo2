
extern void sift_up(int* vector, int tope);
extern void sift_down(int* vector, int tope, int pos_actual);
#include <stdbool.h>

void swap_v(int *vector, int a, int b)
{
    int aux = vector[a];
    vector[a] = vector[b];
    vector[b] = aux;

}

void sift_down_v(int* vector, int tope, int pos_actual){
    int hijo_izq = 2*pos_actual+1;
    int hijo_der = 2*pos_actual+2;

    if(hijo_izq >= tope)
        return;

    int hijo_mas_grande = hijo_izq;

    if(hijo_der < tope){
        if(vector[hijo_der] > vector[hijo_izq])
            hijo_mas_grande = hijo_der;
    }

    if(vector[pos_actual] < vector[hijo_mas_grande]){
        swap_v(vector, pos_actual, hijo_mas_grande);
        sift_down_v(vector, tope, hijo_mas_grande);
    }
}

int *heapify(int* vector, int n)
{
    int primero = n/2;
    while(primero>=0){
        sift_down_v(vector,n, primero);
        primero--;
    }
    return vector;
}


void ordenar_vector(int* vector, int n)
{
    heapify(vector, n);
    while(n>0){
        swap_v(vector, 0,n-1);
        sift_down_v(vector, n-1, 0);
        n--;
    }
}

void heap_sort(int* numeros, int tope, bool ascendente){
    ordenar_vector(numeros, tope);
    if(!ascendente){
        for(int i = 0; i < (tope/2);i++){
            swap_v(numeros,i, tope-i-1);
        }
    }
}
  