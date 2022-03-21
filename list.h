
#ifndef LIST_

#define LIST_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define POSITIVE_FREE       0 - tree->free
#define DOUBLE_NEXT         tree->lst[tree->lst[num].next].next
#define NEXT_OF_NEXT_CELL   tree->lst[next_cell].next

typedef int type;

typedef struct List{

    type data         ;

    long long int next;

    long long int prev;

} List;

typedef struct Tree{

    const char
        *const password ;

    List* lst           ;

    size_t capacity     ;

    size_t size         ;

    long long int free  ;

    bool sort_flag      ;

} Tree;

//===============================================

const List marker_list = {.data = -8, .next = -8, .prev = -8};

//===============================================

void            list_init               (Tree*, size_t)             ;
size_t          list_insert             (Tree*, long long int, type);
size_t          list_delete_after       (Tree*, long long int)      ;
long long int   search_element          (Tree*, long long int)      ;
void            do_list_linearization   (Tree*, const char *const)  ;
void            list_destructor         (Tree*)                     ;
void            list_dump               (Tree*)                     ;

#endif
