#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "requests.h"


static size_t get_body(char *body, size_t size, size_t nitems, void *userdata){
    response *r = (response*)userdata;
    if(body != NULL){
        r->len += (size * nitems);
        if(r->content == NULL){
            printf("%ld\n", r->len);
            /*if((r->content = (char*)calloc((r->len + 1), sizeof(char))) == NULL)
                die("[-] Error allocation memory!");
            strcat(r->content, body);
            r->content[r->len] = '\0';*/
        }
        /*else
            r->content = (char*)realloc(r->content, (r->len + 1) * sizeof(char));
        strcat(r->content, body);
        r->content[r->len] = '\0';*/
    }
    return size * nitems;
}


static size_t get_headers(char *header, size_t size, size_t nitems, void *userdata){
    response *r = (response*)userdata;
    if(header != NULL){
        header[strlen(header) - 2] = '\0';
        r->header = curl_slist_append(r->header, header);
    }
    return size * nitems;
}


int requests(const request *req, response *resp){
    CURL *curl = NULL;
    CURLcode err = 0;
    if(req != NULL && resp != NULL){
        if((curl = curl_easy_init()) != NULL){            
            curl_easy_setopt(curl, CURLOPT_URL, req->url);
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, req->timeout);

            if(req->method != NULL){
                if(strcmp(req->method, "HEAD") == 0)
                    curl_easy_setopt(curl, CURLOPT_NOBODY, true);
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, req->method);
            }

            if(req->http_ver != NULL){
                if(strcmp(req->http_ver, "HTTP/1.0") == 0)
                    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
                else if(strcmp(req->http_ver, "HTTP/1.1") == 0)
                    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
                else if(strcmp(req->http_ver, "HTTP/2.0") == 0 || strcmp(req->http_ver, "HTTP/2") == 0)
                     curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
            }

            if(req->header != NULL)
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER , req->header);

            if(req->cookie != NULL)
                curl_easy_setopt(curl, CURLOPT_COOKIE, req->cookie);

            if(req->proxy != NULL)
                curl_easy_setopt(curl, CURLOPT_PROXY, req->proxy);

            if(req->postdata != NULL)
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req->postdata);

            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, get_headers);
            curl_easy_setopt(curl,  CURLOPT_HEADERDATA, resp);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_body);
            curl_easy_setopt(curl,  CURLOPT_WRITEDATA, resp);

            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, req->verify);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, req->verify);

            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, req->follow);

            if((err = curl_easy_perform(curl)) == CURLE_OK){
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp->code);
                curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &resp->total_time);
                curl_easy_cleanup(curl);
                return err;
            }
            else{
                curl_easy_cleanup(curl);                    
                return err;
            }
        }
    }
    return EOF;
}


void clear_request(request *req){
    if(req != NULL){
        if(req->method != NULL)
            free(req->method);

        if(req->url != NULL)
            free(req->url);

        if(req->http_ver != NULL)
            free(req->http_ver);

        if(req->cookie != NULL)
            free(req->cookie);

        if(req->postdata != NULL)
            free(req->postdata);

        if(req->proxy != NULL)
            free(req->proxy);
        if(req->header != NULL)
            curl_slist_free_all(req->header);
        memset(&req, '\0', sizeof(req));
    }
}


void clear_response(response *resp){
    if(resp != NULL){
        if(resp->content != NULL)
            free(resp->content);
        if(resp->header != NULL)
            curl_slist_free_all(resp->header);
        memset(&resp, '\0', sizeof(resp));
    }
}
