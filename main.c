#include <stdio.h>
#include <stdlib.h>


int main() {



    FILE *fp;
    char *line = NULL, *line2 = NULL;
    size_t len = 0;
    ssize_t read;


    fp = fopen("read.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int flag = 0;
    int flag2 = 0;

    while ((read = getline(&line, &len, fp)) != -1) {

        printf("%s", line);
    }

}