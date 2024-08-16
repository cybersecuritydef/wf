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
    memset(&req, '\0', sizeof(req));
    new_request(opts->method, opts->version, opts->url, NULL, &req);
    resp = requests(&req);
    free_request(&req);
    printf("conde: %ld", resp->code);
    free(resp);
}
