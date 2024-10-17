#include <stdlib.h>
#include <stdio.h>
int test_dummy() {
    return EXIT_SUCCESS;
}

int main(int argc , char * argv[]) {
    if(argc != 2){
        fprintf(stderr,"usage: ./game_test_tyao dummy\n");
        return EXIT_FAILURE;
    }
    char * dummy = argv[1];
    char * p = "dummy";
    while( *p != '\0' && *dummy != '\0' && (*dummy == *p)){
        dummy++;
        p++;
    }
    if(*p != *dummy){
        fprintf(stderr,"usage: ./game_test_tyao dummy\n");
        return EXIT_FAILURE;
    }
    return test_dummy();
}