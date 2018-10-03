//
//  main.c
//  expand
//
//  Created by xiaonizi on 2018/3/17.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>

int IsSame(char a, char b) {
    int flag = 0;
    if(a>='a' && a<='z' && b>='a' && b<='z' && a<b)
        flag = 1;
    else if(a>='A' && a<='Z' && b>='A' && b<='Z' && a<b)
        flag = 1;
    else if(a>='0' && a<='9' && b>='0' && b<='9' && a<b)
        flag = 1;
    return flag;
}

void Expand(char a, char b)
{
    while(a != b) {
        printf("%c", a);
        a++;
    }
}

int main() {
    char sentence[50];
    gets(sentence);
    int i = 0;
    char letter = sentence[0], next_letter;
    while(letter != '\0') {
        next_letter = sentence[++i];
        if(next_letter == '-') {
            next_letter = sentence[++i];
            if(IsSame(letter, next_letter))
                Expand(letter, next_letter);
            else
                printf("%c-", letter);
        }
        else
            printf("%c", letter);
        letter = next_letter;
    }
    printf("\n");
    return 0;
}
