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
void listInsert(Nodo **head,Record data){
    Nodo *newnodo=malloc(sizeof(Nodo));
    newnodo->data=data;
    float media=((float)(data.votoS+data.votoO))/2;
    Nodo *prev=NULL;
    Nodo *iter=(*head);
    while(iter!=NULL && (((float)(iter->data.votoS+iter->data.votoO))/2) <media){
        prev=iter;
        iter=iter->next;
    }
    if(prev==NULL){
        newnodo->next=*head;
        *head=newnodo;
    }
    else if(iter==NULL){
        prev->next=newnodo;
        newnodo->next=NULL;
    }
    else{
        prev->next=newnodo;
        newnodo->next=iter;
    }

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
    Nodo **head=malloc(sizeof(Nodo*));
    *head=NULL;
    char riga[512];
    while(fscanf(f,"%s",riga)==1){
        strcpy(nome,strtok(riga,":"));
        votoS=atoi(strtok(NULL,":"));
        votoO=atoi(strtok(NULL,"\n"));
        
        /*int byte=strchr(riga,':')-riga;
        strncpy(nome,riga,byte);
        nome[byte]='\0';


        char * second=riga+byte+1;
        char numero[255];
        int byte2=strchr(second,':')-second;
        strncpy(numero,second,byte2);
        numero[byte]='\0';
        votoS=atoi(numero);
        
        char * third=second+byte2+1;
        votoO=atoi(third);*/
        Record data=buildRecord(nome,votoS,votoO);
        listInsert(head,data);
    }
    return head;
}

void printLista(Nodo **head){
    Nodo* iter=*head;
    while(iter!=NULL){
        printf("%s %d %d\n",iter->data.nome,iter->data.votoS,iter->data.votoO);
        iter=iter->next;
    }
}
void listInsertByName(Nodo **head,Record data){
    
    Nodo *newnodo=malloc(sizeof(Nodo));
    newnodo->data=data;
    Nodo *prev=NULL;
    Nodo *iter=(*head);
    while(iter!=NULL && strcmp(iter->data.nome,data.nome)<0){
        prev=iter;
        iter=iter->next;
    }
    if(prev==NULL){
        newnodo->next=*head;
        *head=newnodo;
    }
    else if(iter==NULL){
        prev->next=newnodo;
        newnodo->next=NULL;
    }
    else{
        prev->next=newnodo;
        newnodo->next=iter;
    }

}

void listTrimmer(Nodo **L, Nodo **LAE, Nodo **LFN, Nodo **LMZ){
    Nodo * iter=*L;
    while(iter!=NULL){
        
        if(iter->data.nome[0]>='a' && iter->data.nome[0]<='e'){
            printf("%c\n",iter->data.nome[0]);
            listInsertByName(LAE,iter->data);
            
        }
        else if(iter->data.nome[0]>='f' &&iter->data.nome[0]<='n'){
            listInsertByName(LFN,iter->data);
        }
        else if(iter->data.nome[0]>='m' &&iter->data.nome[0]<='z'){
            listInsertByName(LMZ,iter->data);
        }
        
        iter=iter->next;
    }
    *L=NULL;
}

void saveList(Nodo **head, char* filename){
    FILE *f=fopen(filename,"w");
    Nodo* iter=*head;
    while (iter!=NULL){
        fprintf(f,"%s:%d:%d\n",iter->data.nome,iter->data.votoS,iter->data.votoO);
        iter=iter->next;
    }
    
}

Nodo** concatenaListe( Nodo **LAE, Nodo **LFN, Nodo **LMZ){
    Nodo** head= LAE;
    if(*LAE && *LFN && *LMZ){
        
        Nodo * iter=*LAE;
        while(iter->next!=NULL){
           iter=iter->next;
        }
        iter->next=*LFN;
        while(iter->next!=NULL){
           iter=iter->next;
        }
        iter->next=*LMZ;
    }
    return head;
}


int main(int argc, char *argv[]){

    /*printf("Numero di argc: %d\n",argc);
    printf("argv[0]: %s\n",argv[0]);
    printf("argv[1]: %s\n",argv[1]);*/
    
    Inputs in= decodeParameters(argc,argv);
    //printf("%s \n",in.filename);
    Nodo **L=readInputs(in);
    //printLista(L);
    Nodo **LAE=malloc(sizeof(Nodo*));
    Nodo **LFN=malloc(sizeof(Nodo*));
    Nodo **LMZ=malloc(sizeof(Nodo*));
    *LAE=NULL;
    *LFN=NULL;
    *LMZ=NULL;
   
    listTrimmer(L,LAE,LFN,LMZ);
    printf("LAE:\n");
    //printLista(LAE);
    printf("LFN:\n");
    //printLista(LFN);
    printf("LMZ:\n");
    //printLista(LMZ);
    saveList(LAE,"AE.txt");
    saveList(LFN,"FN.txt");
    saveList(LMZ,"MZ.txt");
    L=concatenaListe(LAE,LFN,LMZ);
    printLista(L);
}