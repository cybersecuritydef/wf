#ifndef __PAYLOADS_H__
#define __PAYLOADS_H__

typedef struct{
    struct list *payload;
    size_t count;
}payloads;

payloads *make_payloads(const char *url, const char *wordlist, const char *extlist);

#endif
