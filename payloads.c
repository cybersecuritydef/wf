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
    struct list *ext = NULL;
    struct list *ext_cur = NULL;
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
            while(fgets(buf, sizeof(buf), file) != NULL){
                buf[strlen(buf) - 1] = '\0';
                ext = add_first(ext, buf);                
            }
            fclose(file);
            cur = payload;
            while(cur != NULL){
                ext_cur = ext;
                while(ext_cur != NULL){
                    asprintf(&p, "%s%s", cur->payload->data, ext_cur->data);
                    payload->payload = add_first(payload->payload, p);
                    payload->count += 1;
                    free(p);
                    ext_cur = ext_cur->next;
                }
                cur->payload = cur->payload->next;
            }
        }
        else
            status = EOF;
    }
    return status;
}
