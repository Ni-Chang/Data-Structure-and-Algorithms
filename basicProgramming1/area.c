//
//  main.c
//  area
//
//  Created by xiaonizi on 2018/3/16.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>

void compare(int a, int b, int *big, int *small) {
    if(a>b){
        *big=a;
        *small=b;
    }
    else{
        *big=b;
        *small=a;
    }
}

int getMAX(int a, int b){
    if(a>b)
        return a;
    return b;
}

int getMIN(int a, int b){
    if(a>b)
        return b;
    return a;
}

int main() {
    int ax1, ay1, ax2, ay2, bx1, by1, bx2, by2, MAX_AX, MIN_AX, MAX_BX, MIN_BX, MAX_AY, MIN_AY, MAX_BY, MIN_BY, minMAX_X, maxMIN_X, minMAX_Y, maxMIN_Y, delta_X, delta_Y;
    scanf("%d %d %d %d", &ax1, &ay1, &ax2, &ay2);
    scanf("%d %d %d %d", &bx1, &by1, &bx2, &by2);
    compare(ax1, ax2, &MAX_AX, &MIN_AX);
    compare(bx1, bx2, &MAX_BX, &MIN_BX);
    compare(ay1, ay2, &MAX_AY, &MIN_AY);
    compare(by1, by2, &MAX_BY, &MIN_BY);
    minMAX_X=getMIN(MAX_AX, MAX_BX);
    minMAX_Y=getMIN(MAX_AY, MAX_BY);
    maxMIN_X=getMAX(MIN_AX, MIN_BX);
    maxMIN_Y=getMAX(MIN_AY, MIN_BY);
    delta_X=minMAX_X-maxMIN_X;
    delta_Y=minMAX_Y-maxMIN_Y;
    if(delta_X<=0 || delta_Y<=0)
        printf("%d\n", 0);
    else
        printf("%d\n", delta_X*delta_Y);
    return 0;
}
