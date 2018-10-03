//
//  main.c
//  telsort
//
//  Created by xiaonizi on 2018/4/8.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <string.h>

struct nametel{
    char name[11];
    char tel[11];
};

void sort(struct nametel telbook[], int n){
    int i, j;
    struct nametel temp;
    for(i=0; i<n-1; i++){
        for(j=i+1; j<n; j++){
            if(strcmp(telbook[i].name, telbook[j].name)>0){
                temp=telbook[i];
                telbook[i]=telbook[j];
                telbook[j]=temp;
            }
        }
    }
}

int main() {
    int n, i;
    scanf("%d", &n);
    struct nametel telbook[n];
    for(i=0; i<n; i++){
        scanf("%s", telbook[i].name);
        telbook[i].name[10]='\0';
        scanf("%s", telbook[i].tel);
        telbook[i].tel[10]='\0';
    }
    sort(telbook, n);
    for(i=0; i<n; i++){
        printf("%12s", telbook[i].name);
        printf("%12s", telbook[i].tel);
        printf("\n");
    }
    return 0;
}
