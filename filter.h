#ifndef __LFI_H__
#define __LFI_H__

#include <stdbool.h>

#include "common.h"


bool filter_code(char *match, const long code);

bool filter_size(char *match, const size_t len);

bool filter_word(char *match, const char *content);

#endif
