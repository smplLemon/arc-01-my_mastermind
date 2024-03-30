#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <time.h>
    #define CODELEN 4
    typedef unsigned short flag;

    //the matched array keeps track of which pieces have been counted so that a piece doesn't get counted as both well placed and misplaced
    static flag matched[CODELEN];

    void mystrcpy(char *, char *);
    void readinput(char *);
    int count_wellplaced(char *, char *);
    int count_misplaced(char *, char *);
    