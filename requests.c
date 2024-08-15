#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "requests.h"


response *requests(const request *req){
    CURL *curl = NULL;
    response *resp = NULL;
    if(req){
        if((curl = curl_easy_init())){
            curl_easy_setopt(curl, CURLOPT_URL, req->url);
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, req->timeout);

            if(req->method)
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, req->method);

            if(req->http_ver){
                if(strcmp(req->http_ver, "HTTP/1.0") == 0)
                    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
                else if(strcmp(req->http_ver, "HTTP/1.1") == 0)
                    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
                else if(strcmp(req->http_ver, "HTTP/2.0") == 0 || strcmp(req->http_ver, "HTTP/2") == 0)
                    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
            }

            if(req->header)
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER , req->header);

            if(req->cookie)
                curl_easy_setopt(curl, CURLOPT_COOKIE, req->cookie);

            if(req->proxy)
                curl_easy_setopt(curl, CURLOPT_PROXY, req->proxy);

            if(req->postdata)
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req->postdata);

            /*curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, get_header);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_body);*/

            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, req->verify);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, req->verify);

            if(curl_easy_perform(curl)){
                if((resp = (response*)malloc(sizeof(response)))){
                    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp->code);
                    curl_easy_cleanup(curl);
                    return resp;
                }
                else{
                    die("[-] Error allocation memory!");
                    curl_easy_cleanup(curl);
                }
            }
        }
        else
            die("[-] Curl d'not init!");
    }
    return NULL;
}

void free_request(request *req){
    if(req->method)
        free(req->method);

    if(req->url)
        free(req->url);

    if(req->http_ver)
        free(req->http_ver);

    if(req->cookie)
        free(req->cookie);

    if(req->postdata)
        free(req->postdata);

    if(req->proxy)
        free(req->proxy);
    memset(&req, '\0', sizeof(req));
}
