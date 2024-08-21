#ifndef __LFI_H__
#define __LFI_H__

#include <stdbool.h>

#include "common.h"

bool number_filter(char *match, const size_t num);

bool string_filter(char *match, const char *content);

#endif
