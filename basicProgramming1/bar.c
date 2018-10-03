//
//  main.c
//  bar
//
//  Created by xiaonizi on 2018/3/17.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>

void Readin(int times[]) {
    char letter = 'A';
    while (letter != EOF) {
        letter = getchar();
        if(letter < 'a' || letter > 'z')
            continue;
        times[letter-'a']++;
    }
}

int FindMax(int times[]) {
    int max = times[0], i = 1;
    for(; i<26; i++) {
        if(max < times[i])
            max=times[i];
    }
    return max;
}

int main() {
    int times[26], max_now, i;
    for(i=0; i<26; i++)
        times[i] = 0;
    Readin(times);
    max_now = FindMax(times);
    while (max_now != 0) {
        for(i=0; i<26; i++){
            if(times[i] == max_now){
                printf("*");
                times[i]--;
            }
            else
                printf(" ");
        }
        printf("\n");
        max_now = FindMax(times);
    }
    for(i=0; i<26; i++)
        printf("%c", 'a'+i);
    printf("\n");
    return 0;
}
