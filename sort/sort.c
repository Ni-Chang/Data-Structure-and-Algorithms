//
//  main.c
//  sort
//
//  Created by xiaonizi on 2018/5/31.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int selectSort(int arr[], int n){
    int i, j, d, temp, count = 0;
    for(i=0; i<n-1; i++){
        d=i;
        for(j=i+1; j<n; j++){
            count++;
            if(arr[j]<arr[d])
                d=j;
        }
        if(d!=i){
            temp = arr[d];
            arr[d]=arr[i];
            arr[i]=temp;
        }
    }
    return count;
}

int bubbleSort(int arr[], int n){
    int i, j, flag=1, count = 0, temp;
    for(i=n-1; i>0&&flag==1; i--){
        flag = 0;
        for(j = 0; j < i; j++){
            count++;
            if(arr[j]>arr[j+1]){
                flag = 1;
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return count;
}

void adjust(int arr[], int i, int n, int *count){
    int j, temp;
    temp = arr[i];
    j = 2*i+1;
    while(j<n){
        if(j+1<n && arr[j]<arr[j+1])
            j++;
        
        (*count)++;
        if(temp<arr[j]){
            arr[(j-1)/2]=arr[j];
            j=2*j+1;
        }
        else
            break;
    }
    arr[(j-1)/2]=temp;
}

int heapSort(int arr[], int n){
    int i, temp, count = 0;
    for(i=n/2-1; i>=0; i--){
        adjust(arr, i, n, &count);
    }
    for(i = n-1; i>=1; i--){
        temp = arr[i];
        arr[i]=arr[0];
        arr[0]=temp;
        adjust(arr, 0, i, &count);
    }
    return count;
}

void merge(int x[], int tmp[],int left, int leftend, int rightend, int *count){
    int i=left, j=leftend+1, q=left;
    while(i<=leftend && j<=rightend){
        (*count)++;
        if(x[i]<=x[j])
            tmp[q++]=x[i++];
        else
            tmp[q++]=x[j++];
    }
    while(i<=leftend)
        tmp[q++]=x[i++];
    while(j<=rightend)
        tmp[q++]=x[j++];
    for(i=left; i<=rightend; i++)
        x[i]=tmp[i];
}

void mSort(int arr[], int temp[], int left, int right, int *count){
    int mid;
    if(left<right){
        mid = (left + right)/2;
        mSort(arr, temp, left, mid, count);
        mSort(arr, temp, mid+1, right, count);
        merge(arr, temp, left, mid, right, count);
    }
}

int mergeSort(int arr[], int n){
    int *temp, count=0;
    temp = (int *)malloc(sizeof(int)*n);
    if(temp!=NULL){
        mSort(arr, temp, 0, n-1, &count);
        free(temp);
    }
    return count;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void qSort(int k[ ],int left,int right, int *count)
{
    int i, last;
    if(left<right){
        last=left;
        for(i=left+1;i<=right;i++){
            (*count)++;
            if(k[i]<k[left])
                swap(&k[++last],&k[i]);
        }
        swap(&k[left],&k[last]);
        qSort(k,left,last-1, count);
        qSort(k,last+1,right, count);
    }
}
/*
 void qSort(int arr[], int s, int t, int *count){
 if(s<t){
 int i = 0, j = t+1, temp, key = arr[s];
 do{
 
 do{
 (*count)++;
 i++;
 }while(key>arr[i] && i!=t);
 (*count)--;
 do{
 (*count)++;
 j--;
 }while(key<arr[j] && j!=s);
 (*count)--;
 if(i<j){
 temp = arr[i];
 arr[i] = arr[j];
 arr[j] = temp;
 }
 }while(i<j);
 temp = arr[s];
 arr[s] = arr[j];
 arr[j] = temp;
 qSort(arr, s, j-1, count);
 qSort(arr, j+1, t, count);
 }
 }
 */
int quickSort(int arr[], int num){
    int count = 0;
    qSort(arr, 0, num-1, &count);
    return count;
}



int main(){
    int num, method, i, count;
    scanf("%d %d", &num, &method);
    int original[num];
    for(i=0; i<num; i++){
        scanf("%d", &original[i]);
    }
    switch(method){
        case 1:
            count = selectSort(original, num);
            for(i=0; i<num; i++){
                printf("%d ", original[i]);
            }
            printf("\n%d", count);
            break;
        case 2:
            count = bubbleSort(original, num);
            for(i=0; i<num; i++){
                printf("%d ", original[i]);
            }
            printf("\n%d", count);
            break;
        case 3:
            count = heapSort(original, num);
            for(i=0; i<num; i++){
                printf("%d ", original[i]);
            }
            printf("\n%d", count);
            break;
        case 4:
            count = mergeSort(original, num);
            for(i=0; i<num; i++){
                printf("%d ", original[i]);
            }
            printf("\n%d", count);
            break;
        case 5:
            count = quickSort(original, num);
            for(i=0; i<num; i++){
                printf("%d ", original[i]);
            }
            printf("\n%d", count);
            break;
    }
    return 0;
}
