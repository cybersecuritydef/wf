#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "list.h"
#include "errors.h"


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
        if((newls = (struct list*)calloc(1, sizeof(struct list))) != NULL){
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
    if(ls != NULL && (*ls) != NULL){
        while((*ls)->next != NULL){
            tmp = (*ls);
            (*ls) = (*ls)->next;

            free(tmp->data);
            tmp->data = NULL;

            free(tmp);
            tmp = NULL;
        }

        free((*ls)->data);
        (*ls)->data = NULL;

        free((*ls));
        (*ls) = NULL;
    }
}
