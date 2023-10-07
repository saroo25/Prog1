#include <stdio.h> 
#include <stdlib.h>

struct nodo{
    int valore;
    char carattere;

    struct nodo* next;

};

typedef struct nodo Nodo;


Nodo* insert_ordered(Nodo* testa, int value, char carattere){
    Nodo * new_nodo=malloc(sizeof(Nodo));
    new_nodo->valore=value;
    new_nodo->carattere=carattere;

    Nodo *prev=NULL;
    Nodo *iter=testa;
    while(iter!=NULL && iter->valore>new_nodo->valore){
        prev=iter;
        iter=iter->next;
    }
    if(prev==NULL){
        new_nodo->next=testa;
        testa=new_nodo;
    }
    else if(iter==NULL){
        prev->next=new_nodo;
        new_nodo->next=NULL;
    }
    else{
        prev->next=new_nodo;
        new_nodo->next=iter;
    }
    return testa;
}

void print_lista(Nodo *head){
    Nodo *iter=head;
    while(iter!=NULL){
        printf("(%d , %c) ",iter->valore, iter->carattere);
        iter=iter->next;
    }
    /*for(Nodo *iter=head;iter!=NULL;iter=iter->next){ //alternativa al while
        printf("(%d , %c) ",iter->valore, iter->carattere);
    }*/
    printf("\n");
}

Nodo * remove_list(Nodo *testa, int value){
    if(testa== NULL) return NULL;

    Nodo *iter=testa;
    Nodo* prev=NULL;
    while(iter!=NULL && iter->valore!=value){
        prev=iter;
        iter=iter->next;
    }
    if(prev==NULL){
        testa=testa->next;
    }
    else if(iter!=NULL){
        prev->next=iter->next;
    }
    free(iter);
    return testa;
}

int main(){
    Nodo *head=NULL;
    head=insert_ordered(head, 5,'a');
    head=insert_ordered(head, 1,'b');
    head=insert_ordered(head, 50,'c');
    head=insert_ordered(head, 15,'d');
    head=insert_ordered(head, 7,'e');
    head=insert_ordered(head, 13,'f');
    head=insert_ordered(head, 22,'g');
    head=insert_ordered(head, 40,'h');
    print_lista(head);
    head=remove_list(head,22);
    head=remove_list(head,50);
    print_lista(head);
    

}