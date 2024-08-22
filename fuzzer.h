#ifndef __FUZZER_H__
#define __FUZZER_H__

#include "common.h"
#include "wordlists.h"
#include "headers.h"
#include "requests.h"
#include "encode.h"
#include "filter.h"
#include "print.h"


typedef struct{
    char *hcode;
    char *hsize;
    char *hword;
}filters;


typedef struct{
    int threads;
    char *wordlist;
    char *extlist;
    char *ext;
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

void fuzzer(const options *opts);

#endif
