#ifndef __COMMON_H__
#define __COMMON_H__

#include "list.h"

#define ARRAY_SIZE(x) ((sizeof(x)) / (sizeof(*x)))

#define LEN_BUF 512

void die(const char *msg);

char *strrep(const char *str, const char *oldstr, const char *newstr);

char *strrepeat(const char *str, const size_t depth);

char *strupper(const char *str);

char *strlower(const char *str);

char *strchrupper(const char *str, const int index);

char *strchrlower(const char *str, const int index);

#endif
