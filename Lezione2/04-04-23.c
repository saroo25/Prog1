#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct inputs{
    int n;
    int m;
    char filename[255];
};
typedef struct inputs Inputs;

Inputs decodeParameters(int argc, char *argv[]){
    if(argc!=4){
        fprintf(stderr,"Numero parametri non corretto\n");
        exit(1);
    }
    Inputs i;
    i.n=atoi(argv[1]);
    i.m=atoi(argv[2]);
    strcpy(i.filename,argv[3]);
    if(!(i.n>=3 && i.n<=7) || !(i.m>=3 && i.m<=7) || strcmp(strrchr(i.filename,'.'),".txt") ){
        fprintf(stderr,"Argomenti non validi\n");
        exit(1);
    }
    return i;
}

double ** readFile(Inputs in){
    FILE *f=fopen(in.filename,"r");
    if(!f){
        
        fprintf(stderr,"Impossibile aprire il file\n");
        exit(1);
    }
    double **M=calloc(in.n,sizeof(double*));
    for(int i=0;i<in.n;i++)
        M[i]=malloc(sizeof(double)*in.m);
    for(int i=0;i<in.n;i++){
        for(int j=0;j<in.m;j++){
            fscanf(f,"%lf,",&M[i][j]);
        }
    }
    
    return M;
}
float getMax(double *M,Inputs in){
    float max=M[0];
    for(int j=0;j<in.m;j++){
        if(max<M[j])
            max=M[j];
    }
    return max;
}
float getMin(double *M,Inputs in){
    float min=M[0];
    for(int j=0;j<in.m;j++){
        if(min>M[j])
            min=M[j];
    }
    return min;
}
float getAvg(double *M,Inputs in){
    float sum=0;
    for(int j=0;j<in.m;j++){
        sum+=M[j];
    }
    return sum/=in.m;
}

/*float getAvg(double **M,Inputs in,int index_r){//versione alternativa che prende la matrice e lariga iesima
    float sum=0;
    for(int j=0;j<in.m;j++){
        sum+=M[index_r][j];
    }
    return sum/=in.m;
}*/



int *getArray(double **M,Inputs in){
    int *Y=malloc(sizeof(int)*in.n);
    for(int i=0;i<in.n;i++){
        Y[i]=0;
        float max=getMax(M[i],in);
        float min=getMin(M[i],in);
        float q=getAvg(M[i],in);
        printf("max: %lf min: %lf avg: %lf\n",max,min,q);
        //q=getAvg(M,in,i)//versione alternativa;
        float a=q- (max-min)*0.3;
        float b=q+ (max-min)*0.3;
        
        for(int j=0;j<in.m;j++){
            if(M[i][j]>a && M[i][j]<b){
                Y[i]++;
            }
        }
    }

    return Y;
}

void insertionSort(int *Y,Inputs in){
    for(int i=1;i<in.n;i++){
        int j=i-1;
        int tmp=Y[i];
        while(j>=0 && Y[j]>tmp){
            Y[j+1]=Y[j];
            j--;
        }
        Y[++j]=tmp;
    }
}

int *getCumulative(int *Y,Inputs in){//funzione per la somma cumulativa di un array
    int *Z=malloc(sizeof(int)*in.n);
    Z[0]=Y[0];
    for(int i=1;i<in.n;i++){
        Z[i]=Z[i-1]+Y[i];
    }
    return Z;
}

int main(int argc, char *argv[]){
    Inputs in=decodeParameters(argc,argv);
    //printf("m: %d n: %d filename: %s\n",i.n,i.m,i.filename);
    double **M=readFile(in);
    /*for(int i=0;i<in.n;i++){
        for(int j=0;j<in.m;j++){
            printf("%lf, ",M[i][j]);
        }
        printf("\n");
    }*/
    int *Y=getArray(M,in);
    insertionSort(Y,in);
    for(int i=0;i<in.n;i++)
        printf("%d ",Y[i]);
    printf("\n");
    return 0;
}