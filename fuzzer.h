#ifndef __FUZZER_H__
#define __FUZZER_H__

#include "requests.h"
#include "encode.h"
#include "filter.h"
#include "payloads.h"
#include "errors.h"
#include "tools.h"



typedef struct{
    char *hcode;
    char *hsize;
    char *hword;
}filters;


typedef struct{
    int threads;
    char *wordlist;
    char *extlist;
    char *headers;
    char *version;
    char *method;
    char *cookies;
    char *url;
    char *proxy;
    char *encode;
    char *postdata;
    bool follow;
    bool recursion;
    bool verbose;
    bool verify;
    bool body;
    filters filter;
}options;

void fuzzer(options *opts);

#endif
