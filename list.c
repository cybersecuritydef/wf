#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "list.h"
#include "common.h"


struct list *find_list(struct list *ls, const char *value){
    struct list *cur = ls;
    if(cur && value){
        while(cur && strcmp(cur->data, value))
            cur = cur->next;
        return cur;
    }
    return NULL;
}


struct list *first_list(struct list *ls){
    struct list *first = NULL;
    if(ls){
        first = ls;
        return first;
    }
    return NULL;
}

struct list *last_list(struct list *ls){
    struct list *last = NULL;
    if(ls){
        last = ls;
        while(last->next){
            last = last->next;
        }
        return last;
    }
    return NULL;
}

struct list *add_first(struct list *ls, const char *value){
    struct list *newls = NULL;
    if(value){
        if((newls = (struct list*)malloc(sizeof(struct list)))){
            newls->data = strdup(value);
            newls->next = ls;
            ls = newls;
            return ls;
        }
        else
            die("[-] Error allocation memory!");
    }
    return NULL;
}

struct list *add_last(struct list *ls, const char *value){
    struct list *newls = NULL;
    struct list *last = NULL;
    if(ls){
        if((newls = (struct list*)malloc(sizeof(struct list)))){
            newls->data = strdup(value);
            newls->next = NULL;
            last = last_list(ls);
            last->next = newls;
        }
        else
            die("[-] Error allocation memory!");
    }
    else
        ls = add_first(ls, value);
    return ls;
}

void free_list(struct list **ls){
    struct list *tmp = NULL;
    if(ls && (*ls)){
        while((*ls)->next){
            tmp = (*ls);
            (*ls) = (*ls)->next;
            free(tmp->data);
            free(tmp);
            tmp = NULL;
        }
        free((*ls)->data);
        free((*ls));
        (*ls) = NULL;
    }
}
