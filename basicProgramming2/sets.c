#include <stdio.h>

#define MAXSIZE 100

void sub(int A[], int B[]){
    int i=0, j;
    while(B[i]!=-1){
        j=0;
        while(A[j]!=-1){
            if(A[j]==B[i])
                A[j]=-2;
            j++;
        }
        i++;
    }
}

int main(){
    int A[MAXSIZE], B[MAXSIZE];
    int i=0;
    do{
        scanf("%d", &A[i]);
    }while (A[i++]!=-1);
    i=0;
    do{
        scanf("%d", &B[i]);
    }while (B[i++]!=-1);
    sub(A, B);
    i=0;
    while(A[i]!=-1){
        if(A[i]!=-2)
            printf("%d ", A[i]);
        i++;
    }
}
