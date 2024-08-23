#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fuzzer.h"
#include "print.h"

void fuzzer(const options *opts){
    request req;
    response resp;
    wordlists *words = NULL;
    extlists *exts = NULL;
    int err = 0;
    memset(&req, '\0', sizeof(req));
    memset(&resp, '\0', sizeof(resp));

    /* preparing a request */
    if(opts->url != NULL)
        req.url = strdup(opts->url);

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

    req.header = curl_slist_append(req.header, "User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:8.0) Gecko/20100101 Firefox/8.0");
    req.header = curl_slist_append(req.header, "Accept-Language: *");
    req.header = curl_slist_append(req.header, "Accept-Encoding: *");

   /* make payloads */
    if((words = read_wordlists(opts->wordlist)) == NULL){
        clear_request(&req);
        die("[-] File not found!");   
    }            

    if(opts->extlist != NULL){
        if((exts = read_wordlists(opts->extlist)) == NULL){
            clear_request(&req);
            clear_wordlists(&words);
            die("[-] File not found!");  
        }
    }    
    if((payloads = make_payloads(url, words, exts)) == NULL){
        clear_request(&req);
        clear_wordlists(&words);
        clear_wordlists(&exts);
        die("[-] File not found!");
    }

    
    /* running request */
    err = requests(&req, &resp);
    
    /* output */
    if(err == 0){
        if(opts->verbose)
            print(req.url, &opts->filter, &resp, opts->body);
    }
    else
        printf("%s\n", curl_easy_strerror(err));
    clear_request(&req);
    clear_response(&resp);
}
