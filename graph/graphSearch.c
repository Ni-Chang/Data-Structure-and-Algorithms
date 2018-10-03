//
//  main.c
//  graphSearch
//
//  Created by xiaonizi on 2018/6/15.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct vertex{
    int vertex;
    struct vertex *link;
}Vertex;

typedef struct queue{
    int queue[101];
    int front, rear;
}Queue;

int vertex_num;

void addpath(Vertex G[], int v1, int v2){
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));
    v->vertex = v2;
    v->link = NULL;
    Vertex *temp = &G[v1];
    Vertex *new = temp->link;
    while(new!=NULL && new->vertex < v2){
        temp = temp->link;
        new = new->link;
    }
    v->link = new;
    temp->link = v;
    v = (Vertex *)malloc(sizeof(Vertex));
    v->vertex = v1;
    v->link = NULL;
    temp = &G[v2];
    new = temp->link;
    while(new!=NULL && new->vertex < v1){
        temp = temp->link;
        new = new->link;
    }
    v->link = new;
    temp->link = v;
}

void DFS(Vertex G[], int v, int visited[]){
    visited[v] = 1;
    printf("%d ", v);
    Vertex *p = G[v].link;
    while(p!=NULL){
        if(visited[p->vertex]==0){
            DFS(G, p->vertex, visited);
        }
        p = p->link;
    }
}

void traverseD(Vertex G[], int d){
    int visited[vertex_num], i;
    for(i = 0; i < vertex_num; i++){
        visited[i] = 0;
    }
    for(i = 0; i<vertex_num; i++){
        if(visited[i] == 0 && i!=d){
            DFS(G, i, visited);
        }
    }
}

void enQueue(Queue *q, int item){
    q->queue[q->rear] = item;
    q->rear = (q->rear+1)%101;
}

int deQueue(Queue *q){
    int item = q->queue[q->front];
    q->front = (q->front+1)%101;
    return item;
}

int emptyQ(Queue q){
    if(q.front == q.rear)
        return 1;
    return 0;
}


void BFS(Vertex G[], int v, int visited[], Queue q){
    visited[v] = 1;
    printf("%d ", v);
    enQueue(&q, v);\
    while(!emptyQ(q)){
        v = deQueue(&q);
        Vertex *p = G[v].link;
        while(p!=NULL){
            if(visited[p->vertex]==0){
                visited[p->vertex] = 1;
                printf("%d ", p->vertex);
                enQueue(&q, p->vertex);
            }
            p = p->link;
        }
    }
    
}

void traverseB(Vertex G[], int d){
    int visited[vertex_num], i;
    Queue q;
    q.front = 0;
    q.rear = 0;
    for(i = 0; i < vertex_num; i++){
        visited[i] = 0;
    }
    for(i = 0; i<vertex_num; i++){
        if(visited[i] == 0 && i!=d){
            BFS(G, i, visited, q);
        }
    }
}

void delete(Vertex G[], int d){
    G[d].link = NULL;
    int i;
    Vertex *p, *old_p;
    for(i = 0; i<vertex_num; i++){
        old_p = &G[i];
        p = G[i].link;
        while(p!=NULL){
            if(p->vertex==d){
                old_p->link=p->link;
                free(p);
                
            }
            else{
                old_p = old_p->link;
            }
            p = old_p->link;
        }
    }
}

int main(){
    int edge_num, i, v1, v2, d;
    scanf("%d %d", &vertex_num, &edge_num);
    Vertex G[vertex_num];
    for(i=0; i<vertex_num; i++){
        G[i].vertex = i;
        G[i].link = NULL;
    }
    for(i = 0; i<edge_num; i++){
        scanf("%d %d", &v1, &v2);
        addpath(G, v1, v2);
    }
    scanf("%d", &d);
    traverseD(G, -1);
    printf("\n");
    traverseB(G, -1);
    printf("\n");
    
    delete(G, d);
    
    traverseD(G, d);
    printf("\n");
    traverseB(G, d);
    printf("\n");
    return 0;
}

