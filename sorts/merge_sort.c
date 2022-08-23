

void merge(int* v1, int c1, int* v2, int c2, bool ascendente)
{
    int v3[c1+c2];
    int i1 = 0, i2=0, i3 = 0;

    if(ascendente){
        while(i1 < c1 && i2 < c2){
        
            if(v1[i1] <= v2[i2]){
                v3[i3] = v1[i1];
                i1++;
            }else{
                v3[i3]=v2[i2];
                i2++;
            }
            i3++;
        }
    }else{
        while(i1 < c1 && i2 < c2){
            if(v1[i1] >= v2[i2]){
                v3[i3] = v1[i1];
                i1++;
            }else{
                v3[i3]=v2[i2];
                i2++;
            }
            i3++;
        }
    }    
    while(i1 < c1){
        v3[i3]=v1[i1];
        i3++;
        i1++;
    }
    while(i2 < c2){
        v3[i3] = v2[i2];
        i3++;
        i2++;
    }
    for(int i = 0; i< c1+c2 ; i++){
        v1[i] = v3[i];
    }
}


void merge_sort(int* numeros, int tope, bool ascendente){
    if(tope <= 1)
        return;
    int mitad = tope/2;
   
    merge_sort(numeros, mitad,ascendente);
    merge_sort(numeros+mitad, tope - mitad,ascendente);

    merge(numeros, mitad, numeros+mitad, tope-mitad, ascendente);
}