//
//  main.c
//  mgt
//
//  Created by xiaonizi on 2018/6/17.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct edge{
    int id, v1, v2, weight, flag;
}Edge;

int v_num, e_num, choosed_e[100];
Edge edges[100];

int findmin(){
    int minid = -1, minweight = INT_MAX, i;
    for(i=0; i<e_num; i++){
        if(edges[i].weight < minweight && edges[i].flag==0){
            minid = i;
            minweight = edges[i].weight;
        }
    }
    return minid;
}

void sort(int n){
    int i, j, temp;
    for(j=0; j<n-1; j++){
        for(i=0; i<n-j-1; i++){
            if(choosed_e[i]>choosed_e[i+1]){
                temp = choosed_e[i];
                choosed_e[i] =choosed_e[i+1];
                choosed_e[i+1] = temp;
            }
        }
    }
}

int main() {
    int i, n=0, minpos, total_weight=0;
    scanf("%d %d", &v_num, &e_num);
    int area[v_num];
    for(i=0; i<v_num; i++){
        area[i]=i;
    }
    for(i=0; i<e_num; i++){
        scanf("%d %d %d %d", &edges[i].id, &edges[i].v1, &edges[i].v2, &edges[i].weight);
        edges[i].flag=0;
    }
    while(n!=v_num-1){
        minpos = findmin();
        int v1= edges[minpos].v1, v2= edges[minpos].v2, small, big;
        if(!( area[v1] == area[v2] )){
            choosed_e[n++] = minpos+1;
            if(area[v1]<area[v2]){
                small=area[v1];
                big = area[v2];
                
            }
            else{
                small=area[v2];
                big = area[v1];
            }
            for(i=0; i<v_num; i++){
                if(area[i]==big)
                    area[i]=small;
            }

            total_weight+=edges[minpos].weight;
        }
        edges[minpos].flag=1;
    }
    printf("%d\n", total_weight);
    sort(n);
    for(i=0; i<n; i++){
        printf("%d ", choosed_e[i]);
    }
    return 0;
}
