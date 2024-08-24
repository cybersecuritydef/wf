#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "payloads.h"

static char *join_payloads(const char *fp, const char *sp){
    char *payload = NULL;
    size_t flen = 0;
    size_t slen = 0;
    if(fp != NULL && sp != NULL){
        flen = strlen(fp);
        slen = strlen(sp);
        if((payload = (char*)calloc((flen + slen + 1), sizeof(char))) != NULL){
            memcpy(payload, fp, flen);
            memcpy(payload + flen, sp, slen);
            payload[flen + slen] = '\0';
            return payload;
        }
    }
    return NULL;
}


int make_payloads(const char *url, const char *wordlist, const char *extlist, payloads *payload){
    FILE *fword = NULL;
    char buf[LEN_BUF] = {'\0'};
    char *p = NULL;
    if((fword = fopen(wordlist, "r")) != NULL){
        while(fgets(buf, sizeof(buf), fword) != NULL){
            buf[strlen(buf) - 1] = '\0';
            p = join_payloads(url, buf);
            payload->payload = add_first(payload->payload, p);
            payload->count += 1;
            free(p);
        }
        fclose(fword);
    }
    else
        return EOF;

    return 0;
}
