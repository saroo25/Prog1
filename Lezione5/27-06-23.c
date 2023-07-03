#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <time.h>


typedef struct inputs{
    char filename[255];
    float F;
}Inputs;

Inputs readInput(int argc, char *argv[]){
    if(argc!=3){
        fprintf(stderr,"Numero di argomenti non valido\n");
        exit(1);
    }
    if(!strrchr(argv[1],'.') || strcmp(strrchr(argv[1],'.'),".txt")){
        fprintf(stderr,"estensione file di input non valida\n");
        exit(1);
    }
    if(! (atof(argv[2])>=1 && atof(argv[2])<=20) ){
        fprintf(stderr,"F deve essere compreso tra 1 e 20\n");
        exit(1);
    }
    Inputs I;
    strcpy(I.filename,argv[1]);
    I.F=atof(argv[2]);
    return I;

}

typedef struct data{
    float V;
    char P[255];
}Data;

typedef struct nodo{
    Data d;
    struct nodo* next;
    struct nodo* prev;
}Nodo;

void insert(Nodo **head, Data dati){
    Nodo *new_nodo=malloc(sizeof(Nodo));
    new_nodo->d=dati;
    Nodo *iter=(*head);
    Nodo *prev=NULL;
    while(iter!=NULL && strcmp(iter->d.P,new_nodo->d.P)<0 ){
        prev=iter;
        iter=iter->next;
    }
    if(prev==NULL){
        new_nodo->next=iter;
        new_nodo->prev=NULL;
        if(*head){
            iter->prev=new_nodo;
        }
        (*head)=new_nodo;
    }
    else if(iter==NULL){
        prev->next=new_nodo;
        new_nodo->prev=prev;
        new_nodo->next=NULL;
    }
    else{
        prev->next=new_nodo;
        new_nodo->next=iter;
        iter->prev=new_nodo;
        new_nodo->prev=prev;

    }

}



int main(int argc, char *argv[]){
    Inputs I=readInput(argc,argv);
    printf("%s %f\n",I.filename,I.F);


}