#include <stdio.h> 
#include <stdlib.h>
//Sommare 2 matrici 
//Sommare 2 array
//Data una matrice M e un array A, dividere gli elementi della colonna j di M per A[j]
//Data una matrice calcolare la media per ogni colonna e fare la media delle medie
//Dati 2 array, uno rappresentante i numeri e l'altro rappresentante i pesi calcolare la media pesata

int ** alloc_matrix(int row, int col){
    int **M= malloc(row*sizeof(int*)); //new int*[row];
    for(int i=0;i<row;i++){
        M[i]=malloc(col*sizeof(int));//new int[col];
    }
    return M;
}

int ** somma_Matrici(int **M1,int **M2,int row,int col){
    int **Msomma= alloc_matrix(row,col);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            Msomma[i][j]=M1[i][j]+M2[i][j];
        }
    }

    return Msomma;
    
}//qualunque cosa allocata staticamente (STACK) muore

void init_matrix(int **M, int row, int col, int x){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            M[i][j]=(i+j)*i+x;
        }
    }
}

void stampa_matrix(int **M, int row, int col){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%d ",M[i][j]); //cout<<M[i][j]<<" ";
        }
        printf("\n");//cout<<endl;
    }
}

void stampa_matrix_float(float **M, int row, int col){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%f ",M[i][j]); //cout<<M[i][j]<<" ";
        }
        printf("\n");//cout<<endl;
    }
}

int *init_array(int len,int x){
    int *A=malloc(len*sizeof(int));
    for(int i=0;i<len;i++){
        A[i]=(i+1)*x-i;
    }
    return A;
}

void stampa_arr(int *A,int len){
    for(int i=0;i<len;i++){
        printf("%d\t",A[i]);
    }
    printf("\n");
}

int * somma_Arr(int *A1,int *A2,int len){
    int *somma=malloc(len*sizeof(int));
    for(int i=0;i<len;i++){
        somma[i]=A1[i]+A2[i];
    }
    return somma;
}

float ** div_mat_arr(int **M,int *A, int row,int col){
    float **res=malloc(row*sizeof(float*));
    for(int i=0;i<row;i++){
        res[i]=malloc(col*sizeof(float));
    }

    for(int j=0;j<col;j++){
        for(int i=0;i<row;i++){
            if(A[j]!=0)
                res[i][j]=(float)M[i][j]/A[j];
            
        }
    }
    return res;

}

float media_col(int **M,int row, int col){
    float *A=malloc(col*sizeof(float));
    for(int i=0;i<col;i++)
        A[i]=0;
    
    for(int j=0;j<col;j++){
        for(int i=0;i<row;i++){
            A[j]=A[j]+M[i][j]; //Somma della colonna j nella posizione j dell'array
        }
    }
    for(int pippo=0;pippo<col;pippo++){
        A[pippo]=A[pippo]/row; //sto ottenendo l'array delle medie
    }

    float sum=0;
    for(int i=0;i<col;i++)
        sum+=A[i];
    
    return sum/col;

}

float media_col_alt(int **M,int row, int col){
    float *A=malloc(col*sizeof(float));
    for(int i=0;i<col;i++)
        A[i]=0;
    
    float acc_col=0;
    for(int j=0;j<col;j++){
        float acc_row=0;
        for(int i=0;i<row;i++){
            acc_row+=M[i][j]; 
        }
        acc_col+=acc_row/row;
    }

    return acc_col/col;

}

float media_Pes(int *Val,int *Pes, int len){
    float acc=0;
    float somma_pesi=0;
    for(int i=0;i<len;i++){
        acc+=Val[i]*Pes[i];
        somma_pesi+=Pes[i];
    }

    return acc/somma_pesi;
    

}


int main(){
    /*ES1
    int row=3,col=3;
    int** M1=alloc_matrix(row,col);
    int** M2=alloc_matrix(row,col);//dichiarata ma NON inizializzata
    init_matrix(M1,row,col,2);
    stampa_matrix(M1,row,col);
    printf("---------------------\n");
    init_matrix(M2,row,col,4);
    stampa_matrix(M2,row,col);
    int **M3=somma_Matrici(M1,M2,row,col);
    printf("---------------------\n");
    stampa_matrix(M3,row,col);*/

    /*ES2
    int len=10;
    int *A1=init_array(len,5);
    int *A2=init_array(len,3);
    stampa_arr(A1,len);
    printf("---------------------\n");
    stampa_arr(A2,len);
    int *A3=somma_Arr(A1,A2,len);
    printf("---------------------\n");
    stampa_arr(A3,len);*/

    /* ES3
    int row=3,col=3;
    int **M=alloc_matrix(row,col);
    init_matrix(M,row,col,7);
    int *A=init_array(col,5);
    
    stampa_matrix(M,row,col);
    printf("---------------------\n");
    stampa_arr(A,col);

    float **res=div_mat_arr(M,A,row,col);
    printf("---------------------\n");
    stampa_matrix_float(res,row,col);*/

    /*ES4
    int row=3,col=3;
    int **M=alloc_matrix(row,col);
    init_matrix(M,row,col,12);
    stampa_matrix(M,row,col);
    printf("---------------------\n");
    printf("%f\n",media_col(M,row,col)); //cout<<mediacol(...);
    printf("---------------------\n");
    printf("%f\n",media_col_alt(M,row,col));*/
    int len=10;
    int *A1=init_array(len,15);
    int *A2=init_array(len,3);
    printf("---------------------\n");
    stampa_arr(A1,len);
    printf("---------------------\n");
    stampa_arr(A2,len);
    printf("---------------------\n");
    printf("%f\n",media_Pes(A1,A2,len));


}