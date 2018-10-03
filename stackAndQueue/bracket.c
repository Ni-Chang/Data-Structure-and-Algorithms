//
//  main.c
//  bracket
//
//  Created by xiaonizi on 2018/5/10.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct  node {
    int data, line;
    struct  node  *link;
};
typedef  struct node  *Nodeptr;
typedef  struct node  Node;

Nodeptr Top;

void push(int data, int line){
    Nodeptr p=(Nodeptr)malloc(sizeof(Node));
    p->data=data;
    p->line=line;
    p->link=Top;
    Top=p;
}

int pop(int data, int line){
    if(Top==NULL||(data=='}'&&Top->data!='{')||(data==')'&&Top->data!='(')){
        printf("without maching '%c' at line %d\n", data, line);
        return 1;
    }
    else{
        Nodeptr p=Top;
        Top=Top->link;
        free(p);
        return 0;
    }
}

int main(){
    Top=NULL;
    char c, buf[200];
    int line=1, pos=0, flag;
    int array[400];
    FILE *fp=fopen("example.c", "r");
    c=fgetc(fp);
    while(c!=EOF){
        if(c=='{'||c=='('){
            array[pos++]=c;
            push(c,line);
        }
        else if(c=='}'||c==')'){
            array[pos++]=c;
            flag=pop(c, line);
            if(flag==1){
                fclose(fp);
                return 0;
            }
            
        }
        else if(c==34){
            c=fgetc(fp);
            while(c!=34){
                if(c=='\n'){
                    line++;
                }
                c=getc(fp);
            }
        }
        else if(c==39){
            c=fgetc(fp);
            while(c!=39){
                if(c=='\n'){
                    line++;
                }
                c=getc(fp);
            }
        }
        else if(c=='/'){
            c=getc(fp);
            if(c=='*'){
                c=getc(fp);
                while(1){
                    while(c!='*'){
                        if(c=='\n'){
                            line++;
                        }
                        c=getc(fp);
                    }
                    c=getc(fp);
                    if(c=='/'){
                        break;
                    }
                }
            }
            else if(c=='/'){
                fgets(buf, 199, fp);
                line++;
            }
        }
        else if(c=='\n'){
            line++;
        }
        c=getc(fp);
    }
    if(Top!=NULL){
        printf("without maching '%c' at line %d\n", Top->data, Top->line);
    }
    else{
        int i;
        for(i=0; i<pos; i++){
            printf("%c", array[i]);
        }
    }
    fclose(fp);
    return 0;
}


