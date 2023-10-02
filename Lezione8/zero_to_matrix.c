#include <stdio.h> 
#include <cstdlib>

void init_array(int arr[], int dim){
    for(int i=0;i<dim;i++){
        arr[i]=i*2;
    }
}

void stampa_arr(int arr[],int dim){
    for(int i=0;i<dim;i++){
       printf("%d ",arr[i]);
    }
    printf("\n");
}

int trova_max(int arr[],int dim){
    int max=arr[0];
    for(int i=1;i<dim;i++){
        if(max<arr[i]){
            max=arr[i];
        }
    }
    return max;
}
int trova_min(int arr[],int dim){
    int min=arr[0];
    for(int i=1;i<dim;i++){
        if(min>arr[i]){
            min=arr[i];
        }
    }
    return min;
}

float average(int arr[], int dim){
    int sum=0;
    for(int i=0;i<dim;i++){
        sum+=arr[i];
    }
    return (float)sum/dim;
}

void swap(int *x, int *y){
    int tmp;
    tmp=*x;
    *x=*y;
    *y=tmp;
}

void to_null(int *x){
    x=NULL;
}

int** alloc_matrix(int row,int col){
    int **M;
    M=(int**)malloc(row*sizeof(int*)); //new int*[row]
    for(int i=0;i<row;i++){
        M[i]=(int*)malloc(col*sizeof(int));//new int[col]
    }
    return M;
}

void init_matrix(int **M,int row,int col){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            M[i][j]=i*j+i*i-j;//MODIFICA LA MATRICE ORIGINALE
        }
    }
}
void print_matrix_row(int **M,int row,int col){//stampa per righe
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%d ",M[i][j]);
        }
        printf("\n");
    }
}

void print_matrix_col(int **M,int row,int col){//stampa per colonne
    for(int j=0;j<col;j++){
        for(int i=0;i<row;i++){
            printf("%d ",M[i][j]);
        }
        printf("\n");
    }
}

int *alloc_array_static(int row){
    int M[row];
    return M;
}//M MUORE

int* max_min_matrix(int **M, int row,int col){
    int *A=(int *)malloc(sizeof(int)*col);
    for(int j=0;j<col;j++){
        A[j]=M[0][j];
        if(j%2==0){
            for(int i=1;i<row;i++){
                if(A[j]<M[i][j]){
                    A[j]=M[i][j];
                }
            }
        }
        else{
            for(int i=1;i<row;i++){
                if(A[j]>M[i][j]){
                    A[j]=M[i][j];
                }
            }
        }  
    }
    return A;
}

int main() {
    //ARRAY E FUNZIONI
    //int dim=10;
    //int x[dim];
    //init_array(x,dim);
    
    //stampa_arr(x,dim);
    //int max=trova_max(x,dim);
    //float mean=average(x,dim);
    //printf("%f \n",mean);
    
    /////// PUNTATORI E PASSAGGIO DI PARAMETRI
    //int *x=(int*)malloc(sizeof(int));
    //*x=8;
    //printf("x:%p &x:%p *x:%d &*x:%p\n",x,&x,*x,&*x);
    
    /*int *z=20,*f=56;
    printf("z:%d f:%d\n",z,f);
    swap(z,f);
    to_null(f);
    printf("z:%d f:%d\n",z,f);*/
    //int *x=10;
    //printf("x:%p &x:%p *x:%d\n",x,&x,*x);
    
    ///////ERRORE NEL RITORNO DI MEMORIA ALLOCATA NELLO STACK
    /*int *A=alloc_array_static(5);
    for(int i=0;i<5;i++){
        A[i]=i*10;
    }
    for(int i=0;i<100000;i++);
    printf("%d ",A[3]);
    */

    /////Creazione di matrici e array dinamici
    int row=5,col=5;
    int **M=alloc_matrix(row,col);
    init_matrix(M,row,col);
    print_matrix_row(M,row,col);
    //print_matrix_col(M,row,col);
    int *arr=max_min_matrix(M,row,col);
    stampa_arr(arr,col);

    ////////ESERCIZI
    //Sommare 2 matrici 
    // sommare 2 array
    //Data una matrice M e un array A, dividere gli elementi della colonna j di M per A[j]
    //Data una matrice calcolare la media per ogni colonna e fare la media delle medie
    //Dati 2 array, uno rappresentante i numeri e l'altro rappresentante i pesi calcolare la media pe
    sata.
}

