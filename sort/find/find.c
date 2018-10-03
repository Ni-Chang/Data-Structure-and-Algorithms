//
//  main.c
//  find-
//
//  Created by xiaonizi on 2018/5/24.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NHASH  3001
#define MULT  37

struct index{
    char letter;
    int start, len;
};
typedef struct index Index;

struct hash{
    char word[21];
    struct hash *next;
};
typedef struct hash Hash;

char dic[3500][21];
Index indexTable[26];
Hash hashTable[3001];
int count;

unsigned int hash(char *str)
{
    unsigned int h=0;
    char *p;
    for(p=str; *p!='\0'; p++)
        h = MULT*h + *p;
    return h % NHASH;
}

int sequential(char word[]){
    for(; count<3500; count++){
        if(strcmp(word, dic[count])==0){
            return 1;
        }
        else if(strcmp(word, dic[count])<0){
            return 0;
        }
    }
    return 0;
}

int half(char word[], int low, int high){
    if(low<=high){
        count++;
        int mid = low+(high-low)/2;
        if(strcmp(dic[mid], word)==0){
            return 1;
        }
        else if(strcmp(dic[mid], word)>0){
            return half(word, low, mid-1);
        }
        else{
            return half(word, mid+1, high);
        }
    }
    return 0;
}

int indexs(char word[]){
    return half(word, indexTable[word[0]-'a'].start, indexTable[word[0]-'a'].start+indexTable[word[0]-'a'].len-1);
}

int hashs(char word[]){
    unsigned int h = hash(word);
    Hash* p = &hashTable[h];
    while(p->next!=NULL){
        count++;
        if(strcmp(p->word, word)==0){
            return 1;
        }
        else if(strcmp(p->word, word)>0){
            return 0;
        }
        p=p->next;
    }
    count++;
    if(strcmp(p->word, word)==0){
        return 1;
    }
    return 0;
}

int main(){
    FILE *fp=fopen("dictionary3000.txt", "r");
    char temp = 'a';
    int i;
    for(i=0; i<3001; i++){
        strcpy(hashTable[i].word, "\0");
        hashTable[i].next = NULL;
    }
    unsigned int h;
    for(i=0; fscanf(fp, "%s", dic[i])!=EOF; i++){
        if(dic[i][0]==temp){
            indexTable[temp-'a'].letter=temp;
            indexTable[temp-'a'].start=i;
            indexTable[temp-'a'].len=1;
            temp++;
        }
        else if(dic[i][0]>temp){
            temp++;
            indexTable[temp-'a'].letter=temp;
            indexTable[temp-'a'].start=i;
            indexTable[temp-'a'].len=1;
            temp++;
        }
        else{
            indexTable[temp-'a'-1].len++;
        }
        h=hash(dic[i]);
        if(hashTable[h].word[0] == '\0'){
            strcpy(hashTable[h].word, dic[i]);
        }
        else{
            Hash* p=&hashTable[h];
            Hash* newNode = (Hash *)malloc(sizeof(Hash));
            strcpy(newNode->word, dic[i]);
            newNode->next = NULL;
            while(p->next != NULL){
                p=p->next;
            }
            p->next=newNode;
        }
    }
    fclose(fp);
    char testword[21];
    int method;
    scanf("%s %d", testword, &method);
    count = 0;
    int flag;
    switch(method){
        case 1:
            //printf("0 ");
            flag = sequential(testword);
            printf("%d %d", flag, count+1);
            break;
        case 2:
            //printf("0 ");
            flag=half(testword, 0, i-1);
            printf("%d %d", flag, count);
            break;
        case 3:
            //printf("0 ");
            flag=indexs(testword);
            printf("%d %d", flag, count);
            break;
        case 4:
            //printf("1 ");
            flag = hashs(testword);
            printf("%d %d", flag, count);
            break;
    }
    return 0;
}


