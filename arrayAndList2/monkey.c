//
//  main.c
//  monkey
//
//  Created by xiaonizi on 2018/5/4.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    int money[n];
    int i;
    for(i=0; i<n; i++){
        money[i]=1;
    }
    i=q-1;
    int count, money_num=n;
    while(money_num!=1){
        count=0;
        for(; count<m; i++){
            if(money[i%n]==1){
                count++;
            }
        }
        money[--i%n]=0;
        i++;
        money_num--;
    }
    for(i=0; i<n; i++){
        if(money[i]==1){
            printf("%d",i+1);
            return 0;
        }
    }
}

