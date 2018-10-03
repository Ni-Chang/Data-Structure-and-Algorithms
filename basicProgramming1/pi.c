//
//  main.c
//  example1a
//
//  Created by ChangNi on 2018/3/15.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

double factorial(int n){
    double factrl = 1.0;
    while(n!=1){
        factrl *= n--;
    }
    return factrl;
}

double denominator(int n){
    double denom = 1.0;
    int i;
    for(i=1; i<=n; i++){
        denom *= 2*i+1;
    }
    return denom;
}

double term(int n){
    double term;
    term = 2.0*factorial(n)/denominator(n);
    return term;
}

int main(){
    double e;
    scanf("%lf", &e);
    int n=1;
    double PI=2.0, differ;
    do{
        differ = term(n++);
        PI+=differ;
    }while(differ>e);
    printf("%d %.7lf\n", n, PI);
    return 0;
}