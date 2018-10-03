//
//  main.c
//  find
//
//  Created by xiaonizi on 2018/5/17.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char data[21];
    int height;
    struct node *lchild, *rchild, *parent;
};
typedef struct node Node;

void findpos(Node* t, char str[], Node** result){
    if(t!=NULL){
        findpos(t->lchild, str, result);
        if(strcmp(str, t->data)==0){
            *result=t;
        }
        findpos(t->rchild, str, result);
    }
}

void insertChild(Node* pos, char lchild[], char rchild[]){
    if(strcmp(lchild, "NULL")!=0){
        pos->lchild=(Node *)malloc(sizeof(Node));
        strcpy(pos->lchild->data, lchild);
        pos->lchild->height=pos->height+1;
        pos->lchild->lchild=pos->lchild->rchild=NULL;
        pos->lchild->parent=pos;
    }
    if(strcmp(rchild, "NULL")!=0){
        pos->rchild=(Node *)malloc(sizeof(Node));
        strcpy(pos->rchild->data, rchild);
        pos->rchild->height=pos->height+1;
        pos->rchild->lchild=pos->rchild->rchild=NULL;
        pos->rchild->parent=pos;
    }
}

int main(){
    Node *pos=NULL;
    int num, i;
    char parent[21], lchild[21], rchild[21];
    FILE *fp=fopen("in.txt", "r");
    fscanf(fp, "%d", &num);
    fscanf(fp, "%s %s %s", parent, lchild, rchild);
    Node *root=(Node *)malloc(sizeof(Node));
    strcpy(root->data, parent);
    root->height=1;
    root->lchild=root->rchild=root->parent=NULL;
    insertChild(root, lchild, rchild);
    for(i=1; i<num; i++){
        fscanf(fp, "%s %s %s", parent, lchild, rchild);
        findpos(root, parent, &pos);
        insertChild(pos, lchild, rchild);
    }
    fclose(fp);
    char p1[21], p2[21];
    Node *p1pos=NULL, *p2pos=NULL;
    scanf("%s %s", p1, p2);
    findpos(root, p1, &p1pos);
    findpos(root, p2, &p2pos);
    if(p1pos->height>p2pos->height){
        printf("%s %s %d", p1pos->data, p2pos->data, p1pos->height-p2pos->height);
    }
    else if(p1pos->height<p2pos->height){
        printf("%s %s %d", p2pos->data, p1pos->data, p2pos->height-p1pos->height);
    }
    else{
        int h=p1pos->height;
        while(p1pos!=p2pos){
            p1pos=p1pos->parent;
            p2pos=p2pos->parent;
        }
        printf("%s %s %d\n%s %s %d\n", p1pos->data, p1, h-p1pos->height, p1pos->data, p2, h-p1pos->height);
    }
    return 0;
}

