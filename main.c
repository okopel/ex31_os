#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#define BUFFER_SIZE 10

int main(int argc, char **argv) {
    int status = 1;
    printf("%s,%s\n", argv[1], argv[2]);
    // open the Files
    int in, out;
    if ((in = open(argv[1], O_RDONLY)) == -1) {
        printf("ERROR\n");
        exit(0);
    }
    if ((out = open(argv[2], O_RDONLY)) == -1) {
        printf("ERROR\n");
        exit(0);
    }
    char bufA[BUFFER_SIZE];
    char bufB[BUFFER_SIZE];
    int indexA = 0, indexB = 0;
    size_t reader, readerB;
    while (1) {
        if ((indexA % BUFFER_SIZE) == 0) {
            reader = read(in, bufA, sizeof(bufA));
        }
        if ((indexB % BUFFER_SIZE) == 0) {
            readerB = read(out, bufB, sizeof(bufB));
        }
        if (reader < 0 && readerB <= 0) {
            break;
        }
        char A = bufA[indexA % BUFFER_SIZE];
        char B = bufB[indexB % BUFFER_SIZE];
        if (A == B) {
            indexA++;
            indexB++;
            continue;
        } else if (A == '\n' || A == ' ' || A == '\t') {
            status = 3;
            indexA++;
        } else if (B == '\n' || B == ' ' || B == "\t") {
            status = 3;
            indexB++;
        } else if (abs(A - B) == abs('A' - 'a') && (isalpha(A) && isalpha(B))) {
            status = 3;
            indexA++;
            indexB++;
        } else if (A != B) {
            status = 2;
            break;
        }
    } //end of while
    if (status == 2) {
        printf("2");
    } else if (status == 3) {
        printf("3");
    } else if (status == 1) {
        printf("1");
    }
    return 0;
}

#pragma clang diagnostic pop