/*
 * This project is licensed under GPLv3
 *
 * Copyright (C) 2021 Zekeriya Ay <zekeriyaay.com>
 * Copyright (C) 2021 Berkay Çubuk <berkaycubuk.com>
 */

#include "kwh.h"

const char alphabet[] = "wQk83Ocp9b6vdIYLRXrDZN7Cg02nVWhtKsoG5uT4yPlxzeaiUqHM1EmfBjFJAS";
const char targetPasswd[] = "99VEC49CQ4cf";
const int len = 12;

char *generateRandomString(int len, char *output) {
    for (int i = 0; i < len; i++) {
        output[i] = alphabet[rand() % strlen(alphabet)];
    }

    return output;
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

int findRandomPasswd() {
    int count = 0;
	int running = 1;

    while (running) {
        /* 
         * Memory management magic by: Berkay Çubuk <berkaycubuk.com>
         */
        char *passwd = malloc(len * sizeof(char));

        passwd = generateRandomString(len, passwd);
        
        count++;
        if (!(count % 100000000)) {
            printf("[-]COUNT %d %s\n",count,passwd);
        }
        
        if (passwd == targetPasswd) {
            running = 0;
            printOutput(count, passwd);
        }
        free(passwd);
    }

    return 1;
}

int findSortedPasswd() {
	char *passwd = malloc(len * sizeof(char));
	int count = 0;
	int countLen = 1;

	for (int a = 0; a < strlen(alphabet); a++) {
	for (int b = 0; b < strlen(alphabet); b++) {	
	for (int c = 0; c < strlen(alphabet); c++) {
	for (int d = 0; d < strlen(alphabet); d++) {
	for (int e = 0; e < strlen(alphabet); e++) {
	for (int f = 0; f < strlen(alphabet); f++) {
	for (int g = 0; g < strlen(alphabet); g++) {
	for (int h = 0; h < strlen(alphabet); h++) {
	for (int i = 0; i < strlen(alphabet); i++) {
	for (int j = 0; j < strlen(alphabet); j++) {
	for (int k = 0; k < strlen(alphabet); k++) {
	for (int l = 0; l < strlen(alphabet); l++) {
		passwd[0] = alphabet[a];	
		passwd[1] = alphabet[b];	
		passwd[2] = alphabet[c];	
		passwd[3] = alphabet[d];	
		passwd[4] = alphabet[e];	
		passwd[5] = alphabet[f];	
		passwd[6] = alphabet[g];	
		passwd[7] = alphabet[h];	
		passwd[8] = alphabet[i];	
		passwd[9] = alphabet[j];	
		passwd[10] = alphabet[k];	
		passwd[11] = alphabet[l];	
        
//	printf("[-]COUNT %d %s\n",++count,passwd);
		count++;
        if (!(count % 1000000000)) {
            printf("[-]COUNT %dB %s\n",countLen++,passwd);
        }
        
        if (passwd == targetPasswd) {
            printOutput(count, passwd);
        	free(passwd);
			return 1;
        }
	}}}}}}}}}}}}

    free(passwd);
	return 0;
			
}

int main() {
    // precise seed generation
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    // findRandomPasswd(len);
	findSortedPasswd();

    // be positive :)
    return 1;
}
