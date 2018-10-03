//
//  main.c
//  indivialPath
//
//  Created by xiaonizi on 2018/6/17.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct edge{
    int edgenum, vertex;
    struct edge *link;
}Edge;

typedef struct ver{
    Edge *link;
}Ver;

void addpath(Ver G[], int d, int v1, int v2){
    Edge *v = (Edge *)malloc(sizeof(Edge));
    v->edgenum = d;
    v->vertex = v2;
    v->link = NULL;
    if(G[v1].link == NULL || G[v1].link->edgenum > d){
        v->link = G[v1].link;
        G[v1].link = v;
    }
    else{
        Edge *temp = G[v1].link;
        Edge *new = temp->link;
        while(new!=NULL && new->edgenum < d){
            temp = temp->link;
            new = temp->link;
        }
        v->link = new;
        temp->link = v;
    }
    
    v = (Edge *)malloc(sizeof(Edge));
    v->edgenum = d;
    v->vertex = v1;
    v->link = NULL;
    if(G[v2].link == NULL || G[v2].link->edgenum > d){
        v->link = G[v2].link;
        G[v2].link = v;
    }
    else{
        Edge *temp = G[v2].link;
        Edge *new = temp->link;
        while(new!=NULL && new->edgenum < d){
            temp = temp->link;
            new = temp->link;
        }
        v->link = new;
        temp->link = v;
    }
}

int path[1000];
int vertex_num;

void DFS(Ver G[], int v, int level, int visited[]){
    if(v == vertex_num-1){
        int i;
        for(i=0; i<level; i++){
            printf("%d ", path[i]);
        }
        printf("\n");
        return;
    }
    
    Edge *p = G[v].link;
    while(p!=NULL){
        if(visited[p->vertex]==0){
            path[level] = p->edgenum;
            visited[p->vertex]=1;
            DFS(G, p->vertex, level+1, visited);
            visited[p->vertex]=0;
        }
        p = p->link;
    }
}

void traverseD(Ver G[]){
    int visited[vertex_num], i;
    visited[0]=1;
    for(i = 1; i < vertex_num; i++){
        visited[i] = 0;
    }
    //for(i = 0; i<vertex_num; i++){
      //  if(visited[i] == 0){
            DFS(G, 0, 0, visited);
        //}
    //}
}


int main() {
    int edge_num, i, v1, v2, d;
    scanf("%d %d", &vertex_num, &edge_num);
    Ver G[vertex_num];
    for(i=0; i<vertex_num; i++){
        G[i].link = NULL;
    }
    for(i = 0; i<edge_num; i++){
        scanf("%d %d %d",&d, &v1, &v2);
        addpath(G, d, v1, v2);
    }
    traverseD(G);
    return 0;
}
