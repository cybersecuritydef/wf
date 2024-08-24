#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

void die(const char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(EOF);
}
