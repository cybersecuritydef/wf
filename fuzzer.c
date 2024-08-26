#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fuzzer.h"
#include "print.h"


void fuzzer(const options *opts){
    request req;
    response resp;
    payloads payload;
    struct list *cur = NULL;
    struct tm *tm_start = NULL;
    struct tm *tm_finish = NULL;
    time_t start = 0;
    time_t finish = 0;
    int err = 0;

    memset(&req, '\0', sizeof(req));
    memset(&resp, '\0', sizeof(resp));
    memset(&payload, '\0', sizeof(payload));

    /* preparing a request */
    if(opts->method != NULL)
        req.method = strdup(opts->method);

    if(opts->version != NULL)
        req.http_ver = strdup(opts->version);

    if(opts->postdata != NULL)
        req.postdata = strdup(opts->postdata);

    if(opts->cookies != NULL)
        req.cookie = strdup(opts->cookies);

    req.follow = opts->follow;
    req.verify = opts->verify;

    req.header = add_headers(req.header, opts->headers);

    start = time(NULL);
    tm_start = localtime(&start);
    printf("[!] Start time: %d:%d:%d\n", tm_start->tm_hour, tm_start->tm_min, tm_start->tm_sec);

    printf("[!] URL: %s\n", opts->url);
    printf("[!] Wordlist: %s\n", opts->wordlist);

    if(opts->extlist != NULL)
        printf("[!] Extensions: %s\n", opts->extlist);
    printf("\n");

    /* make payloads */
    printf("[!] Generating wordlists...\n");
    if(make_payloads(opts->url, opts->wordlist, opts->extlist, &payload) == EOF){
        clear_request(&req);
        die("[-] Error make payloads!");
    }

    printf("[!] Wordlist count: %ld\n\n", payload.count);

    cur = payload->payload;
    while(cur != NULL){
        req.url = strdup(cur->data);
        if((err = requests(&req, &resp)) == 0){
            if(opts->verbose)
                print(req.url, &opts->filter, &resp, opts->body);            
        }
        else
            fprintf(stderr, "%s\n", curl_easy_strerror(err));
        clear_response(&resp);
        free(req.url);
        cur = cur->next;
    }
    clear_request(&req);
    
    finish = time(NULL);
    tm_finish = localtime(&finish);
    printf("\n[!] Finish time: %02d:%02d:%02d\n", tm_finish->tm_hour, tm_finish->tm_min, tm_finish->tm_sec);
}
