#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "payloads.h"



int make_payloads(const char *url, const char *wordlist, const char *extlist, payloads *payload){
    FILE *file = NULL;
    char buf[LEN_BUF] = {'\0'};
    char *p = NULL;
    payloads *cur = NULL;
    int status = 0;
    if((file = fopen(wordlist, "r")) != NULL){
        while(fgets(buf, sizeof(buf), file) != NULL){
            buf[strlen(buf) - 1] = '\0';
            asprintf(&p, "%s%s", url, buf);
            payload->payload = add_first(payload->payload, p);
            payload->count += 1;
            free(p);
        }
        fclose(file);
    }
    else
        status = EOF;

    if(extlist != NULL){
        if((file = fopen(extlist, "r")) != NULL){
            cur = payload;
           while(fgets(buf, sizeof(buf), file) != NULL){
               buf[strlen(buf) - 1] = '\0';
               while(cur != NULL){
                   asprintf(&p, "%s%s", cur->payload->data, buf);
                   payload->payload = add_first(payload->payload, p);
                   payload->count += 1;
                   cur->payload = cur->payload->next;
                   free(p);
               }
           }
            fclose(file);
        }
        else
            status = EOF;
    }
    return status;
}
