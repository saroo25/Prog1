#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <time.h>


struct inputs{
    int n;
    char alfabeto[255];
    char out[255];
};
typedef struct inputs Inputs;

Inputs decodeParameters(int argc, char *argv[]){
    if(argc!=4){//controlliamo che ci sia il numero giusto di parametri
        fprintf(stderr,"Numero parametri non valido\n");
        exit(1);
    }
    Inputs in;
    strcpy(in.alfabeto,argv[1]);//copia il primo input in in.alfabeto
    in.n=atoi(argv[2]);//converte il secondo input in un intero
    strcpy(in.out,argv[3]);
    if((strlen(in.alfabeto)<5 || strlen(in.alfabeto)>15)){
        fprintf(stderr,"Alfabeto non valido\n");
        exit(1);
    }
    if(in.n<5 || in.n>15 ){
        fprintf(stderr,"N non valido\n");
        exit(1);
    }
    if(strcmp(strrchr(in.out,'.'),".txt")){
        fprintf(stderr,"estensione file non valida");
        exit(1);
    }
    
    return in;

}
int * readInput(Inputs in){
    int n=in.n;
    int L=strlen(in.alfabeto);
    int *W =malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        int x;
        
        scanf("%d",&x);
        if(x<1){
            x=1;
        }
        if(x>L){
            x=L;
        }
        W[i]=x;
    }
    
    return W;
}
unsigned int get_random() {
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;

    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

char * sampleString(char *alfabeto, int h){//AaBbCc
    char *news=malloc(sizeof(char)*(h+1));
    for(int i=0;i<h;i++){
        int pos_cas=get_random()%strlen(alfabeto);
        news[i]=alfabeto[pos_cas];

    }
    news[h]='\0';
    //printf("%s\n",news);
    return news;
}
char ** getStringArray(int *W,Inputs in){
    char** Q=malloc(sizeof(char*)*in.n);
    for(int i=0;i<in.n;i++){
        Q[i]=sampleString(in.alfabeto,W[i]);
        printf("%s ",Q[i]);
    }
    printf("\n");
    
    return Q;
}

struct nodo{
    char *s;
    struct nodo *next;
};
typedef struct nodo Nodo;

void push(Nodo **head,char *stringa){
    Nodo * new_nodo=malloc(sizeof(Nodo));
    new_nodo->next=*head;
    new_nodo->s=malloc(sizeof(char)*strlen(stringa+1));
    strcpy(new_nodo->s ,stringa);
    *head=new_nodo;

}
bool isEmpty(Nodo **head){//ritorna true se la pila è vuota
    if(*head){
        return false;
    }
    return true;
}

Nodo* pop(Nodo **head){
    if(isEmpty(head)){
        return NULL;
    }
    Nodo *ext=*head;
    *head=(*head)->next;
    return ext;

}

void printPila(Nodo **head){
    Nodo *iter=*head;
    while(iter!=NULL){
        printf("%s ",iter->s);
        iter=iter->next;
    }
    printf("\n");
}

Nodo ** getStack(char **Q,Inputs in){
    Nodo **head=malloc(sizeof(Nodo*));
    fprintf(stderr,"ciao\n");
    
    push(head,Q[0]);
    
    for(int i=1;i<in.n;i++){
        if((strlen(Q[i]))%2==1){
            Nodo *e=pop(head);
            Q[i]=strcat(Q[i],e->s);
            free(e);
        }
        push(head,Q[i]);

    }
    return head;
}

void writeStackToFile(Nodo **head,Inputs in){
    FILE *f=fopen(in.out,"w");
    if(!f){
        fprintf(stderr,"File di output non valido\n");
        exit(1);
    }

    Nodo *iter=*head;
    while(iter!=NULL){
        fprintf(f,"%s\n",iter->s);
        iter=iter->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    Inputs in=decodeParameters(argc,argv);
    int *W=readInput(in);
    char **Q=getStringArray(W,in);
    Nodo **head=getStack(Q,in);
    //printPila(head);
    writeStackToFile(head,in);
    return 0;
}