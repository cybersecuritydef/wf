#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "print.h"
#include "filter.h"

void print(const char *url, const filters *filter, const response *resp, const bool body){
    if((! number_filter(filter->hcode, resp->code)) && (! number_filter(filter->hsize, resp->len)) && (! string_filter(filter->hword, resp->content))){
        printf("%s [code: %ld size: %ld time: %.1f]\n", url, resp->code, resp->len, resp->total_time);
        if(body && resp->content != NULL)
            printf("%s", resp->content);
    }
}
