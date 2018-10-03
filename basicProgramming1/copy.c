//
//  main.c
//  copy
//
//  Created by xiaonizi on 2018/3/17.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>

int main() {
    FILE *fpin = fopen("fcopy.in", "r");
    FILE *fpout = fopen("fcopy.out", "w");
    char letter = fgetc(fpin);
    while(letter != EOF){
        if(letter == '\t' || letter == ' '){
            fputc(' ', fpout);
            letter = fgetc(fpin);
            while (letter == '\t' || letter == ' ') {
                letter = fgetc(fpin);
            }
        }
        else{
            fputc(letter, fpout);
            letter = fgetc(fpin);
        }
    }
    fclose(fpin);
    fclose(fpout);
    return 0;
}
