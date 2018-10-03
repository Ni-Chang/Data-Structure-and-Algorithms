//
//  main.c
//  encode
//
//  Created by xiaonizi on 2018/5/4.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char letter;
    struct Node *next;
    struct Node *before;
}node;

int trans[95];

void removedup(char s[]){
    int i=0, j=0, k, flag;
    while(s[i]!='\0'){
        flag=0;
        for(k=0; k<j; k++){
            if(s[i]==s[k])
                flag=1;
        }
        if(flag==0)
            s[j++]=s[i++];
        else
            i++;
    }
    s[j]='\0';
}

void reverse(char s[]){
    char temp;
    int i=0;
    int j=strlen(s)-1;
    while(i<j){
        temp=s[i];
        s[i]=s[j];
        s[j]=temp;
        i++;
        j--;
    }
}

node *createcycle(char s[]){
    int i;
    node *head=NULL;
    node *temp=NULL;
    for(i=126; i>=32; i--){
        if(strchr(s, i)==NULL){
            temp=(node *)malloc(sizeof(node));
            temp->letter=i;
            temp->next=head;
            if(head!=NULL)
                head->before=temp;
            head=temp;
        }
        
    }
    i=0;
    while(s[i]!='\0'){
        temp=(node *)malloc(sizeof(node));
        temp->letter=s[i];
        temp->next=head;
        head->before=temp;
        head=temp;
        i++;
    }
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=head;
    head->before=temp;
    return head;
}

void encode(node *head){
    int num, i;
    node *old;
    int first=head->letter;
    while(head->next!=head){
        num=head->letter;
        head->before->next=head->next;
        head->next->before=head->before;
        old=head;
        head=head->next;
        free(old);
        i=num;
        for(; i>1; i--){
            head=head->next;
        }
        trans[num-32]=head->letter;
    }
    trans[head->letter-32]=first;
}

int main() {
    char s[33];
    gets(s);
    removedup(s);
    reverse(s);
    encode(createcycle(s));
    FILE* fp1=fopen("in.txt", "r");
    FILE* fp2=fopen("in_crpyt.txt", "w");
    char temp=fgetc(fp1);
    while(temp!=EOF){
        if(temp>=32&&temp<=126)
            temp=trans[temp-32];
        fputc(temp, fp2);
        temp=fgetc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
