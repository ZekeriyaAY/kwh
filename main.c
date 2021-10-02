#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int randNum(int n) {
    return rand() % n;
}

char *randomString(int len) {
    char *output = malloc(len * sizeof(char));

    for (int i = 0; i < len; i++) {
        output[i] = alphabet[randNum(strlen(alphabet))];
    }

    return output;
}

int main() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    srand((time_t)ts.tv_nsec);
    printf("Output: %s\n", randomString(12));

    return 1;
}
