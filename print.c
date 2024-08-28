#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "print.h"
#include "filter.h"

void print(const char *url, const filters *filter, const response *resp){
    if((! number_filter(filter->hcode, resp->code)) && (! number_filter(filter->hsize, resp->len)) && (! string_filter(filter->hword, resp->content))){
        if(resp->code >= 400 && resp->code <= 526)
            printf("[-] %-55s [code: %ld \tsize: %ld \ttime: %.1f s]\n", url, resp->code, resp->len, resp->total_time);
        else
            printf("[+] %-55s [code: %ld \tsize: %ld \ttime: %.1f s]\n", url, resp->code, resp->len, resp->total_time);
    }
}
