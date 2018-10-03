//
//  main.c
//  cipin
//
//  Created by xiaonizi on 2018/5/5.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char word[20];
    int count;
    struct Node *next;
}node;

void lowercase(char s[]){
    int i;
    for(i=0; s[i]!='\0'; i++){
        if(s[i]>='A' && s[i]<='Z'){
            s[i]+=32;
        }
    }
}

node * addNode(char s[], node *head){
    node *p=head;
    while(p!=NULL){
        if(!strcmp(p->word, s)){
            p->count++;
            return head;
        }
        p=p->next;
    }
    p=(node *)malloc(sizeof(node));
    strcpy(p->word, s);
    p->count=1;
    p->next=head;
    head=p;
    return head;
}

void sortword(node *head){
    node *now, *next;
    char tempword[20];
    int tempcount;
    int flag=0;
    while(flag==0){
        flag=1;
        now=head;
        next=head->next;
        while(next!=NULL){
            if(strcmp(now->word, next->word)>0){
                strcpy(tempword, next->word);
                strcpy(next->word, now->word);
                strcpy(now->word, tempword);
                tempcount=now->count;
                now->count=next->count;
                next->count=tempcount;
                flag=0;
            }
            now=next;
            next=next->next;
        }
    }
}

int main() {
    node *head;
    FILE *fp=fopen("article.txt", "r");
    char s[20];
    char c;
    int i;
    while(1){
        c=fgetc(fp);
        if(c==EOF)
            break;
        while(!((c>='a' && c<='z') || (c>='A' && c<='Z') || c==EOF)){
            c=getc(fp);
        }
        if(c==EOF)
            break;
        i=0;
        while((c>='a' && c<='z') || (c>='A' && c<='Z')){
            s[i++]=c;
            c=fgetc(fp);
        }
        s[i]='\0';
        lowercase(s);
        head=addNode(s, head);
    }
    fclose(fp);
    sortword(head);
    while(head!=NULL){
        printf("%s %d\n", head->word, head->count);
        head=head->next;
    }
    return 0;
}
