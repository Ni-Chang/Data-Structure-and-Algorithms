//
//  main.c
//  subtract
//
//  Created by xiaonizi on 2018/4/8.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <string.h>

void reverse(char str[]){
    int i=0, n = strlen(str);
    int j=n-1;
    if(i==j)
        return;
    char temp;
    while(i<j){
        temp=str[i];
        str[i]=str[j];
        str[j]=temp;
        i++;
        j--;
    }
    str[n]='\0';
}

int is_b_bigger(char a[], char b[]){
    int alen=strlen(a), blen=strlen(b), i;
    if(alen>blen){
        for(i=blen; i<alen; i++){
            b[i]='0';
        }
        b[i]='\0';
        return 0;
    }
    else if(blen>alen){
        for(i=alen; i<blen; i++){
            a[i]='0';
        }
        a[i]='\0';
        return 1;
    }
    for(i=alen-1; i>=0; i--){
        if(a[i]>b[i]){
            return 0;
        }
        else if(a[i]<b[i]){
            return 1;
        }
    }
    return -1;
}
void nozero(char a[]){
    int n=strlen(a);
    int i, sub=0;
    for(i=0; i<n-1; i++){
        if(a[i]=='0')
            sub++;
        else
            break;
    }
    for(i=0; i<=(n-sub); i++){
        a[i]=a[i+sub];
    }
}

int main(int argc, const char * argv[]) {
    char a[81], b[81];
    scanf("%s", a);
    scanf("%s", b);
    nozero(a);
    nozero(b);
    reverse(a);
    reverse(b);
    int flag=is_b_bigger(a, b);
    if(flag==-1){
        printf("%d", 0);
        return 0;
    }
    char result[80];
    int i, temp, tp=0;
    if(flag==0){
        for(i=0; i<strlen(a); i++){
            temp=a[i]-b[i]-tp;
            if(temp>=0){
                result[i]=temp+'0';
                tp=0;
            }
            else{
                result[i]=temp+10+'0';
                tp=1;
            }
        }
    }
    else{
        for(i=0; i<strlen(a); i++){
            temp=b[i]-a[i]-tp;
            if(temp>=0){
                result[i]=temp+'0';
                tp=0;
            }
            else{
                result[i]=temp+10+'0';
                tp=1;
            }
        }
    }
/*    if(temp==0)
        same++;
    int n=strlen(result);
    result[n-same]='\0';*/
    result[i]='\0';
    reverse(result);
    nozero(result);
    if(flag==0)
        printf("%s", result);
    else
        printf("-%s", result);
    return 0;
}

