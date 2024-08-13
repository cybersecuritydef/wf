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
    int threads;
    char *headers;
    char *version;
    char *method;
    char *cookies;
    char *url;
    char *proxy;
    char *encode;
    char *postdata;
    char *hcode;
    char *hsize;
    char *hword;
    char *scode;
    char *ssize;
    char *sword;
    bool follow;
    bool recursion;
    bool verbose;
    bool body;
    struct dictlists dict;
}options;

void fuzzer(options *opts);

#endif
