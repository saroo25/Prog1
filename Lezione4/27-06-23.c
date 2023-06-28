#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <time.h>

typedef struct inputs{
    char filename[255];
    int n;
} Inputs;


Inputs decodeParameters(int argc, char *argv[]){
    if(argc!=3){
        fprintf(stderr,"numero di parametri non valido\n");
        exit(1);
    }
    if(strrchr(argv[1],'.')==NULL || strcmp(".bin",strrchr(argv[1],'.'))!=0 ){
        fprintf(stderr,"estensione file non valida\n");
        exit(1);
    }
    if(!(atoi(argv[2])>=3 && atoi(argv[2])<=5)){
        fprintf(stderr,"n deve essere copreso tra 3 e 5\n");
        exit(1);
    }
    Inputs I;
    strcpy(I.filename,argv[1]);
    I.n=atoi(argv[2]);
    return I;

}


typedef struct record{
    int numeroConto;
    char nome[255];
    char cognome[255];
    float saldo;
}Record;

typedef struct nodo{
    Record data;
    struct nodo* next; 
}Nodo;

void insertHead(Nodo **head,Record d){
    Nodo *newnodo=malloc(sizeof(Nodo));
    newnodo->data=d;
    newnodo->next=(*head); 
    (*head)=newnodo;
}

void printList(Nodo **head){
    Nodo *iter=(*head);
    while(iter!=NULL){
        printf("%d %s %s %f\n",iter->data.numeroConto,iter->data.nome,iter->data.cognome,iter->data.saldo);
        iter=iter->next;
    }
}

Record readRecord(){
    Record r;
    scanf("%d %s %s %f",&r.numeroConto,r.nome,r.cognome,&r.saldo);
    return r;
}

Nodo **loadRecord(){
    Nodo **head=malloc(sizeof(Nodo*));
    (*head)=NULL;
    Record r;
    while(1){
        r=readRecord();
        if(feof(stdin)) break;
        insertHead(head,r);
    }

    return head;
    
}
int listLen(Nodo **head){
    int len=0;
    Nodo *iter=(*head);
    while(iter!=NULL){
        iter=iter->next;
        len++;
    }
    return len;
}

Record * getArray(Nodo **head){
    int len=listLen(head);
    Record *X=malloc(sizeof(Record)*len);
    Nodo *iter=(*head);
    for(int i=0;i<len;i++){
        X[i]=iter->data;
        iter=iter->next;
    }
    return X;
}

float saldoMedio(Record *X,int len){
    float media=0;
    for(int i=0;i<len;i++){
        media+=X[i].saldo;
    }
    return media/len;
}


void sort(Record *X,int len){
    float m=saldoMedio(X,len);
    for(int i=0;i<len-1;i++){
        float min=(X[i].saldo-m)*(X[i].saldo-m);
        int min_index=i;
        for(int j=i+1;j<len;j++){
            float saldo_corr=(X[j].saldo-m)*(X[j].saldo-m);
            if(min>saldo_corr){
                min=saldo_corr;
                min_index=j;
            }
        }
        Record tmp=X[i];
        X[i]=X[min_index];
        X[min_index]=tmp;
    }
}

void saveToFile(Record *X,int len, Inputs I){
    FILE *f=fopen(I.filename,"wb");
    for(int i=0;i<len;i++){
        fwrite(&X[i],sizeof(Record),1,f);

    }
    fclose(f);
}
unsigned int get_random() {
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}
void showFileContent(Record *X,int len, Inputs I){
    FILE *f=fopen(I.filename,"rb");

    for(int i=0;i<5;i++){
        int random=get_random()%5;
        fseek(f,sizeof(Record)*random,SEEK_SET);//sposto il puntatore di lettura file (f)
                                                //di ,sizeof(Record)*random posizioni
                                                //SEEK_SET dice da dove deve partire lo spostamento
                                                //dall'inizio del file in questo caso
        Record r;
        fread(&r,sizeof(Record),1,f);
        printf("%d %s %s %f\n",r.numeroConto,r.nome,r.cognome,r.saldo);
        
    }
}

int main(int argc, char *argv[]){
    Inputs I=decodeParameters(argc,argv);
    //printf("Punto A: \nFilename : %s\nN : %d\n",I.filename,I.n);
    Nodo **head=loadRecord();
    /*printf("Punto B\n");
    printList(head);*/
    Record *X =getArray(head);
    sort(X,listLen(head));
    printf("Punto C\n");
    for(int i=0;i<listLen(head);i++)
        printf("%d %s %s %f\n",X[i].numeroConto,X[i].nome,X[i].cognome,X[i].saldo);
    saveToFile(X,listLen(head),I);
    printf("Punto D\n");
    showFileContent(X,listLen(head),I);
}