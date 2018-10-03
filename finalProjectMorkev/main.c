//
//  main.c
//  markov
//
//  Created by xiaonizi on 2018/6/22.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vec.h"

#define WORDLEN 96
#define TABLELEN 898991//524287
//#define FILELEN 6279166
#define MAXOUTPUT 5120000

/*typedef struct sufnode{
    char suf[WORDLEN];
    struct sufnode *next;
}Sufnode;*/

typedef struct prefix{
    char word1[WORDLEN];
    char word2[WORDLEN];
    int sufnum;
    //char arr[ARRAYLEN][WORDLEN];
    //Sufnode *head, *tail;
    cvector suffix;
    struct prefix *next;
}Prefix;


char firstword[WORDLEN], secondword[WORDLEN], suffix[WORDLEN];
Prefix vertex[TABLELEN];
char writebuffer[MAXOUTPUT+1];
char *wpos = writebuffer;

double randseed = 997;

double rrand()
{
    double lambda = 3125.0;
    double m = 34359738337.0;
    double r;
    randseed = fmod(lambda*randseed, m);
    r = randseed / m;
    return r;
}

// BKDR Hash Function
unsigned int BKDRHash(char *str){
    unsigned int hash = 0;
    unsigned int hashseed = 131;
    while (*str){
        hash = hash * hashseed + (*str++);
    }
    return hash %TABLELEN;// & 0x1FFFFF;
}

void process(){
    char temp[2*WORDLEN];
    
    strcpy(temp, firstword);
    strcat(temp, " ");
    strcat(temp, secondword);
    unsigned int hashnum = BKDRHash(temp);
    char flag = 0;

    Prefix *p = &vertex[hashnum];
    while(flag==0 && p!=NULL){
        if(p->sufnum == 0){
            flag = 1;
            p->suffix = cvector_create(WORDLEN);
            
            strcpy(p->word1,firstword);
            strcpy(p->word2, secondword);
            cvector_pushback(p->suffix, suffix);
            p->sufnum=1;
            break;
        }
        else if((strcmp(p->word1, firstword)==0 && strcmp(p->word2, secondword)==0)){
            flag = 1;
            p->sufnum++;
            cvector_pushback(p->suffix, suffix);
            break;
        }
        else if(p->next != NULL){
            p=p->next;
        }
        else{
            break;
        }
    }
    if(flag == 0){
        Prefix *q = (Prefix *)malloc(sizeof(Prefix));
        strcpy(q->word1,firstword);
        strcpy(q->word2, secondword);
        q->sufnum=1;
        q->suffix = cvector_create(WORDLEN);
        cvector_pushback(q->suffix, suffix);
        q->next =NULL;
        p->next = q;
    }
}

Prefix *find(char word1[], char word2[]){
    char temp[2*WORDLEN];
    strcpy(temp, word1);
    strcat(temp, " ");
    strcat(temp, word2);
    unsigned int hashnum = BKDRHash(temp);
    Prefix *p = &vertex[hashnum];
    while(strcmp(p->word1, word1)!=0 || strcmp(p->word2, word2)!=0){
        p=p->next;
    }
    return p;
}

void fadd(char s[]){
    int i=0;
    while(s[i]!='\0'){
        *wpos++ = s[i++];
    }
    *wpos++ = ' ';
}

int main() {

    int i=0, j=0, filelen;
    for(i=0; i<TABLELEN; i++){
        vertex[i].next = NULL;
        vertex[i].sufnum = 0;
        vertex[i].suffix = NULL;
    }
    i=0;
    
    FILE *fpin = fopen("article.txt", "r");
    fseek(fpin, 0, SEEK_END);
    filelen = ftell(fpin);
    fseek(fpin, 0, SEEK_SET);
    char readbuffer[filelen+7];
    fread(readbuffer, 1, filelen, fpin);
    fclose(fpin);
    readbuffer[filelen]=' ';
    readbuffer[filelen+1]='(';
    readbuffer[filelen+2]='e';
    readbuffer[filelen+3]='n';
    readbuffer[filelen+4]='d';
    readbuffer[filelen+5]=')';
    readbuffer[filelen+6]='\0';

    char first[WORDLEN], second[WORDLEN];
    while(readbuffer[i]!='\t' && readbuffer[i]!='\r' && readbuffer[i]!='\n' && readbuffer[i]!=' '){
        first[j] = readbuffer[i];
        firstword[j++] = readbuffer[i++];
    }
    firstword[j]='\0';
    first[j]='\0';
    j=0;
    while(readbuffer[i]=='\t' || readbuffer[i]=='\r' || readbuffer[i]=='\n' || readbuffer[i]==' '){
        i++;
    }
    while(readbuffer[i]!='\t' && readbuffer[i]!='\r' && readbuffer[i]!='\n' && readbuffer[i]!=' '){
        second[j] = readbuffer[i];
        secondword[j++] = readbuffer[i++];
    }
    secondword[j]='\0';
    second[j]='\0';
    j=0;
    while(readbuffer[i]=='\t' || readbuffer[i]=='\r' || readbuffer[i]=='\n' || readbuffer[i]==' '){
        i++;
    }
    while(readbuffer[i]!='\t' && readbuffer[i]!='\r' && readbuffer[i]!='\n' && readbuffer[i]!=' '){
        suffix[j++] = readbuffer[i++];
    }
    suffix[j]='\0';
    j=0;
    while(readbuffer[i]=='\t' || readbuffer[i]=='\r' || readbuffer[i]=='\n' || readbuffer[i]==' '){
        i++;
    }
    while(i<filelen+7){
        process();
        strcpy(firstword, secondword);
        strcpy(secondword, suffix);
        while(readbuffer[i]!='\t' && readbuffer[i]!='\r' && readbuffer[i]!='\n' && readbuffer[i]!=' '){
            suffix[j++] = readbuffer[i++];
        }
        suffix[j]='\0';
        j=0;
        while(readbuffer[i]=='\t' || readbuffer[i]=='\r' || readbuffer[i]=='\n' || readbuffer[i]==' '){
            i++;
        }
    }
    process();
    
    int maxoutput, outputnum=0, N, n;
    scanf("%d", &maxoutput);
    i=0; j=0;
   
    
    //strcpy(writebuffer, first);
    //strcat(writebuffer, " \0");
    //writebuffer[i++] = ' ';
    //writebuffer[i] = '\0';
    
    fadd(first);
    outputnum++;
  //  Sufnode *linknode;
    
    Prefix *sufpos;
    while(outputnum<maxoutput && strcmp(second,"(end)")!=0){
        sufpos = find(first, second);
        strcpy(first, second);
        N = sufpos->sufnum;
        if(N==1){
           // strcpy(second, sufpos->arr[0]);
            cvector_val_at(sufpos->suffix, 0, second);
        }
        else{
            n = (int)(rrand()*N);
            cvector_val_at(sufpos->suffix, n, second);
        }
        fadd(first);
        //strcat(writebuffer, first);
      //  strcat(writebuffer, " \0");
    }
    unsigned long wn = strlen(writebuffer);
    //int a = strlen(readbuffer);
    FILE *fpout = fopen("markov.txt", "w");
    fwrite(writebuffer, 1, wn, fpout);
    //fprintf(fpout, "%d", maxoutput);
    fclose(fpout);
    
    return 0;
}
