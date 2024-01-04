#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <time.h>
    #define CODELEN 4
    typedef unsigned short flag;

    static flag matched[CODELEN];

    void mystrcpy(char *, char *);
    void readinput(char *);
    int count_wellplaced(char *, char *);
    int count_misplaced(char *, char *);
