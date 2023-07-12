#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <time.h>

typedef struct inputs{
    char filename[255];
}Inputs;

Inputs decodeParameters(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr, "I parametri passati sono sbagliati\n");
        exit(1);
    }
    if(strrchr(argv[1],'.')==NULL ||  strcmp(strrchr(argv[1],'.'),".txt")!=0){
        fprintf(stderr, "Il file di input ha un estensione sbagliata\n");
        exit(1);
    }
    Inputs i;
    strcpy(i.filename,argv[1]);
    return i;
}

typedef struct  record{
    char nome[255];
    int votoS;
    int votoO;
}Record;

typedef struct nodo{
    Record data;
    struct nodo *next;
}Nodo;

Record buildRecord(char * nome, int votoS,int votoO){
    Record data;
    strcpy(data.nome,nome);
    data.votoS=votoS;
    data.votoO=votoO;
    return data;
}

Nodo** readInputs(Inputs in){
    FILE *f=fopen(in.filename,"r");
    if(f==NULL){
        fprintf(stderr,"Impossibile aprire il file in lettura\n");
        exit(1);
    }
    char nome[255];
    int votoS;
    int votoO;
    while(fscanf(f,"%255[^:]:%d:%d",nome,&votoS,&votoO)==3){
        //printf("%s %d %d",nome,votoS,votoO);
        Record data=buildRecord(nome,votoS,votoO);
        //Inserimento ordinato in lista 
    }

}




int main(int argc, char *argv[]){

    /*printf("Numero di argc: %d\n",argc);
    printf("argv[0]: %s\n",argv[0]);
    printf("argv[1]: %s\n",argv[1]);*/
    
    Inputs in= decodeParameters(argc,argv);
    //printf("%s \n",in.filename);
    readInputs(in);
}