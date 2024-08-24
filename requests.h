#ifndef __REQUESTS_H__
#define __REQUESTS_H__

#include <stdbool.h>
#include <curl/curl.h>


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
    bool follow;
    long timeout;
}request;

typedef struct{
    size_t code;
    size_t len;
    double total_time;
    char *content;
    headers *header;
}response;

int requests(const request *req, response *resp);

headers *add_headers(headers *h, char *header);

void clear_request(request *req);

void clear_response(response *resp);

#endif
