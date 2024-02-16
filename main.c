#include "my_mastermind.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    char* code = parse_arguments(argc, argv);
    
    run_mastermind(code, 10); 
    
    free(code);
    
    return 0;
}
