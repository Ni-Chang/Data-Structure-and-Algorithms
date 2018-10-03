#include <stdio.h>
#include <stdlib.h>

struct  node {
    int data;
    struct  node  *link;
};
typedef  struct node  *Nodeptr;
typedef  struct node  Node;

Nodeptr Top;

void push(int data){
    Nodeptr p=(Nodeptr)malloc(sizeof(Node));
    p->data=data;
    p->link=Top;
    Top=p;
}

void pop(){
    if(Top==NULL){
        printf("error ");
    }
    else{
        printf("%d ",Top->data);
        Nodeptr p=Top;
        Top=Top->link;
        free(p);
    }
}

int main(){
    Top=NULL;
    int opt, size=0;
    int num;
    scanf("%d", &opt);
    while(opt!=-1){
        if(opt==1){
            scanf("%d", &num);
            if(size==100){
                printf("error ");
            }
            else{
                push(num);
                size++;
            }
        }
        else{
            pop();
            size--;
        }
        scanf("%d", &opt);
    }
    return 0;
}

