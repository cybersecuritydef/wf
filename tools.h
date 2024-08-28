#ifndef __TOOLS_H__
#define __TOOLS_H__


#define ARRAY_SIZE(x) ((sizeof(x)) / (sizeof(*x)))


char *strrep(const char *str, const char *oldstr, const char *newstr);

char *strrepeat(const char *str, const size_t depth);

char *strupper(const char *str);

char *strlower(const char *str);

char *strchrupper(const char *str, const int index);

char *strchrlower(const char *str, const int index);

char *strrdup(char *s, const char *str);

#endif
