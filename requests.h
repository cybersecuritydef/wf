#ifndef __REQUESTS_H__
#define __REQUESTS_H__

#include <stdbool.h>
#include <curl/curl.h>

#include "common.h"

typedef struct curl_slist headers;

typedef struct{
    char *method;
    char *http_ver;
    char *url;
    char *proxy;
    char *cookie;
    char *postdata;
    headers *header;
    bool verify;
    long timeout;
}request;

typedef struct{
    size_t code;
    size_t len;
    double resp_time;
    char *content;
    char *headers;
}response;

response *requests(const request *req);

void free_request(request *req);

#endif
