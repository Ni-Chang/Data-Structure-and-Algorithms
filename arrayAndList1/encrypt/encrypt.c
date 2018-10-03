//
//  main.c
//  encrypt
//
//  Created by xiaonizi on 2018/4/14.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <string.h>

void removeDuplicates(char s[]){
    int i=0, j=0, k, flag=0;
    for(i=0; s[i]!='\0'; i++){
        for(k=0; k<j; k++){
            flag=0;
            if(s[k]==s[i]){
                flag=1;
                break;
            }
        }
        if(flag==0){
            s[j++]=s[i];
        }
    }
    s[j]='\0';
}

void change(char s[]){
    char syb[27];
    strcpy(syb, s);
    int i, flag=0;
    char c;
    for(c='z'; c>='a'; c--){
        flag=0;
        for(i=0; i<strlen(s); i++){
            if(s[i]==c){
                flag=1;
                break;
            }
        }
        if(flag==0){
            strncat(syb, &c, 1);
        }
    }
    FILE *fpin=fopen("encrypt.txt", "r");
    FILE *fpout=fopen("output.txt", "w");
    char letter=fgetc(fpin);
    int pos;
    while(letter != EOF){
        pos=letter-'a';
        if(pos>=0&&pos<=25){
            letter=syb[pos];
        }
        fputc(letter, fpout);
        letter=fgetc(fpin);
    }
    fclose(fpin);
    fclose(fpout);
}

int main() {
    char s[51];
    scanf("%s", s);
    removeDuplicates(s);
    change(s);
    return 0;
}
