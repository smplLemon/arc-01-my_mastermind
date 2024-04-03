#include "../h/my_string.h"

int my_strlen(char* str) {
    int len = 0;
    while(str[len]) {
        len++;
    }
    return len;
}

int my_strcmp(char* str1, char* str2) {
    for(int i = 0; str1[i]; i++) {
        if(str1[i] != str2[i]) {
            return (str1[i]-str2[i]);
        }
    }
    return 0;
}

char* my_strcpy(char* str1, char* str2) {
    for(int i =0; str2[i]; i++) {
        str1[i] = str2[i];
    }
    return str1;
}

int my_isdigit(char *str) {
    int flag = 1;
    for(int i = 0; str[i]; i++) {
        if(str[i] >= 48 && str[i] < 57) {
            flag = 0;
        }
        else {
            flag = 1;
        }
    }
    return flag;
}
