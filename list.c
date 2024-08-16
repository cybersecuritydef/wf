#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "list.h"
#include "common.h"


struct list *find_list(struct list *ls, const char *value){
    struct list *cur = ls;
    if((cur && value) != NULL){
        while(cur != NULL && strcmp(cur->data, value) != 0)
            cur = cur->next;
        return cur;
    }
    return NULL;
}


struct list *first_list(struct list *ls){
    struct list *first = NULL;
    if(ls != NULL){
        first = ls;
        return first;
    }
    return NULL;
}

struct list *last_list(struct list *ls){
    struct list *last = NULL;
    if(ls != NULL){
        last = ls;
        while(last->next != NULL){
            last = last->next;
        }
        return last;
    }
    return NULL;
}

struct list *add_first(struct list *ls, const char *value){
    struct list *newls = NULL;
    if(value != NULL){
        if((newls = (struct list*)malloc(sizeof(struct list))) != NULL){
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
    if(ls != NULL){
        if((newls = (struct list*)malloc(sizeof(struct list))) != NULL){
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
    if((ls && (*ls)) != NULL){
        while((*ls)->next != NULL){
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
