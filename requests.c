#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "requests.h"
#include "errors.h"


static size_t get_body(char *body, size_t size, size_t nitems, void *userdata){
    response *r = (response*)userdata;
    size_t len = 0;
    if(body != NULL){
        r->len = (size * nitems);
        if(r->content == NULL){
            if((r->content = (char*)calloc((r->len + len + 1), sizeof(char))) == NULL)
                die("[-] Error allocation memory!");
        }
        else{
            len = strlen(r->content);
            if((r->content = (char*)realloc(r->content, (r->len + len + 1) * sizeof(char))) == NULL)
                die("[-] Error allocation memory!");
        }
        memcpy(r->content + len, body, r->len);
        r->content[r->len + len] = '\0';
    }
    return (size * nitems);
}


int requests(const request *req, response *resp){
    CURL *curl = NULL;
    CURLcode err = 0;
    int status = EOF;
    struct curl_header *prev = NULL;
    struct curl_header *cur = NULL;
    char *hdr = NULL;
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

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_body);
            curl_easy_setopt(curl,  CURLOPT_WRITEDATA, resp);

            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, req->verify);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, req->verify);

            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, req->follow);

            if((err = curl_easy_perform(curl)) == CURLE_OK){
                while((cur = curl_easy_nextheader(curl, CURLH_HEADER | CURLH_1XX | CURLH_TRAILER, 0, prev)) != NULL) {
                    asprintf(&hdr, "%s: %s", cur->name, cur->value);
                    resp->header = curl_slist_append(resp->header, hdr);
                    prev = cur;
                    free(hdr);
                }
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp->code);
                curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &resp->total_time);
                curl_easy_cleanup(curl);
                status = err;
            }
            else{
                curl_easy_cleanup(curl);
                status = err;
            }
        }
    }
    return status;
}

headers *add_headers(headers *h, char *header){
    char *delim = NULL;
    char *value = NULL;

    /* default headers */
    h = curl_slist_append(h, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:129.0) Gecko/20100101 Firefox/129.0");
    h = curl_slist_append(h, "Accept-Language: *");
    h = curl_slist_append(h, "Accept-Encoding: *");

    if(header != NULL){
        value = strtok_r(header, ",", &delim);
        while(value != NULL){
            h = curl_slist_append(h, value);
            value = strtok_r(NULL, ",", &delim);
        }
    }

    return h;
}

void clear_request(request *req){
    if(req != NULL){
        if(req->method != NULL){
            free(req->method);
            req->method = NULL;
        }


        if(req->url != NULL){
            free(req->url);
            req->url = NULL;
        }


        if(req->http_ver != NULL){
            free(req->http_ver);
            req->http_ver = NULL;
        }


        if(req->cookie != NULL){
            free(req->cookie);
            req->cookie = NULL;
        }


        if(req->postdata != NULL){
            free(req->postdata);
            req->postdata = NULL;
        }


        if(req->proxy != NULL){
            free(req->proxy);
            req->proxy = NULL;
        }


        if(req->header != NULL){
            curl_slist_free_all(req->header);
            req->header = NULL;
        }
    }
}


void clear_response(response *resp){
    if(resp != NULL){
        if(resp->content != NULL){
            free(resp->content);
            resp->content = NULL;
        }

        if(resp->header != NULL){
            curl_slist_free_all(resp->header);
            resp->header = NULL;
        }
    }
}
