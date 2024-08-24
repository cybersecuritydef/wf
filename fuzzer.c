#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fuzzer.h"
#include "print.h"


void fuzzer(const options *opts){
    request req;
    response resp;
    wordlists payloads;
    struct list *cur = NULL;
    int err = 0;
    memset(&req, '\0', sizeof(req));
    memset(&resp, '\0', sizeof(resp));
    memset(&payloads, '\0', sizeof(payloads));

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
    clear_request(&req);
    payloads.words = add_first(payloads.words, "TEST");
    payloads.words = add_first(payloads.words, "FUZZ");
    payloads.words = add_first(payloads.words, "TWWWW");
    payloads.words = add_first(payloads.words, "DASD");
    payloads.words = add_first(payloads.words, "ads456");
    clear_wordlists(&payloads);
   /* make payloads */
    /*if(make_payloads(opts->url, opts->wordlist, opts->extlist, &payloads) == EOF){
        clear_request(&req);
        die("[-] Error make payloads!");
    }
    cur = payloads.words;
    while(cur != NULL){
        req.url = strdup(cur->data);
        err = requests(&req, &resp);
        if(err == 0){
            if(opts->verbose)
                print(req.url, &opts->filter, &resp, opts->body);
        }
        else
            printf("%s %s\n", curl_easy_strerror(err), req.url);
        clear_response(&resp);
        free(req.url);
        req.url = NULL;

        cur = cur->next;
    }
    free_list(&payloads.words);

    req.url = strdup(opts->url);
    err = requests(&req, &resp);
        if(err == 0){
            if(opts->verbose)
                print(req.url, &opts->filter, &resp, opts->body);
        }
        else
            printf("%s %s\n", curl_easy_strerror(err), req.url);
    clear_response(&resp);
    clear_request(&req);*/

}
