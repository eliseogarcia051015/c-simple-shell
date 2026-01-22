#include <stdio.h> //define printf
#include <stdlib.h> //define malloc, getenv, free
#include <string.h> //define strtok

int main(){
    char *path = getenv("PATH");

    if ( path == NULL ) {
        perror("getenv error");
        return 1;
    }

    printf("Original PATH: %s\n", path);

    char *split = strtok(path, ":");
    while ( split != NULL ) {
        printf("Splir: %s\n", split);
        split = strtok(NULL, ":");
    }

    return 0;
}