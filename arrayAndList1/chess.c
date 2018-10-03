#include <stdio.h>

int main(){
    int a[21][21], i, j;
    for(i=0; i<21; i++){
        a[0][i]=3;
        a[20][i]=3;
        a[i][0]=3;
        a[i][20]=3;
    }
    for(i=1; i<20; i++){
        for(j=1; j<20; j++){
            scanf("%d", &a[i][j]);
        }
    }
    for(i=1; i<=19; i++){
        for(j=1; j<=19; j++){
            if(a[i][j]!=0){
                if(i<=16){
                    if(a[i-1][j]==0||a[i+4][j]==0){
                        if(a[i][j]==a[i+1][j]&&a[i][j]==a[i+2][j]&&a[i][j]==a[i+3][j]&&a[i][j]==a[i+4][j]){
                            printf("%d:%d,%d\n", a[i][j], i, j);
                            return 0;
                        }
                    }
                }
                if(j<=16){
                    if(a[i][j-1]==0||a[i][j+4]==0){
                        if(a[i][j]==a[i][j+1]&&a[i][j]==a[i][j+2]&&a[i][j]==a[i][j+3]&&a[i][j]==a[i][j+4]){
                            printf("%d:%d,%d\n", a[i][j], i, j);
                            return 0;
                        }
                    }
                }
                if(i<=16&&j<=16){
                    if(a[i-1][j-1]==0||a[i+4][j+4]==0){
                        if(a[i][j]==a[i+1][j+1]&&a[i][j]==a[i+2][j+2]&&a[i][j]==a[i+3][j+3]&&a[i][j]==a[i+4][j+4]){
                            printf("%d:%d,%d\n", a[i][j], i, j);
                            return 0;
                        }
                    }
                }
                if(i<=16&&j>=4){
                    if(a[i-1][j+1]==0||a[i+4][j-4]==0){
                        if(a[i][j]==a[i+1][j-1]&&a[i][j]==a[i+2][j-2]&&a[i][j]==a[i+3][j-3]&&a[i][j]==a[i+4][j-4]){
                            printf("%d:%d,%d\n", a[i][j], i, j);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    printf("No\n");
    return 0;
}
