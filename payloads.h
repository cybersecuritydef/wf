#ifndef __PAYLOADS_H__
#define __PAYLOADS_H__

#include "list.h"

#define LEN_BUF 512

typedef struct{
    struct list *payload;
    size_t count;
}payloads;

int make_payloads(const char *url, const char *wordlist, const char *extlist, payloads *payload);

#endif
