/*
 * This project is licensed under GPLv3
 *
 * Copyright (C) 2021 Zekeriya Ay <zekeriyaay.com>
 * Copyright (C) 2021 Berkay Çubuk <berkaycubuk.com>
 */

#include "kwh.h"

const char alphabet[] = "012345";
const char targetPasswd[] = "99VEC49CQ4cf";
const int len = 3;

char *generateRandomString(int len, char *output) {
    for (int i = 0; i < len; i++) {
        output[i] = alphabet[rand() % strlen(alphabet)];
    }

    return output;
}

int *generateSortedString(int index, int *passwd) {
    if(index <= len) {
        for (int i = 0; i < len+2; i++) {
            if ((passwd[index] + 1) % strlen(alphabet) == 0) {
                passwd[index] = (passwd[index] + 1) % strlen(alphabet);
                generateSortedString(index + 1, passwd);
            } else {
                passwd[index] = (passwd[index] + 1) % strlen(alphabet);
            }
        }
    }
    
    return passwd;
}

int printOutput(int count, char *beFoundPasswd) {
    FILE *fptr;

    fptr = fopen("result_passwd.txt","w");
    if(fptr == NULL) {
        printf("\n[!]FILE ERROR!\n");
        exit(0);
    }

    fprintf(fptr,"[+]Target Passwd: %s\t COUNT %d --> Be Found Passwd: %s\n",targetPasswd,count,beFoundPasswd);
    printf("\n[+]Target Passwd: %s\t COUNT %d --> Be Found Passwd: %s\n",targetPasswd,count,beFoundPasswd);
    
    fclose(fptr);
    return 1;
}

int findPasswd() {
    int count = 0;
    int running = 1;
    int satir = len-1;

    while (running) {
        /* 
         * Memory management magic by: Berkay Çubuk <berkaycubuk.com>
         */
        int *passwd = malloc(len * sizeof(int));
        for (int i = 0; i < len; i++) {
            passwd[i] = 0;
        } 
        printf("[%ld]\n", (passwd[2] + 1) % strlen(alphabet)); // REMOVE THIS

        // passwd = generateRandomString(len, passwd);
        passwd = generateSortedString(satir, passwd);
        satir--;
        
        for (int i = len-1 ; i >= 0; i--) {
            printf("%d", passwd[i]); // REMOVE THIS
        }
        
        
        count++;
        if (count == 2){
            running = 0;
        }

        // if (!(count % 100000000)) {
        //     printf("[-]COUNT %d %s\n",count,passwd);
        // }
        
        // if (passwd == targetPasswd) {
        //     running = 0;
        //     printOutput(count, passwd);
        // }
        free(passwd);
    }

    return 1;
}

int main() {
    // precise seed generation
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    findPasswd(len);

    // be positive :)
    return 1;
}
