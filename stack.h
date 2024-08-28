#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>


typedef struct stack{
    char *data;
    struct stack *next;
};

void push(struct stack **s, const char *value);

char *pop(struct stack **s);

bool isempty(struct stack *s);


#endif
