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

    //moved strok here to avoid modifying original path variable

    char input[1024];
    bool close = false; 
    while (!close){
        memset(input, 0, sizeof(input)); //clear input buffer
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
        //split input by spaces to get command and arguments
        char *command[100];
        int entrys = 0;
        char *token = strtok(input, " ");
        while (token != NULL && entrys < 100) {
            command[entrys++] = token;
            token = strtok(NULL, " ");
        }
        command[entrys] = NULL; //null terminate the array

        //check if input is an absolute or relative path
        if (input[0] == '/') { //if input contains a slash
            printf("%s is an absolute path\n", input);
            for (int i = 0; i < entrys; i++) {
                printf("arg[%d]: %s\n", i, command[i]);
            }
            continue;
        }else if (strchr(input, '/') != NULL)
        {
            printf("%s is a relative path\n",input);
            for (int i = 0; i < entrys; i++) {
                printf("arg[%d]: %s\n", i, command[i]);
            }
        }
        

        // loop over the path directories, copying each path into a temporary string
        char path_copy[1024];
        strncpy(path_copy, path, sizeof(path_copy));
        path_copy[sizeof(path_copy)-1] = '\0';

        char *directory = strtok(path_copy, ":");
        bool found = false;

        while(directory != NULL) {
            char temp[1024];
            snprintf(temp, sizeof(temp), "%s/%s", directory, input); //construct full path

            if (access(temp, X_OK) == 0) { //check if file is executable
                printf("located '%s' in PATH at '%s' \n", input, temp);
                found = true;
                break;
            }
            directory = strtok(NULL, ":");
        }
        if (!found) {
            printf("unable to locate executable: '%s'\n", input);
        }

        for (int i = 0; i < entrys; i++) {//print arguments
            printf("arg[%d]: %s\n", i, command[i]);
        }

    }
    return 0;
}