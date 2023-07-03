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

void insertRecord(Nodo **head, Data dati){
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

Nodo **buildList(Inputs I){
    FILE *f=fopen(I.filename,"r");
    if(!f){
        fprintf(stderr,"Impossibile aprire il file\n");
        exit(1);
    }
    Nodo **head=malloc(sizeof(Nodo *));
    (*head)=NULL;

    while(1){
        Data d;
        fscanf(f,"%f\n",&d.V);
        fscanf(f,"%s\n",d.P);
        
        
        if(feof(f)) break;
        insertRecord(head,d);
    }
    return head;
}

void printList(Nodo **head){
    Nodo *iter=(*head);
    while(iter!=NULL){
        printf("%f %s\n",iter->d.V,iter->d.P);
        iter=iter->next;
    }

}

void elab(Nodo **head,Inputs I){
    float f=I.F;
    int i=0;
    Nodo *iter=(*head);
    while(iter!=NULL){
        if(iter->d.V>=f){
            i++;
        }
        iter=iter->next;
    }
    printf("Numero di elementi con V>=F %d\n",i);
}

int main(int argc, char *argv[]){
    Inputs I=readInput(argc,argv);
    printf("%s %f\n",I.filename,I.F);
    Nodo **head=buildList(I);
    printList(head);
    elab(head,I);

}