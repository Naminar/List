
#ifndef LIST_

#define LIST_

#define DBG

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int type;

typedef struct List{

    type data ;

    List* next;

    List* prev;

} List;

typedef struct Tree{

    const char
        *const password ;

    List* lst           ;

    size_t capacity     ;

    size_t size         ;

} Tree;

//===============================================

void            list_init               (Tree*, size_t)             ;
bool            list_insert             (Tree*, size_t, type)       ;
bool            list_delete_after       (Tree*, size_t)             ;
List*           search_element          (Tree*, size_t)             ;
void            do_list_linearization   (Tree*, const char *const)  ;
void            list_destructor         (Tree*)                     ;
void            list_dump               (Tree*)                     ;

#endif
