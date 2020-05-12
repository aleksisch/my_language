#ifndef DECLARE_H
#define DECLARE_H


#define STACK_CONSTRUCT(name) stack_construct(name, #name)

#define NDEBUG

#ifdef NDEBUG
#define STACK_DUMP(this)

#else
#define STACK_DUMP(this_) stack_dump(this_)
#endif


#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "constants.h"

struct stack_t
{
    int           canary_start;
    elem_t*       data;                  //pointer on stack data
    const char*   name;                  //struct name
    int           counter;               //pointer on last element
    elem_t*       pointer;               //reserve pointer on data
    int           stk_size;              //max current stack size
    long long int hash_array;            //hash of data
    int           canary_end;
    long long int hash_struct;           //hash of all element in struct
};

enum err_list
{
    UNDERFLOW_           = 1 << 0,
    STACK_OK             = 1 << 1,
    OVERFLOW_            = 1 << 2,
    NULL_STACK           = 1 << 3,
    CANARY_ERROR         = 1 << 4,
    HASH_ERROR           = 1 << 5,
    REALLOC_ERROR        = 1 << 6,
    BAD_POINTER          = 1 << 7,
    HASH_STRUCT_ERROR    = 1 << 8,
    ERROR_IN_CHANGE_SIZE = 1 << 9
};

int   stack_empty        (stack_t* this_);
void  stack_dump         (stack_t* this_);
int   stack_destroy      (stack_t* this_);
int   stack_up_size      (stack_t* this_);
int   stack_down_size    (stack_t* this_);
int   stack_construct    (stack_t* this_, const char* this_name = "Unknown");
int   stack_push         (stack_t* this_, elem_t element);
int   stack_pop          (stack_t* this_, elem_t* element);


void   error                  (stack_t* this_, char* er);
void   stack_perror           (stack_t* this_, int error);
bool   chek_stack_canary      (stack_t* this_);
int    stack_ok                (stack_t* this_);
long long int get_hash_array  (stack_t* this_);
long long int get_hash_struct (stack_t* this_);

int    update_hash_struct (stack_t* this_);
long long int hash_bytes (char* pointer_start, char* pointer_end);
int    test();
#endif // DECLARE_H
