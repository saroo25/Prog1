#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <limits.h>

struct files
{
    char in_file[255];
    char  out_file[255];
};
typedef struct files Files;

bool ext(char *s){
    if(strlen(s)>4 && s[strlen(s)-4]=='.' && s[strlen(s)-3]=='t'&& s[strlen(s)-2]=='x'&& s[strlen(s)-1]=='t')
        return true;
    return false;
}

Files readInput(int argc, char *argv[]){
    if(argc!=3){
        fprintf(stderr,"Numero parametri non valido\n");
        exit(-1);
    }
    if( !ext(argv[1]) || !ext(argv[2])){
        fprintf(stderr,"Estensione file non valida\n");
        exit(-1);
    }
    Files f;
    strcpy(f.in_file,argv[1]);
    strcpy(f.out_file,argv[2]);
    return f;
}

struct data
{
    char nome[255];
    char cognome[255];
    int numero_conto;
    int anno_apertura;
    float saldo;
};

typedef struct data Data;

struct nodo
{
    Data d;
    struct nodo *next;
};

typedef struct nodo Nodo;

void insert_ordered(Nodo **head,Data d){
    Nodo *new_nodo=malloc(sizeof(Nodo));
    new_nodo->d=d;
    new_nodo->next=NULL;

    Nodo *prev=NULL;
    Nodo *iter=(*head);
    while(iter!=NULL && iter->d.anno_apertura < d.anno_apertura){
        prev=iter;
        iter=iter->next;
    }
    if(prev==NULL){
        new_nodo->next=(*head);
        (*head)=new_nodo;
    }
    else{
        prev->next=new_nodo;
        new_nodo->next=iter;
    }

}

void print_list(Nodo **head){
    Nodo *iter=(*head);
    while(iter!=NULL){
        printf("%s %s %d %d %f\n",iter->d.nome,iter->d.cognome,iter->d.numero_conto,iter->d.anno_apertura,iter->d.saldo);
        iter=iter->next;
    }
}

Nodo** readFile(Files fs){
    FILE *f =fopen(fs.in_file,"r");
    if(!f){
        fprintf(stderr,"Impossibile aprire file di input \n");
        exit(-1);
    }
    Data d;
    Nodo **head=malloc(sizeof(Nodo*));
    while(true){
        int x=fscanf(f,"%s %s %d %d %f",d.nome,d.cognome,&d.numero_conto,&d.anno_apertura,&d.saldo);
        
        if(x==EOF)
        {
            break;
        }
        //inserire i nuovi valori in una lista concatenata
        insert_ordered(head,d);
        
        //printf("%s \n",d.nome);
    }
    //print_list(head);

    return head;

}

float getMax(Nodo **head){
    Nodo *iter=*head;
    float max=iter->d.saldo;
    while(iter!=NULL){
        if(iter->d.saldo>max){
            max=iter->d.saldo;
        }
        iter=iter->next;
    }
    return max;
}
float calc_x(Nodo *iter, float m){
    float x=((float)2023-iter->d.anno_apertura)/5;
    if(x>1) 
        x=1;
    x=x*(float)iter->d.saldo/m;
    return x;
}

void removeAccount(Nodo **head){
    Nodo *iter=*head;
    float m=getMax(head);
    float xmax =calc_x(iter,m);
    //printf("%f\n",xmax);
    Nodo *vittima=*head;
    Nodo *prev_vittima=NULL;
    Nodo *prev=NULL;

    while(iter!=NULL){
        float x=calc_x(iter,m);
        //printf("%f ",x);
        if(x>xmax){

            prev_vittima=prev;
            vittima=iter;
            xmax=x;
        }
        prev=iter;
        iter=iter->next;
    }
    
    if(prev_vittima==NULL){
        *head=vittima->next;
        free(vittima);
    }
    else{
        prev_vittima->next=vittima->next;
        free(vittima);
    }

}

void writeFile(Nodo **head, Files d){
    //printf("%s \n",)
    FILE *f=fopen(d.out_file,"w");
    if(!f){
        fprintf(stderr,"Impossibile aprire file di output \n");
        exit(-1);
    }
    Nodo *iter=*head;
    while(iter!=NULL){
        fprintf(f,"%s %s %d %d %f\n",iter->d.nome,iter->d.cognome,iter->d.numero_conto,iter->d.anno_apertura,iter->d.saldo);
        iter=iter->next;
    }
    fclose(f);
}

int len_list(Nodo **head){
    int i=0;
    Nodo *iter=*head;
    while(iter!=NULL){
        i++;
        iter=iter->next;
    }
    return i;
}

int main(int argc, char *argv[]){
    Files fs=readInput(argc, argv);
    //printf("%s \n",fs.in_file);
    //printf("%s \n",fs.out_file);
    Nodo **head= readFile(fs);
    //float max=getMax(head);
    //printf("%f \n",max);
    int len=len_list(head);
    int h=len/2;
    for(int i=0;i<h;i++)
        removeAccount(head);
    
    print_list(head);
    writeFile(head,fs);

}