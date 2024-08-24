#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "payloads.h"



int make_payloads(const char *url, const char *wordlist, const char *extlist, payloads *payload){
    FILE *fword = NULL;
    char buf[LEN_BUF] = {'\0'};
    char *p = NULL;
    int status = 0;
    if((fword = fopen(wordlist, "r")) != NULL){
        while(fgets(buf, sizeof(buf), fword) != NULL){
            buf[strlen(buf) - 1] = '\0';
            asprintf(&p, "%s%s", url, buf);
            payload->payload = add_first(payload->payload, p);
            payload->count += 1;
            free(p);
        }
        fclose(fword);
    }
    else
        status = EOF;

    return status;
}
