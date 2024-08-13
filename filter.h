#ifndef __LFI_H__
#define __LFI_H__

#include <stdbool.h>

#include "common.h"


bool filter_code(char *codes, const long code);

bool filter_size(char *sizes, const size_t len);

bool filter_word(char *words, const char *content);

#endif
