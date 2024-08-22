#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fuzzer.h"

static void print(const char *url, const filters *filter, const response *resp, const bool body){
    if((! number_filter(filter->hcode, resp->code)) && (! number_filter(filter->hsize, resp->len)) && (! string_filter(filter->hword, resp->content))){
        printf("%s [code: %ld size: %ld time: %.1f]\n", url, resp->code, resp->len, resp->total_time);
        if(body && resp->content != NULL)
            printf("%s", resp->content);
    }
}

void fuzzer(const options *opts){
    request req;
    response resp;
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


    /* running request */
    err = requests(&req, &resp);

    /* output */
    if(err == 0){
        if(opts->verbose)
            print(req.url, &opts->filter, &resp, opts->body);
    }
    free_request(&req);
    free_response(&resp);
}
