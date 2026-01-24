#include <stdio.h> //define printf
#include <stdlib.h> //define getenv, free
#include <string.h> //define strtok
#include <stdbool.h> //define bool
#include <unistd.h> //define getcwd, chdir

int main(){
    char *path = getenv("PATH"); //getenv gets path variable

    if ( path == NULL ) {
        perror("getenv error");
        return 1;
    }

    char *split = strtok(path, ":");
    while ( split != NULL ) {
        //printf("Splir: %s\n", split);
        split = strtok(NULL, ":");
    }

    char input[1024];
    bool close = false; 
    while (!close){
        printf("$ ");
        fflush(stdout); //displayed immediately

        if (fgets(input, sizeof(input), stdin) == NULL) {//check if fgets returns NULL
            perror("\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';//necessary because fgets includes newline character

        if (strcmp(input, "exit") == 0) {//compare input with "exit\n"
            close = true;
            continue;
        }

        //checks for pwd
        if (strcmp(input, "pwd") == 0) { 
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("getcwd error ");
            }
            continue;
        }

        //checks for cd
        if (strncmp(input, "cd ", 3) == 0) { //check if input starts with "cd " and has a space
            char *dir = input + 3; //get directory after "cd "
            if (chdir(dir) != 0) {
                perror("chdir error ");
            }
            continue;
        }
        //printf("Unknown command: %s\n", input); //print unknown command
        //otherwise loop over the path directories, copying each path into a temporary string
        char *directory = strtok(path, ":");
        while(directory != NULL) {
            char temp[1024];
            snprintf(temp, sizeof(temp), "%s/%s", directory, input); //construct full path
            printf("%s\n", temp);
            directory = strtok(NULL, ":");
        }
    }
    return 0;
}