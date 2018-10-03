//
//  main.c
//  multi
//
//  Created by xiaonizi on 2018/5/4.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Term{
    int coeff;
    int index;
    struct Term *next;
}term;

term *create(){
    char s[200];
    gets(s);
    int n=strlen(s);
    s[n++]=' ';
    s[n]='\0';
    term *head, *new;
    head=new=NULL;
    int i=0, j=0;
    char tempnum[10];
    head=(term *)malloc(sizeof(term));
    head->next=NULL;
    while(s[i]!=' '){
        tempnum[j++]=s[i++];
    }
    tempnum[j]='\0';
    head->coeff=atoi(tempnum);
    i++;
    j=0;
    while(s[i]!=' '){
        tempnum[j++]=s[i++];
    }
    tempnum[j]='\0';
    head->index=atoi(tempnum);
    i++;
    j=0;
    while(s[i]!='\0'){
        new=(term *)malloc(sizeof(term));
        new->next=head;
        while(s[i]!=' '){
            tempnum[j++]=s[i++];
        }
        tempnum[j]='\0';
        new->coeff=atoi(tempnum);
        i++;
        j=0;
        while(s[i]!=' '){
            tempnum[j++]=s[i++];
        }
        tempnum[j]='\0';
        new->index=atoi(tempnum);
        i++;
        j=0;
        head=new;
    }
    return head;
}

term *find(term *terms, int index){
    while(terms!=NULL){
        if(terms->index==index)
            return terms;
        terms=terms->next;
    }
    return NULL;
}

term *cal(term *head1, term *head2){
    term* result=NULL;
    int coeff;
    int index;
    term *ori=head2;
    while(head1!=NULL){
        head2=ori;
        while(head2!=NULL){
            coeff=head1->coeff*head2->coeff;
            index=head1->index+head2->index;
            if(find(result, index)!=NULL){
                find(result, index)->coeff+=coeff;
            }
            else{
                term *temp=(term *)malloc(sizeof(term));
                temp->coeff=coeff;
                temp->index=index;
                temp->next=result;
                result=temp;
            }
            head2=head2->next;
        }
        head1=head1->next;
    }
    return result;
}

void sort(term *result){
    term *now, *next;
    int tempco, tempindex;
    int flag=0;
    while(flag==0){
        flag=1;
        now=result;
        next=result->next;
        while(next!=NULL){
            if(now->index<next->index){
                tempco=now->coeff;
                tempindex=now->index;
                now->coeff=next->coeff;
                now->index=next->index;
                next->coeff=tempco;
                next->index=tempindex;
                flag=0;
            }
            now=next;
            next=next->next;
        }
    }
}

int main() {
    term *head1=create();
    term *head2=create();
    term *result=cal(head1, head2);
    sort(result);
    while(result!=NULL){
        printf("%d %d ", result->coeff, result->index);
        result=result->next;
    }
    return 0;
}
