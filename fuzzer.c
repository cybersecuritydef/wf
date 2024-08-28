#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>


#include "fuzzer.h"
#include "print.h"

struct pool{
    pthread_t th;
    filters filter;
    bool verbose;
    request req;
};


static void current_time(const char *msg){
    struct tm *tm_cur = NULL;
    time_t cur = 0;
    cur = time(NULL);
    tm_cur = localtime(&cur);
    printf("%s%02d:%02d:%02d\n", msg, tm_cur->tm_hour, tm_cur->tm_min, tm_cur->tm_sec);
}


static void *working(void *arg){
    struct pool *p = (struct pool*)arg;
    response resp;
    int err = 0;
    memset(&resp, '\0', sizeof(resp));
    if((err = requests(&p->req, &resp)) == 0){
        if(p->verbose)
            print(p->req.url, &p->filter, &resp);
    }
    else
        errors(err);
    clear_response(&resp);
    return NULL;
}

void fuzzer(options *opts){

    payloads payload;
    struct pool *p = NULL;
    int num = 0;

    memset(&payload, '\0', sizeof(payload));

    if((p = (struct pool*)calloc(opts->threads, sizeof(struct pool))) == NULL)
        die("[-] Error allocation memory!");

    for(num = 0; num < opts->threads; num++){
        /* preparing a request */
        if(opts->method != NULL)
            p[num].req.method = strdup(opts->method);

        if(opts->version != NULL)
            p[num].req.http_ver = strdup(opts->version);

        if(opts->postdata != NULL)
            p[num].req.postdata = strdup(opts->postdata);

        if(opts->cookies != NULL)
            p[num].req.cookie = strdup(opts->cookies);

        p[num].req.follow = opts->follow;
        p[num].req.verify = opts->verify;
        p[num].verbose = opts->verbose;

        p[num].req.header = add_headers(p[num].req.header, opts->headers);
    }


    current_time("[!] Start time: ");

    printf("[!] URL: %s\n", opts->url);
    printf("[!] Wordlist: %s\n", opts->wordlist);
    if(opts->extlist != NULL)
        printf("[!] Extensions: %s\n", opts->extlist);
    printf("\n");

    /* make payloads */
    printf("[!] Generating wordlists...\n");
    if(make_payloads(opts->url, opts->wordlist, opts->extlist, &payload) == EOF){
        for(num = 0; num < opts->threads; num++)
            clear_request(&p[num].req);
        free(p);
        die("[-] Error make payloads!");
    }
    printf("[!] Payloads count: %ld\n\n", payload.count);

    while(!isempty(payload.payload)){
        for(num = 0; num < opts->threads; ++num){
            p[num].req.url = pop(&payload.payload);
            pthread_create(&p[num].th, NULL, working, &p[num]);
            payload.count--;
        }

        for(num = 0; num < opts->threads; ++num){
            pthread_join(p[num].th, NULL);
            free(p[num].req.url);
        }
        if(opts->threads >= payload.count)
            opts->threads = payload.count;
    }

    memset(&payload, '\0', sizeof(payloads));
    free(p);

    current_time("\n[!] Finish time: ");
}
