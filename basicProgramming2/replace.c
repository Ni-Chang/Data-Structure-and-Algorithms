//
//  main.c
//  replace
//
//  Created by xiaonizi on 2018/4/8.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include<stdio.h>
#include<string.h>
int main()
{
    FILE*in,*out;
    char a[100],b[100],s[2000],c;
    int i,j,k,bj=0,m=0,n;
    gets(a);
    gets(b);
    n=strlen(a);
    in=fopen("filein.txt","r");
    out=fopen("fileout.txt","w");
    while((c=fgetc(in))!=EOF){
        s[m++]=c;
    }
    s[m]='\0';
    for(i=0;i<=(m-n);){
        for(k=i,j=0;j<n;j++,k++){
            if((s[k]!=a[j])&&(s[k]!=(a[j]-32))&&(s[k]!=(a[j]+32))){
                bj=1;
                break;
            }
        }
        if(bj==1){
            fputc(s[i],out);
            i++;
            bj=0;
        }
        else{
            fputs(b,out);
            i+=n;
        }
    }
    for(i=(m-n+1);i<m;i++)
        fputc(s[i],out);
    fclose(in);
    fclose(out);
    return 0;
}

