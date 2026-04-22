#include<time.h>
#include<stdio.h>
int main(void){
    struct tm* currtime;
    time_t now = time(NULL);
    currtime = localtime(&now);
    printf("Current time is  : %s",asctime(currtime));
    char filename[100];
    strftime(filename,sizeof(filename),"%d-%m-%Y",currtime);
    printf("name of file : %s.txt",filename);
    return 0;
}