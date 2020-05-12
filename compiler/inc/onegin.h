#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

struct pointer_on_line
{
    char* start;
    char* end;
};
static const int MAX_SIZE = 256;

void work_file(int *size, struct pointer_on_line** lineptr, char** text,
               const char* input, int* countline);

char *readFile (const char* str, int *size, const char* chmod = "r");

int get_line (char* text, int size);

void get_ptr (char* text, struct pointer_on_line* lineptr, int size);

#endif // FUNC_H_INCLUDED
