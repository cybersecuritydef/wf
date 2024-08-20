#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fuzzer.h"


static void new_request(const char *method, const char *http_ver, const char *url, headers *h, request *req){
    if(method != NULL)
        req->method = strdup(method);

    if(http_ver != NULL)
        req->http_ver = strdup(http_ver);
    else
        req->http_ver = strdup("HTTP/1.1");

    req->url = strdup(url);
}

void fuzzer(options *opts){
    request req;
    response *resp = NULL;
    int err = 0;
    memset(&req, '\0', sizeof(req));
    req.follow = opts->follow;
    new_request(opts->method, opts->version, opts->url, NULL, &req);
    resp = requests(&req);
    if(resp != NULL){
        printf("code: %ld\nTTL:%.1f\n[Body: %s]\nLength: %ld\n\n", resp->code, resp->total_time, resp->content, resp->len);
        while(resp->header != NULL){
            printf("%s\n", resp->header->data);
            resp->header = resp->header->next;
        }
        free_request(&req);
        free_response(resp);
    }
    else
        fprintf(stderr, "%s\n", curl_easy_strerror(err));
    //free(resp);
}
