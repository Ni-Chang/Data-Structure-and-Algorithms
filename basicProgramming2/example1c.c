//
//  main.c
//  example1c
//
//  Created by xiaonizi on 2018/4/8.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int changetoint(char str[]){
    int i=0, result=0;
    for(i=0; i<strlen(str); i++){
        result=result*10+(str[i]-'0');
    }
    return result;
}

int multi_divi(char syb[], int numbers[]){
    int result=0, i=0, j=0, k=0, temp;
    int new_numbers[100], new_syb[100];
    do{
        temp=numbers[i];
        while(syb[i]=='*'||syb[i]=='/'){
            if(syb[i]=='*')
                temp *= numbers[i+1];
            else
                temp /= numbers[i+1];
            i++;
        }
        new_numbers[j++]=temp;
        new_syb[k++]=syb[i++];
    }while (new_syb[k-1]!='=');
    k=0;
    result=new_numbers[0];
    while(new_syb[k]!='='){
        if(new_syb[k]=='+'){
            result += new_numbers[k+1];
        }
        else
            result -= new_numbers[k+1];
        k++;
    }
    return result;
}

int main() {
    char str[100];
    gets(str);
    int i=0, j=0;
    while(str[i]!='\0'){
        if(str[i]!=' '){
            str[j]=str[i];
            j++;
        }
        i++;
    }
    str[j]='\0';
    i=0;
    j=0;
    int k=0, l=0;
    char temp_str[100];
    int numbers[100];
    char syb[100];
    do{
        while(str[i]>='0'&&str[i]<='9'){
            temp_str[j++]=str[i++];
        }
        temp_str[j]='\0';
        numbers[k++]=changetoint(temp_str);
        temp_str[0]='\0';
        j=0;
        syb[l++]=str[i++];
    }while(syb[l-1]!='=');
    printf("%d", multi_divi(syb, numbers));
    return 0;
}
