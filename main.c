#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const char targetPasswd[] = "99VEC49CQ4cf";

char *generateRandomString(int len) {
    char *output = malloc(len * sizeof(char));

    for (int i = 0; i < len; i++) {
        output[i] = alphabet[rand() % strlen(alphabet)];
    }

    return output;
}

/*
        |123456789012|
        |------------|
        |aaaaaaaaaaaa|
        |aaaaaaaaaaab|
        |    ...     |
        |999999999998|
        |999999999999|  
    */
char *generateSortedString(int len, int count) {
    

    char *output = malloc(len * sizeof(char));

    for (int i = len-1; i >= 0; i--) {
        for(int j = 0; j <= 62; j++) {
            output[i] = alphabet[j];
            
        }
    }

    // for (int i = 0; i < len; i++) {
    //     output[i] = alphabet[count % 62];     
    // }

    
    
    return output;
}

int printOutput(int count, char *beFoundPasswd) {
    FILE *fptr;

    fptr = fopen("result_passwd.txt","w");
    if(fptr == NULL){
        printf("\n[!]FILE ERROR!\n");
        exit(0);
    }

    fprintf(fptr,"[+]Target Passwd: %s\t COUNT %d --> Be Found Passwd: %s\n",targetPasswd,count,beFoundPasswd);
    printf("\n[+]Target Passwd: %s\t COUNT %d --> Be Found Passwd: %s\n",targetPasswd,count,beFoundPasswd);
    
    fclose(fptr);
    return 1;
}

int findPasswd(int len){
    int count = 0;
    int running = 1;
    
    while (running) {
        /* 
         * Memory management magic by: Berkay Çubuk <berkaycubuk.com>
         */

        // char *passwd = generateRandomString(len);
        char *passwd = generateSortedString(len, count);
        count++;

        printf("[-]COUNT %d %s\n",count,passwd); // REMOVE THIS
        
        if (!(count % 100000000)) {
            // printf("[-]COUNT %d %s\n",count,passwd);
        }
        
        if (passwd == targetPasswd) {
            running = 0;
            printOutput(count, passwd);
        }
        free(passwd);
    }

    return 1;
}

int main() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    
    findPasswd(12);

    return 1;
}
