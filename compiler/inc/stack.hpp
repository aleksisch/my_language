//@file
#include "stack.h"
/*!
@brief This is a data struct named stack
*/
/*!
Construct stack
\param[in] this_ pointer in struct
\param[in] this_name use define to get name of stack
\return true or false
*/
int stack_construct (stack_t* this_, const char* this_name)
{
    if (this_ == nullptr)
    {
        stack_perror(this_, NULL_STACK);
        return NULL_STACK;
    }

    this_->data          = (elem_t*) calloc(STD_LENGTH_STACK, sizeof(elem_t));
    memset(this_->data, POISON_BYTE, sizeof(elem_t)*STD_LENGTH_STACK);
    this_->name          = this_name + 1; //we use this_name+1 to delete "&"
    this_->counter       = 1;
    this_->stk_size      = STD_LENGTH_STACK;

    #ifndef NDEBUG
    this_->canary_start  = POISON_STACK;

    this_->canary_end    = POISON_STACK;

    this_->hash_array    = get_hash_array(this_);

    this_->pointer       = this_->data;

    this_->hash_struct   = get_hash_struct(this_);

    stack_ok(this_);
    #endif // NDEBUG

    return 0;
}

/*!
Destroy stack
\param[in] this_ pointer on struct
\return true or false
*/
int stack_destroy(stack_t* this_)
{
    int err = 0;
    if ( (err = stack_ok(this_)) != 0)
        return err;

    free(this_->data);
    this_->data         = nullptr;
    this_->pointer      = nullptr;

    this_->counter      = 0;
    this_->stk_size     = 0;
    this_->hash_array   = 0;
    this_->canary_end   = 0;
    this_->canary_start = 0;
    this_->hash_struct  = 0;
    return 0;

}

int stack_empty(stack_t* this_)
{
    int err = 0;
    if ( (err = stack_ok(this_)) != 0)
        return err;

    return (this_->counter <= 1) ? (true) : (false);
}

int stack_push (stack_t* this_, elem_t element)
{
    int err = 0;

    if ( (err = stack_ok(this_)) != 0)
        return err;
    if (this_->counter + 2 >= this_->stk_size)
        if (!stack_up_size(this_))
            return REALLOC_ERROR;

    this_->data [this_->counter++] = element;

    #ifndef NDEBUG
    update_hash_struct(this_);
    #endif

    return 0;
}

/*!
Get and remove last stack element
\param[in] this_ pointer in struct
\param[in] this_name use define to get name of stack
\return true or false
*/
int stack_pop (stack_t* this_, elem_t* element)
{
    int err = 0;
    if ( (err = stack_ok(this_)) != 0)
        return err;
    if (stack_empty(this_) == 1)
    {
        stack_perror(this_, UNDERFLOW_);
        return UNDERFLOW_;
    }
    if (this_->stk_size >= 3*this_->counter)
        if (err = stack_down_size(this_))
            return err;

    *element = this_->data[--this_->counter];

    memset(this_->data + this_->counter, POISON_BYTE, sizeof(elem_t));

    #ifndef NDEBUG
    update_hash_struct(this_);
    #endif // NDEBUG

    return 0;
}
/*!
Double size of stack
\param[in] this_ pointer on stack
*/
int stack_up_size(stack_t* this_)
{
    int err = 0;
    if ( (err = stack_ok(this_)) != 0)
        return err;

    if (this_->counter + 2 < this_->stk_size)
        return ERROR_IN_CHANGE_SIZE;

    this_->stk_size *= 2;

    this_->data = (elem_t*) realloc(this_->data, (this_->stk_size) * sizeof(elem_t));

    if (this_->data == nullptr)
    {
        this_->data = this_->pointer;
        stack_perror(this_, REALLOC_ERROR);
        return REALLOC_ERROR;
    }

    memset(this_->data + this_->stk_size / 2, POISON_BYTE, (this_->stk_size / 2) * sizeof(elem_t));

    #ifndef NDEBUG

    this_->pointer = this_->data;
    update_hash_struct(this_);

    #endif // NDEBUG

    return true;
}

/*!
Size of stack / 2
\param[in] this_ pointer on struct
\return true or false
*/
int stack_down_size(stack_t* this_)
{
    int err = 0;
    if ( (err = stack_ok(this_)) != 0)
        return err;

    if (this_->stk_size <= STD_LENGTH_STACK)
        return 0;

    if (this_->stk_size < this_->counter * 3)
        return ERROR_IN_CHANGE_SIZE;

    this_->stk_size /= 2;

    this_->data = (elem_t*) realloc(this_->data, (this_->stk_size) * sizeof(elem_t));

    if (this_->data == nullptr)
    {
        this_->data = this_->pointer;
        stack_perror(this_, REALLOC_ERROR);
        return REALLOC_ERROR;
    }
    #ifndef NDEBUG
    update_hash_struct(this_);
    this_->pointer = this_->data;
    #endif

    return 0;
}

/*!
Recount two hash: array hash and struct hash
\param[in] this_ pointer on struct
\return true or false
*/
int update_hash_struct(stack_t* this_)
{
    #ifndef NDEBUG
    if (this_ == nullptr)
    {
        stack_perror(this_, NULL_STACK);
        return NULL_STACK;
    }
    this_->hash_array  = get_hash_array(this_);

    this_->hash_struct = get_hash_struct(this_);

    #endif // NDEBUG
    return 0;
}

long long int get_hash_array(stack_t* this_)
{
    #ifdef NDEBUG
    return 0;
    #endif // NDEBUG
    return hash_bytes((char*) this_->data, (char*) (this_->data + this_->stk_size));
}

long long int get_hash_struct(stack_t* this_)
{
    #ifdef NDEBUG
    return 0;
    #endif // NDEBUG
    return hash_bytes((char*) this_, (char*) &(this_->hash_struct));
}

/*!
Get hash from start_pointer to end_pointer
\param[in] this_ pointer on struct
\return hash
*/
long long int hash_bytes(char* start_pointer, char* end_pointer)
{
    assert(start_pointer || end_pointer);

    if (end_pointer > start_pointer)
        assert(0|| "BAD POINTER IN HASH BYTES");

    long long int sum = 0;

    int length = (int) (end_pointer - start_pointer);
    for (int i = 0; i < length; i++)
        sum+= (start_pointer[i]+1754) * 1267 * (i + 284);

    return sum;
}

/*!
Check is stack correct
\param[in] this_ pointer on struct
\return true or false
*/
int stack_ok(stack_t* this_)
{

    int error = 0;
    bool not_null = true;

    if (this_ == nullptr || this_->data == nullptr)
    {
        error |= NULL_STACK;
        not_null = false;
    }

    if (this_->stk_size-1 <= this_->counter && not_null)
        error |= OVERFLOW_;

    if (this_->counter < 1 && not_null)
        error |= UNDERFLOW_;

    #ifdef NDEBUG

    return error;

    #else

    if (this_->data != this_->pointer && not_null)
        error |= BAD_POINTER;

    if ( !chek_stack_canary(this_)  && not_null)
        error |= CANARY_ERROR;

    if (this_->hash_struct != get_hash_struct(this_) && not_null)
        error |= HASH_STRUCT_ERROR;

    if (this_->hash_array  != get_hash_array(this_) && not_null)
        error |= HASH_ERROR;

    if (error) stack_perror (this_, error);

    return error;

    #endif  //NDEBUG
}

bool chek_stack_canary(stack_t* this_)
{
    char* elem1 = (char*)  this_->data;
    char* elem2 = (char*) (this_->data+(this_->stk_size - 1));
    int size_el = sizeof(elem_t);
    for (int i = 0; i < size_el; i++)
    {
        if (elem1[i] != POISON_BYTE ||
            elem2[i] != POISON_BYTE )
            return false;
    }
    if (this_->canary_end   != POISON_STACK ||
        this_->canary_start != POISON_STACK)
        return false;
    return true;
}

/*!
Print all information about stack and error
\param[in] this_ pointer on struct
\param[in] error enum number of array
\return true or false
*/
void stack_perror(stack_t* this_, int error)
{
    #ifdef NDEBUG

    errno |=error;

    #else

    #define GET_ERROR( err, descr )  if (error & err) printf("ERROR: " #err " (%04x|%04x): " descr "\n", error, err)


    GET_ERROR (OVERFLOW_,               "Overflow in array");
    GET_ERROR (UNDERFLOW_,              "Underflow in array");
    GET_ERROR (NULL_STACK,              "Pointer on data in stack is null");
    GET_ERROR (CANARY_ERROR,            "Bad canary, someone break memory");
    GET_ERROR (HASH_ERROR,              "Bad hash, perhaps you are under attack");
    GET_ERROR (REALLOC_ERROR,           "Problem with reallocate memory");
    GET_ERROR (BAD_POINTER,             "Pointer on data was broken");
    GET_ERROR (HASH_STRUCT_ERROR,       "Struct was broken");
    GET_ERROR (ERROR_IN_CHANGE_SIZE,    "can't change stack size");
    STACK_DUMP(this_);
    #endif // NDEBUG

    #undef GET_ERROR
}

void stack_dump (stack_t* this_)
{
    #ifndef CONST_FOR_ELEM_T
    #define CONST_FOR_ELEM_T int
    #endif // CONST_FOR_ELEM_T
    if (this_ == nullptr)
    {
        printf("DUMP FAILED. Pointer is nullptr\n");
        return;
    }
    printf("MEMORY DUMP\n{----------------------------------------------------------------------------\n");
    printf("    Stack %s [%p]\n",                          this_->name, this_);
    printf("    First address is [%p]",                    this_->data);
    printf("    Current stack counter    %d\n",            this_->counter);
    printf("    Canary in struct, start: %d, end: %d\n",   this_->canary_start, this_->canary_end);
    printf("    Stack canary should be   %d \n",           POISON_STACK);
    if (this_->stk_size)
    printf("    Canary in array, start:  " CONST_FOR_ELEM_T
           ", end:  " CONST_FOR_ELEM_T "\n",  this_->data[0], this_->data[this_->stk_size-1]);
    printf("    Array hash chould be is  %lld\n",          this_->hash_array);
    printf("    Array hash is            %lld\n",          get_hash_array(this_));
    printf("    Struct hash should be    %lld\n",          this_->hash_struct);
    printf("    Struct hash is           %lld\n",          get_hash_struct(this_));
    printf("    Stack size               %d \n",           this_->stk_size - 2);
    printf("    Data address             %p \n",           this_->data);
    printf("    Stack elements:\n");
    for (int i = 1; i < this_->stk_size - 1; i++)
        printf("        [%02d] " CONST_FOR_ELEM_T "\n", i, this_->data[i]);

    printf("}----------------------------------------------------------------------------\n\n\n\n");
}
