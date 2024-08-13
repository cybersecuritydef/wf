#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fuzzer.h"



void fuzzer(options *opts){
    if(opts->method)
        printf("Method: %s\n", opts->method);
    if(opts->headers)
        printf("Headers: %s\n", opts->headers);
    if(opts->cookies)
        printf("Cookies: %s\n", opts->cookies);
    if(opts->url)
        printf("Url: %s\n", opts->url);
    if(opts->proxy)
        printf("Proxy: %s\n", opts->proxy);
    if(opts->encode)
        printf("Encode: %s\n", opts->encode);
    if(opts->postdata)
        printf("Post data: %s\n", opts->postdata);
    if(opts->hcode)
        printf("Hcode: %s\n", opts->hcode);
    if(opts->hsize)
        printf("Hsize: %s\n", opts->hsize);
    if(opts->hword)
        printf("Hword: %s\n", opts->hword);
    if(opts->scode)
        printf("Scode: %s\n", opts->scode);
    if(opts->ssize)
        printf("Ssize: %s\n", opts->ssize);
    if(opts->sword)
        printf("Sword: %s\n", opts->sword);
    if(opts->version)
        printf("Version HTTP: %s\n", opts->version);
    printf("Verbose: %d\n", opts->verbose);
    printf("Follow: %d\n", opts->follow);
    printf("Recursion: %d\n", opts->recursion);
    printf("Show body: %d\n", opts->body);
    printf("Threads: %d\n", opts->threads);
}
