//
//  main.c
//  tail
//
//  Created by xiaonizi on 2018/4/13.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void lastfewlines(int num, char filename[]){
    FILE *fp=fopen(filename, "r");
    char buf[100];
    int linecount=0, i;
    while(fgets(buf, 90, fp)!=NULL)
        linecount++;
    fclose(fp);
    fp=fopen(filename, "r");
    for(i=0; i<linecount; i++){
        fgets(buf, 90, fp);
        if(i>=linecount-num){
            printf("%s", buf);
        }
    }
    fclose(fp);
}

int main(int argc, char **argv) {
    int num=10;
    char *filename;
    char *cnum;
    if(argc==3){
        cnum=argv[1]+1;
        num=atoi(cnum);
        filename=argv[2];
    }
    else{
        filename=argv[1];
    }
    lastfewlines(num, filename);
    return 0;
}
