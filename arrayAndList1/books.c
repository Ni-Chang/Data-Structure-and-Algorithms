//
//  main.c
//  books
//
//  Created by xiaonizi on 2018/4/19.
//  Copyright © 2018年 xiaonizi. All rights reserved.
//

#include <stdio.h>
#include <string.h>

struct Book{
    char name[51];
    char author[21];
    char publisher[31];
    char date[11];
};

struct Book book_list[500];
int n;

void readbooks(){
    FILE *fpin = fopen("books.txt", "r");
    if(fpin==NULL){
        n=0;
        return;
    }
    char buffer[200];
    int i, j, k;
    for(i=0; fgets(buffer, 199, fpin)!=NULL; i++){
        if(buffer[0]=='\n'||buffer[0]=='\r'){
            continue;
        }
        for(j=0, k=0; buffer[j]!=' '; j++, k++){
            book_list[i].name[k]=buffer[j];
        }
        book_list[i].name[k]='\0';
        for(++j, k=0; buffer[j]!=' '; j++, k++){
            book_list[i].author[k]=buffer[j];
        }
        book_list[i].author[k]='\0';
        for(++j, k=0; buffer[j]!=' '; j++, k++){
            book_list[i].publisher[k]=buffer[j];
        }
        book_list[i].publisher[k]='\0';
        for(++j, k=0; buffer[j]!='\0'&&buffer[j]!='\n'&&buffer[j]!=' '; j++, k++){
            book_list[i].date[k]=buffer[j];
        }
        book_list[i].date[k]='\0';
    }
    n=i;
    fclose(fpin);
}

void sort(){
    int i, j;
    struct Book temp;
    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if(strcmp(book_list[j].name, book_list[j+1].name)>0){
                temp=book_list[j];
                book_list[j]=book_list[j+1];
                book_list[j+1]=temp;
            }
        }
    }
}

void insert(struct Book new_book){
    book_list[n]=new_book;
    n++;
}

void search(char *search_name){
    sort();
    int i;
    for(i=0; i<n; i++){
        if(strstr(book_list[i].name, search_name)!=NULL){
            printf("%-50s%-20s%-30s%-10s\n", book_list[i].name, book_list[i].author, book_list[i].publisher, book_list[i].date);
        }
    }
}

void delete(char *delete_name){
    int i;
    for(i=0; i<n; i++){
        if(strstr(book_list[i].name, delete_name)){
            book_list[i--] = book_list[n-1];
            n--;
        }
    }
}

void store(){
    sort();
    FILE* fpout=fopen("ordered.txt", "w");
    int i;
    for(i=0; i<n; i++){
        fprintf(fpout, "%-50s%-20s%-30s%-10s\n", book_list[i].name, book_list[i].author, book_list[i].publisher, book_list[i].date);
    }
    fclose(fpout);
}

void readinstr(){
    int instr;
    scanf("%d", &instr);
    while(instr!=0){
        if(instr==1){
            struct Book new_book;
            scanf("%s", new_book.name);
            scanf("%s", new_book.author);
            scanf("%s", new_book.publisher);
            scanf("%s", new_book.date);
            insert(new_book);
        }
        else if(instr==2){
            char search_name[51];
            scanf("%s", search_name);
            search(search_name);
        }
        else{
            char delete_name[51];
            scanf("%s", delete_name);
            delete(delete_name);
        }
        scanf("%d", &instr);
    }
    store();
}

int main() {
    readbooks();
    readinstr();
    return 0;
}
