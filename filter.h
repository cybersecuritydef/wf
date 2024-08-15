#ifndef __LFI_H__
#define __LFI_H__

#include <stdbool.h>

#include "common.h"


bool filter(char *match, const size_t v);

bool filter_word(char *match, const char *content);

#endif
