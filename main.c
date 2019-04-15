/**
 * Ori Kopel
 * 205533151
 * Ex3_1
 * April 19
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


#define BUFFER_SIZE 10

/**
 * check if A is big letter and B is little letter (WLOG)
 * @param A the first char
 * @param B the sec char
 * @return true if there is couple of letters
 */
bool checkForSemiAlpha(char A, char B);

/**
 * check for witespace
 * @param c the char
 * @return true if whiteSpace
 */
bool checkForSemi(char c);

/**
 * Main
 * @param argc =3
 * @param argv the pathes
 * @return 1 for identify files, 3 for semi files, 2 else.
 */
int main(int argc, char **argv) {
    if (argc != 3) {
        perror("NOT 3 PARAMS\n");
        exit(-1);
    }
    int status = 1;//status of identify
    // open the Files
    int in, out;
    if ((in = open(argv[1], O_RDONLY)) == -1) {
        printf("ERROR open argv1\n");
        exit(-1);
    }
    if ((out = open(argv[2], O_RDONLY)) == -1) {
        printf("ERROR open argv2\n");
        exit(-1);
    }
    char bufA[BUFFER_SIZE];
    char bufB[BUFFER_SIZE];

    int indexA = 0, indexB = 0;
    size_t readerA = 0, readerB = 0;
    char A = 0, B = 0;
    while (1) {
        if ((indexA % BUFFER_SIZE) == 0) {
            readerA = read(in, bufA, sizeof(bufA));
        }
        if ((indexB % BUFFER_SIZE) == 0) {
            readerB = read(out, bufB, sizeof(bufB));
        }
        if (readerA <= 0 && readerB <= 0) {//both of the files ended
            break;
        }
        if (readerA >= 0) {//check the next char
            A = bufA[indexA % BUFFER_SIZE];
        }
        if (readerB >= 0) {
            B = bufB[indexB % BUFFER_SIZE];
        }
        if (A == B) {//identify case
            if (A == 0) {//EOF case
                break;
            }
            indexA++;
            indexB++;
            continue;
        } else if (checkForSemi(A)) {//this case is semi because A!=B
            status = 3;
            indexA++;
        } else if (checkForSemi(B)) {
            status = 3;
            indexB++;
        } else if (checkForSemiAlpha(A, B)) {
            status = 3;
            indexA++;
            indexB++;
        } else if (A != B) {
            status = 2;
            break;
        }
    } //end of while
    close(in);
    close(out);
    return status;
}

bool checkForSemi(char c) {
    return (c == '\n' || c == ' ' || c == '\t');
}

bool checkForSemiAlpha(char A, char B) {
    return (abs(A - B) == abs('A' - 'a') && (isalpha(A) && isalpha(B)));
}
