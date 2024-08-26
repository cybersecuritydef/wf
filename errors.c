#include <stdio.h>
#include <stdlib.h>

#include <curl/curl.h>

#include "errors.h"

void die(const char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(EOF);
}

void errors(int errcode){
    if(errcode == EOF)
        perror("");
    else
        fprintf(stderr, "%s\n", curl_easy_strerror(errcode));
}
