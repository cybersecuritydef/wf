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
    struct list *tmp_payload = NULL;
    struct list *ext = NULL;
    struct list *tmp_ext = NULL;
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
            tmp_payload = payload->payload;
            while(tmp_payload != NULL){
                tmp_ext = ext;
                while(tmp_ext != NULL){
                    asprintf(&p, "%s%s", tmp_payload->data, tmp_ext->data);
                    payload->payload = add_first(payload->payload, p);
                    payload->count += 1;
                    free(p);
                    tmp_ext = tmp_ext->next;
                }
                tmp_payload = tmp_payload->next;
            }
            free_list(&ext);
        }
        else
            status = EOF;
    }
    return status;
}
