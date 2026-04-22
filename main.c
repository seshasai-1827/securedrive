#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    char timestamp[40];
    char content[1000];
    char img_path[40]; 
    char audio_path[40];
}entry;

void getfilename(char* filename, size_t capacity){
    struct tm* currtime;
    time_t now = time(NULL);
    currtime = localtime(&(now));
    strftime(filename,capacity,"./data/%d-%m-%Y.txt",currtime);
}

char* get_timestamp(){
    struct tm* currtime;
    time_t now = time(NULL);
    currtime = localtime(&now);
    char *t = asctime(currtime);
    t[strcspn(t,"\n")]='\0';
    return t;
}

entry* get_entry(){
    entry* new_entry = malloc(sizeof(entry));
    strcpy(new_entry->timestamp,get_timestamp());
    printf("provide entry : \n");
    fgets(new_entry->content,1000,stdin);
    return new_entry;
}

int main(void){
    FILE* fp;
    char filename[100];
    getfilename(filename,sizeof(filename));
    fp = fopen(filename,"a");
    entry* en = get_entry();
    fprintf(fp,"\n[%s] : %s",en->timestamp,en->content);
    fclose(fp);
    free(en);
    return 0;
}