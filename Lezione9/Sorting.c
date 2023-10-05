#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

void stampa_arr(int *arr,int dim){
    for(int i=0;i<dim;i++){
       printf("%d ",arr[i]);
    }
    printf("\n");
}
void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void insertion_sort(int *A,int len){
    for(int i=1;i<len;i++){
        int j=i;
        while(j>0 && A[j]<A[j-1]){
            swap(&A[j],&A[j-1]);
            j--;
        }
    }
}


void selection_sort(int *A, int len){
    for(int i=0;i<len;i++){
        int min_index=i;
        for(int j=i;j<len;j++){
            if(A[j]<A[min_index]){
                min_index=j;
            }
        }
        swap(&A[i],&A[min_index]);
    }
}

void bubble_sort(int *A, int len){
    for(int i=0;i<len;i++){
        for(int j=0;j<len-1;j++){
            if(A[j]>A[j+1]){
                swap(&A[j],&A[j+1]);
            }
        }
    }
}

int main(){
    srand(time(NULL));
    int len=10;
    int *A=malloc(len*sizeof(int));
    for(int i=0;i<len;i++){
        A[i]=rand()%51;//riempio random l'array
    }
    stampa_arr(A,len);
    bubble_sort(A,len);
    stampa_arr(A,len);
    


}