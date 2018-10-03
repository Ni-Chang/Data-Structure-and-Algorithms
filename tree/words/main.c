//
//  main.c
//  words
//
//  Created by xiaonizi on 2018/5/21.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char word[20];
    int count;
    struct node *lchild, *rchild;
};
typedef struct node Node;

Node *root;

void tolowercase(char word[]){
    int i=0;
    while(word[i]!='\0'){
        if(word[i]>='A' && word[i] <= 'Z')
            word[i]+=32;
        i++;
    }
}

Node* insert(Node *p, char word[]){
    if(p == NULL){
        p = (Node *)malloc(sizeof(Node));
        strcpy(p->word, word);
        p->count=1;
        p->lchild=NULL;
        p->rchild=NULL;
    }
    else if(strcmp(p->word, word) == 0){
        p -> count++;
    }
    else if (strcmp(p->word, word) > 0){
        p->lchild = insert(p->lchild, word);
    }
    else{
        p->rchild = insert(p->rchild, word);
    }
    return p;
}

void output(Node *node){
    if(node != NULL){
        output(node->lchild);
        printf("%s %d\n", node->word, node->count);
        output(node->rchild);
    }
}

int main() {
    char letter, word[20];
    int i=0;
    root = NULL;
    FILE *fp = fopen("article.txt", "r");
    while((letter = fgetc(fp)) != EOF){
        if((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z')){
            while((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z')){
                word[i++] = letter;
                letter = fgetc(fp);
            }
            word[i]='\0';
            i=0;
            tolowercase(word);
            root = insert(root, word);
        }
    }
    fclose(fp);
    Node *temp = root;
    for(i = 0; i < 3; i++){
        if(temp != NULL){
            printf("%s", temp->word);
            if(temp -> rchild != NULL && i<2){
                printf(" ");
            }
            else{
                printf("\n");
            }
            temp = temp->rchild;
        }
    }
    output(root);
    return 0;
}
