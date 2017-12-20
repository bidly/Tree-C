#include <stdio.h>
#include <stdlib.h>
#include <mem.h>


int main() {



    FILE *fp, *fpSize;
    char *line = NULL, *line2 = NULL;
    size_t len = 0;
    ssize_t read;


    fpSize = fopen("Input1.txt", "r");
    fp = fopen("Input1.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int flag = 0;
    int flag2 = 0;
    int sizeOfFirst = 0;


    while ((read = getline(&line, &len, fpSize)) != -1) {
        if(strlen(line) != 1)
            sizeOfFirst++;
    }
    fclose(fpSize);

    int nodes[sizeOfFirst][2];
    int i = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        if(strlen(line) != 1)
        {
            char *token;
            int j = 0;
            token = strtok(line, " ");
            while (token != NULL) {
                nodes[i][j]= atoi(token);
                token = strtok(NULL, " ");
                j++;
            }
            i++;
        }
    }
    for(i = 0 ; i<sizeOfFirst; i++)
        printf("%d ", nodes[i][1]);
}