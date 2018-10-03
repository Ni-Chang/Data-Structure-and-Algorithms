//
//  main.c
//  calculator
//
//  Created by xiaonizi on 2018/5/14.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* link;
};
typedef struct node Node;

Node* num;
Node* op;

void pushnum(int data){
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data=data;
    newnode->link=num;
    num=newnode;
}

void pushop(int data){
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data=data;
    newnode->link=op;
    op=newnode;
}

void popnum(){
    Node* p=num;
    num=num->link;
    free(p);
}

void popop(){
    Node* p=op;
    op=op->link;
    free(p);
}

int cal(int num1, int num2, int op){
    if(op=='+')
        return num1+num2;
    if(op=='-')
        return num1-num2;
    if(op=='*')
        return num1*num2;
    if(op=='/')
        return num1/num2;
    else
        return -1;
}

int main() {
    num=NULL;
    op=NULL;
    char s[100], numstr[5];
    int numi;
    gets(s);
    int i;
    for(i=0; s[i]!='='; i++){
        if(s[i]>='0' && s[i]<='9'){
            int j=0;
            while (s[i]>='0' && s[i]<='9') {
                numstr[j++]=s[i++];
            }
            numstr[j]='\0';
            i--;
            numi=atoi(numstr);
            pushnum(numi);
        }
        else if(s[i]==')'){
            while(op->data!='('){
                num->link->data=cal(num->link->data, num->data, op->data);
                popnum();
                popop();
            }
            popop();
        }
        else if(s[i]=='+'||s[i]=='-'){
            while(op!=NULL && op->data!='('){
                num->link->data=cal(num->link->data, num->data, op->data);
                popnum();
                popop();
            }
            pushop(s[i]);
        }
        else if(s[i]=='*'||s[i]=='/'){
            while(op!=NULL && op->data!='(' && !(op->data=='+' || op->data=='-')){
                num->link->data=cal(num->link->data, num->data, op->data);
                popnum();
                popop();
            }
            pushop(s[i]);
        }
        else if(s[i]=='('){
            pushop(s[i]);
        }
    }
    while(op!=NULL){
        num->link->data=cal(num->link->data, num->data, op->data);
        popnum();
        popop();
    }
    printf("%d", num->data);
    return 0;
}
