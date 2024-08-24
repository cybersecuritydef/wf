#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "payloads.h"
#include "wordlists.h"

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

int make_payloads(const char *url, const char *wordlist, const char *extlist, wordlists *payloads){
    wordlists *wcur = NULL;
    wordlists *ecur = NULL;
    wordlists *words = NULL;
    wordlists *exts = NULL;
    char *tmp = NULL;

    if(url == NULL)
        return EOF;

    if((words = read_wordlists(wordlist)) != NULL){
        wcur = words;
        while(wcur->words != NULL){
            tmp = join_payloads(url, wcur->words->data);
            payloads->words = add_first(payloads->words, tmp);
            wcur->words = wcur->words->next;
            free(tmp);
        }
        clear_wordlists(words);
        free(words);
    }
    else
        return EOF;

    if(extlist != NULL){
        if((exts = read_wordlists(extlist)) != NULL){
            ecur = exts;
            while(ecur->words != NULL){
                wcur = payloads;
                while(wcur->words != NULL){
                    tmp = join_payloads(wcur->words->data, ecur->words->data);
                    printf("%s\n", ecur->words->data);
                    wcur->words = wcur->words->next;
                    free(tmp);
                }
                ecur->words = ecur->words->next;
            }
            clear_wordlists(exts);
            free(exts);
        }
    }
    return 0;
}
