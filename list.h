#ifndef __LIST_H__
#define __LIST_H__

struct list{
    char *data;
    struct list *next;
};

struct list *first_list(struct list *ls);

struct list *last_list(struct list *ls);

struct list *find_list(struct list *ls, const char *value);

struct list *add_first(struct list *ls, const char *value);

struct list *add_last(struct list *ls, const char *value);

void free_list(struct list **ls);

#endif
