//
//  main.c
//  notation
//
//  Created by xiaonizi on 2018/4/13.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>

int main(){
    char s[101];
    scanf("%s", s);
    int pointpos=0, firstnozeropos=0, shift;
    while(s[pointpos]!='.'){
        pointpos++;
    }
    while(s[firstnozeropos]=='0'||s[firstnozeropos]=='.'){
        firstnozeropos++;
    }
    shift=pointpos-firstnozeropos;
    int i;
    if(shift>0){
        printf("%c.", s[0]);
        i=1;
        while(s[i]!='\0'){
            if(s[i]=='.'){
                i++;
                continue;
            }
            printf("%c", s[i]);
            i++;
        }
        printf("e%d", --shift);
    }
    else{
        i=firstnozeropos;
        printf("%c", s[i++]);
        if(s[i]!='\0'){
            printf(".");
        }
        while(s[i]!='\0'){
            printf("%c", s[i]);
            i++;
        }
        printf("e%d\n", shift);
    }
    return 0;
}


